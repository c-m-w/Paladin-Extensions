/// Utilities.hpp

#pragma once

#define M_ABSTRACT_CLASS class
#define M_ABSTRACT_STRUCT struct

namespace Paladin
{
	/**
	 * \brief Properly sized datatype to hold time.
	 */
	typedef unsigned long long moment_t;
	/**
	 * \brief Gets the local time
	 * \tparam _Datatype The format of time to return in ( std::chrono )
	 * \return Local time in specified format
	 */
	template< typename _Datatype > moment_t GetMoment( );
	/**
	 * \brief Gets the local time
	 * \return Local time in milliseconds
	 */
	moment_t GetMoment( );

	/**
	 * \brief Sleeps the thread that has called for the amount of time, in the unit of time specified.
	 * \tparam _Datatype The unit of time to wait for ( std::chrono ).
	 */
	template< typename _Datatype > void Wait( moment_t );
	/**
	 * \brief Waits a specified amount of time in milliseconds.
	 */
	void Wait( moment_t );


	/**
	 * \brief Gets directory with specied directories upward
	 * \return Directory
	 */
	std::wstring GetDirectory( unsigned = 0 );

    /**
     * \brief Inheritable abstract class that only allows a single object of child class to be instantiated.\n
	           It is recommended that an empty constructor (no parameters) is created, even if it is empty.\n
	           It is suggested that you check that your original constructor was called if it has multiple arguments and you declared an empty constructor
     * \tparam _ChildClass Child class to be restricted
     */
    template< typename _ChildClass > M_ABSTRACT_CLASS ISingleton
    {
    public:
		ISingleton( ) = default;
		~ISingleton( ) = default;

        ISingleton( ISingleton && ) = delete;
        ISingleton( const ISingleton & ) = delete;

        ISingleton &operator=( ISingleton && ) = delete;
        ISingleton &operator=( const ISingleton & ) = delete;

	    template< typename ... _Argument > static _ChildClass &Get( _Argument ... );
    };

    /**
     * \brief Casts strings\n
	           Supports any combination of conversion from `std::string` and `std::wstring` to `std::string` and `std::wstring`
     * \tparam _To Desired string type
     * \tparam _From Current string
     * \return Returns string in desired type
     */
    template< typename _To, typename _From > _To string_cast( const _From & );
    /**
     * \brief Casts strings\n
	           Supports any combination of conversion from `const char *` and `const wchar_t *` to `std::string` and `std::wstring`
     * \tparam _To Desired string type
     * \tparam _From Current string
     * \return Returns string in desired type
     */
    template< typename _To, typename _From > _To string_cast( _From * );
}

#include "Utilities.tpp"
