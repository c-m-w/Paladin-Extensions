/// Tools.hpp

#pragma once

namespace PX::Tools
{
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

	std::size_t PX_API EstimateTableLength( Types::ptr_t* pVirtualTable );
	Types::ptr_t PX_API GetModuleEnd( HMODULE hm );
	HMODULE PX_API FindAddressOrigin( Types::ptr_t ptrAddress );

	struct CHook
	{
	private:
		DWORD dwOldProtection;
		std::size_t zTableLength, zTableSize;
		void* pClassBase;
		Types::ptr_t* pOldTable, *pNewTable;
		HMODULE hAllocationModule;
		bool bSetNewTable;

	public:
		CHook( void* pVirtualTable );
		~CHook( );

		bool Succeeded( );
		bool HookIndex( unsigned uIndex, void* pNewFunction );
		void UnhookIndex( unsigned uIndex );

		void ResetTable( );
		template< typename _fn > _fn GetOriginalFunction( unsigned uIndex );

		void Cleanup( );
	};

	void PX_API OpenLink( Types::cstr_t szLink );

	std::string PX_API TimeToDate( Types::moment_t mmtTime );

	/** \brief Creates shellcode from a byte array. */
	/**	\param bByteArray Array of bytes to convert. */
	/**	\param uSize Size of the byte array. */
	/**	\return Converted byte array. */
	std::string PX_API FormatShellcode( Types::byte_t* bByteArray, unsigned uSize );

	// INFO: Gets the local time
	// *type name*: Time info format type
	/** \brief Gets the local time */
	/** \return Local time in moment_t form */
	Types::moment_t PX_API GetMoment( );
	// INFO: 
	/** \brief Pauses (doesn't free up CPU) the thread that has called for the amount of time within .5 ms */
	/** \param mmtWaitLength Length to wait in milliseconds */
	void PX_API Wait( Types::moment_t mmtWaitLength = 1ull );

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

#if defined PX_USE_NAMESPACES
using namespace PX::Tools;
#endif
