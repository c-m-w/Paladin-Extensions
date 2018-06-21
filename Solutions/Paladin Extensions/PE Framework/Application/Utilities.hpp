/// Utilities.hpp

#pragma once

namespace Paladin
{
#define abstract_class class
    /**
     * \brief Inheritable abstract class that only allows a single object of child class to be instantiated
     * \tparam _ChildClass Child class to be restricted
     */
    template< typename _ChildClass > abstract_class ISingleton
    {
    protected:
        ISingleton( ) = default;
        ~ISingleton( ) = default;
    public:
        ISingleton( ISingleton && ) = delete;
        ISingleton( const ISingleton & ) = delete;

        ISingleton &operator=( ISingleton && ) = delete;
        ISingleton &operator=( const ISingleton & ) = delete;

        static _ChildClass &Get( );
    };

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
