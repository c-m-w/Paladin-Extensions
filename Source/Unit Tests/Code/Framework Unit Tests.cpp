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
	TEST_CLASS( no_class )
	{
	public:

		TEST_METHOD( no_method )
		{
			unsigned short usDeltas[ 100 ];
			memset( &usDeltas, 0, sizeof usDeltas );
			for ( auto u = 0u; u < 100; u++ )
			{
				auto a = GetMoment( );
				Pause( 10000 );
				auto b = GetMoment( );
				usDeltas[ u ] = b - a;
			}
			unsigned int avg = 0i64;
			for ( auto& m: usDeltas )
			{
				avg += m;
			}
			avg /= 100;

			Assert::AreEqual( 10000u, avg );
		}
	};
}









