/// User Interface.hpp
// TODO: document @Cole
#pragma once

namespace PX
{
    namespace UI
    {
        namespace Manager
        {
            PX_SDK const char* szWindowTitle = "Paladin Extensions";
            PX_SDK const char* szApplicationTitle = static_cast< char* >( malloc( 32 ) );

            PX_SDK nk_context* pContext;
            PX_SDK nk_font_atlas* pAtlas;
            PX_SDK struct nk_font *pTahoma, *pTahomaBold, *pRoboto, *pRobotoBold, *pRobotoSmall, *pRobotoBoldSmall;
            PX_SDK struct nk_rect recComboboxWindowBounds;

            PX_SDK Render::ECursor curCurrent;
        }

        namespace Widgets
        {
            enum class EPosition
            {
                LEFT,
                CENTER,
                RIGHT
            };
            enum class ERowType
            {
                DYNAMIC,
                STATIC,
                CUSTOM
            } PX_SDK rowLastRowType;

            PX_SDK struct nk_rect recLastWidgetLocation;
            PX_SDK const char *szColorPickerSubject;
            PX_SDK BYTE* pActiveEditColor = nullptr;
			PX_SDK int iCurrentRowUsedColumns, iCurrentRowMaxColumns;

            bool PX_API Header( const char*, const char*, unsigned );
            bool PX_API PrimaryTab( const char*, bool );
            bool PX_API SecondaryTab( const char*, bool );
            void PX_API Separator( unsigned char, unsigned char, unsigned char, unsigned, unsigned = 3, bool = false );
            bool PX_API Button( EPosition, const char*, bool );
            void PX_API Checkbox( const char*, unsigned, bool* );

            int PX_API Tabs( unsigned, unsigned, unsigned, unsigned, std::deque< const char* >, unsigned );
            int PX_API Subtabs( unsigned, unsigned, unsigned, unsigned, std::deque< const char* >, unsigned );

            void PX_API BeginGroupbox( unsigned, unsigned, unsigned, unsigned, const char*, unsigned );
            void PX_API EndGroupbox( );

            void PX_API ColorPicker( );
            void PX_API ColorButton( const char*, BYTE* );

            int PX_API Combobox( unsigned, unsigned, const char*, std::deque< const char* >, unsigned );
            void PX_API ComboboxMulti( unsigned, unsigned, const char *, std::deque< const char* >, std::deque< bool >& );

			template< typename _t > _t PX_API Inputbox( unsigned, char * );
			template< > int PX_API Inputbox< int >( unsigned, char * );
			template< > float PX_API Inputbox< float >( unsigned, char * );
			template< > char *PX_API Inputbox< char * >( unsigned, char * );

			template< typename _t > _t PX_API Slider( const char *, char *, _t, _t, _t, unsigned, unsigned, unsigned, unsigned, unsigned );
			template< > float PX_API Slider< float >( const char *, char *, float, float, float, unsigned, unsigned, unsigned, unsigned, unsigned );
			template< > int PX_API Slider< int >( const char *, char *, int, int, int, unsigned, unsigned, unsigned, unsigned, unsigned );

            template< ERowType > void PX_API NewRow( unsigned, );

            void PX_API SetRowWidth( float );
            void PX_API Spacing( unsigned = 1 );
            void PX_API VerticalSpacing( unsigned = 5 );
            void PX_API PushCustomRow( unsigned, unsigned, unsigned, unsigned );
            void PX_API EndRow( );
        }
    }
}

#include "User Interface.inl"
