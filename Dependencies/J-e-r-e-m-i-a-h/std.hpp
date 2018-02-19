#pragma once

/// Entire C++ Standard library, compiled by bhopfu1

/// Utilities library
#include <cstdlib>
#include <csignal>
#include <csetjmp>
#include <cstdarg>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <bitset>
#include <functional>
#include <utility>
#include <ctime>
#include <chrono>
#include <cstddef>
#include <initializer_list>
#include <tuple>
//#include <any>				// C++ 17
//#include <optional>			// C++ 17
//#include <variant>			// C++ 17
//#include <compare>			// C++ 17

/// Dynamic memory management
#include <new>
#include <memory>
#include <scoped_allocator>
//#include <memory_resource>	// Not Visual Studio 2017 Pre-installed

/// Numeric limits
#include <climits>
#include <cfloat>
#include <cstdint>
#include <cinttypes>
#include <limits>

/// Error handling
#include <exception>
#include <stdexcept>
#include <cassert>
#include <system_error>
#include <cerrno>

/// Strings library
#include <cctype>
#include <cwctype>
#include <cstring>
#include <cwchar>
#include <cuchar>
#include <string>
//#include <string_view>		// Not Visual Studio 2017 Pre-installed
//#include <charconv>			// Not Visual Studio 2017 Pre-installed

/// Containers library
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>

/// Algorithms library
#include <algorithm>
//#include <execution>			// Not Visual Studio 2017 Pre-installed

/// Iterators library
#include <iterator>

/// Numberics library
#include <cmath>
#include <complex>
#include <valarray>
#include <random>
#include <numeric>
#include <ratio>
#include <cfenv>

/// Input/output library
#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <syncstream>			// Not Visual Studio 2017 Pre-installed
#include <strstream>
#include <iomanip>
#include <streambuf>
#include <cstdio>

/// Localization library
#include <locale>
#include <clocale>
#include <codecvt>

/// Regular Expressions library
#include <regex>

/// Atomic Operations library
#include <atomic>

/// Thread support library
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <future>
#include <condition_variable>

/// Filesystem library
#include <filesystem>
