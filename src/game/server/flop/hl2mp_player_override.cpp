//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:		Player for HL2.
//
//=============================================================================//

#include "cbase.h"
#include "hl2mp_player.h"

#define HL2MPPLAYER_PHYSDAMAGE_SCALE 4.0f

void CHL2MP_Player::Spawn(void)
{
	m_flNextModelChangeTime = 0.0f;
	m_flNextTeamChangeTime = 0.0f;

	PickDefaultSpawnTeam();

	BaseClass::Spawn();

	if (!IsObserver())
	{
		pl.deadflag = false;
		RemoveSolidFlags(FSOLID_NOT_SOLID);

		RemoveEffects(EF_NODRAW);

		GiveDefaultItems();
	}

	SetNumAnimOverlays(3);
	ResetAnimation();

	m_nRenderFX = kRenderNormal;

	m_Local.m_iHideHUD = 0;

	AddFlag(FL_ONGROUND); // set the player on the ground at the start of the round.

	m_impactEnergyScale = HL2MPPLAYER_PHYSDAMAGE_SCALE;

	if (HL2MPRules()->IsIntermission())
	{
		AddFlag(FL_FROZEN);
	}
	else
	{
		RemoveFlag(FL_FROZEN);
	}

	GetViewModel(1)->SetModel("models/weapons/c_arms_fas2_blue_3.mdl");

	m_iSpawnInterpCounter = (m_iSpawnInterpCounter + 1) % 8;

	m_Local.m_bDucked = false;

	SetPlayerUnderwater(false);

	m_bReady = false;
}

void CHL2MP_Player::GiveDefaultItems(void)
{
	EquipSuit();

	CBasePlayer::GiveAmmo(120, "SMG1");
	CBasePlayer::GiveAmmo(90, "AR2");
	CBasePlayer::GiveAmmo(90, "AR2");
	CBasePlayer::GiveAmmo(120, "Pistol");

	GiveNamedItem("weapon_crowbar");
	GiveNamedItem("weapon_pistol_2");
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