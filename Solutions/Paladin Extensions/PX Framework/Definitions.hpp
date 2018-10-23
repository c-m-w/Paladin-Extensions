/// Definitions.hpp

#pragma once

#if defined PX_NUKLEAR_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_IMPLEMENTATION
#define NK_D3D9_IMPLEMENTATION
#else
#define NK_PRIVATE
#endif

#if defined _DEBUG
	/** \brief Evaluates if parameter is equivalent to empty initialized version of parameter
		(false) and throws an exception if the evaluation succeeds */
	/** \param _ToAssert Value to assert. */
#define px_assert( _ToAssert ) \
		if ( ( _ToAssert ) == decltype( _ToAssert )( ) ) \
			throw std::exception( ( PX::Types::str_t( "Failed to assert " ) + #_ToAssert + " in function " + __func__ \
			+ " from line " + std::to_string( unsigned( __LINE__ ) ) + " in file " + ##( __FILE__ ) + "." ).c_str( ) )
#else
	/** \brief Evaluates if parameter is equivalent to empty initialized version of parameter
		(false) and throws an exception if the evaluation succeeds */
	/** \param _ToAssert Value to assert. */
#define px_assert( _ToAssert ) \
		if ( ( _ToAssert ) == decltype( _ToAssert )( ) ) \
			throw
#endif

// identifies head var as "Paladin Extensions" original
#define PX_SDK inline
// identifies function as "Paladin Extensions" original
#define PX_API __cdecl
// identifies constant as "Paladin Extensions" original
#define PX_DEF constexpr auto
// identifies instruct as "Paladin Extensions" original
#define PX_EXT extern
// identifies in-lines as "Paladin Extensions" original
#define PX_INL __forceinline
// identifies noexcept as "Paladin Extensions" original
#define PX_NOX noexcept
// identifies end func as "Paladin Extensions" original
#define PX_END __declspec( noreturn )
// identifies returned as "Paladin Extensions" original
#define PX_RET [ [ nodiscard ] ]
// identifies unusable as "Paladin Extensions" original
#define PX_DEP( reason ) [ [ deprecated( #reason ) ] ]
// identifies stacking as "Paladin Extensions" original
#define PX_STK [ [ fallthrough ] ]

/** \brief Identifies a class as abstract. */
#define px_abstract_class class
/** \brief Identifies a function as abstract. */
#define px_abstract virtual
/** \brief Identifies an interface. */
#define px_interface class

/** \brief Path to appdata directory */
#define PX_APPDATA ( PX::Types::wstr_t( _wgetenv( PX_XOR( L"APPDATA" ) ) ) + PX_XOR( L"\\PX\\" ) )

/** \brief Maximum managed keys. */
#define PX_MAX_KEY 256

/** \brief Size of a memory page. */
#define PX_PAGE ( 1024 * 4 )

/** \brief Value of memory on the stack before it is assigned a value. */
#define PX_UNITIALIZED_STACK_MEMORY 0xCCCCCCCC

#define PX_MOV_EAX	0xB8
#define PX_MOV_EDX	0xBA
#define PX_PUSH		0x68

#define PX_EXTENSION_SECTIONS 7

// TODO: make this an enumerated type
#define PX_EXTENSION_NONE ( -1 )
#define PX_EXTENSION_MANAGER 1
#define PX_EXTENSION_CSGO 2
#define PX_EXTENSION_PUBG 3
#define PX_EXTENSION_RSIX 4
#define PX_EXTENSION_MAX 5

#if defined _DEBUG
#define PX_DEPENDENCIES_ESCAPE 1
#else
#define PX_DEPENDENCIES_ESCAPE 0
#endif

#if defined _DEBUG
#define D3D_DEBUG_INFO
#endif

#define PX_CUSTOM_FVF ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE )

// Encrypts string data on compile, then decrypts for access on run.
#if defined NDEBUG
#define PX_XOR( String ) ( PX::XOR::AXorString< PX::XOR::ACStringTraits< decltype( String ) >::char_trait_t, \
		PX::XOR::AConstructIndexList< ( sizeof( String ) - 1 ) / PX::XOR::ACStringTraits< decltype( String ) >::int_trait_t >::result_t >( String ).Decrypt( ) )
#else
#define PX_XOR( String ) ( String )
#endif

#if defined _DEBUG
#define PX_SHOW_ALL_DEBUG true
#define PX_SHOW_LOG_DEBUG true
#define PX_SHOW_NFO_DEBUG true
#define PX_SHOW_DBG_DEBUG true
#define PX_SHOW_SCS_DEBUG true
#define PX_SHOW_WRN_DEBUG true
#define PX_SHOW_ERR_DEBUG true

#define PX_LOG if constexpr ( PX_SHOW_ALL_DEBUG || PX_SHOW_LOG_DEBUG ) \
				   PX::dbg::SDebugStream::Get( )
#define PX_NFO if constexpr ( PX_SHOW_ALL_DEBUG || PX_SHOW_NFO_DEBUG ) \
				   PX::dbg::SDebugStream::Get( ) << "\n[NFO] "
#define PX_DBG if constexpr ( PX_SHOW_ALL_DEBUG || PX_SHOW_DBG_DEBUG ) \
				   PX::dbg::SDebugStream::Get( ) << "\n[DBG] "
#define PX_SCS if constexpr ( PX_SHOW_ALL_DEBUG || PX_SHOW_SCS_DEBUG ) \
				   PX::dbg::SDebugStream::Get( ) << "\n[SCS] "
#define PX_WRN if constexpr ( PX_SHOW_ALL_DEBUG || PX_SHOW_WRN_DEBUG ) \
				   PX::dbg::SDebugStream::Get( ) << "\n[WRN] "
#define PX_ERR if constexpr ( PX_SHOW_ALL_DEBUG || PX_SHOW_ERR_DEBUG ) \
				   PX::dbg::SDebugStream::Get( ) << "\n[ERR] "
#else
#define PX_LOG /##/
#define PX_NFO /##/
#define PX_DBG /##/
#define PX_SCS /##/
#define PX_WRN /##/
#define PX_ERR /##/
#endif


// Singleton access macros
/** \brief Input interface singleton access macro */
#define PX_INPUT PX::CInputManager::Get( )
/** \brief File manager class singleton access macro */
#define PX_FILES PX::Files::CConfig::Get( )
/** \brief Configuration access macro for convenience */
#define PX_CONFIG PX_FILES.jsCurrent
/** \brief Undocumented WINAPI Manager */
#define PX_WINAPI PX::sys::SWindowsAPI::Get( )
