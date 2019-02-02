/// Connectivity.hpp

#pragma once

class CConnectivity: public IBase
{
private:

	bool Initialize( ) override;

	CURL *pConnection;

public:

	CConnectivity( ) = default;

	void Shutdown( ) override;
} inline _Connection;
