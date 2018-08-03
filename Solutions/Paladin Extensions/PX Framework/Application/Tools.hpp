/// Tools.hpp

#pragma once

namespace PX::Tools
{
	// INFO: Inheritable struct that manages a single instantiated object of child class/structure
	// *_Child*: Child class/structure to be restricted
	template< class _Child > struct SSingleton
	{
		SSingleton( ) = default;
		~SSingleton( ) = default;

		SSingleton( SSingleton&& ) = delete;
		SSingleton( const SSingleton& ) = delete;

		SSingleton& operator=( SSingleton&& ) = delete;
		SSingleton& operator=( const SSingleton& ) = delete;

		static _Child& PX_API Get( );
	};

	/** \brief Plays a sound. */
	/**	\param szFileName File name of the sound. */
	void PX_API EmitSound( Types::wcstr_t szFileName );

	/** \brief Paladin time datatype, long enough to hold any time type, down to microseconds. */
	typedef unsigned long long moment_t;
	// INFO: Gets the local time
	// *type name*: Time info format type
	template< typename = std::chrono::milliseconds > Tools::moment_t PX_API GetMoment( );
	// INFO: Sleeps the thread that has called for the amount of time, in the unit of time specified.
	// *type name*: The unit of time to wait for ( std::chrono ).
	template< typename = std::chrono::milliseconds > void PX_API Wait( Tools::moment_t );

	// Get main screen dimensions
	unsigned* GetScreenDimensions( );

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

#include "Tools.inl"
