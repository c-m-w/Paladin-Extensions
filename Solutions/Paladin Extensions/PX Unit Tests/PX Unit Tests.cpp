/// PX Unit Tests.cpp

#include "PX Precompiled.hpp"

#pragma warning( push, 0 )
#pragma warning( disable: ALL_CODE_ANALYSIS_WARNINGS )
#include "CppUnitTest.h"
#pragma warning( pop )

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define PX_USE_NAMESPACES
#include "../PX Framework/PX Framework.hpp"

__LineInfo lInfo( L"", "", 0 );

#define PX_ASSERT_INFO &( lInfo = __LineInfo( L"PX Unit Tests.cpp", __func__, __LINE__ ) )

namespace PX::UnitTests
{
	namespace GlobalTools
	{
		str_t GetFileData( wcstr_t wsz )
		{
			auto pResource = _wfopen( wsz, L"r" );
			if ( nullptr == pResource )
				return { };

			fseek( pResource, 0, SEEK_END );
			const auto lSize = ftell( pResource );
			rewind( pResource );

			str_t strData;
			strData.resize( lSize );
			fread( &strData[ 0 ], 1, lSize, pResource );

			fclose( pResource );
			return strData;
		}
	}

	namespace Framework
	{
		namespace Application
		{
			TEST_CLASS( Types )
			{
			public:
				TEST_METHOD( StringTypes )
				{
					auto bstrszcmp = [ ]( bstr_t bstr, bcstr_t bsz ) -> bool
					{
						bool b = bstr == bsz;
						std::size_t z = 0;
						for each ( auto by in bstr )
						{
							if ( !b )
								return false;
							b &= by == bsz[ z ];
							z++;
						}
						return b;
					};

					{
						bstr_t bstr = ( unsigned char * )"\x12\x16";
						bstr_t bstr2 = ( unsigned char * )"\x12\x16";
						bstr_t bstr3 = bstr2;

						Assert::IsTrue( bstr == bstr, L"bstr self equality check failed", PX_ASSERT_INFO );
						Assert::IsTrue( bstr == bstr2, L"bstr same equality check failed", PX_ASSERT_INFO );
						Assert::IsTrue( bstr == bstr3, L"bstr copy equality check failed", PX_ASSERT_INFO );

						Assert::IsTrue( bstr.c_str( ) == bstr, L"bstr self cstr equality check failed", PX_ASSERT_INFO );
						Assert::IsTrue( bstr.c_str( ) == bstr2, L"bstr same cstr equality check failed", PX_ASSERT_INFO );
						Assert::IsTrue( bstr3.c_str( ) == bstr, L"bstr copy cstr equality check failed", PX_ASSERT_INFO );
					}

					{
						byte b[ ] = { 'X'_b, u'X'_b, U'X'_b, L'X'_b };
						bstr_t bstr = bstr_t( "X\0"_b ) + u'X'_b + U'X'_b + L'X'_b;

						bcstr_t bsz[ ] = { "ABCabc123!@#\0"_b, u"ABCabc123!@#\0"_b, U"ABCabc123!@#\0"_b, L"ABCabc123!@#\0"_b };
						bstr_t bstrs[ ] = { "ABCabc123!@#\0"_b, u"ABCabc123!@#\0"_b, U"ABCabc123!@#\0"_b, L"ABCabc123!@#\0"_b };

						for ( std::size_t z = 0; z < 4; z++ )
						{
							Assert::IsTrue( b[ z ] == bstr[ z ], L"bstr operator''b check failed", PX_ASSERT_INFO );
							Assert::IsTrue( bstrszcmp( bstrs[ z ], bsz[ z ] ), L"bstr operator\"\"b check failed", PX_ASSERT_INFO );
						}
					}
				}

				TEST_METHOD( Color )
				{
					// test == operator
					{
						color_t clr[ 2 ] {
							{ 0x24, 0x58, 0xA2, 0xCD },
							{ 0x24, 0x58, 0xA2, 0xCD }
						};
						Assert::IsTrue( clr[ 0 ] == clr[ 1 ], L"Equality check failed", PX_ASSERT_INFO );
						Assert::IsTrue( !( clr[ 0 ] != clr[ 1 ] ), L"Equality check failed", PX_ASSERT_INFO );
					}

					// test initialization with ptr and data management
					byte_t b[ 4 ] { 0xE0, 0xE8, 0xF0, 0xFF };
					color_t clr { ptr_t( b ) };
					{
						Assert::AreEqual( b[ 0 ], clr.r, L"Red check failed", PX_ASSERT_INFO );
						Assert::AreEqual( b[ 1 ], clr.g, L"Green check failed", PX_ASSERT_INFO );
						Assert::AreEqual( b[ 2 ], clr.b, L"Blue check failed", PX_ASSERT_INFO );
						Assert::AreEqual( b[ 3 ], clr.a, L"Alpha check failed", PX_ASSERT_INFO );

						Assert::AreEqual( *reinterpret_cast< unsigned* >( b ), clr.Hex, L"Hex check failed", PX_ASSERT_INFO );

						for ( int z = 0; z < 4; z++ )
							Assert::AreEqual( b[ z ], clr[ z ], L"Array operator check failed", PX_ASSERT_INFO );
						for ( int z = 0; z < 4; z++ )
							Assert::AreEqual( float( b[ z ] ) / 255.f, clr[ float( z ) ], L"Array operator for floats check failed", PX_ASSERT_INFO );

						Assert::AreEqual( byte_t( 0.2126 * double( b[ 0 ] ) + 0.7152 * double( b[ 1 ] ) + 0.0722 * double( b[ 2 ] ) ), clr.Luminance, L"Luminance check failed", PX_ASSERT_INFO );
					}

					// test initialization & assignment with float and data management
					b[ 0 ] = b[ 1 ] = b[ 2 ] = 0xFF;
					b[ 3 ] = 0x00;
					clr.rfl = clr.gfl = clr.bfl = 1.f;
					clr.afl = 0.f;
					{
						const color_t clrFloat { 1.f, 1.f, 1.f };

						Assert::AreEqual( b[ 0 ], clr.r, L"Red check failed", PX_ASSERT_INFO );
						Assert::AreEqual( b[ 1 ], clr.g, L"Green check failed", PX_ASSERT_INFO );
						Assert::AreEqual( b[ 2 ], clr.b, L"Blue check failed", PX_ASSERT_INFO );
						Assert::AreEqual( b[ 3 ], clr.a, L"Alpha check failed", PX_ASSERT_INFO );

						Assert::AreEqual( b[ 0 ], clrFloat.r, L"Red check failed", PX_ASSERT_INFO );
						Assert::AreEqual( b[ 1 ], clrFloat.g, L"Green check failed", PX_ASSERT_INFO );
						Assert::AreEqual( b[ 2 ], clrFloat.b, L"Blue check failed", PX_ASSERT_INFO );
						Assert::AreEqual( byte_t( 0xFF ), clrFloat.a, L"Alpha check failed", PX_ASSERT_INFO );

						Assert::AreEqual( *reinterpret_cast< unsigned* >( b ), clr.Hex, L"Hex check failed", PX_ASSERT_INFO );
						Assert::AreEqual( *reinterpret_cast< unsigned* >( b ), clrFloat.Hex >> 8, L"Hex check failed", PX_ASSERT_INFO );

						for ( int z = 0; z < 4; z++ )
							Assert::AreEqual( b[ z ], clr[ z ], L"Array operator check failed", PX_ASSERT_INFO );
						for ( int z = 0; z < 4; z++ )
							Assert::AreEqual( float( b[ z ] ) / 255.f, clr[ float( z ) ], L"Array operator for floats check failed", PX_ASSERT_INFO );

						for ( int z = 0; z < 3; z++ )
							Assert::AreEqual( b[ z ], clrFloat[ z ], L"Array operator check failed", PX_ASSERT_INFO );
						for ( int z = 0; z < 3; z++ )
							Assert::AreEqual( float( b[ z ] ) / 255.f, clrFloat[ float( z ) ], L"Array operator for floats check failed", PX_ASSERT_INFO );

						Assert::AreEqual( byte_t( 0.2126 * double( b[ 0 ] ) + 0.7152 * double( b[ 1 ] ) + 0.0722 * double( b[ 2 ] ) ), clr.Luminance, L"Luminance check failed", PX_ASSERT_INFO );
						Assert::AreEqual( byte_t( 0.2126 * double( b[ 0 ] ) + 0.7152 * double( b[ 1 ] ) + 0.0722 * double( b[ 2 ] ) ), clrFloat.Luminance, L"Luminance check failed", PX_ASSERT_INFO );
					}
				}

				TEST_METHOD( ColorSequence )
				{
					// test independent functionality
					{
						const color_t clrStart { 0xC8, 0x00, 0x00 };
						const color_t clrEnd { 0x00, 0x00, 0xC8 };
						Assert::AreEqual( color_t { 0xC8, 0x00, 0x00 }.Hex, color_sequence_t::GetGradient( clrStart, clrEnd, 0.00f ).Hex, L"Gradient check failed", PX_ASSERT_INFO );
						Assert::AreEqual( color_t { 0x96, 0x00, 0x32 }.Hex, color_sequence_t::GetGradient( clrStart, clrEnd, 0.25f ).Hex, L"Gradient check failed", PX_ASSERT_INFO );
						Assert::AreEqual( color_t { 0x64, 0x00, 0x64 }.Hex, color_sequence_t::GetGradient( clrStart, clrEnd, 0.50f ).Hex, L"Gradient check failed", PX_ASSERT_INFO );
						Assert::AreEqual( color_t { 0x32, 0x00, 0x96 }.Hex, color_sequence_t::GetGradient( clrStart, clrEnd, 0.75f ).Hex, L"Gradient check failed", PX_ASSERT_INFO );
						Assert::AreEqual( color_t { 0x00, 0x00, 0xC8 }.Hex, color_sequence_t::GetGradient( clrStart, clrEnd, 1.00f ).Hex, L"Gradient check failed", PX_ASSERT_INFO );
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
							color_sequence_t clrseq( clr[ 0 ], dur[ 0 ] );
							Assert::AreEqual( clr[ 0 ].Hex, clrseq.GetColor( 0 ).Hex, L"Get color check failed", PX_ASSERT_INFO );
							Assert::AreEqual( dur[ 0 ], clrseq.GetDuration( 0 ), L"Get duration check failed", PX_ASSERT_INFO );
							clrseq.PutNewColorSequence( clr[ 1 ], dur[ 1 ] );
							Assert::AreEqual( clr[ 0 ].Hex, clrseq.GetColor( 0 ).Hex, L"Assign new color check failed", PX_ASSERT_INFO );
							Assert::AreEqual( clr[ 1 ].Hex, clrseq.GetColor( 1 ).Hex, L"New color check failed", PX_ASSERT_INFO );
							Assert::AreEqual( dur[ 0 ], clrseq.GetDuration( 0 ), L"Assign new duration check failed", PX_ASSERT_INFO );
							Assert::AreEqual( dur[ 1 ], clrseq.GetDuration( 1 ), L"New duration check failed", PX_ASSERT_INFO );
							clrseq.DeleteColorSequence( 0 );
							Assert::AreEqual( clr[ 1 ].Hex, clrseq.GetColor( 0 ).Hex, L"Color push back check failed", PX_ASSERT_INFO );
							Assert::AreEqual( dur[ 1 ], clrseq.GetDuration( 0 ), L"Duration push back check failed", PX_ASSERT_INFO );
						}
						// multi init
						{
							color_sequence_t clrseq( clr, dur, 2 );
							Assert::AreEqual( clr[ 0 ].Hex, clrseq.GetColor( 0 ).Hex, L"Get color check failed", PX_ASSERT_INFO );
							Assert::AreEqual( clr[ 1 ].Hex, clrseq.GetColor( 1 ).Hex, L"Get color check failed", PX_ASSERT_INFO );
							Assert::AreEqual( dur[ 0 ], clrseq.GetDuration( 0 ), L"Get duration check failed", PX_ASSERT_INFO );
							Assert::AreEqual( dur[ 1 ], clrseq.GetDuration( 1 ), L"Get duration check failed", PX_ASSERT_INFO );
						}
					}
				}
				// todo: @cole tests for post_data_t, links_t, extensions_t, vertex_t, drawing_t, line_t, polygon_t, text_t, module_t
			};

