#include "CSGO SDK.hpp"

// here, we include files and compile the lib to see if everything is ok. also, testing members in functions and whatnot might help.

CNetChannel test;

void Test()
{
	auto bob = test.GetTotalData(1);
}

// here, we test our extensions of classes

EXTENDED_SDK_CLASS( CNetChannel ) test2;

void Test2()
{
	auto bob = test2.OurCustomNetChannelFunction();
}
