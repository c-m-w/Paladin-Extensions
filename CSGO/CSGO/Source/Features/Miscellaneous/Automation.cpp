#include "../../dllmain.h"

void CAutomation::AutoJump( )
{
	if ( eng.GetFlags( ) & FL_ONGROUND )
	{
		eng.SetJump( FA_TICK );
		//if ( FAKE SCROLL ) {
		//	for ( int i = rand( ) % 5; i < 7; i++ )
		//	{
		//		eng.WaitTicks( rand( ) % 3 + 1 );
		//		eng.SetJump( FA_TICK );
		//	}
	}
		/*else if ( DIST FROM GROUND < 45 && DIST FROM GROUND > 0 )
		{
			if ( !( DIST FROM GROUND % 15 ) )
			{
				eng.SetJump( FA_TICK );
			}
		}*/
	else
	{
		eng.SetJump( !FA_PRESS );
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
		if ( eng.GetAttack( ) & FA_PRESS )
		{
			if ( eng.GetFlags( ) & !FL_ONGROUND )
			{
				eng.SetAttack( !FA_PRESS );
			}
		}
	}
	eng.WaitTicks( 1 );
}

void CAutomation::AutoShoot( )
{
	if ( eng.GetNextPrimaryAttack( ) <= 0.f &&
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
		eng.SetAttack( FA_TICK );
	}
	else
	{
		eng.SetAttack( !FA_PRESS );
	}
	eng.WaitTicks( 1 );
}

CAutomation aut;
