/// Hooks.cpp

#include "../PX CSGO.hpp"

#define PX_PRINT( var ) std::cout << #var << ": " << var << std::endl;
#define PX_PRINT_ENUM( var, enum_type ) std::cout << std::string( #var ).substr( 0, std::string( #var ).find_last_of( '[' ) ) << "[ " << enum_type << " ]: " << var << std::endl;

using namespace PX::VirtualTableIndicies;
using namespace PX::Information;
using namespace Interfaces;

namespace PX
{
	namespace Hooks
	{
		bool PX_API SetHooks( )
		{
			return hkDirectXDevice->HookIndex( uEndScene, reinterpret_cast< void* >( EndScene ) )
				&& hkDirectXDevice->HookIndex( uReset, reinterpret_cast< void* >( Reset ) )
				&& hkDirectXDevice->HookIndex( uPresent, reinterpret_cast< void* >( Present ) )
				&& hkSurface->HookIndex( uLockCursor, reinterpret_cast< void* >( LockCursor ) );
		}

		bool PX_API InitializeHooks( )
		{
			hkDirectXDevice = new Tools::CHook( pDevice );
			hkClientBase = new Tools::CHook( pClientBase );
			hkSurface = new Tools::CHook( pSurface );

			return hkDirectXDevice->Succeeded( )
				&& hkClientBase->Succeeded( )
				&& hkSurface->Succeeded( ) ? SetHooks( ) : false;
		}

		HRESULT __stdcall EndScene( IDirect3DDevice9* pDeviceParameter )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< Types::endscene_t >( uEndScene );

			//std::cout << "EndScene has been called." << std::endl;

			{
				UI::Manager::CSGO::OnEndScene( Types::ptr_t( _ReturnAddress( ) ) );
			}

			return fnOriginal( pDeviceParameter );
		}

		HRESULT __stdcall Reset( IDirect3DDevice9* pDeviceParameter, D3DPRESENT_PARAMETERS* pParams )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< Types::reset_t  >( uReset );
			static auto iOldWindowWidth = -1, iOldWindowHeight = -1;

			//std::cout << "Reset has been called." << std::endl;

			{
				UI::Manager::CSGO::bCreatedTextures = false;
				UI::Manager::OnReset( );
			}

			const auto hrReset = fnOriginal( pDeviceParameter, pParams );

			if ( SUCCEEDED( hrReset ) )
			{
				UI::Manager::OnSuccessfulReset( );
				UI::Manager::CSGO::bCreatedTextures = true;
			}

			return hrReset;
		}

		HRESULT __stdcall Present( IDirect3DDevice9* pDeviceParameter, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< Types::present_t >( uPresent );

			//std::cout << "Present has been called." << std::endl;

			return fnOriginal( pDeviceParameter, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
		}

		void __fastcall LockCursor( ISurface* pThisClass, void* edx )
		{
			static auto fnOriginal = hkSurface->GetOriginalFunction< Types::lockcursor_t >( uLockCursor );

			if ( Render::bShouldRender )
				return pSurface->UnlockCursor( );
			return fnOriginal( pThisClass );
		}
	}
}
