/// Framework.hpp

#pragma once

#include "Development Environment/Build Output Wrapper.hpp"
#define NO_ENTRY
#include "Development Environment/Entry Manager.hpp"

#include <nanosvg/src/nanosvg.h>
#include <nanosvg/src/nanosvgrast.h>

#include <stb/stb_image_write.h>

#include "Development Environment/Icon Font Definitions/Font Awesome Icons.hpp"
#include "Development Environment/Icon Font Definitions/Material Design Icons.hpp"
#include "Source Development Kit/Application Programming Interfaces/Utilities.hpp"
#include "Source Development Kit/Application Programming Interfaces/Color.hpp"
#include "Source Development Kit/Application Programming Interfaces/Base Interface.hpp"
#include "Source Development Kit/Application Programming Interfaces/Temporary Pointer.hpp"

#include "Development Environment/Logging.hpp"
#include "Source Development Kit/Application Programming Interfaces/Cryptography.hpp"
#include "Source Development Kit/Application Programming Interfaces/Filesystem.hpp"
#include "Source Development Kit/Toolkits/System Utilities.hpp"
#include "Source Development Kit/Toolkits/Memory Manager.hpp"
#include "Source Development Kit/Toolkits/Hooking.hpp"
#include "Source Development Kit/Application Programming Interfaces/Input Handler.hpp"
#include "Source Development Kit/Toolkits/Resource Manager.hpp"

#include "Source Development Kit/Application Programming Interfaces/Connectivity.hpp"
#include "Source Development Kit/Application Programming Interfaces/Window.hpp"
#include "Source Development Kit/Application Programming Interfaces/Drawing/Shaders.hpp"
#include "Source Development Kit/Application Programming Interfaces/Drawing/Font Manager.hpp"
#include "Source Development Kit/Application Programming Interfaces/Drawing/Drawing.hpp"
#include "Source Development Kit/Toolkits/GUI/GUI.hpp"
#include "Source Development Kit/Toolkits/Authentication.hpp"

#if defined _DEBUG
inline CApplicationWindow *pConsoleWindow;
#endif

void ShutdownFramework( );

inline bool SetupFramework( )
{
	static auto bInitializedOnce = false;
	if ( bInitializedOnce )
		throw std::runtime_error( ENC( "Initializing framework twice." ) );

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
		 || !_Input.Setup( )
		 || !_MemoryManager.Setup( ) )
	{
		ShutdownFramework( );
		return false;
	}

	return bInitializedOnce = true, true;
}

inline void ShutdownFramework( )
{
	_MemoryManager.Shutdown( );
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
#define LOG( Prefix, Location, Message, ... ) _Log.Log( EPrefix::##Prefix, ELocation::##Location, ENC( Message ), __VA_ARGS__ )
#define NET ( _Connection )
#define INPUT ( _Input )
#define FONTS ( _FontManager )
#define DRAW ( _Drawing )
#define AUTH  ( _Authentication )
#define SI ( _SystemInformation )
#define MEM ( _MemoryManager )
#endif
