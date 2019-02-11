/// Framework Unit Tests.cpp

#include "Precompile.hpp"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"

namespace Framework
{
	TEST_CLASS( Development_Environment )
	{
		TEST_METHOD( Logging ) // todo unit test
		{

		}
	};

	namespace Source_Development_Kit
	{
		namespace Application_Programming_Interface
		{
			TEST_CLASS( Color )
			{
				TEST_METHOD( Color_Structure )
				{
					// test == operator
					{
						color_t clr[ 2 ] {
							{ 0x24, 0x58, 0xA2, 0xCD },
							{ 0x24, 0x58, 0xA2, 0xCD }
						};
						Assert::IsTrue( clr[ 0 ] == clr[ 1 ], L"Equality 1 check failed" );
						Assert::IsTrue( !( clr[ 0 ] != clr[ 1 ] ), L"Equality 2 check failed" );
					}

					// test initialization list
					unsigned char b[ 4 ] { 0xFF, 0xF0, 0xE8, 0xE0 };
					unsigned char ba[ 4 ] { 0xF0, 0xE8, 0xE0, 0xFF };
					color_t clr { 0xE0, 0xE8,0xF0,0xFF };
					{
						Assert::AreEqual( b[ 3 ], clr.r, L"Red check failed" );
						Assert::AreEqual( b[ 2 ], clr.g, L"Green check failed" );
						Assert::AreEqual( b[ 1 ], clr.b, L"Blue check failed" );
						Assert::AreEqual( b[ 0 ], clr.a, L"Alpha check failed" );

						Assert::AreEqual( *reinterpret_cast< unsigned* >( b ), clr.rgba, L"RGBA check failed" );
						Assert::AreEqual( *reinterpret_cast< unsigned* >( ba ), clr.argb, L"ARGB check failed" );

						for ( int z = 0; z < 4; z++ )
							Assert::AreEqual( b[ z ], clr[ z ], L"Array operator check failed" );
						for ( int z = 0; z < 4; z++ )
							Assert::AreEqual( float( b[ z ] ) / 255.f, clr[ float( z ) ], L"Array operator for floats check failed" );

						clr.a = 255;
						Assert::AreEqual( 0.2126 * double( b[ 3 ] ) + 0.7152 * double( b[ 2 ] ) + 0.0722 * double( b[ 1 ] ), clr.luma, L"Luminance 1 check failed" );
						Assert::AreEqual( 0.299 * double( b[ 3 ] ) + 0.587 * double( b[ 2 ] ) + 0.114 * double( b[ 1 ] ), clr.luma601, L"Luminance 2 check failed" );
					}

					// test initialization & assignment with float and data management
					b[ 3 ] = b[ 2 ] = b[ 1 ] = 0xFF;
					b[ 0 ] = 0x00;
					clr.rfl = clr.gfl = clr.bfl = 1.f;
					clr.afl = 0.f;
					{
						const color_t clrFloat { 1.f, 1.f, 1.f };

						Assert::AreEqual( b[ 3 ], clr.r, L"Red 1 check failed" );
						Assert::AreEqual( b[ 2 ], clr.g, L"Green 1 check failed" );
						Assert::AreEqual( b[ 1 ], clr.b, L"Blue 1 check failed" );
						Assert::AreEqual( b[ 0 ], clr.a, L"Alpha 1 check failed" );

						Assert::AreEqual( b[ 3 ], clrFloat.r, L"Red 2 check failed" );
						Assert::AreEqual( b[ 2 ], clrFloat.g, L"Green 2 check failed" );
						Assert::AreEqual( b[ 1 ], clrFloat.b, L"Blue 2 check failed" );
						Assert::AreEqual( unsigned char( 0xFF ), clrFloat.a, L"Alpha 2 check failed" );

						Assert::AreEqual( *reinterpret_cast< unsigned* >( b ), clr.rgba, L"RGBA 2 check failed" );
						b[0 ]=0xff;
						Assert::AreEqual( *reinterpret_cast< unsigned* >( b ), clrFloat.rgba, L"RGBA float check failed" );
						b[ 0 ] = 0x00;

						for ( int z = 0; z < 4; z++ )
							Assert::AreEqual( b[ z ], clr[ z ], L"Array operator 1 check failed" );
						for ( int z = 0; z < 4; z++ )
							Assert::AreEqual( float( b[ z ] ) / 255.f, clr[ float( z ) ], L"Array operator for floats 1 check failed" );

						b[ 0 ] = 0xff;
						for ( int z = 0; z < 3; z++ )
							Assert::AreEqual( b[ z ], clrFloat[ z ], L"Array operator 2 check failed" );
						for ( int z = 0; z < 3; z++ )
							Assert::AreEqual( float( b[ z ] ) / 255.f, clrFloat[ float( z ) ], L"Array operator for floats 2 check failed" );
						b[ 0 ] = 0x00;

						clr.a = 0xff;
						Assert::AreEqual(0.2126 * double( b[ 3 ] ) + 0.7152 * double( b[2 ] ) + 0.0722 * double( b[ 1 ] ), clr.luma, L"Luminance 1 check failed" );
						Assert::AreEqual( 0.299 * double( b[ 3 ] ) + 0.587 * double( b[ 2] ) + 0.114 * double( b[ 1 ] ), clr.luma601, L"Luminance 2 check failed" );
						Assert::AreEqual(0.2126 * double( b[ 3 ] ) + 0.7152 * double( b[2 ] ) + 0.0722 * double( b[ 1 ] ), clrFloat.luma, L"Luminance float 1 check failed" );
						Assert::AreEqual( 0.299 * double( b[ 3 ] ) + 0.587 * double( b[ 2] ) + 0.114 * double( b[ 1 ] ), clrFloat.luma601, L"Luminance float 2 check failed" );
					}
				}

				TEST_METHOD( Color_Sequence )
				{
									// test independent functionality
					{
						const color_t clrStart { 0xC8, 0x00, 0x00 };
						const color_t clrEnd { 0x00, 0x00, 0xC8 };
						Assert::AreEqual( color_t { 0xC8, 0x00, 0x00 }.rgba, CColor::GetGradient( clrStart, clrEnd, 0.00f ).rgba, L"Gradient 1 check failed" );
						Assert::AreEqual( color_t { 0x96, 0x00, 0x32 }.rgba, CColor::GetGradient( clrStart, clrEnd, 0.25f ).rgba, L"Gradient 2 check failed" );
						Assert::AreEqual( color_t { 0x64, 0x00, 0x64 }.rgba, CColor::GetGradient( clrStart, clrEnd, 0.50f ).rgba, L"Gradient 3 check failed" );
						Assert::AreEqual( color_t { 0x32, 0x00, 0x96 }.rgba, CColor::GetGradient( clrStart, clrEnd, 0.75f ).rgba, L"Gradient 4 check failed" );
						Assert::AreEqual( color_t { 0x00, 0x00, 0xC8 }.rgba, CColor::GetGradient( clrStart, clrEnd, 1.00f ).rgba, L"Gradient 5 check failed" );
					}

					// test initialization methods & functionality
					{
						color_t clr[ 2 ] {
							{ rand( ), rand( ), rand( ), rand( ) },
							{ rand( ), rand( ), rand( ), rand( ) }
						};
						moment_t dur[ 2 ] { 1000ull, 500ull };
						// simple init & functionality
						{
							CColor clrseq( clr[ 0 ], dur[ 0 ] );
							Assert::AreEqual( clr[ 0 ].rgba, clrseq[ 0 ].clr.rgba, L"Get color 1 check failed" );
							Assert::AreEqual( dur[ 0 ], clrseq[ 0 ].mmtDuration, L"Get 1 duration check failed" );
							clrseq.PutNewColorSequence( { clr[ 1 ], dur[ 1 ] } );
							Assert::AreEqual( clr[ 0 ].rgba, clrseq[ 0 ].clr.rgba, L"Assign new color check failed" );
							Assert::AreEqual( clr[ 1 ].rgba, clrseq[ 1 ].clr.rgba, L"New color check failed" );
							Assert::AreEqual( dur[ 0 ], clrseq[ 0 ].mmtDuration, L"Assign new duration check failed" );
							Assert::AreEqual( dur[ 1 ], clrseq[ 1 ].mmtDuration, L"New duration check failed" );
							clrseq.DeleteColorSequence( 0 );
							Assert::AreEqual( clr[ 1 ].rgba, clrseq[ 0 ].clr.rgba, L"Color push back check failed" );
							Assert::AreEqual( dur[ 1 ], clrseq[ 0 ].mmtDuration, L"Duration push back check failed" );
						}
						// multi init
						{
							CColor clrseq( { { clr[ 0 ], dur[ 0 ] }, { clr[ 1 ],dur[ 1 ] } } );
							Assert::AreEqual( clr[ 0 ].rgba, clrseq[ 0 ].clr.rgba, L"Get color 2 check failed" );
							Assert::AreEqual( clr[ 1 ].rgba, clrseq[ 1 ].clr.rgba, L"Get color 3 check failed" );
							Assert::AreEqual( dur[ 0 ], clrseq[ 0 ].mmtDuration, L"Get duration 2 check failed" );
							Assert::AreEqual( dur[ 1 ], clrseq[ 1 ].mmtDuration, L"Get duration 3 check failed" );
						}
					}
				}
			};

