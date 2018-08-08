/// Inclusions.hpp

#pragma once

#include <Jeremia-h/Standard Library.hpp>

#include <Windows.h>

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
#ifdef _DEBUG
#pragma comment( lib, "libcurl_a_debug.lib" )
#else
#pragma comment( lib, "libcurl_a.lib" )
#endif

#include <comdef.h>
#include <Wbemidl.h>
#pragma comment( lib, "wbemuuid.lib" )
#include <TlHelp32.h>

#include <Psapi.h>

#include <DirectX/d3d9.h>
#pragma comment( lib, "d3d9.lib" )

#include <IconFontCppHeaders/IconsFontAwesome5-Solid.hpp>

#include <vurtun/nuklear.h>
#include <vurtun/demo/d3d9/nuklear_d3d9.h>

#include <Shlwapi.h>
#include <nlohmann/json.hpp>

#include <playsoundapi.h>
#pragma comment( lib, "Winmm.lib" )
