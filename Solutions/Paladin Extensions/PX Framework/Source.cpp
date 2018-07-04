/// Source.cpp
// For testing

#include "PX Framework.hpp"

void Example( )
{
    PX::Render::BeginRender( );

    const wchar_t* wsz = L"Hi";
    const char* sz = "Hi";

    PX_XOR( wsz );
    PX_XOR( sz );

    PX::Cryptography::Encrypt( std::string( "hi" ), std::string( "hi" ) );
}
