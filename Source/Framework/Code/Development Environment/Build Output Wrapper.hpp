/// Build Output Wrapper.hpp

#pragma once

#define Stringize( L ) #L
#define StringizeValue( L ) Stringize( L )
#define ERROR( Code, Message ) __FILE__ "(" StringizeValue( __LINE__ ) "): error " Stringize( Code ) ": " Stringize( Message )
#define WARNING( Code, Message ) __FILE__ "(" StringizeValue( __LINE__ ) "): warning " Stringize( Code ) ": " Stringize( Message )
#define MESSAGE( Code, Message ) __FILE__ "(" StringizeValue( __LINE__ ) "): note " Stringize( Code ) ": " Stringize( Message )
