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
                template< typename _t > PX_ABSTRACT_STRUCT IFilterImplementation
                {
                    inline static nk_plugin_filter fnFilter = nk_filter_ascii;
                    static char* ret( char* szBuffer )
                    {
                        return szBuffer;
                    }
                };
                template< > PX_ABSTRACT_STRUCT IFilterImplementation< int >
                {
                    inline static nk_plugin_filter fnFilter = nk_filter_decimal;
                    static int ret( char* szBuffer )
                    {
                        return strlen( szBuffer ) ? std::stoi( szBuffer ) : 0;
                    }
                };
                template< > PX_ABSTRACT_STRUCT IFilterImplementation< float >
                {
                    inline static nk_plugin_filter fnFilter = nk_filter_float;
                    static float ret( char* szBuffer )
                    {
                        return strlen( szBuffer ) ? std::stof( szBuffer ) : 0.f;
                    }
                };
            }

            template< typename _t > _t PX_API Inputbox( unsigned uMaxCharacters, char* szBuffer )
            {
                auto rcBounds = nk_widget_bounds( Manager::pContext );
                if ( nk_input_is_mouse_prev_hovering_rect( &Manager::pContext->input, rcBounds ) )
                    Render::SetCursor( Render::IBEAM );
                nk_edit_string_zero_terminated( Manager::pContext, NK_EDIT_FIELD | NK_EDIT_AUTO_SELECT, szBuffer, uMaxCharacters, IFilterImplementation< _t >::fnFilter );
                return IFilterImplementation< _t >::ret( szBuffer );
            }

            template< ERowType > void PX_API NewRow( unsigned, unsigned )
            {
                
            }

            template< ERowType > void PX_API BeginRow( unsigned, unsigned )
            {
                
            }
        }
    }
}
