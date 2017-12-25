#include "../../dllmain.h"
address_t<int> currentEntity; //CPlayerGlow



struct glowStruct_t
{
  DWORD m_hEntity;
  float r = 1;
  float g = 0;
  float b = 0;
  float thicc;
 
  char pad1[ 4 ]; 
  float flUnk; 
  float m_flBloomAmount;
  float localplayeriszeropoint3;
 
 
  bool RenderWhenOccluded;
  bool RenderWhenUnoccluded;
  bool fullBloom;
  char pad2[ 1 ]; 
 
  int m_nFullBloomStencilTestValue;
  int iUnk; 
  int m_nSplitScreenSlot;    
  int m_nNextFreeSlot;
};


void CGlow::Glow()
{
	while ( plrEntities.val.size( ) != eng.GetGlobalVars( ).ulMaxClients )
	{
		Wait( 1 );
	}
	for ( unsigned long x = plrEntities.val.size( ); x > 0; x-- )
	{
		if ( !plrEntities.val.at( x ).bDormant )
		{
			if ( plrLocalPlayer.val.ulTeamNum != plrEntities.val.at( x ).ulTeamNum )
			{
				address_t<DWORD> glowPointer { mem.dwClientBase + pdwGlowManager.off };
				currentEntity.loc = ( x + GLOWINDEX );
				mem.Get(currentEntity);

				address_t<glowStruct_t> GlowBuffer;
				GlowBuffer.loc = (glowPointer.val + (x * sizeof(glowStruct_t)));
				mem.Get(GlowBuffer);

				mem.Set(GlowBuffer);


				
			}
		}
	}
}

CGlow glo;
