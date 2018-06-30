/// Source.cpp
// For testing

#include "PX Framework.hpp"

void Example( )
{
    // nk_button_label( new nk_context, new char ); // INACCESSIBLE
    // PX::Render::Button( ); // INACCESSIBLE

    const wchar_t* wsz = L"Hi";
    const char* sz = "Hi";

    PX_XOR( wsz );
    PX_XOR( sz );
}
