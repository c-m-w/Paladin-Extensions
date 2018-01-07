#include "../../dllmain.h"

void CGlow::Glow( )
{
	for ( unsigned long ulEntity = 0; ulEntity < 64; ulEntity++ )
	{
		address_t< long > lEntity;
		lEntity.dwLocation = eng.GetEntityBase( ulEntity ) + INDEX_DISTANCE_GLOW;

		if ( !plrEntities[ ulEntity ]._My_val.xValue.bDormant )
		{
			if ( plrLocalPlayer._My_val.xValue.ulTeamNum != plrEntities[ ulEntity ]._My_val.xValue.ulTeamNum )
			{
				if ( plrEntities[ ulEntity ]._My_val.xValue.bLifeState == LIFE_ALIVE )
				{
					mem.Get( pdwGlowManager );
					mem.Get( lEntity );
					address_t< glow_t > gloEntityGlow;
					gloEntityGlow.dwLocation = pdwGlowManager.xValue + lEntity.xValue * sizeof( glow_t );
					mem.Get( gloEntityGlow );

					gloEntityGlow.xValue.flRed = 2.f - float( plrEntities[ ulEntity ]._My_val.xValue.ulHealth ) / 50.f;
					gloEntityGlow.xValue.flGreen = float( plrEntities[ ulEntity ]._My_val.xValue.ulHealth ) / 50.f;
					gloEntityGlow.xValue.flBlue = 0.f;
					gloEntityGlow.xValue.bRenderWhenOccluded = false;
					gloEntityGlow.xValue.bRenderWhenUnoccluded = true;

					vector_t vecEntityDistance( plrLocalPlayer._My_val.xValue.corOrigin, plrEntities[ ulEntity ]._My_val.xValue.corOrigin );
					float flDistance = sqrt( pow( vecEntityDistance.flDeltaX, 2 ) + pow( vecEntityDistance.flDeltaY, 2 ) + pow( vecEntityDistance.flDeltaZ, 2 ) );
					gloEntityGlow.xValue.flAlpha = 2500.f / flDistance;

					gloEntityGlow.xValue.bFullBloom = false;
					mem.Set( gloEntityGlow );
				}
			}
		}
	}
}

CGlow glo;
