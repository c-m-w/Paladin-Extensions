#include <iostream>
#include <vector>
#include <array>

// ReSharper disable once CppInconsistentNaming
typedef unsigned long DWORD;

void PrintClass( char *szClassName )
{
	std::cout << "class C" << szClassName << "\n{\n";
}

void PrintClass(  )
{
	std::cout << std::endl;
}

void PrintVariable( char *szVariableName, char *szVariableDatatype )
{
	std::cout << "    " << szVariableDatatype << " " << szVariableName << ";\n";
}

int main( )
{
	char chClassName[64];
	std::cout << "Enter the class name: ";
	std::cin >> chClassName;
	std::cout << std::endl;

	std::cout << "Enter the number variables: ";
	int i = 0;
	std::cin >> i;
	std::cout << std::endl;

	std::vector<char[64]> chVariables;
	std::vector<DWORD> dwPadding;

	for ( ; i > 0; i-- )
	{
		std::cout << "Enter the variable name: ";
		char chVariableBuffer[ 64 ];
		std::cin >> chVariableBuffer;
		std::cout << std::endl;

		chVariables.push_back( chVariableBuffer );

		std::cout << "Enter the variable's address in decimal: ";
		char chAddressBuffer[ 64 ];
		std::cin >> chAddressBuffer;
		std::cout << std::endl;

		DWORD iAddressBuffer = int( chAddressBuffer ) - 48;

		dwPadding.push_back( iAddressBuffer );
	}

	PrintClass( chClassName );

	DWORD dwLastAddress;

	for ( auto &chVariable : chVariables )
	{
		// if sizeof our datatype > current LastAddress, put a buffer! TODO
		char *chDatatypeBuffer;
		if ( chVariable[0] == *"b" )
		{
			chDatatypeBuffer = "bool";
		}
		else if ( chVariable[ 0 ] == *"f" && chVariable[ 1 ] == *"l" )
		{
			chDatatypeBuffer = "float";
		}
		else if ( chVariable[ 0 ] == *"f" )
		{
			chDatatypeBuffer = "flag";
		}
		else if ( chVariable[ 0 ] == *"i" )
		{
			chDatatypeBuffer = "int";
		}
		else if ( chVariable[ 0 ] == *"n" )
		{
			chDatatypeBuffer = "unsigned int";
		}
		else if ( chVariable[ 0 ] == *"l" )
		{
			chDatatypeBuffer = "long";
		}
		else if ( chVariable[ 0 ] == *"c" && chVariable[ 1 ] == *"l" && chVariable[ 2 ] == *"r" )
		{
			chDatatypeBuffer = "color";
		}
		else if ( chVariable[ 0 ] == *"v" && chVariable[ 1 ] == *"e" && chVariable[ 2 ] == *"c" )
		{
			chDatatypeBuffer = "Vector";
		}
		else if ( chVariable[ 0 ] == *"a" && chVariable[ 1 ] == *"n" && chVariable[ 2 ] == *"g" )
		{
			chDatatypeBuffer = "angle_t";
		}
		else if ( chVariable[ 0 ] == *"d" && chVariable[ 1 ] == *"b" )
		{
			chDatatypeBuffer = "double";
		}
		else
		{
			chDatatypeBuffer = "unknown";
		}
		PrintVariable( chVariable, chDatatypeBuffer );
		dwLastAddress = dwPadding.at( i );
		i++;
	}

	PrintClass( );




	system( "pause" );
}
