/// Debug.hpp

#pragma once

namespace Paladin
{
	namespace dbg
	{
		template< typename _Datatype > void Assert( _Datatype );

#if defined( _DEBUG )
#define DBG << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [DBG] "
#define SCS << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [SCS] "
#define WRN << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [WRN] "
#define ERR << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [ERR] "
#define LER << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << " [LER] "
#elif
#define DBG
#define SCS
#define WRN
#define ERR
#define LER
#endif

		class CDebugPrint
		{
#if defined( _DEBUG )
			std::stringstream strsDebugLog;
		public:
			CDebugPrint( );
			CDebugPrint( CDebugPrint && ) = delete;
			CDebugPrint &operator=( const CDebugPrint & ) = delete;
			CDebugPrint &operator=( CDebugPrint && ) = delete;
			~CDebugPrint( );
			CDebugPrint( const CDebugPrint & );
#endif
			template < typename _Datatype > CDebugPrint operator<<( const _Datatype & );
		} extern out;

		constexpr char tab = '\t';
		constexpr char endl = '\n';
		constexpr char quote = '\"';

		extern std::ios_base &( *bin )( std::ios_base & );
		extern std::ios_base &( *oct )( std::ios_base & );
		extern std::ios_base &( *dec )( std::ios_base & );
		extern std::ios_base &( *hex )( std::ios_base & );

		void LastError( );
		void Pause( );
	}
}
