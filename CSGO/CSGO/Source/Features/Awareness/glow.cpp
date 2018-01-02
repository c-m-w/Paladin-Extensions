#include "../../dllmain.h"
address_t<int> currentEntity; //CPlayerGlow
int cPlayerHealth;
bool hpBasedGlow = true;


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

	for ( unsigned long ulEntity = 0; ulEntity < 64; ulEntity++ )
	{
		std::cout << ulEntity << " " << aplrEntities[ulEntity]._My_val.xValue.ulHealth << std::endl;
		currentEntity.dwLocation = (eng.GetEntityBase( ulEntity )) + GLOWINDEX;
		if ( !aplrEntities[ulEntity]._My_val.xValue.bDormant )
		{
			if ( aplrLocalPlayer._My_val.xValue.ulTeamNum != aplrEntities[ulEntity]._My_val.xValue.ulTeamNum )
			{
				if (aplrEntities[ulEntity]._My_val.xValue.ulHealth > 0 && aplrEntities[ulEntity]._My_val.xValue.ulHealth < 100){
				mem.Get( pdwGlowManager );		
				mem.Get(currentEntity);

				address_t<glowStruct_t> glowBuffer;
				glowBuffer.dwLocation = pdwGlowManager.xValue + (ulEntity * sizeof(glowStruct_t));
				mem.Get(glowBuffer);
				cPlayerHealth =	aplrEntities[ulEntity]._My_val.xValue.ulHealth;

				
					if (hpBasedGlow){
				glowBuffer.xValue.flRed = 1.0 - cPlayerHealth/100.0;
				glowBuffer.xValue.flGreen = cPlayerHealth/100.0;
				glowBuffer.xValue.flBlue = 0.2;
					}
					else {
				glowBuffer.xValue.flRed = 1.0;
				glowBuffer.xValue.flGreen = 0;
				glowBuffer.xValue.flBlue = 0.2;
					}

				glowBuffer.xValue.bRenderWhenOccluded = false;
				glowBuffer.xValue.bRenderWhenUnoccluded = true;
				glowBuffer.xValue.flAlpha = 0.8;
				glowBuffer.xValue.bFullBloom = false;
				mem.Set(glowBuffer);

				}

				
			}
		}
	}
}

CGlow glo;
