//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "npcevent.h"
#include "in_buttons.h"

#ifdef CLIENT_DLL
	#include "c_hl2mp_player.h"
#else
	#include "grenade_ar2.h"
	#include "hl2mp_player.h"
	#include "basegrenade_shared.h"
#endif

#include "weapon_hl2mpbase.h"
#include "weapon_flopbase_machinegun.h"

#ifdef CLIENT_DLL
#define CWeaponAR_1 C_WeaponAR_1
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

class CWeaponAR_1 : public CFlopMachineGun
{
public:
	DECLARE_CLASS( CWeaponAR_1, CFlopMachineGun );

	CWeaponAR_1();

	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

	
	void	Precache( void );
	void	AddViewKick( void );
	void	SecondaryAttack( void );

	int		GetMinBurst() { return 2; }
	int		GetMaxBurst() { return 5; }

	virtual void Equip( CBaseCombatCharacter *pOwner );
	bool	Reload( void );

	float	GetFireRate( void ) { return 0.1f; }
	Activity	GetPrimaryAttackActivity( void );

	virtual bool GetBurstEnabled() { return true; }

	virtual const Vector& GetBulletSpread( void )
	{
		static const Vector cone = VECTOR_CONE_5DEGREES;
		return cone;
	}

	const WeaponProficiencyInfo_t *GetProficiencyValues();

#ifndef CLIENT_DLL
	DECLARE_ACTTABLE();
#endif

protected:

	Vector	m_vecTossVelocity;
	float	m_flNextGrenadeCheck;
	
private:
	CWeaponAR_1( const CWeaponAR_1 & );
};

IMPLEMENT_NETWORKCLASS_ALIASED( WeaponAR_1, DT_WeaponAR_1 )

BEGIN_NETWORK_TABLE( CWeaponAR_1, DT_WeaponAR_1 )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CWeaponAR_1 )
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( weapon_ar_1, CWeaponAR_1 );
PRECACHE_WEAPON_REGISTER(weapon_ar_1);

#ifndef CLIENT_DLL
acttable_t	CWeaponAR_1::m_acttable[] = 
{
	{ ACT_HL2MP_IDLE,					ACT_HL2MP_IDLE_AR2,						false },
	{ ACT_HL2MP_RUN,					ACT_HL2MP_RUN_AR2,						false },
	{ ACT_HL2MP_IDLE_CROUCH,			ACT_HL2MP_IDLE_CROUCH_AR2,				false },
	{ ACT_HL2MP_WALK_CROUCH,			ACT_HL2MP_WALK_CROUCH_AR2,				false },
	{ ACT_HL2MP_GESTURE_RANGE_ATTACK,	ACT_HL2MP_GESTURE_RANGE_ATTACK_AR2,		false },
	{ ACT_HL2MP_GESTURE_RELOAD,			ACT_HL2MP_GESTURE_RELOAD_AR2,			false },
	{ ACT_HL2MP_JUMP,					ACT_HL2MP_JUMP_AR2,						false },
	{ ACT_RANGE_ATTACK1,				ACT_RANGE_ATTACK_AR2,					false },
};

IMPLEMENT_ACTTABLE(CWeaponAR_1);
#endif

//=========================================================
CWeaponAR_1::CWeaponAR_1( )
{
	m_fMinRange1		= 0;// No minimum range. 
	m_fMaxRange1		= 1400;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponAR_1::Precache( void )
{
#ifndef CLIENT_DLL
	UTIL_PrecacheOther("grenade_ar2");
#endif

	BaseClass::Precache();
}

//-----------------------------------------------------------------------------
// Purpose: Give this weapon longer range when wielded by an ally NPC.
//-----------------------------------------------------------------------------
void CWeaponAR_1::Equip( CBaseCombatCharacter *pOwner )
{
	m_fMaxRange1 = 1400;

	BaseClass::Equip( pOwner );
}

//-----------------------------------------------------------------------------
// Purpose: 
// Output : Activity
//-----------------------------------------------------------------------------
Activity CWeaponAR_1::GetPrimaryAttackActivity( void )
{
	if ( m_nShotsFired < 2 )
		return ACT_VM_PRIMARYATTACK;

	if ( m_nShotsFired < 3 )
		return ACT_VM_RECOIL1;
	
	if ( m_nShotsFired < 4 )
		return ACT_VM_RECOIL2;

	return ACT_VM_RECOIL3;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CWeaponAR_1::Reload( void )
{
	bool fRet;
	float fCacheTime = m_flNextSecondaryAttack;

	fRet = DefaultReload( GetMaxClip1(), GetMaxClip2(), ACT_VM_RELOAD );
	if ( fRet )
	{
		// Undo whatever the reload process has done to our secondary
		// attack timer. We allow you to interrupt reloading to fire
		// a grenade.
		m_flNextSecondaryAttack = GetOwner()->m_flNextAttack = fCacheTime;

		WeaponSound( RELOAD );
	}

	return fRet;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponAR_1::AddViewKick( void )
{
	#define MAX_VERTICAL_KICK   8.0f	// What is the max recoil angle?
	#define SLIDE_LIMIT         10		// How many shots does it take for the recoil to reach max?
	#define HORIZONTAL_PREC		0.8f	// How much horizontal recoil
	
	//Get the view kick
	CBasePlayer *pPlayer = ToBasePlayer( GetOwner() );

	if ( pPlayer == NULL )
		return;

	DoMachineGunKick( pPlayer, MAX_VERTICAL_KICK, m_nShotsFired, SLIDE_LIMIT, HORIZONTAL_PREC );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponAR_1::SecondaryAttack( void )
{

}

//-----------------------------------------------------------------------------
const WeaponProficiencyInfo_t *CWeaponAR_1::GetProficiencyValues()
{
	static WeaponProficiencyInfo_t proficiencyTable[] =
	{
		{ 7.0,		0.75	},
		{ 5.00,		0.75	},
		{ 10.0/3.0, 0.75	},
		{ 5.0/3.0,	0.75	},
		{ 1.00,		1.0		},
	};

	COMPILE_TIME_ASSERT( ARRAYSIZE(proficiencyTable) == WEAPON_PROFICIENCY_PERFECT + 1);

	return proficiencyTable;
}
