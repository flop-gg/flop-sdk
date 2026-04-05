#include "vgui_controls/Panel.h"
#include "vgui_controls/HTML.h"
#include "GameUI/IGameUI.h"

// This is an html panel tailored for main menu.
class MenuPanel : public vgui::HTML
{
	DECLARE_CLASS_SIMPLE(MenuPanel, vgui::HTML);
public:
	MenuPanel(Panel* parent, const char* name, bool allowJavaScript = false, bool bPopupWindow = false);
	~MenuPanel();

	virtual bool OnStartRequest(const char* url, const char* target, const char* pchPostData, bool bIsRedirect);
};

// This class is what is actually used instead of the main menu.
class OverrideUI_RootPanel : public vgui::Panel
{
	DECLARE_CLASS_SIMPLE( OverrideUI_RootPanel, vgui::Panel );
public:
	OverrideUI_RootPanel(vgui::VPANEL parent);
	virtual ~OverrideUI_RootPanel();

	IGameUI*		GetGameUI();

	vgui::HTML* m_pHTMLMenu;

protected:
	virtual void	ApplySchemeSettings(vgui::IScheme *pScheme);

private:
	bool			LoadGameUI();

	int				m_ExitingFrameCount;
	bool			m_bCopyFrameBuffer;

	IGameUI*		gameui;
};

extern OverrideUI_RootPanel *guiroot;