/// User Interface.inl

#pragma once

namespace PX::UI::Widgets
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
		template< typename _t > struct SFilterImplementation
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
		template< > struct SFilterImplementation< int >
		{
			inline static nk_plugin_filter fnFilter = fnDecimal;
			static int ret( char* szBuffer )
			{
				return strlen( szBuffer ) && strcmp( szBuffer, "-" ) ? std::stoi( szBuffer ) : 0;
			}
		};

		int fnFloat( const nk_text_edit* box, nk_rune unicode )
		{
			( void )box;
			if ( unicode == 190 )
				unicode = '.';
			if ( ( unicode < '0' || unicode > '9' ) && unicode != '.' && unicode != '-' )
				return nk_false;
			return nk_true;
		}
		template< > struct SFilterImplementation< float >
		{
			inline static nk_plugin_filter fnFilter = fnFloat;
			static float ret( char* szBuffer )
			{
				return strlen( szBuffer ) && strcmp( szBuffer, "-" ) && strcmp( szBuffer, "." ) ? std::stof( szBuffer ) : 0.f;
			}
		};
	}

	template< typename _t > _t PX_API Inputbox( unsigned uMaxCharacters, char* szBuffer )
	{
		px_assert( iCurrentRowMaxColumns - iCurrentRowUsedColumns > 0 );
		iCurrentRowUsedColumns++;

		if ( HoveringNextWidget( ) )
			SetWidgetActive( Render::CURSOR_IBEAM );
		EditTextBox( Manager::pContext, NK_EDIT_FIELD | NK_EDIT_AUTO_SELECT, szBuffer, uMaxCharacters, SFilterImplementation< _t >::fnFilter );
		return SFilterImplementation< _t >::ret( szBuffer );
	}
}
