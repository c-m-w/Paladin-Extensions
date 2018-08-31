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
		bool PX_API SetHooks( )
		{
			return hkDirectXDevice->HookIndex( uEndScene, reinterpret_cast< void* >( EndScene ) )
				&& hkDirectXDevice->HookIndex( uReset, reinterpret_cast< void* >( Reset ) )
				&& hkClientBase->HookIndex( uFrameStageNotify, reinterpret_cast< void* >( FrameStageNotify ) )
				&& hkClientBase->HookIndex( uCreateMove, reinterpret_cast< void* >( CreateMove ) )
				&& hkClientMode->HookIndex( uDoPostScreenEffects, reinterpret_cast< void* >( DoPostScreenEffects ) )
				&& hkSurface->HookIndex( uLockCursor, reinterpret_cast< void* >( LockCursor ) )
				&& hkPanel->HookIndex( uPaintTraverse, reinterpret_cast< void* >( PaintTraverse ) );
		}

		bool PX_API InitializeHooks( )
		{
			hkDirectXDevice	= new Tools::CHook( pDevice );
			hkClientBase	= new Tools::CHook( pClientBase );
			hkClientMode	= new Tools::CHook( pClientMode );
			hkSurface		= new Tools::CHook( pSurface );
			hkPanel			= new Tools::CHook( pPanel );

			return hkDirectXDevice->Succeeded( )
				&& hkClientBase->Succeeded( )
				&& hkClientMode->Succeeded( )
				&& hkSurface->Succeeded( )
				&& hkPanel->Succeeded( ) ?
				SetHooks( ) 
			: false;
		}

		void PX_API Destruct( )
		{
			delete hkDirectXDevice;
			delete hkClientBase;
			delete hkClientMode;
			delete hkSurface;
			delete hkPanel;
		}

		HRESULT __stdcall EndScene( IDirect3DDevice9* pDeviceParameter )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< end_scene_t >( uEndScene );
			static auto ptrDesiredReturnAddress = 0u;
			const auto ptrReturnAddress = ptr_t( _ReturnAddress( ) );

			if ( !ptrDesiredReturnAddress )
			{
				if ( Tools::FindAddressOrigin( ptrReturnAddress ) == Modules::mOverlay.hModule )
					ptrDesiredReturnAddress = ptrReturnAddress;
			}

			if ( ptrDesiredReturnAddress == ptrReturnAddress )
			{
				IDirect3DStateBlock9* pNewState = nullptr;
				IDirect3DVertexDeclaration9* pVertexDeclaration = nullptr;
				IDirect3DVertexShader9* pVertexShader = nullptr;
				DWORD dwColorWrite, dwSRGBWrite;

				pDevice->CreateStateBlock( D3DSBT_PIXELSTATE, &pNewState );

				px_assert( D3D_OK == pDevice->GetVertexDeclaration( &pVertexDeclaration )
						   && D3D_OK == pDevice->GetVertexShader( &pVertexShader )

						   && D3D_OK == pDevice->GetRenderState( D3DRS_COLORWRITEENABLE, &dwColorWrite )
						   && D3D_OK == pDevice->GetRenderState( D3DRS_SRGBWRITEENABLE, &dwSRGBWrite )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_COLORWRITEENABLE, UINT_MAX )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE, NULL )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO )

						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_MAGFILTER, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_MINFILTER, D3DTADDRESS_WRAP )
						   && D3D_OK == pDevice->SetSamplerState( NULL, D3DSAMP_SRGBTEXTURE, NULL ) );

				Features::Awareness::Draw( );
				Drawing::DrawFigures( );
				UI::Manager::CSGO::OnEndScene( );

				px_assert( D3D_OK == pDevice->SetVertexDeclaration( pVertexDeclaration )
						   && D3D_OK == pDevice->SetVertexShader( pVertexShader )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_COLORWRITEENABLE, dwColorWrite )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE, dwSRGBWrite ) );

				pNewState->Apply( );
				pNewState->Release( );
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

		void __stdcall PaintTraverse( vgui::VPANEL panel, bool forceRepaint, bool allowForce )
		{
			constexpr auto szDesiredPanelName = PX_XOR( "FocusOverlayPanel" );
			static auto fnOriginal = hkPanel->GetOriginalFunction< paint_traverse_t >( uPaintTraverse );
			static auto vpDesiredPanelID = vgui::VPANEL( 0u );

			fnOriginal( pPanel, panel, forceRepaint, allowForce );
			if ( !vpDesiredPanelID && !strcmp( szDesiredPanelName, pPanel->GetName( panel ) ) )
				vpDesiredPanelID = panel;
			if ( vpDesiredPanelID != panel )
				return;

			{
				Tools::OnPaintTraverse( );
			}
		}
	}
}
