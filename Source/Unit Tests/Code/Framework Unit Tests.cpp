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

					const std::basic_string< char, std::char_traits< char >, std::allocator< char > > str = sz;
					const std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > wstr = wsz;

					// const char *
					{
						Assert::IsTrue( string_cast< std::string >( sz ) == sz, L"\"""const char *""\" to \"std::string\" cast check failed)" );
						Assert::IsTrue( string_cast< std::wstring >( sz ) == wsz, L"\"""const char *""\" to \"std::wstring\" cast check failed)" );
					};
					// const wchar_t *
					{
						Assert::IsTrue( string_cast< std::string >( wsz ) == sz, L"\"""const wchar_t *""\" to \"std::string\" cast check failed)" );
						Assert::IsTrue( string_cast< std::wstring >( wsz ) == wsz, L"\"""const wchar_t *""\" to \"std::wstring\" cast check failed)" );
					
					};
					//
					// std::string
					{
						Assert::IsTrue( string_cast< std::string >( str ) == sz, L"\"""std::string""\" to \"std::string\" cast check failed)" );
						Assert::IsTrue( string_cast< std::wstring >( str ) == wsz, L"\"""std::string""\" to \"wcstr_t\" cast check failed)" );
					};
					// std::wstring
					{
						Assert::IsTrue( string_cast< std::string >( str ) == sz, L"\"""std::wstring""\" to \"std::string\" cast check failed)" );
						Assert::IsTrue( string_cast< std::wstring >( wstr ) == wsz, L"\"""std::wstring""\" to \"std::wstring\" cast check failed)" );
					};
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
