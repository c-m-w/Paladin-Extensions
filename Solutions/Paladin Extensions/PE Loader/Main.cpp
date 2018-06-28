/// Main.cpp

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_IMPLEMENTATION

#include "Main.hpp"

bool CUserInterface::DrawUserInterface( )
{
	nk_style_set_font( pContext, &pRoboto->handle );
	if ( nk_begin( pContext, szNuklearWindowTitle, nk_rect( 0, 0, float( uWindowWidth ), float( uWindowHeight ) ),
				   NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_CLOSABLE | NK_WINDOW_NO_SCROLLBAR )
		 && HandleWindowInput( ) )
	{
		auto b = false;
		nk_layout_row_dynamic( pContext, 20, 1 );
		nk_button_label( pContext, "MEN????" );
		if ( pContext->last_widget_state & ( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER ) && !b )
		{
			b = true;
			SetActiveCursor( HAND );
		}
		nk_layout_row_dynamic( pContext, 30, 1 );
		static auto sz = static_cast< char* >( malloc( 16 ) );
		nk_edit_string_zero_terminated( pContext, NK_EDIT_BOX | NK_EDIT_AUTO_SELECT | NK_EDIT_NO_HORIZONTAL_SCROLL | NK_TEXT_EDIT_SINGLE_LINE, sz, 16, nk_filter_ascii );
		if ( pContext->last_widget_state & ( NK_WIDGET_STATE_ACTIVE | NK_WIDGET_STATE_HOVER ) && !b )
		{
			b = true;
			SetActiveCursor( IBEAM );
		}
	}
	else
		bShouldDrawInterface = false; // Top right 'x' button has been clicked.
	nk_end( pContext );

	RenderUserInterface( );
	return bShouldDrawInterface;
}

void OnLaunch( )
{
	dbg::out M_DBG << "This is output only visible if compiled in debug" << dbg::endl;
	dbg::out M_ERR << "This is error output" << dbg::endl;

	dbg::out << string_cast< std::string >( L"This is a wide string, printed through casting means" ) << dbg::endl;
	dbg::out << std::wstring( L"This is a wide string, still printable through normal means" ) << dbg::endl;
	dbg::out << L"This is a wide string, still printable through normal means" << dbg::endl;
	const wchar_t *wsz = L"This is a wide string, still printable through normal means";
	dbg::out << wsz << dbg::endl;
	dbg::out << M_XOR( "This is an encrypted string, still readable on runtime" ) << dbg::endl;

	unsigned u[ ]
	{
		500, 500
	};
	ui = new CUserInterface( "men", u, L"MEN_ASS" );
	ui->InitializeUserInterface( );

	while ( ui->DrawUserInterface( ) )
		Wait/*< std::chrono::milliseconds >*/( 1 );
	ui->Shutdown( );
}
