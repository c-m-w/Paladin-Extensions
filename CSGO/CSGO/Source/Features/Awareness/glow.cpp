#include "../../dllmain.h"

void CGlow::Glow( )
{
	for ( unsigned long ulEntity = 0; ulEntity < 64; ulEntity++ )
	{
		address_t< long > lEntity;
		lEntity.dwLocation = eng.GetEntityBase( ulEntity ) + INDEX_DISTANCE_GLOW;

		if ( !plrEntities[ ulEntity ].xValue._My_val.bDormant )
		{
			if ( plrLocalPlayer.xValue._My_val.ulTeamNum != plrEntities[ ulEntity ].xValue._My_val.ulTeamNum )
			{
				if ( plrEntities[ ulEntity ].xValue._My_val.bLifeState == LIFE_ALIVE )
				{
					mem.Get( pdwGlowManager );
					mem.Get( lEntity );
					address_t< glow_t > gloEntityGlow;
					gloEntityGlow.dwLocation = pdwGlowManager.xValue + lEntity.xValue * sizeof( glow_t );
					mem.Get( gloEntityGlow );

					glow_t glowEntityGlowTemp;
					glowEntityGlowTemp.flRed = 2.f - float( plrEntities[ ulEntity ].xValue._My_val.ulHealth ) / 50.f;
					glowEntityGlowTemp.flGreen = float( plrEntities[ ulEntity ].xValue._My_val.ulHealth ) / 50.f;
					glowEntityGlowTemp.flBlue = 0.f;
					glowEntityGlowTemp.bRenderWhenOccluded = false;
					glowEntityGlowTemp.bRenderWhenUnoccluded = true;
					vector_t vecEntityDistance( plrLocalPlayer.xValue._My_val.corOrigin, plrEntities[ ulEntity ].xValue._My_val.corOrigin );
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
