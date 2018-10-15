/// PX Unit Tests.cpp

#include "PX Precompiled.hpp"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define PX_USE_NAMESPACES
#include "../PX Framework/PX Framework.hpp"
#define PX_ASSERT_INFO new __LineInfo( _T( __FILE__ ), __func__, __LINE__ )

namespace PX::UnitTests
{
	namespace GlobalTools
	{
		std::string GetFileData( wcstr_t wsz )
		{
			auto pResource = _wfopen( wsz, L"r" );
			if ( nullptr == pResource )
				return { };

			fseek( pResource, 0, SEEK_END );
			const auto lSize = ftell( pResource );
			rewind( pResource );

			std::string strData;
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
					const unsigned long ulTimeSinceCompilation = PX::Tools::GetMoment( ) / 10000000ull - tmTime;
					Assert::IsTrue( ulTimeSinceCompilation > 0ul, L"GetMoment check failed", PX_ASSERT_INFO );

					// check with run time
					Sleep( 3000 );
					const unsigned long ulChangeInTime = time( nullptr ) - ( ulTimeSinceCompilation + tmTime );
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
#define PX_STR "the quick brown fox jumps over the lazy dog"
#define PX_WSTR L"the quick brown fox jumps over the lazy dog"
					const char *sz = PX_STR;
					const wchar_t *wsz = PX_WSTR;
					std::string str = PX_STR;
					std::wstring wstr = PX_WSTR;

					// all possible "const char *" conversions
					{
						Assert::AreEqual( 0, strcmp( string_cast< std::string >( sz ).c_str( ), sz ), LR"(""const char *"" to ""const char *"" cast check failed)", PX_ASSERT_INFO );
						Assert::AreEqual( 0, wcscmp( string_cast< std::wstring >( sz ).c_str( ), wsz ), LR"(""const char *"" to ""const wchar_t *"" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< std::string >( sz ) == str, LR"(""const char *"" to ""std::string"" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< std::wstring >( sz ) == wstr, LR"(""const char *"" to ""std::wstring"" cast check failed)", PX_ASSERT_INFO );
					}
					// all possible "const wchar_t *" conversions
					{
						Assert::AreEqual( 0, wcscmp( string_cast< std::wstring >( wsz ).c_str( ), wsz ), LR"(""const wchar_t *"" to ""const wchar_t *"" cast check failed)", PX_ASSERT_INFO );
						Assert::AreEqual( 0, strcmp( string_cast< std::string >( wsz ).c_str( ), sz ), LR"(""const wchar_t *"" to ""const char *"" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< std::wstring >( wsz ) == wstr, LR"(""const wchar_t *"" to ""std::wstring"" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< std::string >( wsz ) == str, LR"(""const wchar_t *"" to ""std::string"" cast check failed)", PX_ASSERT_INFO );
					}
					// all possible "std::string" conversions
					{
						Assert::IsTrue( string_cast< std::string >( str ) == str, LR"(""std::string"" to ""std::string"" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< std::wstring >( str ) == wstr, LR"(""std::string"" to ""std::wstring"" cast check failed)", PX_ASSERT_INFO );
						Assert::AreEqual( 0, strcmp( string_cast< std::string >( str ).c_str( ), sz ), LR"(""std::string"" to ""const char *"" cast check failed)", PX_ASSERT_INFO );
						Assert::AreEqual( 0, wcscmp( string_cast< std::wstring >( str ).c_str( ), wsz ), LR"(""std::string"" to ""const wchar_t *"" cast check failed)", PX_ASSERT_INFO );
					}
					// all possible "std::wstring" conversions
					{
						Assert::IsTrue( string_cast< std::wstring >( wstr ) == wstr, LR"(""std::wstring"" to ""std::wstring"" cast check failed)", PX_ASSERT_INFO );
						Assert::IsTrue( string_cast< std::string >( wstr ) == str, LR"(""std::wstring"" to ""std::string"" cast check failed)", PX_ASSERT_INFO );
						Assert::AreEqual( 0, wcscmp( string_cast< std::wstring >( wstr ).c_str( ), wsz ), LR"(""std::wstring"" to ""const wchar_t *"" cast check failed)", PX_ASSERT_INFO );
						Assert::AreEqual( 0, strcmp( string_cast< std::string >( wstr ).c_str( ), sz ), LR"(""std::wstring"" to ""const char *"" cast check failed)", PX_ASSERT_INFO );
					}
#undef PX_STR
#undef PX_WSTR
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
					Assert::AreEqual( "Intel(R) Xeon(R) CPU E5-1650 v2 @ 3.50GHz", jsSystemInfo[ "cpu" ].get< std::string >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "AMD FirePro D500 (FireGL V)\nAMD FirePro D500 (FireGL V)", jsSystemInfo[ "gpu" ].get< std::string >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "Default Monitor\nGeneric PnP Monitor", jsSystemInfo[ "display" ].get< std::string >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "JEREMIAH", jsSystemInfo[ "pc" ].get< std::string >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "Microsoft Windows 10 Pro", jsSystemInfo[ "os" ].get< std::string >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "NA76ENT9\nS18WNYBD801667", jsSystemInfo[ "drive" ].get< std::string >( ).c_str( ),
									  L"System info does not match saved", PX_ASSERT_INFO );
					Assert::AreEqual( "Mac-F60DEB81FF30ACF6", jsSystemInfo[ "board" ].get< std::string >( ).c_str( ),
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
						std::ofstream ofLogFile;
						ofLogFile.open( std::string( getenv( "APPDATA" ) ) + R"(\\PX\\UnitTest.log)", std::iostream::trunc );
						ofLogFile.close( );
					}

					STARTUPINFO si { sizeof( STARTUPINFO ) };
					PROCESS_INFORMATION pi;

					auto fnCleanUp = [ & ]( )
					{
						TerminateProcess( pi.hProcess, 0 );
						CloseHandle( pi.hProcess );
						CloseHandle( pi.hThread );
					};

					Assert::AreNotEqual( 0, CreateProcess( LR"(C:\Users\Jeremiah\Documents\Paladin-Extensions\Solutions\Paladin Extensions\PX Unit Tests\Unit Test Empty.exe)",
													nullptr, nullptr, nullptr, FALSE, 0x0, nullptr, nullptr, &si, &pi ), L"CreateProcess failed", PX_ASSERT_INFO );

					if ( !sys::LoadLibraryEx( L"Unit Test Empty.exe", LR"(C:\Users\Jeremiah\Documents\Paladin-Extensions\Solutions\Paladin Extensions\PX Unit Tests\Unit Test Test.dll)" ) )
					{
						fnCleanUp( );
						Assert::Fail( L"LoadLibraryEx failed", PX_ASSERT_INFO );
					}

					Pause( 100 ); // give the process some time to run

					fnCleanUp( );

					Assert::AreEqual( R"([OPN] Attached
[NFO] Detaching
[CLS] Detached)", GlobalTools::GetFileData( LR"(C:\Users\Jeremiah\AppData\Roaming\PX\UnitTest.log)" ).c_str( ), L"Log check failed", PX_ASSERT_INFO );
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
