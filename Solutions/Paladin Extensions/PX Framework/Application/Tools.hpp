/// Utilities.hpp

#pragma once

namespace PX
{
	namespace Tools
	{
		// INFO: Typedefs for long datatypes
		
        typedef const char* cstr_t;
        typedef const wchar_t* wcstr_t;
        typedef uintptr_t ptr_t;
		typedef unsigned char byte_t;
		
		// INFO: Inheritable abstract class that only allows a single object of child class/structure to be instantiated
		// *_Child*: Child class/structure to be restricted
		template< class _Child > PX_ABSTRACT_CLASS ISingleton
		{
        public:
			ISingleton( ) = default;
			~ISingleton( ) = default;

			ISingleton( ISingleton&& ) = delete;
			ISingleton( const ISingleton& ) = delete;

			ISingleton& operator=( ISingleton&& ) = delete;
			ISingleton& operator=( const ISingleton& ) = delete;

			static _Child& PX_API Get( );
		};

		// INFO: Data type sized to hold any time
		typedef unsigned long long moment_t;
		// INFO: Gets the local time
		// *type name*: Time info format type
		template< typename = std::chrono::milliseconds > moment_t PX_API GetMoment( );
		// INFO: Sleeps the thread that has called for the amount of time, in the unit of time specified.
		// *type name*: The unit of time to wait for ( std::chrono ).
		template< typename = std::chrono::milliseconds > void PX_API Wait( moment_t );

		// INFO: Gets directory with specified directories upward
		// PARAM: Levels to escape
		std::wstring PX_API GetDirectory( unsigned = 0 );

		// INFO: Casts strings\n
		// INFO: Supports any combination of conversion from "std::string" and "std::wstring" to "std::string" and "std::wstring"
		// *_To*: Desired string type
		// *_From*: Current string
		template< typename _To, typename _From > _To PX_API string_cast( const _From& );
		// INFO: Casts strings\n
		// INFO: Supports any combination of conversion from "const char*" and "const wchar_t*" to "std::string" and "std::wstring"
		// *_To*: Desired string type
		// *_From*: Current string
		template< typename _To, typename _From > _To PX_API string_cast( _From* );
	}
}

#include "Tools.inl"
