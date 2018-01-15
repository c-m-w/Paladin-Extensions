#include "../../dllmain.h"

void CGlow::Glow( )
{
	for ( int iEntity { }; iEntity <= 64; iEntity++ )
	{
		address_t< int > iCurrentEntity { };
		iCurrentEntity.dwLocation = eng.GetEntityBase( iEntity ) + INDEX_DISTANCE_GLOW;

		if ( !plrEntities[ iEntity ].xValue.bDormant )
		{
			if ( plrEntities[ iEntity ].xValue.bLifeState == LIFE_ALIVE )
			{
				if ( plrLocalPlayer.xValue.iTeamNum != plrEntities[ iEntity ].xValue.iTeamNum )
				{
					mem.Get( pdwGlowManager );
					mem.Get( iCurrentEntity );
					address_t< glow_t > gloEntityGlow;
					gloEntityGlow.dwLocation = pdwGlowManager.xValue + iCurrentEntity.xValue * sizeof( glow_t );
					mem.Get( gloEntityGlow );

					glow_t glowEntityGlowTemp;
					glowEntityGlowTemp.flRed = 2.f - float( plrEntities[ iEntity ].xValue.iHealth ) / 50.f;
					glowEntityGlowTemp.flGreen = float( plrEntities[ iEntity ].xValue.iHealth ) / 50.f;
					glowEntityGlowTemp.flBlue = 0.f;
					glowEntityGlowTemp.bRenderWhenOccluded = false;
					glowEntityGlowTemp.bRenderWhenUnoccluded = true;
					vector_t vecEntityDistance( plrLocalPlayer.xValue.corOrigin, plrEntities[ iEntity ].xValue.corOrigin );
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
