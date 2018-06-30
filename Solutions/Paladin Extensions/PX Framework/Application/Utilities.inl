/// Utilities.inl

#pragma once

namespace PX
{
    namespace Utilities
    {
        template< typename _t, int i > vector_t< _t, i >::vector_t( std::initializer_list< _t > vecInitialData )
        {
            if ( vecInitialData.size( ) <= i )
                return;

            int j = 1;
            for ( auto vecSubData : vecInitialData )
            {
                _Data[ j ] = vecSubData;
                j++;
            }
        }

        template< typename _t, int i > _t vector_t< _t, i >::operator[ ]( int iIndex ) const
        {
            return _Data[ iIndex ];
        }

        template< typename _t, int i > vector_t< _t, i > vector_t< _t, i >::operator+( const vector_t& rhs ) const
        {                                                                                              
            _Data += rhs._Data;                                                                        
            return *this;                                                                              
        }                                                                                              
        template< typename _t, int i > vector_t< _t, i > vector_t< _t, i >::operator-( const vector_t& rhs ) const
        {                                                                                              
            _Data -= rhs._Data;                                                                        
            return *this;                                                                              
        }                                                                                              
        template< typename _t, int i > vector_t< _t, i > vector_t< _t, i >::operator*( const vector_t& rhs ) const
        {                                                                                              
            _Data *= rhs._Data;                                                                        
            return *this;                                                                              
        }                                                                                              
        template< typename _t, int i > vector_t< _t, i > vector_t< _t, i >::operator/( const vector_t& rhs ) const
        {
            _Data /= rhs._Data;
            return *this;
        }
        template< typename _t, int i > vector_t< _t, i >& vector_t< _t, i >::operator+=( const vector_t& rhs )
        {                                                 
            *this = *this + rhs;                          
            return *this;                                 
        }                                                 
        template< typename _t, int i > vector_t< _t, i >& vector_t< _t, i >::operator-=( const vector_t& rhs )
        {                                                                                                
            *this = *this - rhs;                                                                         
            return *this;                                                                                
        }                                                                                                
        template< typename _t, int i > vector_t< _t, i >& vector_t< _t, i >::operator*=( const vector_t& rhs )
        {                                                                                                
            *this = *this * rhs;                                                                         
            return *this;                                                                                
        }                                                                                                
        template< typename _t, int i > vector_t< _t, i >& vector_t< _t, i >::operator/=( const vector_t& rhs )
        {
            *this = *this / rhs;
            return *this;
        }

        template< class _Child > template< typename ... _Arg > _Child& ISingleton<_Child >::Get( _Arg ... _Args )
        {
            static _Child _ChildClassObject( _Args ... );
            return _ChildClassObject;
        }

        template< typename _t > moment_t GetMoment( )
        {
            return std::chrono::duration_cast< _t >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
        }
        template< typename _t > void Wait( moment_t mmtWaitLength )
        {
            std::this_thread::sleep_for( _t( mmtWaitLength ) );
        }

        // INFO: Deduces traits and uses matching casting function of trait
        template< typename > PX_ABSTRACT_STRUCT IStringTraits;
        template< > PX_ABSTRACT_STRUCT IStringTraits< std::wstring >
        {
            typedef wchar_t char_trait_t;

            static int ByteConvert( const int iCodePage, LPCWSTR wszData, int iDataLength, LPSTR szBuffer, int iBufferSize )
            {
                return WideCharToMultiByte( iCodePage, 0, wszData, iDataLength, szBuffer, iBufferSize, nullptr, nullptr );
            }
        };
        template< > PX_ABSTRACT_STRUCT IStringTraits< std::string >
        {
            typedef char char_trait_t;

            static int ByteConvert( const int iCodePage, LPCSTR szData, int iDataLength, LPWSTR wszBuffer, int iBufferSize )
            {
                return MultiByteToWideChar( iCodePage, 0, szData, iDataLength, wszBuffer, iBufferSize );
            }
        };

        // INFO: Differentiates casting from like or unlike string types 
        template< typename _To, typename _From > PX_ABSTRACT_STRUCT IStringCastImplementation
        {
            static _To Cast( const _From& _Source )
            {
                int iLength = IStringTraits< _From >::ByteConvert( CP_ACP, _Source.data( ), _Source.length( ), nullptr, 0 );
                if ( iLength == 0 )
                    return _To( );

                std::vector< typename IStringTraits< _To >::char_trait_t > _strBuffer( iLength );
                IStringTraits< _From >::ByteConvert( CP_ACP, _Source.data( ), _Source.length( ), &_strBuffer[ 0 ], iLength );

                return _To( _strBuffer.begin( ), _strBuffer.end( ) );
            }
        };
        template< typename _From > PX_ABSTRACT_STRUCT IStringCastImplementation< _From, _From >
        {
            static const _From& Cast( const _From& _Source )
            {
                return _Source;
            }
        };

        // INFO: Interface for C-Style string casting
        template< typename > PX_ABSTRACT_STRUCT IStringTypeOfCharacter;
        template< > PX_ABSTRACT_STRUCT IStringTypeOfCharacter< const char* >
        {
            typedef std::string wrap_t;
        };
        template< > PX_ABSTRACT_STRUCT IStringTypeOfCharacter< const wchar_t* >
        {
            typedef std::wstring wrap_t;
        };

        template< typename _To, typename _From > _To string_cast( const _From& _Source )
        {
            return IStringCastImplementation< _To, _From >::Cast( _Source );
        }
        template< typename _To, typename _From > _To string_cast( _From* _Source )
        {
            return IStringCastImplementation< _To, typename IStringTypeOfCharacter< const _From* >::wrap_t >::Cast( _Source );
        }
        template< typename _To, typename _From > _To* string_cast( const _From& _Source )
        {
            return IStringCastImplementation< _To, _From >::Cast( _Source ).c_str( );
        }
        template< typename _To, typename _From > _To* string_cast( _From* _Source )
        {
            return IStringCastImplementation< _To, typename IStringTypeOfCharacter< const _From* >::wrap_t >::Cast( _Source ).c_str( );
        }
    }
}