			TEST_CLASS( Connectivity )
			{ };

			TEST_CLASS( Cryptography )
			{ };

			TEST_CLASS( Filesystem )
			{ };
			
			TEST_CLASS( Utilities )
			{
				TEST_METHOD( String_Cast )
				{
					const auto sz = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0";
					const auto wsz = L"`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0";
					const auto bsz = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0"_b;

					const std::string str = sz;
					const std::wstring wstr = wsz;
					const std::bstring bstr = bsz;

					// const char *
					{
						Assert::IsTrue( string_cast< std::string >( sz ) == sz, L"\"""const char *""\" to \"std::string\" cast check failed)" );
						Assert::IsTrue( string_cast< std::wstring >( sz ) == wsz, L"\"""const char *""\" to \"std::wstring\" cast check failed)" );
						Assert::IsTrue( string_cast< std::bstring >( sz ) == bsz, L"\"""const char *""\" to \"std::bstring\" cast check failed)" );
					}
					// const wchar_t *
					{
						Assert::IsTrue( string_cast< std::string >( wsz ) == sz, L"\"""const wchar_t *""\" to \"std::string\" cast check failed)" );
						Assert::IsTrue( string_cast< std::wstring >( wsz ) == wsz, L"\"""const wchar_t *""\" to \"std::wstring\" cast check failed)" );
						Assert::IsTrue( string_cast< std::bstring >( wsz ) == bsz, L"\"""const wchar_t *""\" to \"std::bstring\" cast check failed)" );
					}
					// const unsigned char *
					{
						Assert::IsTrue( string_cast< std::string >( bsz ) == sz, L"\"""const unsigned *""\" to \"std::string\" cast check failed)" );
						Assert::IsTrue( string_cast< std::wstring >( bsz ) == wsz, L"\"""const unsigned *""\" to \"std::wstring\" cast check failed)" );
						Assert::IsTrue( string_cast< std::bstring >( bsz ) == bsz, L"\"""const unsigned *""\" to \"std::bstring\" cast check failed)" );
					}
					// std::string
					{
						Assert::IsTrue( string_cast< std::string >( str ) == sz, L"\"""std::string""\" to \"std::string\" cast check failed)" );
						Assert::IsTrue( string_cast< std::wstring >( str ) == wsz, L"\"""std::string""\" to \"wcstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::bstring >( str ) == bsz, L"\"""std::string""\" to \"std::bstring\" cast check failed)" );
					}
					// std::wstring
					{
						Assert::IsTrue( string_cast< std::string >( wstr ) == sz, L"\"""std::wstring""\" to \"std::string\" cast check failed)" );
						Assert::IsTrue( string_cast< std::wstring >( wstr ) == wsz, L"\"""std::wstring""\" to \"std::wstring\" cast check failed)" );
						Assert::IsTrue( string_cast< std::bstring >( wstr ) == bsz, L"\"""std::wstring""\" to \"std::bstring\" cast check failed)" );
					}
					// std::bstring
					{
						Assert::IsTrue( string_cast< std::string >( bstr ) == sz, L"\"""std::bstring""\" to \"std::string\" cast check failed)" );
						Assert::IsTrue( string_cast< std::wstring >( bstr ) == wsz, L"\"""std::bstring""\" to \"std::wstring\" cast check failed)" );
						Assert::IsTrue( string_cast< std::bstring >( bstr ) == bsz, L"\"""std::bstring""\" to \"std::bstring\" cast check failed)" );
					}
				}
			};
		};

		namespace Toolkits
		{
			TEST_CLASS( Authentication )
			{ };

			TEST_CLASS( Graphical_User_Interface )
			{ };

			TEST_CLASS( Memory_Manager )
			{ };

			TEST_CLASS( Resource_Manager )
			{ };

			TEST_CLASS( System_Information )
			{
				TEST_METHOD( Get_Hardware )
				{
					//Assert::AreEqual( AUTH.GetHardware( )[ "cpu" ].get< std::string >( ).c_str( ), "hello" );
				}
			};
		};
	}
}
