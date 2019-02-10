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
			{ };

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
