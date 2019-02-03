/// Precompile.hpp

#pragma once

// Compiler
#pragma warning( push, 0 ) // warning level set to 0
#include <codeanalysis/warnings.h>
#pragma warning( disable: ALL_CODE_ANALYSIS_WARNINGS )

// Standard C++
#define _SILENCE_CXX17_UNCAUGHT_EXCEPTION_DEPRECATION_WARNING // crypto++
#include "Code/Development Environment/Standard Library.hpp"
#undef _SILENCE_CXX17_UNCAUGHT_EXCEPTION_DEPRECATION_WARNING

// Windows
#define WIN32_LEAN_AND_MEAN // remove unnecessary includes
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

#undef ERROR

// D3D
#include <d3d9.h>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <DirectXMath.h>
#include <d3dx9tex.h>
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "d3d9.lib" )

#include <ft2build.h>
#include FT_FREETYPE_H
#pragma comment( lib, "freetype.lib" )

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
