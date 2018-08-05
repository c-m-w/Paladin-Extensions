/// Types.hpp

#pragma once

namespace PX::Types
{
	/** \brief Paladin constant char string. */
	typedef const char* cstr_t;
	/** \brief Paladin wide constant char string. */
	typedef const wchar_t* wcstr_t;
	/** \brief Paladin address variable. */
	typedef uintptr_t ptr_t;
	/** \brief Paladin byte datatype. Stores one byte of data. */
	typedef unsigned char byte_t;
	/** \brief Paladin callback function type. */
	typedef void( PX_API fn_callback_t )( );
}
