/// Framework.hpp

#pragma once

#include "Development Environment/Build Output Wrapper.hpp"
#define NO_ENTRY
#include "Development Environment/Entry Manager.hpp"

#include "Development Environment/Icon Font Definitions/Font Awesome Icons.hpp"
#include "Development Environment/Icon Font Definitions/Material Design Icons.hpp"
#include "Source Development Kit/Application Programming Interfaces/Utilities.hpp"
#include "Source Development Kit/Application Programming Interfaces/Color.hpp"
#include "Source Development Kit/Application Programming Interfaces/Base Interface.hpp"

#include "Source Development Kit/Application Programming Interfaces/Cryptography.hpp"
#include "Source Development Kit/Application Programming Interfaces/Filesystem.hpp"
#include "Development Environment/Logging.hpp"
#include "Source Development Kit/Toolkits/System Utilities.hpp"
#include "Source Development Kit/Toolkits/Memory Manager.hpp"
#include "Source Development Kit/Application Programming Interfaces/Input.hpp"
#include "Source Development Kit/Toolkits/Resource Manager.hpp"

#include "Source Development Kit/Application Programming Interfaces/Connectivity.hpp"
#include "Source Development Kit/Application Programming Interfaces/Window.hpp"
#include "Source Development Kit/Application Programming Interfaces/Drawing.hpp"
#include "Source Development Kit/Toolkits/Graphical User Interface.hpp"
#include "Source Development Kit/Toolkits/Authentication.hpp"

#if defined _DEBUG
inline CApplicationWindow *pConsoleWindow;
#endif

void ShutdownFramework( );

inline bool SetupFramework( )
{
#if defined _DEBUG
	pConsoleWindow = new CApplicationWindow( GetConsoleWindow( ), nullptr );
	pConsoleWindow->Resize( 1200, 600 );
	pConsoleWindow->SetTitle( ENC( "Paladin Extensions Debug Console" ) );
#endif
	if ( !_Filesystem.Setup( )
		|| !_Log.Setup( )
		|| !_Cryptography.Setup( )
		|| !_Connection.Setup( )
		|| !_ResourceManager.Setup( )
		|| !_Input.Setup( ) )
	{
		ShutdownFramework( );
		return false;
	}

	return true;
}

inline void ShutdownFramework( )
{
	_Input.Shutdown( );
	_ResourceManager.Shutdown( );
	_Connection.Shutdown( );
	_Cryptography.Shutdown( );
	_Log.Shutdown( );
	_Filesystem.Shutdown( );
#if defined _DEBUG
	delete pConsoleWindow;
#endif
}

#if defined USE_NAMESPACES
using namespace Utilities;
using namespace Interface;
#endif

// todo cleanup all references to normal class objects and replace with definitions
#if defined USE_DEFINITIONS
#define CRYPTO ( _Cryptography )
#define ENCODE( _String ) ( CRYPTO.Base64< encode_t >( _String ) )
#define DECODE( _String ) ( CRYPTO.Base64< decode_t >( _String ) )
#define ENCRYPT( _String ) ( CRYPTO.Crypt< encrypt_t >( _String ) )
#define DECRYPT( _String ) ( CRYPTO.Crypt< decrypt_t >( _String ) )
#define FS ( _Filesystem )
#define RESOURCES ( _ResourceManager )
#define LOG ( _Log )
#define NET ( _Connection )
#define INPUT ( _Input )
#define DRAW ( _Drawing )
#define AUTH  ( _Authentication )
#define SI ( _SystemInformation )
#define MEM ( _MemoryManager )
#endif
