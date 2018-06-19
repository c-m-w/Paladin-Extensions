/// Utilities.hpp

#pragma once

namespace Paladin
{
	/**
	* \brief Casts strings; supports any combination of conversion from std::string, std::wstring, const char *, and const wchar_t *
	* \tparam _Desired Desired string type
	* \return Returns string in desired type
	*/
	template < typename _Desired, typename _Current > _Desired string_cast( _Current );
}