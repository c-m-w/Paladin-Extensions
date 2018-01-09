#include "../../dllmain.h"

void CGlow::Glow( )
{
	for ( unsigned int uiEntity = 0; uiEntity < 64; uiEntity++ )
	{
		address_t< int > iEntity;
		iEntity.dwLocation = eng.GetEntityBase( uiEntity ) + INDEX_DISTANCE_GLOW;

		if ( !plrEntities[ uiEntity ].xValue._My_val.bDormant )
		{
			if ( plrLocalPlayer.xValue._My_val.uiTeamNum != plrEntities[ uiEntity ].xValue._My_val.uiTeamNum )
			{
				if ( plrEntities[ uiEntity ].xValue._My_val.bLifeState == LIFE_ALIVE )
				{
					mem.Get( pdwGlowManager );
					mem.Get( iEntity );
					address_t< glow_t > gloEntityGlow;
					gloEntityGlow.dwLocation = pdwGlowManager.xValue + iEntity.xValue * sizeof( glow_t );
					mem.Get( gloEntityGlow );

					glow_t glowEntityGlowTemp;
					glowEntityGlowTemp.flRed = 2.f - float( plrEntities[ uiEntity ].xValue._My_val.uiHealth ) / 50.f;
					glowEntityGlowTemp.flGreen = float( plrEntities[ uiEntity ].xValue._My_val.uiHealth ) / 50.f;
					glowEntityGlowTemp.flBlue = 0.f;
					glowEntityGlowTemp.bRenderWhenOccluded = false;
					glowEntityGlowTemp.bRenderWhenUnoccluded = true;
					vector_t vecEntityDistance( plrLocalPlayer.xValue._My_val.corOrigin, plrEntities[ uiEntity ].xValue._My_val.corOrigin );
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
