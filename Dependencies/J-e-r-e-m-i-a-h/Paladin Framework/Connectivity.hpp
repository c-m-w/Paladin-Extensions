#pragma once
#include "Framework.hpp"

namespace Paladin
{
	class CConnectivity;
	extern CConnectivity con;

	class CConnectivity
	{
		std::ifstream ifRegistration( "reg.key" );

		int iUserID;
		std::string strSecretKey;

	public:
		CConnectivity( )
		{
			std::string strBuffer;
			std::getline( ifRegistration, strBuffer );
			iUserID = std::stoi( strBuffer );
			std::getline( ifRegistration, strSecretKey );
		}

	private:
		int GetUniqueID( )
		{
			// Get Unique ID
		}
		int Connect( )
		{
			// Securely connect to server
		}
		void Initialize( )
		{
			// Encrypt information
		}
		
	public:
		int Authenticate( )
		{
			// Connect to server and pass information ( UserID, SecretKey, UniqueID )
		}
		bool Heartbeat( )
		{
			// Call authenticate and confirm with check based on threading
		}
	};

	CConnectivity con;
}
