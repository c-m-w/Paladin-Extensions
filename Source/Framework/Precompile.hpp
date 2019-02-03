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

#include <curl/include/curl/curl.h>
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
