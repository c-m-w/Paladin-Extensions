#pragma once
#pragma warning(disable : 4996)

#include "C++ Standard Library.hpp"

#include <Windows.h>
#include "Paladin Framework/Debugging.hpp"

#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/sha3.h>
#include <cryptopp/aes.h>
#include "Paladin Framework/Encryption.hpp"

#define CURL_STATICLIB
#include <curl/curl.h>
#include "Paladin Framework/Connectivity.hpp"

#include <nlohmann/json.hpp>
#include "Paladin Framework/Configuration.hpp"

#include <d3d9.h>
#include "Paladin Framework/Drawing.hpp"

#define WIN32_LEAN_AND_MEAN
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_D3D9_IMPLEMENTATION
#include <vurtun/nuklear.h>
#include "Paladin Framework/GUI.hpp"

using namespace Paladin;
