#pragma once
#include "../Framework.hpp"

namespace Paladin
{
	class CInjection;
	extern CInjection inject;

	class CInjection
	{
	public:
		bool GetElevationState( HANDLE hTarget = 0 )
		{
			HANDLE hTokenTarget;
			TOKEN_ELEVATION teTarget;
			DWORD dwReturnLength = sizeof( TOKEN_ELEVATION );
			if ( OpenProcessToken( hTarget ? hTarget : GetCurrentProcess( ), TOKEN_QUERY, &hTokenTarget ) &&
				 GetTokenInformation( hTokenTarget, TokenElevation, &teTarget, dwReturnLength, &dwReturnLength ) )
			{
				CloseHandle( hTokenTarget );
				return teTarget.TokenIsElevated;
			}
			CloseHandle( hTokenTarget );
			return false;
		}
	};

	CInjection inject;
}
