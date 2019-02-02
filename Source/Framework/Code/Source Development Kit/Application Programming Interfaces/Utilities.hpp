/// Utilities.hpp

#pragma once

/** \brief Contains utilities to be used in other areas of the framework / other projects. */
namespace Utilities
{
	/** \brief Datatype to store time. */
	using moment_t = unsigned __int64;

	/** \brief Gets the time since epoch in milliseconds. */
	/** \return Time since epoch in milliseconds. */
	moment_t GetMoment( );
	void Pause( moment_t mmtPauseLength = 1ui64 );
}

#include "Utilities.inl"
