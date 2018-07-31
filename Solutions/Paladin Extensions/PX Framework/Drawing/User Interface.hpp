/// User Interface.hpp

#pragma once

namespace PX
{
    namespace UI
    {
        namespace Manager
        {
			PX_SDK nk_context* pContext;
			PX_SDK Tools::cstr_t szNuklearWindowTitle;

			enum EFont
			{
				FONT_TAHOMA,
				FONT_TAHOMABOLD,
				FONT_ROBOTO,
				FONT_ROBOTOBOLD,
				FONT_ROBOTOSMALL,
				FONT_ROBOTOBOLDSMALL,
				FONT_ENVY,
				FONT_MAX
			};

			void PX_API Initialize( Tools::cstr_t );
			void PX_API OnRelease( );
			void PX_API Resize( unsigned, unsigned );
			bool PX_API OnEvent( HWND, UINT, WPARAM, LPARAM );
			bool PX_API Render( );
			void PX_API SetLayout( );
        }

        namespace Widgets
        {
            enum class EPosition
            {
                LEFT,
                CENTER,
                RIGHT
            };

			enum ERowType
			{
				ROW_DYNAMIC,
				ROW_STATIC,
				ROW_CUSTOM,
				ROW_MAX
			};

			PX_SDK int iCurrentRowUsedColumns, iCurrentRowMaxColumns;

			bool PX_API HoveringNextWidget( );
			nk_flags PX_API EditTextBox( struct nk_context* ctx, nk_flags flags, char* buffer, int max, nk_plugin_filter filter );
			// Creates a header for the window with a title, subtitle and two callbacks for the minimize and close buttons.
			void PX_API Header( Tools::cstr_t, Tools::cstr_t, std::function< void( PX_API )( ) >, std::function< void( PX_API )( ) > );
        	bool PX_API PrimaryTab( Tools::cstr_t, bool );
            bool PX_API SecondaryTab( Tools::cstr_t, bool );
            void PX_API Separator( unsigned char, unsigned char, unsigned char, unsigned, unsigned = 3, bool = false );
            bool PX_API Button( EPosition, Tools::cstr_t, bool );
            void PX_API Checkbox( Tools::cstr_t, unsigned, bool* );

            int PX_API Tabs( unsigned, unsigned, unsigned, unsigned, std::deque< Tools::cstr_t >, unsigned );
            int PX_API Subtabs( unsigned, unsigned, unsigned, unsigned, std::deque< Tools::cstr_t >, unsigned );

            void PX_API BeginGroupbox( unsigned, unsigned, unsigned, unsigned, Tools::cstr_t, unsigned );
            void PX_API EndGroupbox( );

            void PX_API ColorPicker( );
            void PX_API ColorButton( Tools::cstr_t, Tools::byte_t* );

            int PX_API Combobox( unsigned, unsigned, Tools::cstr_t, std::deque< Tools::cstr_t >, unsigned );
            void PX_API ComboboxMulti( unsigned, unsigned, Tools::cstr_t, std::deque< Tools::cstr_t >, std::deque< bool >& );

			template< typename _t > _t PX_API Inputbox( unsigned, char* );

            int PX_API Slider( Tools::cstr_t, char*, int, int, int, unsigned, unsigned, unsigned, unsigned, unsigned );
			float PX_API Slider( Tools::cstr_t, char*, float, float, float, unsigned, unsigned, unsigned, unsigned, unsigned );

            void PX_API BeginRow( unsigned, unsigned, ERowType );

            void PX_API SetRowWidth( float );
            void PX_API Spacing( unsigned = 1 );
            void PX_API VerticalSpacing( unsigned = 5 );
            void PX_API PushCustomRow( unsigned, unsigned, unsigned, unsigned );
        }
    }
}

#include "User Interface.inl"
