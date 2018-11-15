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
}
