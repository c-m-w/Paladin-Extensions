/// Information.cpp

#include "PX Precompiled.hpp"
#include "../../PX CSGO.hpp"

using namespace PX::Tools;
using namespace PX::Information;
using namespace PX::Drawing;
using namespace Pointers;

namespace PX::Features::Awareness
{
	CBasePlayer* pLocalPlayer = nullptr;

	enum
	{
		TOPLEFT,
		TOPRIGHT,
		BOTTOMLEFT,
		BOTTOMRIGHT,
		TLRB_MAX
	};

	struct _
	{
		CBaseEntity* p = nullptr;
		bool operator!( ) const { return p == nullptr; }

		_& operator=( entity_ptr_t p ) { this->p = p; return *this; }

		CBaseEntity* operator->( ) const { return p; }
		template< typename _t > _t* operator->( ) const { return reinterpret_cast< _t* >( p ); }
		
		bool Friendly( ) const { return p->IsPlayer( ) && p->m_iTeamNum( ) == pLocalPlayer->m_iTeamNum( ); }
		Vector vecBox[ TLRB_MAX ] { { }, { }, { }, { } };
		bool bBoxVisibility = false;
		EState enumExistence = STATE_MAX;
	} pEntity;

	void PX_API DrawStatistics( )
	{
		if ( !pEngineClient->IsInGame( ) )
			return;
		pLocalPlayer = GetLocalPlayer( );
		if ( !pLocalPlayer )
			return;

		for ( auto i = 0; i < pEntityList->GetMaxEntities( ); i++ )
		{
			pEntity = entity_ptr_t( pEntityList->GetClientEntity( i ) );
			if ( !pEntity )
				continue;

			switch ( pEntity->GetClientClass( )->m_ClassID )
			{
				case ClassID_CCSPlayer:
				case ClassID_CBaseAnimating:
				case ClassID_CHEGrenade:
				case ClassID_CFlashbang:
				case ClassID_CSmokeGrenade:
				case ClassID_CDecoyGrenade:
				case ClassID_CIncendiaryGrenade:
				case ClassID_CBaseCSGrenadeProjectile: // projectile flash and he
				case ClassID_CSmokeGrenadeProjectile:
				case ClassID_CDecoyProjectile:
				case ClassID_CMolotovProjectile:
				case ClassID_CChicken:
				case ClassID_CC4:
				case ClassID_CPlantedC4:
				default: ;
			}
		}
	}
}