			TEST_CLASS( Tools )
			{
			public:
				TEST_METHOD( TimeToDate )
				{
					Assert::AreEqual( "Never", PX::Tools::TimeToDate( 0ull ).c_str( ), "Time to date check failed", PX_ASSERT_INFO );
					// todo: test 1st - 29th
				}

				TEST_METHOD( GetMoment )
				{
					// format compile time
					tm tmCompileTime { 0 };
					{
						//char szWeekDay[ 4 ];
						char szMonth[ 4 ];
						sscanf( __TIMESTAMP__, "%s %s %d %d:%d:%d %d",
								&/*szWeekDay*/szMonth, &szMonth, &tmCompileTime.tm_mday,
								&tmCompileTime.tm_hour, &tmCompileTime.tm_min, &tmCompileTime.tm_sec,
								&tmCompileTime.tm_year );
						szMonth[ 3 ] = '\0';
						static const char szWeekDays[ ] = "SunMonTueWedThuFriSat";
						static const char szMonths[ ] = "JanFebMarAprMayJunJulAugSepOctNovDec";
						tmCompileTime.tm_year -= 1900;
						//tmCompileTime.tm_wday = ( strstr( szWeekDays, szWeekDay ) - szWeekDays ) / 3;
						tmCompileTime.tm_mon = ( strstr( szMonths, szMonth ) - szMonths ) / 3;
						tmCompileTime.tm_isdst = -1;
						tmCompileTime.tm_yday = 0;
					}
					const auto tmTime = mktime( &tmCompileTime );
					Assert::IsTrue( tmTime != -1, L"mktime check failed", PX_ASSERT_INFO );
					const auto ulTimeSinceCompilation = unsigned long( PX::Tools::GetMoment( ) / 10000000ull - tmTime );
					Assert::IsTrue( ulTimeSinceCompilation > 0ul, L"GetMoment check failed", PX_ASSERT_INFO );

					// check with run time
					Sleep( 3000 );
					const auto ulChangeInTime = unsigned long( time( nullptr ) - ( ulTimeSinceCompilation + tmTime ) );
					Assert::IsTrue( 4 >= ulChangeInTime && ulChangeInTime >= 2, L"GetMoment check failed", PX_ASSERT_INFO );
				}

				TEST_METHOD( Pause )
				{
					auto mmt = PX::Tools::GetMoment( );
					PX::Tools::Pause( 0 ); // shouldn't take more than 5 microseconds
					Assert::IsTrue( PX::Tools::GetMoment( ) - mmt <= 50ull, L"Pause 0 check failed", PX_ASSERT_INFO );

					mmt = PX::Tools::GetMoment( );
					PX::Tools::Pause( 1 ); // shouldn't take more than 1.5 milliseconds or less than .5 milliseconds
					Assert::IsTrue( 5000ull <= PX::Tools::GetMoment( ) - mmt && PX::Tools::GetMoment( ) - mmt <= 15000ull, L"Pause 1 check failed", PX_ASSERT_INFO );

					mmt = PX::Tools::GetMoment( );
					PX::Tools::Pause( 2 ); // shouldn't take more than 2.5 milliseconds or less than 1.5 milliseconds
					Assert::IsTrue( 15000ull <= PX::Tools::GetMoment( ) - mmt && PX::Tools::GetMoment( ) - mmt <= 25000ull, L"Pause 2 check failed", PX_ASSERT_INFO );

					mmt = PX::Tools::GetMoment( );
					PX::Tools::Pause( 5 ); // shouldn't take more than 5.5 milliseconds or less than 4.5 milliseconds
					Assert::IsTrue( 45000ull <= PX::Tools::GetMoment( ) - mmt && PX::Tools::GetMoment( ) - mmt <= 55000ull, L"Pause 5 check failed", PX_ASSERT_INFO );
				}

				TEST_METHOD( StringCast )
				{
					cstr_t sz = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0";
					cstr16_t usz = u"`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0";
					cstr32_t Usz = U"`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0";
					wcstr_t wsz = L"`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0";
					bcstr_t bsz = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0"_b;

					str_t str = sz;
					str16_t ustr = usz;
					str32_t Ustr = Usz;
					wstr_t wstr = wsz;
					bstr_t bstr = bsz;

					// cstr_t
					{
						Assert::IsTrue( string_cast< str_t >( sz ) == sz, L"\"""cstr_t""\" to \"cstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( sz ) == usz, L"\"""cstr_t""\" to \"cstr16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( sz ) == Usz, L"\"""cstr_t""\" to \"cstr32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( sz ) == wsz, L"\"""cstr_t""\" to \"wcstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( sz ) == bsz, L"\"""cstr_t""\" to \"bcstr_t\" cast check failed)", PX_ASSERT_INFO );

						Assert::IsTrue( string_cast< str_t >( sz ) == str, L"\"""cstr_t""\" to  to \"str_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( sz ) == ustr, L"\"""cstr_t""\" to  to \"str16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( sz ) == Ustr, L"\"""cstr_t""\" to  to \"str32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( sz ) == wstr, L"\"""cstr_t""\" to  to \"wstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( sz ) == bstr, L"\"""cstr_t""\" to  to \"bstr_t\" cast check failed)", PX_ASSERT_INFO );
					};
					// cstr16_t
					{
						Assert::IsTrue( string_cast< str_t >( usz ) == sz, L"\"""cstr16_t""\" to \"cstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( usz ) == usz, L"\"""cstr16_t""\" to \"cstr16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( usz ) == Usz, L"\"""cstr16_t""\" to \"cstr32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( usz ) == wsz, L"\"""cstr16_t""\" to \"wcstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( usz ) == bsz, L"\"""cstr16_t""\" to \"bcstr_t\" cast check failed)", PX_ASSERT_INFO );

						Assert::IsTrue( string_cast< str_t >( usz ) == str, L"\"""cstr16_t""\" to  to \"str_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( usz ) == ustr, L"\"""cstr16_t""\" to  to \"str16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( usz ) == Ustr, L"\"""cstr16_t""\" to  to \"str32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( usz ) == wstr, L"\"""cstr16_t""\" to  to \"wstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( usz ) == bstr, L"\"""cstr16_t""\" to  to \"bstr_t\" cast check failed)", PX_ASSERT_INFO );
					};
					// cstr32_t
					{
						Assert::IsTrue( string_cast< str_t >( Usz ) == sz, L"\"""cstr32_t""\" to \"cstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( Usz ) == usz, L"\"""cstr32_t""\" to \"cstr16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( Usz ) == Usz, L"\"""cstr32_t""\" to \"cstr32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( Usz ) == wsz, L"\"""cstr32_t""\" to \"wcstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( Usz ) == bsz, L"\"""cstr32_t""\" to \"bcstr_t\" cast check failed)", PX_ASSERT_INFO );

						Assert::IsTrue( string_cast< str_t >( Usz ) == str, L"\"""cstr32_t""\" to  to \"str_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( Usz ) == ustr, L"\"""cstr32_t""\" to  to \"str16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( Usz ) == Ustr, L"\"""cstr32_t""\" to  to \"str32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( Usz ) == wstr, L"\"""cstr32_t""\" to  to \"wstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( Usz ) == bstr, L"\"""cstr32_t""\" to  to \"bstr_t\" cast check failed)", PX_ASSERT_INFO );
					};
					// wcstr_t
					{
						Assert::IsTrue( string_cast< str_t >( wsz ) == sz, L"\"""wcstr_t""\" to \"cstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( wsz ) == usz, L"\"""wcstr_t""\" to \"cstr16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( wsz ) == Usz, L"\"""wcstr_t""\" to \"cstr32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( wsz ) == wsz, L"\"""wcstr_t""\" to \"wcstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( wsz ) == bsz, L"\"""wcstr_t""\" to \"bcstr_t\" cast check failed)", PX_ASSERT_INFO );

						Assert::IsTrue( string_cast< str_t >( wsz ) == str, L"\"""wcstr_t""\" to  to \"str_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( wsz ) == ustr, L"\"""wcstr_t""\" to  to \"str16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( wsz ) == Ustr, L"\"""wcstr_t""\" to  to \"str32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( wsz ) == wstr, L"\"""wcstr_t""\" to  to \"wstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( wsz ) == bstr, L"\"""wcstr_t""\" to  to \"bstr_t\" cast check failed)", PX_ASSERT_INFO );
					};
					// bcstr_t
					{
						Assert::IsTrue( string_cast< str_t >( bsz ) == sz, L"\"""bcstr_t""\" to \"cstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( bsz ) == usz, L"\"""bcstr_t""\" to \"cstr16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( bsz ) == Usz, L"\"""bcstr_t""\" to \"cstr32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( bsz ) == wsz, L"\"""bcstr_t""\" to \"wcstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( bsz ) == bsz, L"\"""bcstr_t""\" to \"bcstr_t\" cast check failed)", PX_ASSERT_INFO );

						Assert::IsTrue( string_cast< str_t >( bsz ) == str, L"\"""bcstr_t""\" to  to \"str_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( bsz ) == ustr, L"\"""bcstr_t""\" to  to \"str16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( bsz ) == Ustr, L"\"""bcstr_t""\" to  to \"str32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( bsz ) == wstr, L"\"""bcstr_t""\" to  to \"wstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( bsz ) == bstr, L"\"""bcstr_t""\" to  to \"bstr_t\" cast check failed)", PX_ASSERT_INFO );
					};

					// str_t
					{
						Assert::IsTrue( string_cast< str_t >( str ) == sz, L"\"""str_t""\" to \"cstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( str ) == usz, L"\"""str_t""\" to \"cstr16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( str ) == Usz, L"\"""str_t""\" to \"cstr32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( str ) == wsz, L"\"""str_t""\" to \"wcstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( str ) == bsz, L"\"""str_t""\" to \"bcstr_t\" cast check failed)", PX_ASSERT_INFO );

						Assert::IsTrue( string_cast< str_t >( str ) == str, L"\"""str_t""\" to  to \"str_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( str ) == ustr, L"\"""str_t""\" to  to \"str16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( str ) == Ustr, L"\"""str_t""\" to  to \"str32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( str ) == wstr, L"\"""str_t""\" to  to \"wstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( str ) == bstr, L"\"""str_t""\" to  to \"bstr_t\" cast check failed)", PX_ASSERT_INFO );
					};
					// str16_t
					{
						Assert::IsTrue( string_cast< str_t >( ustr ) == sz, L"\"""str16_t""\" to \"cstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( ustr ) == usz, L"\"""str16_t""\" to \"cstr16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( ustr ) == Usz, L"\"""str16_t""\" to \"cstr32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( ustr ) == wsz, L"\"""str16_t""\" to \"wcstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( ustr ) == bsz, L"\"""str16_t""\" to \"bcstr_t\" cast check failed)", PX_ASSERT_INFO );

						Assert::IsTrue( string_cast< str_t >( ustr ) == str, L"\"""str16_t""\" to  to \"str_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( ustr ) == ustr, L"\"""str16_t""\" to  to \"str16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( ustr ) == Ustr, L"\"""str16_t""\" to  to \"str32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( ustr ) == wstr, L"\"""str16_t""\" to  to \"wstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( ustr ) == bstr, L"\"""str16_t""\" to  to \"bstr_t\" cast check failed)", PX_ASSERT_INFO );
					};
					// str32_t
					{
						Assert::IsTrue( string_cast< str_t >( Ustr ) == sz, L"\"""str32_t""\" to \"cstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( Ustr ) == usz, L"\"""str32_t""\" to \"cstr16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( Ustr ) == Usz, L"\"""str32_t""\" to \"cstr32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( Ustr ) == wsz, L"\"""str32_t""\" to \"wcstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( Ustr ) == bsz, L"\"""str32_t""\" to \"bcstr_t\" cast check failed)", PX_ASSERT_INFO );

						Assert::IsTrue( string_cast< str_t >( Ustr ) == str, L"\"""str32_t""\" to  to \"str_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( Ustr ) == ustr, L"\"""str32_t""\" to  to \"str16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( Ustr ) == Ustr, L"\"""str32_t""\" to  to \"str32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( Ustr ) == wstr, L"\"""str32_t""\" to  to \"wstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( Ustr ) == bstr, L"\"""str32_t""\" to  to \"bstr_t\" cast check failed)", PX_ASSERT_INFO );
					};
					// wstr_t
					{
						Assert::IsTrue( string_cast< str_t >( wstr ) == sz, L"\"""wstr_t""\" to \"cstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( wstr ) == usz, L"\"""wstr_t""\" to \"cstr16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( wstr ) == Usz, L"\"""wstr_t""\" to \"cstr32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( wstr ) == wsz, L"\"""wstr_t""\" to \"wcstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( wstr ) == bsz, L"\"""wstr_t""\" to \"bcstr_t\" cast check failed)", PX_ASSERT_INFO );

						Assert::IsTrue( string_cast< str_t >( wstr ) == str, L"\"""wstr_t""\" to  to \"str_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( wstr ) == ustr, L"\"""wstr_t""\" to  to \"str16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( wstr ) == Ustr, L"\"""wstr_t""\" to  to \"str32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( wstr ) == wstr, L"\"""wstr_t""\" to  to \"wstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( wstr ) == bstr, L"\"""wstr_t""\" to  to \"bstr_t\" cast check failed)", PX_ASSERT_INFO );
					};
					// bstr_t
					{
						Assert::IsTrue( string_cast< str_t >( bstr ) == sz, L"\"""bstr_t""\" to \"cstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( bstr ) == usz, L"\"""bstr_t""\" to \"cstr16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( bstr ) == Usz, L"\"""bstr_t""\" to \"cstr32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( bstr ) == wsz, L"\"""bstr_t""\" to \"wcstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( bstr ) == bsz, L"\"""bstr_t""\" to \"bcstr_t\" cast check failed)", PX_ASSERT_INFO );

						Assert::IsTrue( string_cast< str_t >( bstr ) == str, L"\"""bstr_t""\" to  to \"str_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str16_t >( bstr ) == ustr, L"\"""bstr_t""\" to  to \"str16_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< str32_t >( bstr ) == Ustr, L"\"""bstr_t""\" to  to \"str32_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< wstr_t >( bstr ) == wstr, L"\"""bstr_t""\" to  to \"wstr_t\" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< bstr_t >( bstr ) == bstr, L"\"""bstr_t""\" to  to \"bstr_t\" cast check failed)", PX_ASSERT_INFO );
					};
				}
				// todo: @cole tests for EstimateTableLength, GetModuleEnd, FindAddressOrigin, CHook, OpenLink, FormatShellcode
			};

			TEST_CLASS( Debug )
			{
			public:
				TEST_METHOD( Logging )
				{
					{
						std::wofstream wof( L"C:/debug.log", std::ofstream::trunc );
						wof.close( );
					}

					SetLastError( 0x0 );
					PX_NFO << "Unit Test Log";
					PX_DBG << "Unit Test Log";
					PX_SCS << "Unit Test Log";
					PX_WRN << "Unit Test Log";
					PX_ERR << "Unit Test Log";
					PX_LOG << "\tAppended Unit Test Log";
					
					Assert::AreEqual(
#if defined _DEBUG
R"([OPN] Begin new logging session
[NFO] Unit Test Log
[DBG] Unit Test Log
[SCS] Unit Test Log
[WRN] Unit Test Log
[ERR] Unit Test Log	Appended Unit Test Log)"
#else
R"()"
#endif
						, GlobalTools::GetFileData( L"C:/debug.log" ).c_str( ), L"Log comparison failed", PX_ASSERT_INFO );
				}
			};

			TEST_CLASS( InputManager )
			{
			public:
				// todo: @cole CKeyState, CInputManager
			};

			TEST_CLASS( FileManager )
			{
			public:
				// todo: @cole LoadResources, FileRead, FileWrite
			};
		}

		namespace Security
		{
			TEST_CLASS( Cryptography )
			{
			public:
				TEST_METHOD( StringXOR )
				{
					// multi xor
					Assert::AreNotEqual( R"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)",
									  ( PX::XOR::AXorString< PX::XOR::ACStringTraits< decltype( R"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)" )
									  >::char_trait_t, PX::XOR::AConstructIndexList< ( sizeof( R"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)" ) - 1 )
										/ PX::XOR::ACStringTraits< decltype( R"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)" ) >::int_trait_t >::result_t >
										( R"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)" ).Get( ) ),
									  L"Multi-byte XOR inequality check failed", PX_ASSERT_INFO );
					// wide xor
					Assert::AreNotEqual( LR"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)",
									  ( PX::XOR::AXorString< PX::XOR::ACStringTraits< decltype( LR"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)" )
									  >::char_trait_t, PX::XOR::AConstructIndexList< ( sizeof( LR"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)" ) - 1 )
										/ PX::XOR::ACStringTraits< decltype( LR"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)" ) >::int_trait_t >::result_t >
										( LR"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)" ).Get( ) ),
									  L"Wide XOR inequality check failed", PX_ASSERT_INFO );

					// multi unxor
					Assert::AreEqual( R"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)",
									  PX_XOR( R"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)" ),
									  L"Multi-byte UnXOR equality check failed", PX_ASSERT_INFO );
					// wide unxor
					Assert::AreEqual( LR"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)",
									  PX_XOR( LR"(ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=[]\;',./~!@#$%^&*()_+{}|:"<>?)" ),
									  L"Wide UnXOR equality check failed", PX_ASSERT_INFO );
				}
				// todo: @cole InitializeEncryption, GenerateHash, Base64, AES256CBC, Encrypt, Decrypt, GenerateIdentifier
			};

			TEST_CLASS( SystemManagement )
			{
			public:
				TEST_METHOD( RetrieveSystemInformation )
				{
					auto jsSystemInfo = GetSystemInfo( );
					Assert::AreEqual( "Intel(R) Xeon(R) CPU E5-1650 v2 @ 3.50GHz", jsSystemInfo[ "cpu" ].get< str_t >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "AMD FirePro D500 (FireGL V)\nAMD FirePro D500 (FireGL V)", jsSystemInfo[ "gpu" ].get< str_t >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "Default Monitor\nGeneric PnP Monitor", jsSystemInfo[ "display" ].get< str_t >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "JEREMIAH", jsSystemInfo[ "pc" ].get< str_t >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "Microsoft Windows 10 Pro", jsSystemInfo[ "os" ].get< str_t >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "NA76ENT9\nS18WNYBD801667", jsSystemInfo[ "drive" ].get< str_t >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "Mac-F60DEB81FF30ACF6", jsSystemInfo[ "board" ].get< str_t >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
				}
				// todo: @cole AssembleExtensionInformation, FindProcessThread, FindModuleEx, IsProcessThreadRunning, NecessaryModulesLoaded, WipeMemoryEx, WipeMemory, LoadLibraryEx, LoadRawLibraryEx, LoadRawLibrary, FindInternalHandle
			};

			TEST_CLASS( Connectivity )
			{
			public:
				TEST_METHOD( WebsiteConnection )
				{
					Assert::IsTrue( InitializeConnection( ), L"Connection initialization check failed", PX_ASSERT_INFO );
					Assert::IsTrue( InitializeEncryption( ), L"Encryption initialization check failed", PX_ASSERT_INFO );

					post_data_t dqPostData;
					dqPostData.emplace_back( "input", "ret" );

					Assert::AreEqual( "ret", Decrypt( Request( "https://www.paladin.rip/auth/test_safe.php", dqPostData ) ).c_str( ), L"Encrypted request return check failed", PX_ASSERT_INFO );

					CleanupConnection( );
				}
				// todo: @cole GeneratePostData, RequestExtension, Login, RequestExtensionInformation
			};

			TEST_CLASS( Injection )
			{
				/*
/// Empty.exe

#define PX_ENTRY_AS_WIN
#define _CRT_SECURE_NO_WARNINGS
#include "../../Entry Manager.hpp"

const wchar_t* wszWindowTitle = L"Empty"; // Class name

LRESULT CALLBACK WindowProc( _In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam )
{
	return DefWindowProc( hwnd, uMsg, wParam, lParam ); // we just want the default window proc for this simple process
}

void OnLaunch( )
{
	std::thread tInjectionTarget( [ ]( ) // for thread hijacking
	{
		while ( true )
			Sleep( 10 );
	} );

	tInjectionTarget.detach( );

	while ( true )
		Sleep( 10 ); // to keep the process running
}



/// Test.dll

#define PX_ENTRY_AS_DLL
#define _CRT_SECURE_NO_WARNINGS
#define PX_INSTANCE_ID "Test"
#include "../../Entry Manager.hpp"

std::ofstream ofConfirmRun;

void OnAttach( )
{
	// logging
	ofConfirmRun.open( std::string( getenv( "APPDATA" ) ) + "\\PX\\UnitTest.log", std::iostream::trunc );
	ofConfirmRun << "[OPN] Attached\n";
	ofConfirmRun << "[NFO] Detaching\n";
	Detach( ); // test detach
}

void OnDetach( )
{
	if ( !ofConfirmRun.is_open( ) ) // check if we somehow failed to enter, such as a replica mutex
	{
		ofConfirmRun.open( std::string( getenv( "APPDATA" ) ) + "\\PX\\UnitTest.log", std::iostream::trunc );
		ofConfirmRun << "[ERR] Called to detach before attach";
		ExitProcess( 3 );
	}
	ofConfirmRun << "[CLS] Detached and terminating host";
	ofConfirmRun.close( );
	ExitProcess( 2 ); // terminate process to keep pc clean for multiple tests
}
				*/
			public:
				TEST_METHOD( LoadLibraryEx )
				{
					{
						std::ofstream ofLog;
						ofLog.open( str_t( getenv( "APPDATA" ) ) + R"(\\PX\\UnitTest.log)", std::iostream::trunc );
						Assert::IsTrue( ofLog.is_open( ) && ofLog.good( ), L"Log file clear filed", PX_ASSERT_INFO );
						ofLog.close( );
					}

					STARTUPINFO si { sizeof( STARTUPINFO ) };
					PROCESS_INFORMATION pi;

					auto fnCleanUp = [ & ]( bool bWait )
					{
						if ( bWait )
							Pause( 1000 ), TerminateProcess( pi.hProcess, 0 );
						else
							TerminateProcess( pi.hProcess, 0 );
						CloseHandle( pi.hProcess );
						CloseHandle( pi.hThread );
					};

					Assert::AreNotEqual( 0, CreateProcess( LR"(C:\Users\Jeremiah\Documents\Paladin Extensions\Solutions\Paladin Extensions\PX Unit Tests\Unit Test Empty.exe)",
													nullptr, nullptr, nullptr, FALSE, 0x0, nullptr, nullptr, &si, &pi ), L"CreateProcess failed", PX_ASSERT_INFO );

					if ( !sys::LoadLibraryEx( L"Unit Test Empty.exe", LR"(C:\Users\Jeremiah\Documents\Paladin-Extensions\Solutions\Paladin Extensions\PX Unit Tests\Unit Test Log.dll)" ) )
					{
						fnCleanUp( false );
						Assert::Fail( L"LoadLibraryEx failed", PX_ASSERT_INFO );
					}

					fnCleanUp( true );

					Assert::AreEqual( R"([OPN] Attached
[NFO] Detaching
[CLS] Detached and terminating host)", GlobalTools::GetFileData( ( wstr_t( _wgetenv( L"APPDATA" ) ) + LR"(\\PX\\UnitTest.log)" ).c_str( ) ).c_str( ), L"Log check failed", PX_ASSERT_INFO );

					Assert::AreNotEqual( 0, DeleteFile( LR"(C:\Users\Jeremiah\AppData\Roaming\PX\UnitTest.log)" ), L"Delete file failed", PX_ASSERT_INFO );
				}
			};
		}

		namespace Design
		{
			TEST_CLASS( RenderEngine )
			{
			public:
				// todo: @cole SetWindowSize, InitializeRenderTarget, Destruct, SetWindowProc
			};

			TEST_CLASS( Drawing )
			{
			public:
				// todo: @cole InitializeDrawing, Destruct, Polygon, Line, Text, GetTextSize, DrawQueue
			};

			namespace UserInterface
			{
				TEST_CLASS( Manager )
				{
				public:
					// todo: @cole InitializeNuklear, InitializeUI, Destruct, CalculateTextBounds, SetFont, OnReset, OnSuccessfulReset, HandleEvent, Render, SetLayout, MouseHoveringRectangle, SetWidgetPosition
				};
				TEST_CLASS( Widgets )
				{
				public:
					// todo: @cole HoveringNextWidget, EditTextBox, NextWidgetBounds, SetWidgetActive, Tooltip, Header, PrimaryTab, SecondaryTab, Separator, Button, Checkbox, Tabs, SubTabs, BeginGroupbox, EndGroupbox, ColorPicker, ColorButton, Combobox, ComboboxMulti, Inputbox, Slider, Text, BeginRow, EndRow, SetRowWidth, Spacing, PushCustomRow
				};
			}
		}
	}

	namespace Installer
	{
		
	}

	namespace Launcher
	{
		
	}

	namespace Manager
	{
		TEST_CLASS( Functionality )
		{
		public:
			// todo: @cole RetrieveLaunchInformation, RetrieveExtensionInformation
		};
	}

	namespace CSGO
	{
		TEST_CLASS( Information )
		{
		public:
			// todo: @cole I don't have any good ideas for unit testing CSGO, except maybe CreateProcess a dummy exe from hardcoded data and seeing if basic initialization works. anything independent of csgo, but maybe unit testing isn't needed for this
		};

		TEST_CLASS( Hooks )
		{
		public:
			// todo: @cole same as with PX::UnitTests::CSGO::Information, but CreateProcess a dummy exe from hardcoded data and seeing if basic hooking works should actually be plausible.
		};
	}
}
