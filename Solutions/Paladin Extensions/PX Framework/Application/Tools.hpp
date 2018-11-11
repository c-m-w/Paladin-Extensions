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

	class CStandardHook
	{
	private:
		DWORD dwOldProtection;
		std::size_t zTableLength, zTableSize;
		void* pClassBase;
		Types::ptr_t* pOldTable, *pNewTable;
		HMODULE hAllocationModule;
		bool bSetNewTable;

	public:
		CStandardHook( void* pVirtualTable );
		~CStandardHook( );

		bool Succeeded( );
		bool HookIndex( unsigned uIndex, void* pNewFunction );
		void UnhookIndex( unsigned uIndex );

		void ResetTable( );
		template< typename _fn > _fn GetOriginalFunction( unsigned uIndex );

		void Cleanup( );
	};

	class CTrampolineHook
	{
	private:
		uintptr_t* pOldTable = nullptr,
			*pNewTable = nullptr;
		std::size_t sTable = 0;
		DWORD dwTableProtection = NULL;
		HMODULE hTableOrigin = nullptr;
		bool bInitialized = false, bSetProtection = false;

		struct stub_t
		{
			static constexpr std::size_t STUB_SIZE = 6;
			static constexpr unsigned char STUB[ ] {
												0x68, 0xCC, 0xCC, 0xCC, 0xCC,	// push 0xCCCCCCCC
												0xC3							// retn
			};

			uintptr_t ptrAddress;
			DWORD dwProtect;
		};
		std::vector< stub_t > vecStubs { };

	public:
		CTrampolineHook( ) = default;
		CTrampolineHook( void* pTable );
		~CTrampolineHook( );

		void Setup( void* pTable );
		bool Succeeded( );
		bool SetProtection( );
		bool HookIndex( unsigned uIndex, void* pAddress );
		bool ResetProtection( );

		template< typename _fn > _fn GetOriginalFunction( unsigned uIndex );

		void UnhookAll( );
	};

	enum class EMBType
	{
		NONE = MB_OK | MB_HELP,
		FATAL_ERROR = MB_ICONHAND | MB_HELP,
		RETRY_ERROR = MB_ICONHAND | MB_OK | MB_RETRYCANCEL | MB_HELP,
		QUERY = MB_ICONQUESTION | MB_YESNO | MB_HELP,
		WARNING = MB_ICONEXCLAMATION | MB_OK | MB_HELP,
		INFO = MB_ICONASTERISK | MB_OK | MB_HELP,
	};

	// returns true if selected YES on EMBType::QUERY or selected RETRY on EMBType::ERROR
	bool Popup( EMBType popType, const wchar_t* wszMessage, bool bDelete = false );

	void PX_API OpenLink( Types::cstr_t szLink );

	Types::str_t PX_API TimeToDate( Types::moment_t mmtTime );

	/** \brief Creates shellcode from a byte array. */
	/**	\param bByteArray Array of bytes to convert. */
	/**	\param uSize Size of the byte array. */
	/**	\return Converted byte array. */
	Types::str_t PX_API FormatShellcode( Types::byte_t* bByteArray, unsigned uSize );

	/** \brief Gets the local time */
	/**			Divide return by 10000000ull to go to seconds */
	/** \return Local time in moment_t form (tenths of microsecond) */
	Types::moment_t PX_API GetMoment( );
	/** \brief Pauses (doesn't free up CPU) the thread that has called for the amount of time within .5 ms */
	/** \param mmtPauseLength Length to pause in milliseconds */
	void PX_API Pause( Types::moment_t mmtPauseLength = 1ull );

	template< typename _t = std::chrono::milliseconds > PX_EXT PX_INL void Wait( Types::moment_t mmtTime );

	// Get main screen dimensions
	unsigned* GetScreenDimensions( );

	/** \brief Supports any combination of string casting conversion of "str_t", "str16_t", "str32_t", and "wstr_t" */
	/** \tparam _To Desired string type */
	/** \tparam _From Current string */
	/** \return Converted string in desired type */
	template< typename _To, typename _From > _To PX_API string_cast( const _From& );
	/** \brief Supports any combination of string casting conversion from "char", "char16_t", "char32_t", "wchar_t", and "byte_t", and of "str_t", "str16_t", "str32_t", and "wstr_t" */
	/** \tparam _To Desired string type */
	/** \tparam _From Current string */
	/** \return Converted string in desired type */
	template< typename _To, typename _From > _To PX_API string_cast( _From* );

	template< typename _t > _t GenerateRandomNumber( _t _Min, _t _Max, unsigned uSeed = 0u );
}

#include "Tools.inl"

#if defined PX_USE_NAMESPACES
using namespace PX::Tools;
#endif
