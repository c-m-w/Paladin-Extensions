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
	strHitsound = PX_XOR( "hitsound.mp3" ),
		strHitsoundHead = PX_XOR( "head_hitsound.mp3" ),
	strPrefix = PX_XOR( "*" );

	bool PX_API CopyHitsoundFiles( )
	{
		return true;
		//std::filesystem::copy( string_cast< std::string >( Files::GetPXDirectory( ) ) + strHitsound, strSoundDirectory );
		//std::filesystem::copy( string_cast< std::string >( Files::GetPXDirectory( ) ) + strHitsoundHead, strSoundDirectory );
		//return std::filesystem::exists( strSoundDirectory + PX_XOR( "\\" ) + strHitsound	)
		//	&& std::filesystem::exists( strSoundDirectory + PX_XOR( "\\" ) + strHitsoundHead );
	}

	void PX_API RemoveHitsoundFiles( )
	{
		return;
		std::remove( ( strSoundDirectory + PX_XOR( "\\" ) + strHitsound ).c_str( ) );
		std::remove( ( strSoundDirectory + PX_XOR( "\\" ) + strHitsoundHead ).c_str( ) );
	}

	void PX_API Hitsound( IGameEvent* pEvent )
	{
		if ( !_Settings._Miscellaneous._Other.bHitSound )
			return;

		const auto iLocalPlayer = pEngineClient->GetLocalPlayer( ),
					iAttacker = pEngineClient->GetPlayerForUserID( pEvent->GetInt( PX_XOR( "userid" ) ) );
		if ( iLocalPlayer != iAttacker )
			return;

		pSurface->PlaySound_( ( strPrefix + ( pEvent->GetInt( PX_XOR( "hitgroup" ) ) == HITGROUP_HEAD ? strHitsoundHead : strHitsound ) ).c_str( ) );
	}
}
