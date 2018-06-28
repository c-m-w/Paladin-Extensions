#pragma once

namespace Paladin
{ 
	template< typename _Datatype > moment_t GetMoment( )
	{
		return std::chrono::duration_cast< _Datatype >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
	}

    template< typename _Datatype > struct SStringTraits;

    template< > struct SStringTraits< std::string >
    {
        typedef char char_trait_t;

        static int ByteConvert( const int iCodePage, LPCSTR szData, int iDataLength, LPWSTR wszBuffer, int iBufferSize )
        {
            return MultiByteToWideChar( iCodePage, 0, szData, iDataLength, wszBuffer, iBufferSize );
        }
    };

    template< > struct SStringTraits< std::wstring >
    {
        typedef wchar_t char_trait_t;

        static int ByteConvert( const int iCodePage, LPCWSTR wszData, int iDataLength, LPSTR szBuffer, int iBufferSize )
        {
            return WideCharToMultiByte( iCodePage, 0, wszData, iDataLength, szBuffer, iBufferSize, nullptr, nullptr );
        }
    };

    template< typename _To, typename _From > struct SStringCastImplementation
    {
        static _To Cast( const _From &_Source )
        {
            int iLength = SStringTraits< _From >::ByteConvert( CP_ACP, _Source.data( ), _Source.length( ), nullptr, 0 );
            if ( iLength == 0 )
                return _To( );

            std::vector< typename SStringTraits< _To >::char_trait_t > _strBuffer( iLength );
            SStringTraits< _From >::ByteConvert( CP_ACP, _Source.data( ), _Source.length( ), &_strBuffer[ 0 ], iLength );

            return _To( _strBuffer.begin( ), _strBuffer.end( ) );
        }
    };

    template< typename _ChildClass > template< typename ... _Argument > _ChildClass &ISingleton< _ChildClass >::Get( _Argument ... _Arguments )
    {
        static _ChildClass _ChildClassObject( _Arguments... );
        return _ChildClassObject;
    }

    template< typename _To, typename _From > _To string_cast( const _From &_Source )
    {
        return SStringCastImplementation< _To, _From >::Cast( _Source );
    }

    template< typename _Datatype > struct SStringTypeOfCharacter;

    template< > struct SStringTypeOfCharacter< const char * >
    {
        typedef std::string wrap_t;
    };

    template< > struct SStringTypeOfCharacter< const wchar_t * >
    {
        typedef std::wstring wrap_t;
    };

    template< typename _To, typename _From > _To string_cast( _From *_Source )
    {
        return SStringCastImplementation< _To, typename SStringTypeOfCharacter< const _From * >::wrap_t >::Cast( _Source );
    }
}
