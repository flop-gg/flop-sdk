//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:		Player for HL2.
//
//=============================================================================//

#include "cbase.h"
#include "hl2mp_player.h"

void CHL2MP_Player::GiveDefaultItems(void)
{
	EquipSuit();

	CBasePlayer::GiveAmmo(120, "SMG1");
	CBasePlayer::GiveAmmo(90, "AR2");
	CBasePlayer::GiveAmmo(90, "AR2");
	CBasePlayer::GiveAmmo(120, "Pistol");

	GiveNamedItem("weapon_crowbar");
	GiveNamedItem("weapon_pistol_1");
	GiveNamedItem("weapon_ar_1");

	const char* szDefaultWeaponName = engine->GetClientConVarValue(engine->IndexOfEdict(edict()), "cl_defaultweapon");

	CBaseCombatWeapon* pDefaultWeapon = Weapon_OwnsThisType(szDefaultWeaponName);

	if (pDefaultWeapon)
	{
		Weapon_Switch(pDefaultWeapon);
	}
	else
	{
		Weapon_Switch(Weapon_OwnsThisType("weapon_physcannon"));
	}
}