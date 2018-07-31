/// User Interface.inl

#pragma once

namespace PX
{
    namespace UI
    {
        namespace Widgets
        {
            namespace
            {
				int fnAscii( const nk_text_edit* box, nk_rune unicode )
				{
					( void )box;
					if ( unicode > 128 )
						return nk_false;
					return nk_true;
				}
                template< typename _t > PX_ABSTRACT_STRUCT IFilterImplementation
                {
					inline static nk_plugin_filter fnFilter = fnAscii;
                    static char* ret( char* szBuffer )
                    {
                        return szBuffer;
                    }
                };

	            int fnDecimal( const nk_text_edit* box, nk_rune unicode )
	            {
					( void )box;
					if ( ( unicode < '0' || unicode > '9' ) && unicode != '-' )
						return nk_false;
					return nk_true;
	            }
                template< > PX_ABSTRACT_STRUCT IFilterImplementation< int >
                {
					inline static nk_plugin_filter fnFilter = fnDecimal;
                    static int ret( char* szBuffer )
                    {
                        return strlen( szBuffer ) ? std::stoi( szBuffer ) : 0;
                    }
                };

				int fnFloat( const nk_text_edit* box, nk_rune unicode )
				{
					( void )box;
					if ( ( unicode < '0' || unicode > '9' ) && unicode != '.' && unicode != '-' )
						return nk_false;
					return nk_true;
				}
                template< > PX_ABSTRACT_STRUCT IFilterImplementation< float >
                {
					inline static nk_plugin_filter fnFilter = fnFloat;
                    static float ret( char* szBuffer )
                    {
                        return strlen( szBuffer ) ? std::stof( szBuffer ) : 0.f;
                    }
                };
            }

            template< typename _t > _t PX_API Inputbox( unsigned uMaxCharacters, char* szBuffer )
            {
				dbg::Assert( iCurrentRowMaxColumns - iCurrentRowUsedColumns > 0 );
				iCurrentRowUsedColumns++;

                if ( HoveringNextWidget( ) )
                    Render::SetCursor( Render::CURSOR_IBEAM );
                EditBox( Manager::pContext, NK_EDIT_FIELD | NK_EDIT_AUTO_SELECT, szBuffer, uMaxCharacters, IFilterImplementation< _t >::fnFilter );
                return IFilterImplementation< _t >::ret( szBuffer );
            }
        }
    }
}
