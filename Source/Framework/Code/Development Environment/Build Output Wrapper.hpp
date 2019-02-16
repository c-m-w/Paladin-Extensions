/// Build Output Wrapper.hpp

#pragma once

/** \brief Converts a symbol to a string */
/** \param Symbol Symbol to convert */
#define Stringize( Symbol ) #Symbol
/** \brief Converts a symbol's value to a string */
/** \param Symbol Symbol to convert */
#define StringizeValue( Symbol ) Stringize( Symbol )
/** \brief Outputs an error to the build queue. Use `#pragma message( ERROR( ... ) )` for output */
/** \param Code Symbol for code error */
/** \param Message Symbol for error message */
#define ERROR( Code, Message ) __FILE__ "(" StringizeValue( __LINE__ ) "): error " Stringize( Code ) ": " Stringize( Message )
/** \brief Outputs a warning to the build queue. Use `#pragma message( WARNING( ... ) )` for output */
/** \param Code Symbol for code warning */
/** \param Message Symbol for warning message */
#define WARNING( Code, Message ) __FILE__ "(" StringizeValue( __LINE__ ) "): warning " Stringize( Code ) ": " Stringize( Message )
/** \brief Outputs an message to the build queue. Use `#pragma message( MESSAGE( ... ) )` for output */
/** \param Code Symbol for code message */
/** \param Message Symbol for message */
#define MESSAGE( Code, Message ) __FILE__ "(" StringizeValue( __LINE__ ) "): note " Stringize( Code ) ": " Stringize( Message )
