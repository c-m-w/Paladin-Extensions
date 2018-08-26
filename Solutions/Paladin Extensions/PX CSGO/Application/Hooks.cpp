/// Hooks.cpp

#include "../PX CSGO.hpp"

#define PX_PRINT( var ) std::cout << #var << ": " << var << std::endl;
#define PX_PRINT_ENUM( var, enum_type ) std::cout << std::string( #var ).substr( 0, std::string( #var ).find_last_of( '[' ) ) << "[ " << enum_type << " ]: " << var << std::endl;

using namespace PX::Information;
using namespace Memory::VirtualTableIndicies;
using namespace Pointers;

namespace PX
{
	namespace Hooks
	{
		std::vector< Tools::CHook* > vecHookPointers { };

		bool PX_API SetHooks( )
		{
			return hkDirectXDevice->HookIndex( uEndScene, reinterpret_cast< void* >( EndScene ) )
				&& hkDirectXDevice->HookIndex( uReset, reinterpret_cast< void* >( Reset ) )
				&& hkClientBase->HookIndex( uFrameStageNotify, reinterpret_cast< void* >( FrameStageNotify ) )
				&& hkClientBase->HookIndex( uCreateMove, reinterpret_cast< void* >( CreateMove ) )
				&& hkClientMode->HookIndex( uDoPostScreenEffects, reinterpret_cast< void* >( DoPostScreenEffects ) )
				&& hkSurface->HookIndex( uLockCursor, reinterpret_cast< void* >( LockCursor ) );
		}

		bool PX_API InitializeHooks( )
		{
			hkDirectXDevice = new Tools::CHook( pDevice );
			hkClientBase = new Tools::CHook( pClientBase );
			hkClientMode = new Tools::CHook( pClientMode );
			hkSurface = new Tools::CHook( pSurface );

			vecHookPointers.emplace_back( hkDirectXDevice );
			vecHookPointers.emplace_back( hkClientBase );
			vecHookPointers.emplace_back( hkSurface );

			return hkDirectXDevice->Succeeded( )
				&& hkClientBase->Succeeded( )
				&& hkClientMode->Succeeded( )
				&& hkSurface->Succeeded( ) ? 
				SetHooks( ) 
			: false;
		}

		void PX_API Destruct( )
		{
			for each( auto& hkPointer in vecHookPointers )
				delete hkPointer;
		}

		HRESULT __stdcall EndScene( IDirect3DDevice9* pDeviceParameter )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< end_scene_t >( uEndScene );

			{
				UI::Manager::CSGO::OnEndScene( ptr_t( _ReturnAddress( ) ) );
			}

			return fnOriginal( pDeviceParameter );
		}

		HRESULT __stdcall Reset( IDirect3DDevice9* pDeviceParameter, D3DPRESENT_PARAMETERS* pParams )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< reset_t  >( uReset );

			{
				UI::Manager::CSGO::OnReset( );
				UI::Manager::OnReset( );
			}

			const auto hrReset = fnOriginal( pDeviceParameter, pParams );

			if ( SUCCEEDED( hrReset ) )
			{
				UI::Manager::CSGO::OnSuccessfulReset( pParams->BackBufferWidth, pParams->BackBufferHeight );
				UI::Manager::OnSuccessfulReset( pParams->BackBufferWidth, pParams->BackBufferHeight );
			}

			return hrReset;
		}

		void __stdcall FrameStageNotify( ClientFrameStage_t cfsStage )
		{
			static auto fnOriginal = hkClientBase->GetOriginalFunction< frame_stage_notify_t >( uFrameStageNotify );
			return fnOriginal( cfsStage );
		}

		void __stdcall CreateMove( int sequence_number, float input_sample_frametime, bool active )
		{
			static auto fnOriginal = hkClientBase->GetOriginalFunction< create_move_t >( uCreateMove );
			fnOriginal( sequence_number, input_sample_frametime, active );

			const auto pLocalPlayer = Tools::GetLocalPlayer( );
			if ( nullptr == pLocalPlayer )
				return;
			
			std::cout << "Local Player Health: " << pLocalPlayer->m_iHealth( ) << std::endl;
		}

		int __stdcall DoPostScreenEffects( int iUnknown )
		{
			static auto fnOriginal = hkClientMode->GetOriginalFunction< do_post_screen_effects_t >( uDoPostScreenEffects );

			{
				Features::Awareness::GlowEntities( );
			}

			return fnOriginal( pClientMode, iUnknown );
		}

		void __fastcall LockCursor( ISurface* pThisClass, void* edx )
		{
			static auto fnOriginal = hkSurface->GetOriginalFunction< lock_cursor_t >( uLockCursor );

			if ( Render::bShouldRender )
				return pSurface->UnlockCursor( );
			return fnOriginal( pThisClass );
		}
	}
}
