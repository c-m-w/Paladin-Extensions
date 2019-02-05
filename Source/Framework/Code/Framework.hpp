/// Framework.hpp

#pragma once

#define XOR( _String ) ( _String )

#include "Development Environment/Build Output Wrapper.hpp"
#define NO_ENTRY
#include "Development Environment/Entry Manager.hpp"

#include "Development Environment/Font Awesome Icons.hpp"
#include "Source Development Kit/Application Programming Interfaces/Utilities.hpp"
#include "Source Development Kit/Application Programming Interfaces/Color.hpp"
#include "Source Development Kit/Application Programming Interfaces/Base Interface.hpp"

#include "Source Development Kit/Application Programming Interfaces/Cryptography.hpp"
#include "Source Development Kit/Application Programming Interfaces/Filesystem.hpp"
#include "Development Environment/Logging.hpp"
#include "Source Development Kit/Toolkits/Memory Manager.hpp"
#include "Source Development Kit/Application Programming Interfaces/Input.hpp"
#include "Source Development Kit/Toolkits/Resource Manager.hpp"

#include "Source Development Kit/Application Programming Interfaces/Connectivity.hpp"
#include "Source Development Kit/Application Programming Interfaces/Window.hpp"
#include "Source Development Kit/Application Programming Interfaces/Drawing.hpp"
#include "Source Development Kit/Toolkits/Graphical User Interface.hpp"

void ShutdownFramework( );

inline bool SetupFramework( )
{
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
}

#if defined USE_NAMESPACES
using namespace Utilities;
using namespace Interface;
#endif

#if defined USE_DEFINITIONS
#define CRYPTO ( _Cryptography )
#define ENCODE( _String ) ( CRYPTO.Base64< encode_t >( _String ) )
#define DECODE( _String ) ( CRYPTO.Base64< decode_t >( _String ) )
#define ENCRYPT( _String ) ( CRYPTO.Crypt< encrypt_t >( _String ) )
#define DECRYPT( _String ) ( CRYPTO.Crypt< decrypt_t >( _String ) )
#define FS ( _Filesystem )
#define LOG ( _Log )
#define NET ( _Connection )
#define INPUT ( _Input )
#define DRAW ( _Drawing )
#endif
