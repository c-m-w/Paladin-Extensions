#include "main.h"

void DrawInterface( )
{
	// call class
	// draw menu
}

void DeleteInterface( )
{
	// call class
	// close all drawings of menu
}

bool Authenticate( )
{
	if ( pro.GetElevationState( GetCurrentProcess( ) ) == EElevation::ADMIN )
	{
		if ( pro.GetPremium( ) == EPremium::BANNED )
		{
			// TODO Delete file
		}
		if ( pro.GetPremium( ) <= EPremium::NOT_PREMIUM )
		{
			return false;
		}
		if ( pro.GetPremium( ) <= EPremium::CONNECTION_FAILURE )
		{
			return false;
		}
		if ( pro.GetPremium( ) <= EPremium::HARDWARE_MISMATCH )
		{
			OPEN_MESSAGE( L"Paladin Loader", L"Your unique identifier has changed - please create a support ticket.", 0 );
			return false;
		}
		if ( pro.GetPremium( ) <= EPremium::EXPIRED )
		{
			OPEN_MESSAGE( L"Paladin Loader", L"Your premium has expired, please renew your premium on the forum.", 0 );
			return false;
		}
		if ( pro.GetPremium( ) == EPremium::DEVELOPER )
		{
			// TODO developer
			return pro.GetPremium( ) == EPremium::DEVELOPER;
		}
		return pro.GetPremium( ) == EPremium::PREMIUM;
	}
	OPEN_MESSAGE( L"Paladin Loader", L"Please run the loader as an administrator.", 0 );
	return false;
}

void Verify( )
{
	// create thread, done here
	// check all dlls exist and are correct size
}

void Inject( )
{
	// call class
	// get user input for middleman
	// inject into selected middleman
}

void StartHeartbeat( )
{
	std::thread( [ & ]
	{
		std::wofstream fsInstance( "cur.inst", std::wofstream::out );
		fsInstance << "true";
		while ( true /* FindWindow(MIDDLEMAN) IS STILL OPEN */ )
		{
			if ( !Authenticate( ) )
			{
				pro.KillAnticheat( L"MIDDLEMAN", L"MIDDLEMAN.EXE" );
				std::wofstream fsRegKey( "reg.key", std::wofstream::out | std::wofstream::trunc );
				fsRegKey.close( );
			}
		}
		fsInstance << "false";
		fsInstance.close( );
	} );
	// confirm authenticity of run, & used to check for multiple instances
}

int CALLBACK WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR szCmdLine, _In_ int iCmdShow )
{
	SetDebug( );

	DrawInterface( );

	if ( !Authenticate( ) ) return 0;

	Verify( );

	Inject( );

	DeleteInterface( );

	StartHeartbeat( );

#ifdef _DEBUG

	FreeConsole( );

#endif

	return 0;
}
