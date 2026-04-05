#include "cbase.h"
#include "overrideui_rootpanel.h"
#include "ioverrideinterface.h"

#include "vgui/ILocalize.h"
#include "vgui/IPanel.h"
#include "vgui/ISurface.h"
#include "vgui/ISystem.h"
#include "vgui/IVGui.h"
#include "ienginevgui.h"
#include <engine/IEngineSound.h>
#include "filesystem.h"

using namespace vgui;

// See interface.h/.cpp for specifics:  basically this ensures that we actually Sys_UnloadModule the dll and that we don't call Sys_LoadModule 
//  over and over again.
static CDllDemandLoader g_GameUIDLL( "GameUI" );

OverrideUI_RootPanel *guiroot = NULL;

MenuPanel::MenuPanel(Panel* parent, const char* name, bool allowJavaScript, bool bPopupWindow)
	: HTML(parent, name, allowJavaScript, bPopupWindow)
{
}

MenuPanel::~MenuPanel()
{
}

bool MenuPanel::OnStartRequest(const char* url, const char* target, const char* pchPostData, bool bIsRedirect)
{
	if (FStrEq(url, "game://serverbrowser"))
	{
		engine->ClientCmd("openserverbrowser");
		return false; 
	}
	return BaseClass::OnStartRequest(url, target, pchPostData, bIsRedirect);
}

void OverrideGameUI()
{
	if( !OverrideUI->GetPanel() )
	{
		OverrideUI->Create(NULL);
	}
	if( guiroot->GetGameUI() )
	{
		guiroot->GetGameUI()->SetMainMenuOverride( guiroot->GetVPanel() );
		return;
	}
}

OverrideUI_RootPanel::OverrideUI_RootPanel(VPANEL parent) : Panel( NULL, "OverrideUIRootPanel" )
{
	SetParent(parent);
	guiroot = this;

	m_bCopyFrameBuffer = false;
	gameui = NULL;

	LoadGameUI();

	m_ExitingFrameCount = 0;

	m_pHTMLMenu = new vgui::HTML(this, "HTMLPanel", true);
	m_pHTMLMenu->SetSize(ScreenWidth(), ScreenHeight());
	m_pHTMLMenu->SetPos(0, 0);
}

IGameUI *OverrideUI_RootPanel::GetGameUI()
{
	if( !gameui )
	{
		if ( !LoadGameUI() )
			return NULL;
	}

	return gameui;
}

bool OverrideUI_RootPanel::LoadGameUI()
{
	if( !gameui )
	{
		CreateInterfaceFn gameUIFactory = g_GameUIDLL.GetFactory();
		if ( gameUIFactory )
		{
			gameui = (IGameUI *) gameUIFactory(GAMEUI_INTERFACE_VERSION, NULL);
			if( !gameui )
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

OverrideUI_RootPanel::~OverrideUI_RootPanel()
{
	gameui = NULL;
	g_GameUIDLL.Unload();
}

void OverrideUI_RootPanel::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);

	// Resize the panel to the screen size
	// Otherwise, it'll just be in a little corner
	int wide, tall;
	vgui::surface()->GetScreenSize(wide, tall);
	SetSize(wide,tall);

	const char* gameDir = engine->GetGameDirectory();
	char filePath[256];
	// Windows can handle raw paths, while Linux (and other POSIX platforms) only handle file:// paths.
#if defined(_WIN32)
	sprintf(filePath, "%s/resource/menu.html", gameDir); // You can replace menu.html with whatever you want to name your HTML file
#else
	sprintf(filePath, "file://%s/resource/menu.html", gameDir); // You can replace menu.html with whatever you want to name your HTML file
#endif

	m_pHTMLMenu->SetSize(wide, tall);
	m_pHTMLMenu->OpenURL(filePath, NULL, false);
}