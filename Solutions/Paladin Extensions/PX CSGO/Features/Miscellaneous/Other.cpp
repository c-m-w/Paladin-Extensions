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

	void PX_API NoTeamDamage( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		if ( pCmd->buttons & IN_ATTACK )
			if ( pLocalPlayer->m_iTeamNum( ) == pLocalPlayer->TraceRayFromAngle( QAngle( pClientState->viewangles ) + pLocalPlayer->m_aimPunchAngle( ) ).hit_entity->GetBaseEntity( )->m_iTeamNum( ) )
				pCmd->buttons &= ~IN_ATTACK;
	}

	void PX_API LastMomentDefuse( player_ptr_t pLocalPlayer, CUserCmd *pCmd )
	{
		if ( pCmd->buttons & IN_USE )
			return; // our job has already been done

		if ( !pLocalPlayer->IsAlive( ) /*|| bomb != planted*/ ) // safety and optimization
			return;

		IClientEntity* pC4Entity { };
		for ( auto u = 0u; u < pEntityList->GetMaxEntities( ); u++ ) // find bomb
			if ( ( pC4Entity = pEntityList->GetClientEntity( u ) ) != nullptr ? pC4Entity->GetClientClass( )->m_ClassID == ClassID_CPlantedC4 : false )
				break;
			else
				pC4Entity = nullptr; // clear p if not

		if ( pC4Entity == nullptr ) // maybe somehow no bomb
			return;

		auto pC4 = reinterpret_cast< CPlantedC4* >( pC4Entity->GetBaseEntity( ) );
		if ( !pC4->m_bBombDefused( ) && pC4->m_bBombTicking( ) ) // if counting down and has not been defused
		{
			auto buffer = pC4->m_flC4Blow( ) - pGlobalVariables->m_flCurrentTime;
			if ( buffer <= ( pLocalPlayer->m_bHasDefuser( ) ? 5.f : 10.f ) // if the time is less than defuse time
				 && buffer >= pLocalPlayer->GetDefuseTimer( ) ) // and we are faster than the ticker
				pCmd->buttons |= IN_USE; // defuse

			// todo, check if bomb is within defusing distance
		}
	}

	void PX_API ChokeStream( )
	{
		*pSendPackets = pGlobalVariables->m_iTickCount % ( _Settings._Miscellaneous._Other.iChoke + 1 );
	}

	void PX_API AutomaticFire( player_ptr_t pLocalPlayer, CUserCmd *pCmd )
	{
		if ( !_Settings._Miscellaneous._Other.bAutomaticFire )
			return;

		auto hActiveWeapon = pLocalPlayer->m_hActiveWeapon( );
		if ( !hActiveWeapon )
			return;

		hActiveWeapon->CanFire( ) ? pCmd->buttons |= IN_ATTACK : pCmd->buttons &= ~IN_ATTACK;
	}

	void PXClanTag( )
	{
		if ( _Settings._Miscellaneous._Other.flClanTagSpeed == 0.f ) // divide by zero safety
			_Settings._Miscellaneous._Other.flClanTagSpeed = FLT_EPSILON;
		
		if ( pGlobalVariables->m_iTickCount % int( ceilf( 1.f / ( _Settings._Miscellaneous._Other.flClanTagSpeed * 2.6666666f * pGlobalVariables->m_flIntervalPerTick ) ) ) )
			return;

		static str_t strTagUnchanged = PX_XOR( "www.paladin-extensions.com" );
		static str_t strTag = strTagUnchanged;
		static bool bDirection = true; // true is right to the left, false is left to the right.

		auto fnRotate = [ ]( str_t &str, int iAmount )
		{
			std::reverse( str.begin( ), str.begin( ) + iAmount );
			std::reverse( str.begin( ) + iAmount, str.end( ) );
			std::reverse( str.begin( ), str.end( ) );
		};

		if ( strTag.substr( 0, PX_MAX_CLAN_LENGTH ) == strTagUnchanged.substr( 0, PX_MAX_CLAN_LENGTH ) )
			bDirection = true;
		else if ( strTag.substr( 0, PX_MAX_CLAN_LENGTH )
				  == strTagUnchanged.substr( strTagUnchanged.length( ) - PX_MAX_CLAN_LENGTH, strTagUnchanged.length( ) ) )
			bDirection = false;

		if ( bDirection )
			fnRotate( strTag, 1 );
		else
			fnRotate( strTag, strTag.length( ) - 1 );

		SetClantag( strTag.substr( 0, PX_MAX_CLAN_LENGTH ).c_str( ) );
	}
}
