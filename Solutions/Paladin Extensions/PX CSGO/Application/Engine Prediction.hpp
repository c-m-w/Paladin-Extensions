/// Engine Prediction.hpp

#pragma once

namespace PX::Prediction
{
	bool PX_API InitializePrediction( );
	void PX_API Start( Types::player_ptr_t pLocalPlayer, CUserCmd *pCmd );
	void PX_API End( Types::player_ptr_t pLocalPlayer );
}
