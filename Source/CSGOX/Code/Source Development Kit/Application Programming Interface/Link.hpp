/// Link.hpp

#pragma once

#include "../../CSGO SDK/Code/Inclusion.hpp"

// todo get most stuff from server @not biohazard
/** \brief Will link the regions of memory from our reconstruction of the SDK to the live runtime memory */
class CLink: public IBase
{
public:
	enum EModules
	{
		// bin
		ENGINE,
		VGUI2,
		VGUIMATSURFACE,

		// csgo/bin
		CLIENT,

		SHADERAPIDX9,

		MODULES_MAX
	};

	const char* szModuleNames[ MODULES_MAX ]
	{
		ENC( "engine.dll" ),
		ENC( "vgui2.dll" ),
		ENC( "vguimatsurface.dll" ),

		ENC( "client_panorama.dll" ),

		ENC( "shaderapidx9.dll" )
	};

	HMODULE hEngineBase,
		hVGUI2Base,
		hVGUIMatSurfaceBase,

		hClientBase,
	
		hShaderAPIDX9;

	// C++ Standard §8.3.2/4: There shall be no references to references, **no arrays of references**, and no pointers to references.
	// suck my dick, C++. i always find a way.	
	std::array< HMODULE&, MODULES_MAX > hBases
	{
		hEngineBase,
		hVGUI2Base,
		hVGUIMatSurfaceBase,
		hClientBase,
		hShaderAPIDX9
	};

	CreateInterfaceFn fnCreateInterface[ MODULES_MAX ];

	// Interfaces
	enum EInterfaces
	{
		DEVICE,
		INTERFACES_MAX
	};

	struct SInterfaceContext
	{
		const char* strPattern;
		EModules enumModule;
	} _InterfacesContext[ INTERFACES_MAX ];
	

	inline static void* pDevice = nullptr;

	std::array< void*&, INTERFACES_MAX > pInterfaces
	{
		pDevice
	};
	

	// Indices	
	inline static std::size_t zFoo = 0,
		zBar = 0;
	

	// Offsets
	inline static std::ptrdiff_t dFoo = 0,
		dBar = 0;
	

	// Hooks
	/*CImportHook*/CVirtualTableHook hkDirectXDevice;
	HRESULT __stdcall BeginScene( IDirect3DDevice9* pThis );
	HRESULT __stdcall EndScene( IDirect3DDevice9* pThis );
	HRESULT __stdcall Reset( IDirect3DDevice9* pThis, D3DPRESENT_PARAMETERS* pParams );

	CVirtualTableHook hkClientBase;
	void __stdcall CreateMove( int iSequenceNumber, float iInputSampleFrame, bool bActive );
	void __stdcall FrameStageNotify( ClientFrameStage_t cfsStage );

	CVirtualTableHook hkClientMode;
	void __stdcall OverrideView( CViewSetup* pViewSetup );
	float __stdcall GetViewmodelFOV( );
	int __stdcall DoPostScreenEffects( int iUnknown );

	CVirtualTableHook hkPanel;
	void __stdcall PaintTraverse( vgui::VPANEL panel, bool forceRepaint, bool allowForce );

	CVirtualTableHook hkModelRender;
	void __stdcall DrawModelExecute( IMatRenderContext* pContext, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld );

	CVirtualTableHook hkViewRender;
	void __stdcall SceneEnd( );
	void __stdcall SceneBegin( );
	void __cdecl m_nSequence( const CRecvProxyData* pData, void* pStructure, void* pOutput );

	CVirtualTableHook hkEngineSound;
	void __stdcall EmitSoundATT( IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, CUtlVector< Vector >* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, void* pUnknown );
	

	bool Initialize( ) override;
	void Uninitialize( ) override;
} inline _Link;
