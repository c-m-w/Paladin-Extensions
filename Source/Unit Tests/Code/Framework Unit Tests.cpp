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
					MessageBox( 0, 0, 0, 0 );
					const auto sz = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0";
					const auto usz = u"`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0";
					const auto Usz = U"`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0";
					const auto wsz = L"`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0";
					const auto bsz = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n\t\0"_b;

					MessageBox( 0, 0, 0, 0 );
					const std::basic_string< char, std::char_traits< char >, std::allocator< char > > str = sz;
					const std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > ustr = usz;
					const std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > Ustr = Usz;
					const std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > wstr = wsz;
					const std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > bstr = bsz;

					MessageBox( 0, 0, 0, 0 );
					// cstr_t
					{
						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( sz ) == sz, L"\"""cstr_t""\" to \"cstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( sz ) == usz, L"\"""cstr_t""\" to \"cstr16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( sz ) == Usz, L"\"""cstr_t""\" to \"cstr32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( sz ) == wsz, L"\"""cstr_t""\" to \"wcstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( sz ) == bsz, L"\"""cstr_t""\" to \"bcstr_t\" cast check failed)" );

						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( sz ) == str, L"\"""cstr_t""\" to  to \"str_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( sz ) == ustr, L"\"""cstr_t""\" to  to \"str16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( sz ) == Ustr, L"\"""cstr_t""\" to  to \"str32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( sz ) == wstr, L"\"""cstr_t""\" to  to \"wstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( sz ) == bstr, L"\"""cstr_t""\" to  to \"bstr_t\" cast check failed)" );
					};
					// cstr16_t
					{
						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( usz ) == sz, L"\"""cstr16_t""\" to \"cstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( usz ) == usz, L"\"""cstr16_t""\" to \"cstr16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( usz ) == Usz, L"\"""cstr16_t""\" to \"cstr32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( usz ) == wsz, L"\"""cstr16_t""\" to \"wcstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( usz ) == bsz, L"\"""cstr16_t""\" to \"bcstr_t\" cast check failed)" );

						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( usz ) == str, L"\"""cstr16_t""\" to  to \"str_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( usz ) == ustr, L"\"""cstr16_t""\" to  to \"str16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( usz ) == Ustr, L"\"""cstr16_t""\" to  to \"str32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( usz ) == wstr, L"\"""cstr16_t""\" to  to \"wstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( usz ) == bstr, L"\"""cstr16_t""\" to  to \"bstr_t\" cast check failed)" );
					};
					// cstr32_t
					{
						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( Usz ) == sz, L"\"""cstr32_t""\" to \"cstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( Usz ) == usz, L"\"""cstr32_t""\" to \"cstr16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( Usz ) == Usz, L"\"""cstr32_t""\" to \"cstr32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( Usz ) == wsz, L"\"""cstr32_t""\" to \"wcstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( Usz ) == bsz, L"\"""cstr32_t""\" to \"bcstr_t\" cast check failed)" );

						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( Usz ) == str, L"\"""cstr32_t""\" to  to \"str_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( Usz ) == ustr, L"\"""cstr32_t""\" to  to \"str16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( Usz ) == Ustr, L"\"""cstr32_t""\" to  to \"str32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( Usz ) == wstr, L"\"""cstr32_t""\" to  to \"wstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( Usz ) == bstr, L"\"""cstr32_t""\" to  to \"bstr_t\" cast check failed)" );
					};
					// wcstr_t
					{
						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( wsz ) == sz, L"\"""wcstr_t""\" to \"cstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( wsz ) == usz, L"\"""wcstr_t""\" to \"cstr16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( wsz ) == Usz, L"\"""wcstr_t""\" to \"cstr32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( wsz ) == wsz, L"\"""wcstr_t""\" to \"wcstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( wsz ) == bsz, L"\"""wcstr_t""\" to \"bcstr_t\" cast check failed)" );

						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( wsz ) == str, L"\"""wcstr_t""\" to  to \"str_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( wsz ) == ustr, L"\"""wcstr_t""\" to  to \"str16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( wsz ) == Ustr, L"\"""wcstr_t""\" to  to \"str32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( wsz ) == wstr, L"\"""wcstr_t""\" to  to \"wstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( wsz ) == bstr, L"\"""wcstr_t""\" to  to \"bstr_t\" cast check failed)" );
					};
					// bcstr_t
					{
						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( bsz ) == sz, L"\"""bcstr_t""\" to \"cstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( bsz ) == usz, L"\"""bcstr_t""\" to \"cstr16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( bsz ) == Usz, L"\"""bcstr_t""\" to \"cstr32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( bsz ) == wsz, L"\"""bcstr_t""\" to \"wcstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( bsz ) == bsz, L"\"""bcstr_t""\" to \"bcstr_t\" cast check failed)" );

						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( bsz ) == str, L"\"""bcstr_t""\" to  to \"str_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( bsz ) == ustr, L"\"""bcstr_t""\" to  to \"str16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( bsz ) == Ustr, L"\"""bcstr_t""\" to  to \"str32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( bsz ) == wstr, L"\"""bcstr_t""\" to  to \"wstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( bsz ) == bstr, L"\"""bcstr_t""\" to  to \"bstr_t\" cast check failed)" );
					};
					MessageBox( 0, 0, 0, 0 );

					// str_t
					{
						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( str ) == sz, L"\"""str_t""\" to \"cstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( str ) == usz, L"\"""str_t""\" to \"cstr16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( str ) == Usz, L"\"""str_t""\" to \"cstr32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( str ) == wsz, L"\"""str_t""\" to \"wcstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( str ) == bsz, L"\"""str_t""\" to \"bcstr_t\" cast check failed)" );

						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( str ) == str, L"\"""str_t""\" to  to \"str_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( str ) == ustr, L"\"""str_t""\" to  to \"str16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( str ) == Ustr, L"\"""str_t""\" to  to \"str32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( str ) == wstr, L"\"""str_t""\" to  to \"wstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( str ) == bstr, L"\"""str_t""\" to  to \"bstr_t\" cast check failed)" );
					};
					// str16_t
					{
						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( ustr ) == sz, L"\"""str16_t""\" to \"cstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( ustr ) == usz, L"\"""str16_t""\" to \"cstr16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( ustr ) == Usz, L"\"""str16_t""\" to \"cstr32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( ustr ) == wsz, L"\"""str16_t""\" to \"wcstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( ustr ) == bsz, L"\"""str16_t""\" to \"bcstr_t\" cast check failed)" );

						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( ustr ) == str, L"\"""str16_t""\" to  to \"str_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( ustr ) == ustr, L"\"""str16_t""\" to  to \"str16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( ustr ) == Ustr, L"\"""str16_t""\" to  to \"str32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( ustr ) == wstr, L"\"""str16_t""\" to  to \"wstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( ustr ) == bstr, L"\"""str16_t""\" to  to \"bstr_t\" cast check failed)" );
					};
					// str32_t
					{
						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( Ustr ) == sz, L"\"""str32_t""\" to \"cstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( Ustr ) == usz, L"\"""str32_t""\" to \"cstr16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( Ustr ) == Usz, L"\"""str32_t""\" to \"cstr32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( Ustr ) == wsz, L"\"""str32_t""\" to \"wcstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( Ustr ) == bsz, L"\"""str32_t""\" to \"bcstr_t\" cast check failed)" );

						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( Ustr ) == str, L"\"""str32_t""\" to  to \"str_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( Ustr ) == ustr, L"\"""str32_t""\" to  to \"str16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( Ustr ) == Ustr, L"\"""str32_t""\" to  to \"str32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( Ustr ) == wstr, L"\"""str32_t""\" to  to \"wstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( Ustr ) == bstr, L"\"""str32_t""\" to  to \"bstr_t\" cast check failed)" );
					};
					// wstr_t
					{
						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( wstr ) == sz, L"\"""wstr_t""\" to \"cstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( wstr ) == usz, L"\"""wstr_t""\" to \"cstr16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( wstr ) == Usz, L"\"""wstr_t""\" to \"cstr32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( wstr ) == wsz, L"\"""wstr_t""\" to \"wcstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( wstr ) == bsz, L"\"""wstr_t""\" to \"bcstr_t\" cast check failed)" );

						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( wstr ) == str, L"\"""wstr_t""\" to  to \"str_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( wstr ) == ustr, L"\"""wstr_t""\" to  to \"str16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( wstr ) == Ustr, L"\"""wstr_t""\" to  to \"str32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( wstr ) == wstr, L"\"""wstr_t""\" to  to \"wstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( wstr ) == bstr, L"\"""wstr_t""\" to  to \"bstr_t\" cast check failed)" );
					};
					// bstr_t
					{
						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( bstr ) == sz, L"\"""bstr_t""\" to \"cstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( bstr ) == usz, L"\"""bstr_t""\" to \"cstr16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( bstr ) == Usz, L"\"""bstr_t""\" to \"cstr32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( bstr ) == wsz, L"\"""bstr_t""\" to \"wcstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( bstr ) == bsz, L"\"""bstr_t""\" to \"bcstr_t\" cast check failed)" );

						Assert::IsTrue( string_cast< std::basic_string< char, std::char_traits< char >, std::allocator< char > > >( bstr ) == str, L"\"""bstr_t""\" to  to \"str_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char16_t, std::char_traits< char16_t >, std::allocator< char16_t > > >( bstr ) == ustr, L"\"""bstr_t""\" to  to \"str16_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< char32_t, std::char_traits< char32_t >, std::allocator< char32_t > > >( bstr ) == Ustr, L"\"""bstr_t""\" to  to \"str32_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< wchar_t, std::char_traits< wchar_t >, std::allocator< wchar_t > > >( bstr ) == wstr, L"\"""bstr_t""\" to  to \"wstr_t\" cast check failed)" );
						Assert::IsTrue( string_cast< std::basic_string< unsigned char, std::char_traits< unsigned char >, std::allocator< unsigned char > > >( bstr ) == bstr, L"\"""bstr_t""\" to  to \"bstr_t\" cast check failed)" );

						MessageBox( 0, 0, 0, 0 );
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
					Assert::AreEqual( SI.GetHardware( )[ "cpu" ].get< std::string >( ).c_str( ), "hello" );
				}
			};
		};
	}
}
