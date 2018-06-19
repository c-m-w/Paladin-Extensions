/// Utilities.cpp

#include "../Framework.hpp"

namespace Paladin
{
	template< typename _Desired, typename _Current > _Desired string_cast( _Current _CurrentString )
	{
		auto lambda_caster = [ ]( auto _str )
		{
			if ( typeid( _str ) == typeid( std::string ) )
			{
				std::wstring wstr;
				wstr.resize( MultiByteToWideChar( CP_ACP, 0, _str.c_str( ), _str.length( ) + 1, nullptr, 0 ) );
				MultiByteToWideChar( CP_ACP, 0, _str.c_str( ), _str.length( ) + 1, &wstr[ 0 ], wstr.size( ) );
				return wstr;
			}
			else if ( typeid( _str ) == typeid( std::wstring ) )
			{
				std::string str;
				str.resize( WideCharToMultiByte( CP_ACP, 0, _str.c_str( ), _str.length( ) + 1, nullptr, 0, nullptr, nullptr ) );
				WideCharToMultiByte( CP_ACP, 0, _str.c_str( ), _str.length( ) + 1, &str[ 0 ], str.size( ), nullptr, nullptr );
				return str;
			}
			else
			{
				throw std::exception( XOR( "Attempted to cast unknown string type" ) );
			}
		};

		if ( typeid( _Current ) == typeid( std::string ) && typeid( _Desired ) == typeid( std::wstring ) ||
			 typeid( _Current ) == typeid( std::wstring ) && typeid( _Desired ) == typeid( std::string ) )
		{
			return lambda_caster( _CurrentString );
		}

		if ( typeid( _Current ) == typeid( std::string ) && typeid( _Desired ) == typeid( const wchar_t * ) ||
			 typeid( _Current ) == typeid( std::wstring ) && typeid( _Desired ) == typeid( const char * ) )
		{
			return lambda_caster( _CurrentString ).c_str( );
		}

		if ( typeid( _Current ) == typeid( const char * ) && typeid( _Desired ) == typeid( std::wstring ) )
		{
			return lambda_caster( std::string( _CurrentString ) );
		}

		if ( typeid( _Current ) == typeid( const wchar_t * ) && typeid( _Desired ) == typeid( std::string ) )
		{
			return lambda_caster( std::wstring( _CurrentString ) );
		}

		if ( typeid( _Current ) == typeid( const char * ) && typeid( _Desired ) == typeid( const wchar_t * ) )
		{
			return lambda_caster( std::string( _CurrentString ) ).c_str( );
		}

		if ( typeid( _Current ) == typeid( const wchar_t * ) && typeid( _Desired ) == typeid( const char * ) )
		{
			return lambda_caster( std::wstring( _CurrentString ) ).c_str( );
		}

		throw std::exception( XOR( "Attempted to cast unknown string type" ) );
	}
}
