/// Framework.hpp

#pragma once

#include <J-e-r-e-m-i-a-h/Standard Namespace.hpp>

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

#define NK_PRIVATE
#include <vurtun/nuklear.h>
#include <vurtun/demo/d3d9/nuklear_d3d9.h>
#include "Drawing/User Interface.hpp"

/**
 * \brief Application Information - These files provide general utilities for storing and managing application information
 */
#include <Shlwapi.h>
#include <nlohmann/json.hpp>
#include "Application/Information/Configuration.hpp"
