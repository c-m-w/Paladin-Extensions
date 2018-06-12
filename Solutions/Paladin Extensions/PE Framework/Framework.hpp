/// Framework.hpp

#pragma once

#include <J-e-r-e-m-i-a-h/Standard Namespace.hpp>

// Application
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Application/Debug.hpp"

// Security
#include <cryptopp/aes.h>
#include "Security/Encryption.hpp"

#include <curl/curl.h>
#include "Security/Connectivity.hpp"

#include "Security/Injection.hpp"

// Drawing
#include <d3d9.h>
#include "Drawing/Render.hpp"
#include "Drawing/User Interface.hpp"

// Application Information
#include <nlohmann/json.hpp>
#include "Application/Information/Configuration.hpp"
