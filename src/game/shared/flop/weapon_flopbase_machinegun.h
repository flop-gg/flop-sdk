//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "weapon_hl2mpbase.h"
#include "weapon_hl2mpbasehlmpcombatweapon.h"

#ifndef BASEFLCOMBATWEAPON_H
#define BASEFLCOMBATWEAPON_H
#ifdef _WIN32
#pragma once
#endif

#if defined( CLIENT_DLL )
	#define CFlopMachineGun C_FlopMachineGun
#endif

//=========================================================
// Machine gun base class
//=========================================================
class CFlopMachineGun : public CBaseHL2MPCombatWeapon
{
public:
	DECLARE_CLASS( CFlopMachineGun, CBaseHL2MPCombatWeapon );
	DECLARE_DATADESC();

	CFlopMachineGun();
	
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

	void	PrimaryAttack( void );

	// Default calls through to m_hOwner, but plasma weapons can override and shoot projectiles here.
	virtual void	ItemPostFrame( void );
	virtual void	FireBullets( const FireBulletsInfo_t &info );
	virtual bool	Deploy( void );

	virtual const Vector &GetBulletSpread( void );

	int				WeaponSoundRealtime(WeaponSound_t shoot_type);

	// utility function
	static void DoMachineGunKick( CBasePlayer *pPlayer, float maxVerticleKickAngle, int shotsFired, int shotLimit, float horizontalPrecision );

	virtual bool HasSecondaryAttack( void ) { return false; }
	virtual void SecondaryAttack( void ) { return; }

private:
	CFlopMachineGun( const CFlopMachineGun & );

protected:

	int	m_nShotsFired;	// Number of consecutive shots fired

	float	m_flNextSoundTime;	// real-time clock of when to make next sound

	CNetworkVar(int, m_iBurst);
	CNetworkVar(int, m_iBurstVal);
};

#endif // BASEFLCOMBATWEAPON_H
