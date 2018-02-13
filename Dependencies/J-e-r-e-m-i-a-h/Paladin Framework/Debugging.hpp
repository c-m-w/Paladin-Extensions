#pragma once

namespace dbg
{
	const char endl = '\n';

#define DBG << " DBG "
#define SCS << " SCS "
#define WRN << " WRN "
#define ERR << " ERR "
#define LER << " LER "

#ifdef _DEBUG

	class CDebugging
	{
		std::ofstream ofLogFile;
		HANDLE hConsole;
	public:
		CDebugging( );
		CDebugging( CDebugging & );
		CDebugging( CDebugging && ) = delete;
		CDebugging &operator=( CDebugging & ) = delete;
		CDebugging &operator=( CDebugging && ) = delete;
		~CDebugging( );
		template < typename xDatatype > CDebugging operator<<( const xDatatype & );
	};

#else

	class CDebugging {
		template < typename xDatatype > CDebugging operator<<( const xDatatype & );
	};

#endif

	extern CDebugging out;
}
