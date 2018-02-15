#pragma once

namespace dbg
{
	class CDebugging;
	extern CDebugging out;
	extern constexpr auto dec;
	extern constexpr auto hex;
	extern constexpr auto endl;
	extern constexpr auto tab;
	extern constexpr auto quote;
	extern constexpr auto money;

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
