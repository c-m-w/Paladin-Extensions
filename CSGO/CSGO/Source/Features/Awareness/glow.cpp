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
	address_t< CPlayer > aplrLocalPlayerCopy = aplrLocalPlayer;
	std::vector< address_t< CPlayer > > aplrEntitiesCopy;
	for ( size_t sizSize = aplrEntities.size(  ); sizSize > 0; sizSize --)
	{
		aplrEntitiesCopy.push_back( aplrEntities.at( sizSize )._My_val );
	}
	for ( unsigned long ulEntity = aplrEntitiesCopy.size( ); ulEntity > 0; ulEntity-- )
	{
		if ( !aplrEntitiesCopy.at( ulEntity ).xValue.bDormant )
		{
			if ( aplrLocalPlayerCopy.xValue.ulTeamNum != aplrEntitiesCopy.at( ulEntity ).xValue.ulTeamNum )
			{
				address_t<DWORD> glowPointer { mem.dwClientBase + pdwGlowManager.dwOffset };
				currentEntity.dwLocation = ulEntity + GLOWINDEX;
				mem.Get(currentEntity);

				address_t<glowStruct_t> glowBuffer;
				glowBuffer.dwLocation = glowPointer.xValue + ulEntity * sizeof(glowStruct_t);
				mem.Get(glowBuffer);

				mem.Set(glowBuffer);


				
			}
		}
	}
}

CGlow glo;
