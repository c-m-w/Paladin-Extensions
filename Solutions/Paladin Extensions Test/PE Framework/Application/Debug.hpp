/// Debug.hpp

#pragma once

namespace Paladin
{
    namespace dbg
    {
        template< typename _Datatype > void Assert( _Datatype );

        /**
        * \brief Sets the console text print color with flags from constructor parameter
        */
        struct SetPrintColor
        {
            WORD m_wDesiredAttributes;
            explicit SetPrintColor( const WORD );
        };

        /**
         * \brief Outputs debugging information if and only if compiled as debug to debug log and console.
         */
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
            template< typename _Datatype > CDebugPrint operator<<( const _Datatype & );
            template< > CDebugPrint operator<<< SetPrintColor > ( const SetPrintColor & );
            template< > CDebugPrint operator<<< std::wstring >( const std::wstring & );
            template< > CDebugPrint operator<<< const wchar_t * >( const wchar_t *const & );
        } static out;

        constexpr auto tab = '\t';
        constexpr auto endl = '\n';
        constexpr auto quote = '\"';

        /**
         * \brief Changes stream data output into binary format.
         */
        static std::ios_base &bin( std::ios_base & );
		/**
		 * \brief Changes stream data output into octal format.
		 */
        static std::ios_base &oct( std::ios_base & );
		/**
		 * \brief Changes stream data output into decimal format.
		 */
		static std::ios_base &dec( std::ios_base & );
		/**
		 * \brief Changes stream data output into hexidecimal format.
		 */
		static std::ios_base &hex( std::ios_base & );

        /**
         * \brief Outputs last error code in textual format.
         */
        void LastError( );
    }
}

/**
 * \brief Optional output indicators
 */
#if defined( _DEBUG )
#define M_DBG << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << \
	    Paladin::dbg::SetPrintColor( FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE ) << " [DBG] " << \
	    Paladin::dbg::SetPrintColor( ~FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
#define M_SCS << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << \
	    Paladin::dbg::SetPrintColor( FOREGROUND_INTENSITY | ~FOREGROUND_RED | FOREGROUND_GREEN | ~FOREGROUND_BLUE  ) << " [SCS] " << \
	    Paladin::dbg::SetPrintColor( ~FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
#define M_WRN << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << \
	    Paladin::dbg::SetPrintColor( FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | ~FOREGROUND_BLUE ) << " [WRN] " << \
	    Paladin::dbg::SetPrintColor( ~FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
#define M_ERR << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << \
	    Paladin::dbg::SetPrintColor( FOREGROUND_INTENSITY | FOREGROUND_RED | ~FOREGROUND_GREEN | ~FOREGROUND_BLUE ) << " [ERR] " << \
	    Paladin::dbg::SetPrintColor( ~FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
#define M_LER << std::put_time( std::localtime( new time_t { std::time( nullptr ) } ), "[%H:%M:%S]" ) << \
	    Paladin::dbg::SetPrintColor( ~FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | ~FOREGROUND_BLUE ) << " [LER] " << \
	    Paladin::dbg::SetPrintColor( ~FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE )
#elif not defined( _DEBUG)
#define M_DBG
#define M_SCS
#define M_WRN
#define M_ERR
#define M_LER
#endif

#include "Debug.tpp"
