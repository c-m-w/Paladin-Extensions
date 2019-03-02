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

	public:

		CDeviceHook( ) = default;
		~CDeviceHook( ) = default;

		HRESULT __stdcall Reset( D3DPRESENT_PARAMETERS *pPresentationParameters );
		HRESULT __stdcall BeginScene( );
		HRESULT __stdcall EndScene( );
	} _Device;
} extern _Hooks;
