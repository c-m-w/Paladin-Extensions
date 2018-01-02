#include "../../dllmain.h"

struct glowStruct_t
{
	DWORD dwEntityBase { };
	float flRed = 1;
	float flGreen = 0;
	float flBlue = 0;
	float flAlpha = 1;
private:
	BYTE x14[0x8] { };
public:
	float flBloomAmount { }; // 0x22
	float localplayeriszeropoint3 { }; // 0x26
	bool bRenderWhenOccluded { }; // 0x27
	bool bRenderWhenUnoccluded { }; // 0x28
	bool bFullBloom { }; // 0x29
private:
	BYTE x30[ 0x1 ] { };
public:
	int nFullBloomStencilTestValue { }; // 0x31
private:
	BYTE x35[ 0x4 ] { };
public:
	int nSplitScreenSlot { };
	int nNextFreeSlot { };
};

void CGlow::Glow( )
{
	for ( unsigned long ulEntity = 0; ulEntity < 64; ulEntity++ )
	{
		std::cout << ulEntity << " " << aplrEntities[ ulEntity ]._My_val.xValue.ulHealth << std::endl;
		address_t< int > currentEntity;
		currentEntity.dwLocation = eng.GetEntityBase( ulEntity ) + GLOWINDEX;
		if ( !aplrEntities[ ulEntity ]._My_val.xValue.bDormant )
		{
			if ( aplrLocalPlayer._My_val.xValue.ulTeamNum != aplrEntities[ ulEntity ]._My_val.xValue.ulTeamNum )
			{
				if ( aplrEntities[ ulEntity ]._My_val.xValue.ulHealth > 0 && aplrEntities[ ulEntity ]._My_val.xValue.ulHealth < 100 )
				{
					mem.Get( pdwGlowManager );
					mem.Get( currentEntity );

					address_t< glowStruct_t > glowBuffer;
					glowBuffer.dwLocation = pdwGlowManager.xValue + ulEntity * sizeof(glowStruct_t);
					mem.Get( glowBuffer );
					int cPlayerHealth = aplrEntities[ ulEntity ]._My_val.xValue.ulHealth;

					bool hpBasedGlow = true;
					if ( hpBasedGlow )
					{
						glowBuffer.xValue.flRed = 1.f - cPlayerHealth / 100.f;
						glowBuffer.xValue.flGreen = cPlayerHealth / 100.f;
						glowBuffer.xValue.flBlue = 0.2f;
					}
					else
					{
						glowBuffer.xValue.flRed = 1.f;
						glowBuffer.xValue.flGreen = 0.f;
						glowBuffer.xValue.flBlue = 0.2f;
					}

					glowBuffer.xValue.bRenderWhenOccluded = false;
					glowBuffer.xValue.bRenderWhenUnoccluded = true;
					glowBuffer.xValue.flAlpha = 0.8f;
					glowBuffer.xValue.bFullBloom = false;
					mem.Set( glowBuffer );
				}
			}
		}
	}
}

CGlow glo;
