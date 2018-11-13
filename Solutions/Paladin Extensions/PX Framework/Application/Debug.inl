/// Debug.inl

#pragma once

namespace PX::dbg
{
	namespace
	{
		PX_SDK std::ofstream ofLogFile( "C:/debug.log" );
		PX_SDK bool bNotFirstPrint;
	}

	template< typename _t > PX_INL SDebugStream & PX_API SDebugStream::operator<<( const _t &_Log )
	{
		if ( !bNotFirstPrint )
		{
			bNotFirstPrint = true;
			std::cout << "[OPN] Begin new logging session";
			ofLogFile << "[OPN] Begin new logging session";
		}
		std::cout << _Log;
		ofLogFile << _Log;
		std::cout.flush( );
		ofLogFile.flush( );
		return *this;
	}
}
