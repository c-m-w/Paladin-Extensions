/// Inclusions.hpp

#pragma once
#pragma warning( push, 0 )

// Standard
#include <Jeremia-h/Standard Library.hpp>

// Windows
#include <Windows.h>
#include <VersionHelpers.h>
#include <shellapi.h>
#include <winternl.h>
#include <ntstatus.h>
#include <strsafe.h>
#include <Shlwapi.h>
#include <intrin.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <comdef.h>
#include <WbemIdl.h>
#pragma comment( lib, "Shlwapi.lib" )
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
#if defined _DEBUG
#pragma comment( lib, "d3dx9d.lib" )
#else
#pragma comment( lib, "d3dx9.lib" )
#endif
#pragma comment( lib, "d3d9.lib" )

// Fonts
#include <IconFontCppHeaders/IconsFontAwesome5-Solid.hpp>

// Nuklear
#include <vurtun/nuklear.h>
#include <vurtun/demo/d3d9/nuklear_d3d9.h>

// Json
#include <nlohmann/json.hpp>

#undef xor
#undef LoadLibraryEx

#pragma warning( pop )
