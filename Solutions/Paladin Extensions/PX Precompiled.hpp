/// PX Precompiled.hpp

#pragma once

// Compiler
#pragma warning( push, 0 )

// Standard C++ Library
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS // review Uncomment?
#include <Jeremia-h/Standard Library.hpp>

// Windows
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#undef LoadLibraryEx
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

// Crypto++
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#pragma comment( lib, "cryptlib.lib" )

// cURL
#define CURL_STATICLIB
#include <curl/curl.h>
#pragma comment( lib, "Ws2_32.lib" )
#pragma comment( lib, "wldap32.lib" )
#pragma comment( lib, "Crypt32.lib" )
#pragma comment( lib, "Normaliz.lib" )
#pragma comment( lib, "libcurl_a.lib" )

// Direct X
#include <d3d9.h>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <DirectXMath.h>
#include <d3dx9tex.h>
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "d3d9.lib" )

// Fonts
#include <IconFontCppHeaders/IconsFontAwesome5-Solid.hpp>

// Json
#include <nlohmann/json.hpp>
#undef xor

// Compiler
#pragma warning( pop )
#pragma warning( disable: 4098 4099 4100 4307 4309 4996 )
