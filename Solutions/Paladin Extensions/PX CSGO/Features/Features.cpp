/// Features.cpp

#include "PX Precompiled.hpp"
#include "../PX CSGO.hpp"

namespace PX::Features
{
	bool PX_API InitializeFeatures( )
	{
		PX_INPUT.AddGlobalCallback( [ ]( unsigned uKey, bool bPressed )
		{
			for( auto& toggle : toggle_t::vecToggles )
				if( toggle->UseKeyBinds( ) )
					for( auto& keybind : toggle->GetBinds( ) )
						if( keybind.kKey == uKey )
							switch( keybind.iKeyBindMode )
							{
								case KEYBIND_TOGGLE:
								{
									if( bPressed )
										toggle->Get( ) = !toggle->Get( );
								}
								break;

								case KEYBIND_WHILE_PRESSED:
								{
									toggle->Get( ) = bPressed;
								}
								break;

								case KEYBIND_WHILE_NOT_PRESSED:
								{
									toggle->Get( ) = !bPressed;
								}
								break;

								case KEYBIND_ENABLE:
								{
									if ( bPressed )
										toggle->Get( ) = true;
								}
								break;

								case KEYBIND_DISABLE:
								{
									if ( bPressed )
										toggle->Get( ) = false;
								}
								break;

								default:
									break;
							}
		} );

		PX_CONFIG.LoadDefaultConfiguration( PX_EXTENSION_CSGO, &_Settings, sizeof( settings_t ) );
		return true;
	}
}
