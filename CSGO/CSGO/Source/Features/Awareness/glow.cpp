#include "../../dllmain.h"
address_t< long > lEntity;
bool hpBasedGlow = true;
int cPlayerHealth = 0;
address_t< int > cPlayerHealthAddress;

void CGlow::Glow( )
{
	for ( unsigned long ulEntity = 64; ulEntity < 250; ulEntity++ )
	{

		//std::cout << ulEntity << " " << plrEntities[ ulEntity ]._My_val.xValue.bLifeState << std::endl;
		//std::cout << ulEntity << " " << plrEntities[ ulEntity ]._My_val.xValue.ulTeamNum << std::endl;

		lEntity.dwLocation = eng.GetEntityBase( ulEntity ) + GLOWINDEX;

		/*
		cPlayerHealthAddress.dwLocation = lEntity.dwLocation + 0xFC;
		mem.Get(cPlayerHealthAddress);
		std::cout << cPlayerHealthAddress.xValue << std::endl;
		*/

		//std::cout << "ENTITYBASEGET:: " << eng.GetEntityBase(ulEntity) << std::endl;
		//std::cout << "LOCATION::" << lEntity.dwLocation << std::endl;
		if ( !plrEntities[ ulEntity ]._My_val.xValue.bDormant )
		{
			if ( plrLocalPlayer._My_val.xValue.ulTeamNum != plrEntities[ ulEntity ]._My_val.xValue.ulTeamNum )
			{
				/*plrEntities[ ulEntity ]._My_val.xValue.ulHealth > 0 && plrEntities[ ulEntity ]._My_val.xValue.ulHealth < 101*/ 
				if ( true )
				{
					mem.Get( pdwGlowManager );
					mem.Get( lEntity );
					address_t< glow_t > gloEntityGlow;
					gloEntityGlow.dwLocation = pdwGlowManager.xValue + ulEntity * sizeof( glow_t);
					mem.Get( gloEntityGlow );

					if(hpBasedGlow){
					gloEntityGlow.xValue.flRed = 2.f - float( plrEntities[ ulEntity ]._My_val.xValue.ulHealth ) / 50.f;
					gloEntityGlow.xValue.flGreen = float( plrEntities[ ulEntity ]._My_val.xValue.ulHealth ) / 50.f;
					gloEntityGlow.xValue.flBlue = 0.f;
					}

					gloEntityGlow.xValue.bRenderWhenOccluded = false;
					gloEntityGlow.xValue.bRenderWhenUnoccluded = true;

					vector_t vecEntityDistance( plrLocalPlayer._My_val.xValue.corOrigin, plrEntities[ ulEntity ]._My_val.xValue.corOrigin );
					float flDistance = sqrt( pow( vecEntityDistance.flDeltaX, 2 ) + pow( vecEntityDistance.flDeltaY, 2 ) + pow( vecEntityDistance.flDeltaZ, 2 ) );
					gloEntityGlow.xValue.flAlpha = 1000.f / flDistance;

					gloEntityGlow.xValue.bFullBloom = false;
					mem.Set( gloEntityGlow );
				}
			}
		}
	}
}

CGlow glo;
