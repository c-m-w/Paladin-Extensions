/// Other.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX;
using namespace Information;
using namespace Pointers;
using namespace Tools;

namespace PX::Features::Miscellaneous
{
	const std::string strSoundDirectory = PX_XOR( "csgo\\sound" ),
	strHitsound = PX_XOR( "hitsound.wav" ),
		strHitsoundHead = PX_XOR( "head_hitsound.wav" ),
	strPrefix = PX_XOR( "*" );

	bool PX_API CopyHitsoundFiles( )
	{
		if ( !std::filesystem::exists( string_cast< std::string >( Files::GetPXDirectory( ) ) + PX_XOR( "Resources\\" ) + strHitsound )
			 || !std::filesystem::exists( string_cast< std::string >( Files::GetPXDirectory( ) ) + PX_XOR( "Resources\\" ) + strHitsoundHead ) )
			return false;

		RemoveHitsoundFiles( );
		std::filesystem::copy( string_cast< std::string >( Files::GetPXDirectory( ) ) + PX_XOR( "Resources\\" ) + strHitsound, strSoundDirectory );
		std::filesystem::copy( string_cast< std::string >( Files::GetPXDirectory( ) ) + PX_XOR( "Resources\\" ) + strHitsoundHead, strSoundDirectory );
		return std::filesystem::exists( strSoundDirectory + PX_XOR( "\\" ) + strHitsound	)
			&& std::filesystem::exists( strSoundDirectory + PX_XOR( "\\" ) + strHitsoundHead );
	}

	void PX_API RemoveHitsoundFiles( )
	{
		std::remove( ( strSoundDirectory + PX_XOR( "\\" ) + strHitsound ).c_str( ) );
		std::remove( ( strSoundDirectory + PX_XOR( "\\" ) + strHitsoundHead ).c_str( ) );
	}

	void PX_API Hitsound( IGameEvent* pEvent )
	{
		if ( !_Settings._Miscellaneous._Other.bHitSound )
			return;

		const auto iLocalPlayer = pEngineClient->GetLocalPlayer( ),
					iAttacker = pEngineClient->GetPlayerForUserID( pEvent->GetInt( PX_XOR( "attacker" ) ) );
		if ( iLocalPlayer != iAttacker )
			return;

		pSurface->PlaySound_( ( strPrefix + ( pEvent->GetInt( PX_XOR( "hitgroup" ) ) == HITGROUP_HEAD ? strHitsoundHead : strHitsound ) ).c_str( ) );
	}
}
