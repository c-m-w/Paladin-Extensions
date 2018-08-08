/// Framework.hpp

#pragma once

#include <Jeremia-h/Standard Library.hpp>

/**
 * \brief Application - These files provide general utilities for application development
 */
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include "Application/Utilities.hpp"

#include "Application/Debug.hpp"

#include "Application/Input.hpp"

/**
 * \brief Security - These files provide specific functionality for ensuring security and verifying authenticity
 */
#include <cryptopp/aes.h>
#include "Security/Encryption.hpp"

#include <curl/curl.h>
#include "Security/Connectivity.hpp"

#include <Psapi.h>
#include "Security/Injection.hpp"

/**
 * \brief Drawing - These files provide specific functionality for creating visuals
 */
#include <d3d9.h>
#include "Drawing/Render.hpp"

#if defined _DEBUG
#define M_DEPENDENCIES 3
#else
#define M_DEPENDENCIES 0
#endif
#if defined NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_D3D9_IMPLEMENTATION
#else
#define NK_PRIVATE
#endif
#include <vurtun/nuklear.h>
#include <vurtun/demo/d3d9/nuklear_d3d9.h>
#include <IconFontCppHeaders/IconsFontAwesome5-Solid.hpp>
#include "Drawing/User Interface.hpp"

/**
 * \brief Application Information - These files provide general utilities for storing and managing application information
 */
#include <Shlwapi.h>
#include <nlohmann/json.hpp>
#include "Application/Information/Configuration.hpp"
