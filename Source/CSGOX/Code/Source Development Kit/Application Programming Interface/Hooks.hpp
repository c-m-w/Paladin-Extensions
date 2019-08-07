/// Hooks.hpp

#pragma once

class CHooks: public IBase
{
private:

	bool Initialize( ) override;
	void Uninitialize( ) override;

public:

	class CDeviceHook: public IBase, public CVirtualTableHook
	{
	private:

		bool Initialize( ) override;
		void Uninitialize( ) override;

		static inline void *pReset = nullptr,
			*pBeginScene = nullptr,
			*pEndScene = nullptr;

	public:

		CDeviceHook( ) = default;
		~CDeviceHook( ) = default;

		HRESULT __stdcall Reset( D3DPRESENT_PARAMETERS *pPresentationParameters );
		HRESULT __stdcall BeginScene( );
		HRESULT __stdcall EndScene( );
	} _Device;

	class CClientModeHook: public IBase, public CVirtualTableHook
	{
	private:

		bool Initialize( ) override;
		void Uninitialize( ) override;

		static inline void *pCreateMove  = nullptr;

	public:

		CClientModeHook( ) = default;
		~CClientModeHook( ) = default;

		void __stdcall CreateMove( int iSequence, float flInputSampleFrametime, bool bActive );
	} _ClientMode;
} extern _Hooks;
