/// Hooks.cpp

#include "PX Precompiled.hpp"
#include "../PX CSGO.hpp"

using namespace PX::Information;
using namespace Memory::VirtualTableIndicies;
using namespace Pointers;

namespace PX
{
	namespace Hooks
	{
		bool PX_API SetHooks( )
		{
			return hkDirectXDevice->HookIndex( uBeginScene, reinterpret_cast< void* >( BeginScene ) )
				&& hkDirectXDevice->HookIndex( uEndScene, reinterpret_cast< void* >( EndScene ) )
				&& hkDirectXDevice->HookIndex( uReset, reinterpret_cast< void* >( Reset ) )
				&& hkClientBase->HookIndex( uFrameStageNotify, reinterpret_cast< void* >( FrameStageNotify ) )
				&& hkClientBase->HookIndex( uCreateMove, reinterpret_cast< void* >( CreateMove ) )
				&& hkClientMode->HookIndex( uDoPostScreenEffects, reinterpret_cast< void* >( DoPostScreenEffects ) )
				&& hkPanel->HookIndex( uPaintTraverse, reinterpret_cast< void* >( PaintTraverse ) )
				&& hkModelRender->HookIndex( uDrawModelExecute, reinterpret_cast< void* >( DrawModelExecute ) )
				&& hkViewRender->HookIndex( uSceneEnd, reinterpret_cast< void* >( SceneEnd ) )
				&& hkClientBase->ResetProtection( )
				&& hkClientMode->ResetProtection( )
				&& hkPanel->ResetProtection( )
				&& hkModelRender->ResetProtection( )
				&& hkViewRender->ResetProtection( );
		}

		bool PX_API InitializeHooks( )
		{
			hkDirectXDevice = new Tools::CStandardHook( pDevice );
			hkClientBase	= new Tools::CTrampolineHook( pClientBase );
			hkClientMode	= new Tools::CTrampolineHook( pClientMode );
			hkPanel			= new Tools::CTrampolineHook( pPanel );
			hkModelRender	= new Tools::CTrampolineHook( pModelRender );
			hkViewRender	= new Tools::CTrampolineHook( pViewRender );

			return hkDirectXDevice->Succeeded( )
				&& hkClientBase->Succeeded( ) && hkClientBase->SetProtection( )
				&& hkClientMode->Succeeded( ) && hkClientMode->SetProtection( )
				&& hkPanel->Succeeded( ) && hkPanel->SetProtection( )
				&& hkModelRender->Succeeded( ) && hkModelRender->SetProtection( )
				&& hkViewRender->Succeeded( ) && hkViewRender->SetProtection( ) ?
				SetHooks( )
				: false;
		}

		void PX_API Destruct( )
		{
			delete hkDirectXDevice;
			delete hkClientBase;
			delete hkClientMode;
			delete hkPanel;
			delete hkModelRender;
			delete hkViewRender;
		}

		HRESULT __stdcall BeginScene( IDirect3DDevice9* pThis )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< begin_scene_t >( uBeginScene );
			static auto ptrDesiredReturnAddress = 0u;
			const auto ptrReturnAddress = ptr_t( _ReturnAddress( ) );

			if ( !ptrDesiredReturnAddress )
			{
				if ( Tools::FindAddressOrigin( ptrReturnAddress ) == Modules::mOverlay.hModule )
					ptrDesiredReturnAddress = ptrReturnAddress;
			}

			if ( ptrDesiredReturnAddress == ptrReturnAddress )
				Features::Awareness::Draw( );

			return fnOriginal( pThis );
		}

		HRESULT __stdcall EndScene( IDirect3DDevice9* pThis )
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

				Drawing::DrawQueue( );
				UI::Manager::CSGO::OnEndScene( );

				px_assert( D3D_OK == pDevice->SetVertexDeclaration( pVertexDeclaration )
						   && D3D_OK == pDevice->SetVertexShader( pVertexShader )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_COLORWRITEENABLE, dwColorWrite )
						   && D3D_OK == pDevice->SetRenderState( D3DRS_SRGBWRITEENABLE, dwSRGBWrite ) );

				pNewState->Apply( );
				pNewState->Release( );
			}

			return fnOriginal( pThis );
		}

		HRESULT __stdcall Reset( IDirect3DDevice9* pThis, D3DPRESENT_PARAMETERS* pParams )
		{
			static auto fnOriginal = hkDirectXDevice->GetOriginalFunction< reset_t  >( uReset );

			{
				UI::Manager::CSGO::OnReset( );
				UI::Manager::OnReset( );
				Drawing::Destruct( );
			}

			const auto hrReset = fnOriginal( pThis, pParams );

			if ( SUCCEEDED( hrReset ) )
			{
				UI::Manager::CSGO::OnSuccessfulReset( pParams->BackBufferWidth, pParams->BackBufferHeight );
				UI::Manager::OnSuccessfulReset( pParams->BackBufferWidth, pParams->BackBufferHeight );
				Drawing::InitializeDrawing( );
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
			const auto pCmd = Tools::GetUserCmd( sequence_number );
			const auto pVerifiedCmd = Tools::GetVerifiedUserCmd( sequence_number );

			if ( nullptr == pLocalPlayer
				 || nullptr == pCmd
				 || pCmd->command_number == 0
				 || nullptr == pVerifiedCmd )
				return;

			{
				Features::Combat::Trigger( pLocalPlayer, pCmd );
				Features::Miscellaneous::AutoJump( pLocalPlayer, pCmd );
			}

			pVerifiedCmd->m_cmd = *pCmd;
			pVerifiedCmd->m_crc = Tools::GetCmdHash( pCmd );
		}

		int __stdcall DoPostScreenEffects( int iUnknown )
		{
			static auto fnOriginal = hkClientMode->GetOriginalFunction< do_post_screen_effects_t >( uDoPostScreenEffects );

			{
				Features::Awareness::GlowEntities( );
			}

			return fnOriginal( pClientMode, iUnknown );
		}

		void __stdcall PaintTraverse( vgui::VPANEL panel, bool forceRepaint, bool allowForce )
		{
			const auto szDesiredPanelName = PX_XOR( "FocusOverlayPanel" );
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

		void __stdcall DrawModelExecute( IMatRenderContext* pContext, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld )
		{
			static auto fnOriginal = hkModelRender->GetOriginalFunction< draw_model_execute_t >( uDrawModelExecute );
			const auto pLocalPlayer = Tools::GetLocalPlayer( );
			auto bShouldOverride = false;

			if( nullptr != pLocalPlayer )
			{
				bShouldOverride = Features::Awareness::OverrideMaterial( pLocalPlayer, pContext, state, pInfo, pCustomBoneToWorld, fnOriginal );
			}

			if ( bShouldOverride )
				pModelRender->ForcedMaterialOverride( nullptr );
			else
				if( pContext && ptr_t( pContext ) != 0xffffffff )
					fnOriginal( pModelRender, pContext, state, pInfo, pCustomBoneToWorld );
		}

		void __stdcall SceneEnd( )
		{
			static auto fnOriginal = hkViewRender->GetOriginalFunction< scene_end_t >( uSceneEnd );
			fnOriginal( pViewRender );
			
			{
				const auto pLocalPlayer = Tools::GetLocalPlayer( );
				if ( nullptr == pLocalPlayer )
					return;
			
				Features::Awareness::RenderEntities( pLocalPlayer );
			}
		}
	}
}
