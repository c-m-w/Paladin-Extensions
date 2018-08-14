/// Inclusions.hpp

#pragma once
#pragma warning( push, 0 )

#include <Jeremia-h/Standard Library.hpp>

#include <Windows.h>
#include <strsafe.h>
#include <shellapi.h>
#include <winternl.h>
#include <ntstatus.h>
#pragma comment( lib, "Shlwapi.lib" )

#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#pragma comment( lib, "cryptlib.lib" )

#include <curl/curl.h>
#pragma comment( lib, "Ws2_32.lib" )
#pragma comment( lib, "wldap32.lib" )
#pragma comment( lib, "Crypt32.lib" )
#pragma comment( lib, "Normaliz.lib" )
#pragma comment( lib, "libcurl_a.lib" )

#include <comdef.h>
#include <WbemIdl.h>
#pragma comment( lib, "wbemuuid.lib" )
#include <TlHelp32.h>

#include <Psapi.h>

#include <DirectX/d3d9.h>
#pragma comment( lib, "d3d9.lib" )
#include <DirectX/d3dx9core.h>
#include <DirectX/d3dx9math.h>
#include <DirectX/d3dx9tex.h>
#pragma comment( lib, "d3dx9.lib" )

#include <IconFontCppHeaders/IconsFontAwesome5-Solid.hpp>

#include <vurtun/nuklear.h>
#include <vurtun/demo/d3d9/nuklear_d3d9.h>

#include <Shlwapi.h>
#include <nlohmann/json.hpp>

#include <playsoundapi.h>
#pragma comment( lib, "Winmm.lib" )

#pragma warning( pop )
