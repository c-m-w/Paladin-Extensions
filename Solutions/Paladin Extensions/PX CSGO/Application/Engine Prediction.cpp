/// Engine Prediction.cpp

#include "PX Precompiled.hpp"
#include "../PX CSGO.hpp"

using namespace PX;
using namespace Information;
using namespace Pointers;
using namespace Tools;

namespace PX::Prediction
{
	ptr_t* pPlayer = nullptr;
	int* pPredictionSeed = nullptr;
	auto flOldCurtime = 0.f;
	auto flOldFrametime = 0.f;
	CMoveData mdCurrent { };

	bool PX_API InitializePrediction( )
	{
	pPlayer = *reinterpret_cast< ptr_t** >( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Prediction Player" ) ].get< str_t >( ) )
		+ jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Prediction Player" ) ].get< int >( ) );
		pPredictionSeed = *reinterpret_cast< int** >( Modules::mClient.FindPattern( jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Signatures" ) ][ PX_XOR( "Prediction Seed" ) ].get< str_t >( ) )
													  + jsMemoryInformation[ PX_XOR( "Patterns" ) ][ PX_XOR( "Offsets" ) ][ PX_XOR( "Prediction Seed" ) ].get< int >( ) );

		return pPlayer != nullptr
			&& pPredictionSeed != nullptr;
	}

	void PX_API Start( player_ptr_t pLocalPlayer, CUserCmd* pCmd )
	{
		if ( pPredictionSeed == nullptr )
			InitializePrediction( );
		if ( pPredictionSeed == nullptr )
			return;

		*pPredictionSeed = MD5_PseudoRandom( pCmd->command_number ) & 0x7FFFFFFF;
		pGlobalVariables->m_flCurrentTime = pLocalPlayer->m_nTickBase( ) * pGlobalVariables->m_flIntervalPerTick;
		pGlobalVariables->m_flFrameTime = pGlobalVariables->m_flIntervalPerTick;
		*pPlayer = ptr_t( pLocalPlayer );
		pLocalPlayer->m_pCurrentCommand( ) = pCmd;
		flOldCurtime = pGlobalVariables->m_flCurrentTime;
		flOldFrametime = pGlobalVariables->m_flFrameTime;

		memset( &mdCurrent, 0, sizeof mdCurrent );
		pGameMovement->StartTrackPredictionErrors( pLocalPlayer );
		pMoveHelper->SetHost( pLocalPlayer );
		pPrediction->SetupMove( pLocalPlayer, pCmd, pMoveHelper, &mdCurrent );
		pGameMovement->ProcessMovement( pLocalPlayer, &mdCurrent );
		pPrediction->FinishMove( pLocalPlayer, pCmd, &mdCurrent );
	}

	void PX_API End( player_ptr_t pLocalPlayer )
	{
		pGameMovement->FinishTrackPredictionErrors( pLocalPlayer );

		pGlobalVariables->m_flCurrentTime = flOldCurtime;
		pGlobalVariables->m_flFrameTime = flOldFrametime;
		*pPredictionSeed = -1;
		pLocalPlayer->m_pCurrentCommand( ) = nullptr;
		//pMoveHelper->SetHost( nullptr );
		*pPlayer = 0;
	}
}
