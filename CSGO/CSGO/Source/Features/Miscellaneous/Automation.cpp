#include "../../dllmain.h"

void CAutomation::AutoJump( )
{
	if ( eng.GetFlags( ) & FL_ONGROUND )
	{
		eng.SetJump( KS_TICK );
	}
	else
	{
		eng.SetJump( ~KS_PRESS );
	}
	eng.WaitTicks( 1 );
}

void CAutomation::AutoNade( )
{
	if ( eng.GetActiveWeaponIndex( ) == EWeapon::FLASHBANG ||
		eng.GetActiveWeaponIndex( ) == EWeapon::HEGRENADE ||
		eng.GetActiveWeaponIndex( ) == EWeapon::SMOKEGRENADE ||
		eng.GetActiveWeaponIndex( ) == EWeapon::MOLOTOV ||
		eng.GetActiveWeaponIndex( ) == EWeapon::DECOY ||
		eng.GetActiveWeaponIndex( ) == EWeapon::INCGRENADE )
	{
		if ( eng.GetAttack( ) & KS_PRESS )
		{
			if ( eng.GetFlags( ) & ~FL_ONGROUND )
			{
				eng.SetAttack( ~KS_PRESS );
			}
		}
	}
	eng.WaitTicks( 1 );
}

void CAutomation::AutoShoot( )
{
	if ( eng.GetNextPrimaryAttack( ) == 0.f &&
		( eng.GetActiveWeaponIndex( ) == EWeapon::DEAGLE ||
			eng.GetActiveWeaponIndex( ) == EWeapon::ELITE ||
			eng.GetActiveWeaponIndex( ) == EWeapon::FIVESEVEN ||
			eng.GetActiveWeaponIndex( ) == EWeapon::GLOCK ||
			eng.GetActiveWeaponIndex( ) == EWeapon::AWP ||
			eng.GetActiveWeaponIndex( ) == EWeapon::TEC9 ||
			eng.GetActiveWeaponIndex( ) == EWeapon::HKP2000 ||
			eng.GetActiveWeaponIndex( ) == EWeapon::P250 ||
			eng.GetActiveWeaponIndex( ) == EWeapon::SSG08 ||
			eng.GetActiveWeaponIndex( ) == EWeapon::USP_SILENCER ||
			eng.GetActiveWeaponIndex( ) == EWeapon::CZ75A ) )
	{
		eng.SetAttack( KS_TICK );
	}
	else
	{
		eng.SetAttack( ~KS_PRESS );
	}
	eng.WaitTicks( 1 );
}

CAutomation aut;
