#pragma once

namespace dbg
{
	class CDebugging;
	extern CDebugging out;
	constexpr auto endl = std::endl;
	constexpr auto tab = '\t';
	constexpr auto quote = '\"';
	constexpr auto hex = std::hex;
	constexpr auto dec = std::dec;

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
		CDebugging( CDebugging & );
		template < typename xDatatype > CDebugging operator<<( const xDatatype & );
	};

#endif

	void ler( );
}
