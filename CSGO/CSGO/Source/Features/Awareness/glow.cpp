#include "../../dllmain.h"

void CGlow::Glow( )
{
	for ( int iEntity = 0; iEntity < 64; iEntity++ ) // NOLINT
	{
		address_t< int > iCurrentEntity;
		iCurrentEntity.dwLocation = eng.GetEntityBase( iEntity ) + INDEX_DISTANCE_GLOW;

		if ( !plrEntities[ iEntity ].xValue._My_val.bDormant )
		{
			if ( plrLocalPlayer.xValue._My_val.iTeamNum != plrEntities[ iEntity ].xValue._My_val.iTeamNum )
			{
				if ( plrEntities[ iEntity ].xValue._My_val.bLifeState == LIFE_ALIVE )
				{
					mem.Get( pdwGlowManager );
					mem.Get( iCurrentEntity );
					address_t< glow_t > gloEntityGlow;
					gloEntityGlow.dwLocation = pdwGlowManager.xValue + iCurrentEntity.xValue * sizeof( glow_t);
					mem.Get( gloEntityGlow );

					glow_t glowEntityGlowTemp;
					glowEntityGlowTemp.flRed = 2.f - float( plrEntities[ iEntity ].xValue._My_val.iHealth ) / 50.f;
					glowEntityGlowTemp.flGreen = float( plrEntities[ iEntity ].xValue._My_val.iHealth ) / 50.f;
					glowEntityGlowTemp.flBlue = 0.f;
					glowEntityGlowTemp.bRenderWhenOccluded = false;
					glowEntityGlowTemp.bRenderWhenUnoccluded = true;
					vector_t vecEntityDistance( plrLocalPlayer.xValue._My_val.corOrigin, plrEntities[ iEntity ].xValue._My_val.corOrigin );
					float flDistance = sqrt( pow( vecEntityDistance.flDeltaX, 2 ) + pow( vecEntityDistance.flDeltaY, 2 ) + pow( vecEntityDistance.flDeltaZ, 2 ) );
					glowEntityGlowTemp.flAlpha = 2500.f / flDistance;
					glowEntityGlowTemp.bFullBloom = false;

					gloEntityGlow.xValue = glowEntityGlowTemp;
					mem.Set( gloEntityGlow );
				}
			}
		}
	}
}

CGlow glo;
