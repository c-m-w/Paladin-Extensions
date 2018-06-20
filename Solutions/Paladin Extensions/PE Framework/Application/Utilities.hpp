/// Utilities.hpp

#pragma once

namespace Paladin
{
    /**
    * \brief Casts strings; supports any combination of conversion from `std::string` and `std::wstring` to `std::string` and `std::wstring`
    * \tparam _To Desired string type
    * \tparam _From Current string
    * \return Returns string in desired type
    */
    template< typename _To, typename _From > _To string_cast( const _From & );
    /**
    * \brief Casts strings; supports any combination of conversion from `const char *` and `const wchar_t *` to `std::string` and `std::wstring`
    * \tparam _To Desired string type
    * \tparam _From Current string
    * \return Returns string in desired type
    */
    template< typename _To, typename _From > _To string_cast( _From * );
}
