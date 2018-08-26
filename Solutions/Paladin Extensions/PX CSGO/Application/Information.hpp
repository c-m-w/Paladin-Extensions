/// Interfaces.hpp

#pragma once

namespace PX::Information
{
	extern nlohmann::json jsMemoryInformation;

	bool PX_API InitializeInformation( );

	namespace Memory
	{
		bool PX_API Setup( );

		namespace VirtualTableIndicies
		{
			// Device
			PX_DEF uEndScene = 42u;
			PX_DEF uReset = 16u;

			// Client Base
			PX_DEF uFrameStageNotify = 37u;
			PX_DEF uCreateMove = 22u;

			// Client Mode
			PX_DEF uDoPostScreenEffects = 44u;

			// Surface
			PX_DEF uLockCursor = 67u;

			// CBaseEntity
			PX_DEF uIsPlayer = 152u;
			PX_DEF uIsWeapon = 160u;

			// CBaseCombatWeapon
			PX_DEF uGetInaccuracy = 467u;
			PX_DEF uGetSpread = 436u;
			PX_DEF uUpdateAccuracyPenalty = 468u;
		}

		namespace Offsets
		{
			PX_DEF ptrBombTimer = 0x297C;
			PX_DEF ptrDefuseTimer = 0x2994;
		}
	}
	
	namespace Modules
	{
		PX_SDK std::string strCreateInterfaceName = PX_XOR( "CreateInterface" );
		struct SModule: Types::module_t
		{
			CreateInterfaceFn ciFactory { };

			bool Setup( std::wstring wstrModule );
		};

		bool PX_API Setup( );

		PX_SDK SModule mEngine;
		PX_SDK SModule mClient;
		PX_SDK SModule mDirectX;
		PX_SDK SModule mOverlay;
		PX_SDK SModule mVGUI;
	}

	namespace Pointers
	{
		bool PX_API FindPointers( );

		PX_SDK bool* pSendPackets = nullptr; // Only modify in CreateMove
		PX_SDK CGlobalVarsBase* pGlobalVariables = nullptr;
		PX_SDK CClientState* pClientState = nullptr;

		PX_SDK IDirect3DDevice9* pDevice = nullptr;
		PX_SDK IBaseClientDLL* pClientBase = nullptr;
		PX_SDK IClientMode* pClientMode = nullptr;
		PX_SDK CGlowObjectManager* pGlowObjectManager = nullptr;
		PX_SDK IVEngineClient* pEngineClient = nullptr;
		PX_SDK ISurface* pSurface = nullptr;
		PX_SDK IClientEntityList* pEntityList = nullptr;
	}

	namespace NetworkedVariableManager // http://www.bailopan.net/table_dump.txt
	{
		struct networked_variable_table_t
		{
			Types::cstr_t szName { };
			RecvProp* pProp { };
			Types::ptr_t ptrOffset { };
			std::vector< RecvProp* > vecChildProps;
			std::vector< networked_variable_table_t > vecChildTables;

			networked_variable_table_t( ) = default;
			networked_variable_table_t( Types::cstr_t _szName, RecvProp* _pProp = nullptr, Types::ptr_t _ptrOffset = 0u ):
				szName( _szName ), pProp( _pProp ), ptrOffset( _ptrOffset ) { }
		};

		PX_SDK std::vector< networked_variable_table_t > vecNetworkedVariables { };

		bool PX_API FindNetworkedVariables( );
		Types::ptr_t PX_API FindOffset( Types::cstr_t szTable, Types::cstr_t szVariable );
	}
}

#define PX_NETVAR_REFERENCE( type, name, table, netvar )													\
    type& name() const																						\
	{																										\
        static int ptrOffset = PX::Information::NetworkedVariableManager::FindOffset( table, netvar );		\
        return *reinterpret_cast< type* >( PX::Types::ptr_t( this ) + ptrOffset );							\
    }

#define PX_NETVAR_REFERENCE_OFFSET( type, name, table, netvar, offset )										\
    type& name() const																						\
	{																										\
        static int ptrOffset = PX::Information::NetworkedVariableManager::FindOffset( table, netvar );		\
        return *reinterpret_cast< type* >( PX::Types::ptr_t( this ) + ptrOffset + offset );					\
    }

#define PX_NETVAR_POINTER( type, name, table, netvar )														\
    type* name() const																						\
	{																										\
        static int ptrOffset = PX::Information::NetworkedVariableManager::FindOffset( table, netvar );		\
        return reinterpret_cast< type* >( PX::Types::ptr_t( this ) + ptrOffset );							\
    }

#define PX_NETVAR_POINTER_OFFSET( type, name, table, netvar, offset )										\
    type* name() const																						\
	{																										\
        static int ptrOffset = PX::Information::NetworkedVariableManager::FindOffset( table, netvar );		\
        return reinterpret_cast< type* >( PX::Types::ptr_t( this ) + ptrOffset + offset );					\
    }
