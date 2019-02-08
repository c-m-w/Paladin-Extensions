/// Framework Unit Tests.cpp

#include "Precompile.hpp"
#include "CppUnitTest.h"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#define USE_DEFINITIONS
#include "../../Framework/Code/Framework.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Framework
{
	TEST_CLASS( Time )
	{
	public:

		TEST_METHOD( GetTime )
		{
			auto actual = unsigned __int64( std::chrono::duration_cast< std::chrono::nanoseconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( ) );
			auto expected = unsigned __int64( std::chrono::duration_cast< std::chrono::nanoseconds >( std::chrono::steady_clock::now( ).time_since_epoch( ) ).count( ) );


			Assert::AreEqual( expected + 116444736000000000ui64, actual, L"2");
		}
	};
}
