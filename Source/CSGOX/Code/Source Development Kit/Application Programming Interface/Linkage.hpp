/// Link.hpp

#pragma once

#include "../../CSGO SDK/Code/Inclusion.hpp"

// todo get most stuff from server @not jeremy
/** \brief Will link the regions of memory from our reconstruction of the SDK to the live runtime memory */
namespace Linkage
{
	bool SetupLinkage( );
	void RemoveLinkage( );

	namespace Modules
	{
		bool LinkModules( );

		enum
		{
			MODULES_SHADERAPIDX9,

			MODULES_INTERFACEABLE_MODULES,
			// bin
			MODULES_ENGINE = MODULES_INTERFACEABLE_MODULES,
			MODULES_VGUI2,
			MODULES_VGUIMATSURFACE,

			// csgo/bin
			MODULES_CLIENT,

			MODULES_MAX
		};

		inline const char* szModuleNames[ MODULES_MAX ]
		{
			ENC( "shaderapidx9.dll" ),

			ENC( "engine.dll" ),
			ENC( "vgui2.dll" ),
			ENC( "vguimatsurface.dll" ),

			ENC( "client_panorama.dll" )
		};

		inline HMODULE hEngineBase,
			hVGUI2Base,
			hVGUIMatSurfaceBase,

			hClientBase,

			hShaderAPIDX9;



		inline std::array< std::reference_wrapper< HMODULE >, MODULES_MAX > hBases
		{
			hEngineBase,
			hVGUI2Base,
			hVGUIMatSurfaceBase,
			hClientBase,
			hShaderAPIDX9
		};
	}

	namespace Interfaces
	{
		bool LinkInterfaces( );

		inline CreateInterfaceFn fnCreateInterface[ Modules::MODULES_MAX ];

		enum
		{
			INTERFACES_DEVICE,
			INTERFACES_CLIENT_BASE,
			INTERFACES_CLIENT_MODE,
			INTERFACES_PANEL,
			INTERFACES_MODEL_RENDER,
			INTERFACES_VIEW_RENDER,
			INTERFACES_ENGINE_SOUND,
			INTERFACES_MAX
		};

		struct
		{
			const char* strPattern;
			decltype( Modules::MODULES_MAX ) enumModule;
		} inline _InterfacesContext[ INTERFACES_MAX ];

		inline IDirect3DDevice9* pDevice = nullptr;
		inline IBaseClientDLL* pClientBase = nullptr;
		inline IClientMode* pClientMode = nullptr;
		inline IPanel* pPanel = nullptr;
		inline IVModelRender* pModelRender = nullptr;
		inline IVRenderView* pEngineRenderView = nullptr;
		inline IEngineSound* pEngineSound = nullptr;

		inline std::array< std::reference_wrapper< void* >, INTERFACES_MAX > pInterfaces
		{
			*reinterpret_cast< void** >( &pDevice ),
			*reinterpret_cast< void** >( &pClientBase ),
			*reinterpret_cast< void** >( &pClientMode ),
			*reinterpret_cast< void** >( &pPanel ),
			*reinterpret_cast< void** >( &pModelRender ),
			*reinterpret_cast< void** >( &pEngineRenderView ),
			*reinterpret_cast< void** >( &pEngineSound )
		};
	}

	namespace Indices
	{
		enum
		{
			INDICES_ZFOO,
			INDICES_ZBAR,
			INDICES_MAX
		};
		inline std::size_t zFoo,
			zBar;

		inline std::array< std::reference_wrapper< std::size_t >, INDICES_MAX > pIndices
		{
			zFoo,
			zBar
		};
	}

	namespace Offsets
	{
		enum
		{
			OFFSETS_DFOO,
			OFFSETS_DBAR,
			asdf,
			fdsa
			,fdsaff,
			fdsza,
			fdsaa,
			OFFSETS_MAX
		};
		inline std::ptrdiff_t dFoo = 1,
			dBar = 1;

		inline std::array< std::reference_wrapper< std::ptrdiff_t>, OFFSETS_MAX > pOffsets
		{
			dFoo,
			dBar,
			dFoo,
			dBar,
			dFoo,
			dBar,
			dFoo,
		};
	}

	namespace Hooks
	{
		bool SetupHooks( );
		void DestroyHooks( );

		enum
		{
			HOOKS_DIRECTX_DEVICE,
			HOOKS_CLIENT_BASE,
			HOOKS_CLIENT_MODE,
			HOOKS_PANEL,
			HOOKS_MODEL_RENDER,
			HOOKS_VIEW_RENDER,
			HOOKS_ENGINE_SOUND,
			HOOKS_MAX
		};

		inline CVirtualTableHook hkDirectXDevice;
		HRESULT __stdcall BeginScene( IDirect3DDevice9* pThis );
		HRESULT __stdcall EndScene( IDirect3DDevice9* pThis );
		HRESULT __stdcall Reset( IDirect3DDevice9* pThis, D3DPRESENT_PARAMETERS* pParams );

		inline CVirtualTableHook hkClientBase;
		void __stdcall CreateMove( int iSequenceNumber, float iInputSampleFrame, bool bActive );
		void __stdcall FrameStageNotify( ClientFrameStage_t cfsStage );

		inline CVirtualTableHook hkClientMode;
		void __stdcall OverrideView( CViewSetup* pViewSetup );
		float __stdcall GetViewmodelFOV( );
		int __stdcall DoPostScreenEffects( int iUnknown );

		inline CVirtualTableHook hkPanel;
		void __stdcall PaintTraverse( vgui::VPANEL panel, bool forceRepaint, bool allowForce );

		inline CVirtualTableHook hkModelRender;
		void __stdcall DrawModelExecute( IMatRenderContext* pContext, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld );

		inline CVirtualTableHook hkViewRender;
		void __stdcall SceneEnd( );
		void __stdcall SceneBegin( );
		void __cdecl m_nSequence( const CRecvProxyData* pData, void* pStructure, void* pOutput );

		inline CVirtualTableHook hkEngineSound;
		void __stdcall EmitSoundATT( IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, CUtlVector< Vector >* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, void* pUnknown );

		inline std::array< std::reference_wrapper< CVirtualTableHook >, HOOKS_MAX > pHooks
		{
			hkDirectXDevice,
			hkClientBase,
			hkClientMode,
			hkPanel,
			hkModelRender,
			hkViewRender,
			hkEngineSound,
		};
	}
}
