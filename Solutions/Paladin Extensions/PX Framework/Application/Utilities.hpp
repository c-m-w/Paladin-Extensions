/// Utilities.hpp

#pragma once

namespace PX
{
	namespace Utilities
	{
		// INFO: Dimention-dynamic vector
		// INFO: - supports operations
		// *_t*: vector datatype
		// *i*: vector size
		template< typename _t, int i > class vector_t
		{
			std::array< _t, i > _Data;
		public:
			PX_API vector_t( ) = default;
			PX_API vector_t( std::initializer_list< _t > );

			// INFO: returns vector data from index of ID parameter
			_t PX_API operator[ ]( int ) const;
			vector_t PX_API operator+( const vector_t& ) const;
			vector_t PX_API operator-( const vector_t& ) const;
			vector_t PX_API operator*( const vector_t& ) const;
			vector_t PX_API operator/( const vector_t& ) const;
			vector_t& PX_API operator+=( const vector_t& );
			vector_t& PX_API operator-=( const vector_t& );
			vector_t& PX_API operator*=( const vector_t& );
			vector_t& PX_API operator/=( const vector_t& );
		};

		// INFO: Inheritable abstract struct that only allows a single object of child class/struct to be instantiated
		// *_ChildClass*: Child class/struct to be restricted
		template< class _Child > PX_ABSTRACT_STRUCT ISingleton
		{
		public:
			ISingleton( ) = default;
			~ISingleton( ) = default;

			ISingleton( ISingleton&& ) = delete;
			ISingleton( const ISingleton& ) = delete;

			ISingleton& operator=( ISingleton&& ) = delete;
			ISingleton& operator=( const ISingleton& ) = delete;

			template< typename ... _Arg > static _Child& Get( _Arg ... );
		};

		// INFO: Datatype sized to hold any time
		typedef unsigned long long moment_t;
		// INFO: Gets the local time
		// *typename*: Time info format type
		template< typename = std::chrono::milliseconds > moment_t GetMoment( );
		// INFO: Sleeps the thread that has called for the amount of time, in the unit of time specified.
		// *typename*: The unit of time to wait for ( std::chrono ).
		template< typename = std::chrono::milliseconds > void Wait( moment_t );

		// INFO: Gets directory with specied directories upward
		// PARAM: Levels to escape
		std::wstring GetDirectory( unsigned = 0 );

		// INFO: Casts strings\n
		// INFO: Supports any combination of conversion from "std::string" and "std::wstring" to "std::string" and "std::wstring"
		// *_To*: Desired string type
		// *_From*: Current string
		template< typename _To, typename _From > _To string_cast( const _From & );
		// INFO: Casts strings\n
		// INFO: Supports any combination of conversion from "const char*" and "const wchar_t*" to "std::string" and "std::wstring"
		// *_To*: Desired string type
		// *_From*: Current string
		template< typename _To, typename _From > _To string_cast( _From* );
		// INFO: Casts strings\n
		// INFO: Supports any combination of conversion from "std::string" and "std::wstring" to "const char*" and "const wchar_t*"
		// *_To*: Desired string type
		// *_From*: Current string
		template< typename _To, typename _From > _To* string_cast( const _From & );
		// INFO: Casts strings\n
		// INFO: Supports any combination of conversion from "const char*" and "const wchar_t*" to "const char*" and "const wchar_t*"
		// *_To*: Desired string type
		// *_From*: Current string
		template< typename _To, typename _From > _To* string_cast( _From* );
	}
}

#include "Utilities.inl"
