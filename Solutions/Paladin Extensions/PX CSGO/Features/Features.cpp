/// Features.cpp

#include "PX Precompiled.hpp"
#include "../PX CSGO.hpp"

namespace PX::Features
{
	bool PX_API InitializeFeatures( )
	{
		toggle_t::Initialize( &_Settings, sizeof( settings_t ) );
		PX_INPUT.AddGlobalCallback( [ ]( unsigned uKey, bool bPressed )
		{
			toggle_t::Event( uKey, bPressed );
		} );

		PX_CONFIG.SetContext( &_Settings, sizeof( settings_t ), PX_EXTENSION_CSGO );
		return Awareness::CreateMaterials( )
				//&& Events::AddEventCallback( Miscellaneous::Hitsound, PX_XOR( "player_hurt" ), false )
				//&& Events::AddEventCallback( Miscellaneous::BulletBeam, PX_XOR( "weapon_fire" ), false )
				//&& Events::AddEventCallback( Miscellaneous::CreateHitmarker, PX_XOR( "bullet_impact" ), false )
				&& Miscellaneous::CopyHitsoundFiles( );
	}

	void PX_API ShutdownFeatures( )
	{
		Awareness::RemoveMaterials( );
		Miscellaneous::RemoveHitsoundFiles( );
	}
}
