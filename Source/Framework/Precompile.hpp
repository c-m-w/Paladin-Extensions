/// Precompile.hpp

#pragma once

// Compiler
#pragma warning( push, 0 ) // warning level set to 0
#include <CodeAnalysis/Warnings.h>
#pragma warning( disable: ALL_CODE_ANALYSIS_WARNINGS )

// VMProtect
#include <VMProtect/VMProtectSDK.h>

// Standard C++
#define _SILENCE_CXX17_UNCAUGHT_EXCEPTION_DEPRECATION_WARNING // crypto++
#include "Code/Development Environment/Standard Library.hpp"
#undef _SILENCE_CXX17_UNCAUGHT_EXCEPTION_DEPRECATION_WARNING

// Windows
#define VC_EXTRALEAN // remove unnecessary includes
#define NOMINMAX // disable min/max macros
#include <Windows.h>
#include <tchar.h>
#include <VersionHelpers.h>
#include <shellapi.h>
#include <winternl.h>
#include <ntstatus.h>
#include <strsafe.h>
#include <Shlwapi.h>
#pragma comment( lib, "Shlwapi.lib" )
#include <intrin.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <comdef.h>
#include <WbemIdl.h>
#pragma comment( lib, "wbemuuid.lib" )

// Driver Development Kit
extern "C"
{
	NTSYSAPI
		NTSTATUS
		NTAPI
		RtlGetVersion(
			_Out_
			_At_( lpVersionInformation->dwOSVersionInfoSize, _Pre_ _Valid_ )
			_When_( lpVersionInformation->dwOSVersionInfoSize == sizeof( RTL_OSVERSIONINFOEXW ),
					_At_( ( PRTL_OSVERSIONINFOEXW )lpVersionInformation, _Out_ ) )
			PRTL_OSVERSIONINFOW lpVersionInformation
		);
}
#pragma comment( lib, "ntdll.lib" )

#undef ERROR
#undef EncryptFile
#undef DecryptFile
#undef LoadLibraryEx

// DirectX
#include <D2D1.h>
#include <d3d9.h>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <DirectXMath.h>
#include <d3dx9tex.h>
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3dx10.lib" )

#include <FW1FontWrapper/FW1FontWrapper.h>
#pragma comment( lib, "FW1FontWrapper.lib" )

// OpenSSL
#if defined _DEBUG
#pragma comment( lib, "libcryptod.lib" )
#pragma comment( lib, "libssld.lib" )
#else
#pragma comment( lib, "libcrypto.lib" )
#pragma comment( lib, "libssl.lib" )
#endif

// cURL
#define CURL_STATICLIB // specify cURL is lib, not dll
#include <curl_1/curl/curl.h>
#pragma comment( lib, "Ws2_32.lib" )
#pragma comment( lib, "wldap32.lib" )
#pragma comment( lib, "Crypt32.lib" )
#pragma comment( lib, "Normaliz.lib" )
#if defined _DEBUG
#pragma comment( lib, "libcurld.lib" )
#else
#pragma comment( lib, "libcurl.lib" )
#endif

// Json for C++
#include <nlohmann/json.hpp>

// Crypto++
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#if defined _DEBUG
#pragma comment( lib, "cryptlibd.lib" )
#else
#pragma comment( lib, "cryptlib.lib" )
#endif

// Compiler
#pragma warning( pop ) // reset warning level
#pragma warning( push )
#pragma warning( disable: 4100 4307 4309 ) // unreferenced parameter; overflow; truncation
