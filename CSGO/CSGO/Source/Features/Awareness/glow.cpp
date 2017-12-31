#include "../../dllmain.h"
address_t<int> currentEntity; //CPlayerGlow



struct glowStruct_t
{
	DWORD dwEntityBase{};
	float flRed = 1;
	float flGreen = 0;
	float flBlue = 0;
	float flAlpha = 1;
private:
	BYTE x14[0x4]{};
public:
	float flUnk{};
	float flBloomAmount{};
	float localplayeriszeropoint3{};

	bool bRenderWhenOccluded{};
	bool bRenderWhenUnoccluded{};
	bool bFullBloom{};
private:
	BYTE pad2[ 1 ]{};
public:

	int nFullBloomStencilTestValue{};
	int iUnk{};
	int nSplitScreenSlot{};
	int nNextFreeSlot{};
};


void CGlow::Glow()
{
	/*
	address_t< CPlayer > aplrLocalPlayerCopy = aplrLocalPlayer;
	address_t< CPlayer > aplrEntitiesCopy[64];
	for (int i = 0; i < 64; i++)
	{
		aplrEntitiesCopy[i] = aplrEntities[i];
	
	}
	*/
	for ( unsigned long ulEntity = 0; ulEntity <= 64; ulEntity++ )
	{
		if ( !aplrEntities[ulEntity]._My_val.xValue.bDormant )
		{
			if ( aplrLocalPlayer._My_val.xValue.ulTeamNum != aplrEntities[ulEntity]._My_val.xValue.ulTeamNum )
			{
				//if (aplrEntities[ulEntity]._My_val.xValue.ulHealth > 0){

				mem.Get( pdwGlowManager );

				std::cout << "glowpointer " << pdwGlowManager.xValue << std::endl;
				currentEntity.dwLocation = eng.GetEntityBase( ulEntity ) + GLOWINDEX;
				mem.Get(currentEntity);
				std::cout << "current entity " << currentEntity.xValue << std::endl;

				address_t<glowStruct_t> glowBuffer;
				glowBuffer.dwLocation = pdwGlowManager.xValue + (ulEntity * sizeof(glowStruct_t));
				mem.Get(glowBuffer);
				glowBuffer.xValue.flRed = 0.8;
				glowBuffer.xValue.flBlue = 0.5;
					glowBuffer.xValue.flGreen = 0.2;
				glowBuffer.xValue.bRenderWhenOccluded = false;
				glowBuffer.xValue.bRenderWhenUnoccluded = true;
				glowBuffer.xValue.flAlpha = 0.8;
					glowBuffer.xValue.bFullBloom = false;
				mem.Set(glowBuffer);
			//	}

				
			}
		}
	}
}

CGlow glo;
