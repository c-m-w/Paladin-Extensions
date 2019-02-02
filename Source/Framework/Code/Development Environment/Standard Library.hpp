/// Standard Library.hpp

#pragma once

// Concepts library
#if _MSVC_LANG > 201703L // C++ 20 or later
#include <concepts>
#endif

// Utilities library
#include <cstdlib>
#include <csignal>
#include <csetjmp>
#include <cstdarg>
#include <typeinfo>
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <typeindex>
#include <type_traits>
#endif
#include <bitset>
#include <functional>
#include <utility>
#include <ctime>
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <chrono>
#endif
#include <cstddef>
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <initializer_list>
#include <tuple>
#endif
#if _MSVC_LANG >= 201703L // C++ 17 or later
#include <any>
#include <optional>
#include <variant>
#endif
#if _MSVC_LANG > 201703L // C++ 20 or later
#include <compare>
#include <version>
#endif

// Dynamic memory management
#include <new>
#include <memory>
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <scoped_allocator>
#endif
#if _MSVC_LANG >= 201703L // C++ 17 or later
#include <memory_resource>
#endif

// Numeric limits
#include <climits>
#include <cfloat>
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <cstdint>
#include <cinttypes>
#endif
#include <limits>

// Error handling
#include <exception>
#include <stdexcept>
#include <cassert>
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <system_error>
#endif
#include <cerrno>

// Strings library
#include <cctype>
#include <cwctype>
#include <cstring>
#include <cwchar>
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <cuchar>
#endif
#include <string>
#if _MSVC_LANG >= 201703L // C++ 17 or later
#include <string_view>
#include <charconv>
#endif

// Containers library
#include <array>
#include <vector>
#include <deque>
#include <list>
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <forward_list>
#endif
#include <set>
#include <map>
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <unordered_set>
#include <unordered_map>
#endif
#include <stack>
#include <queue>
#if _MSVC_LANG > 201703L // C++ 20 or later
#include <span>
#endif

// Algorithms library
#include <algorithm>
#if _MSVC_LANG >= 201703L // C++ 17 or later
#include <execution>
#endif

// Iterators library
#include <iterator>

// Numerics library
#include <cmath>
#include <complex>
#include <valarray>
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <random>
#endif
#include <numeric>
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <ratio>
#include <cfenv>
#endif
#if _MSVC_LANG > 201703L // C++ 20 or later
#include <bit>
#endif

// Input/output library
#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#if _MSVC_LANG > 201703L // C++ 20 or later
#include <syncstream>
#endif
#if _MSVC_LANG < 199711L // C++ 11 depricated
#include <strstream>
#endif
#include <iomanip>
#include <streambuf>
#include <cstdio>

// Localization library
#include <locale>
#include <clocale>
#if _MSVC_LANG >= 199711L // C++ 11
#if _MSVC_LANG < 201703L // C++ 17 deprecated
#include <codecvt>
#endif
#endif

// Regular Expressions library
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <regex>
#endif

// Atomic Operations library
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <atomic>
#endif

// Thread support library
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <thread>
#include <mutex>
#endif
#if _MSVC_LANG >= 201402L // C++ 14 or later
#include <shared_mutex>
#endif
#if _MSVC_LANG >= 199711L // C++ 11 or later
#include <future>
#include <condition_variable>
#endif

// Filesystem library
#if _MSVC_LANG >= 201703L // C++ 17 or later
#include <filesystem>
#endif
