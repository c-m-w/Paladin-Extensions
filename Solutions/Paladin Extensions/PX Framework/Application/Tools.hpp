/// Tools.hpp

#pragma once

namespace PX::Tools
{
	using namespace Types;

	// INFO: Inheritable class that manages a single instantiated object of child class/structure
	// *_Child*: Child class/structure to be restricted
	template< class _Child > px_abstract_class ASingleton
	{
	public:
		ASingleton( ) = default;
		~ASingleton( ) = default;

		ASingleton( ASingleton&& ) = delete;
		ASingleton( const ASingleton& ) = delete;

		ASingleton& operator=( ASingleton&& ) = delete;
		ASingleton& operator=( const ASingleton& ) = delete;

		static _Child& PX_API Get( );
	};

	void PX_API OpenLink( cstr_t szLink );

	std::string PX_API TimeToDate( moment_t mmtTime );

	/** \brief Creates shellcode from a byte array. */
	/**	\param bByteArray Array of bytes to convert. */
	/**	\param uSize Size of the byte array. */
	/**	\return Converted byte array. */
	std::string PX_API FormatShellcode( byte_t* bByteArray, unsigned uSize );

	// INFO: Gets the local time
	// *type name*: Time info format type
	template< typename = std::chrono::milliseconds > moment_t PX_API GetMoment( );
	// INFO: Sleeps the thread that has called for the amount of time, in the unit of time specified.
	// *type name*: The unit of time to wait for ( std::chrono ).
	template< typename = std::chrono::milliseconds > void PX_API Wait( moment_t );

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
