/// Visuals.hpp

#pragma once

namespace PX::Features::Miscellaneous
{
	void PX_API DarkenWorld( );
	void PX_API DrawAimbotFOV( );
	void PX_API VisualizeSpread( );
	void PX_API ModifyRenderFOV( CViewSetup* pViewSetup );
	void PX_API ModifyViewmodelFOV( float* pFOV );
	void PX_API BulletBeam( IGameEvent* pEvent );
	void PX_API CreateHitmarker( IGameEvent* pEvent );
	void PX_API DrawHitmarkers( );

	void PX_API MinimizeFlash( player_ptr_t pLocalPlayer );
	void PX_API SmokeWireframe( );
	void PX_API ScopeWireframe( );
	void PX_API MaximizeRadarVisibility( );
}
