#pragma once

namespace dbg
{
	class CDebugging;
	extern CDebugging out;
	extern const char endl;

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

	void ler( );
}
