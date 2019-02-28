/// Link.hpp

#pragma once

#include "../../CSGO SDK/Code/Inclusion.hpp"

// todo get most stuff from server
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
			D3D9,

			INTERFACEABLE_MODULES,
			// bin
			ENGINE = INTERFACEABLE_MODULES,
			VGUI2,
			VGUIMATSURFACE,

			// csgo/bin
			CLIENT,

			MODULES_MAX
		};

		inline const char* szModuleNames[ MODULES_MAX ]
		{
			ENC( "d3d9.dll" ),

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
			DEVICE,
			INTERFACES_MAX
		};

		struct
		{
			const char* strPattern;
			decltype( Modules::MODULES_MAX ) enumModule;
		} inline _InterfacesContext[ INTERFACES_MAX ];

		inline IDirect3DDevice9* pDevice = nullptr;

		inline std::array< std::reference_wrapper< void * >, INTERFACES_MAX > pInterfaces
		{
			*reinterpret_cast< void ** >( &pDevice )
		};
	}

	namespace Indices
	{
		enum
		{
			ZFOO,
			ZBAR,
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
			DFOO,
			DBAR,
			OFFSETS_MAX
		};
		inline std::ptrdiff_t dFoo,
			dBar;

		inline std::array< std::reference_wrapper< std::ptrdiff_t>, OFFSETS_MAX > pOffsets
		{
			dFoo,
			dBar
		};
	}

	namespace Hooks
	{
		bool SetupHooks( );
		void DestroyHooks( );

		inline CImportHook hkDirectXDevice;
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
	}
}
