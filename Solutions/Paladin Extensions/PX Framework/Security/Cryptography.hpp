/// Encryption.hpp

#pragma once

namespace PX
{
    namespace Cryptography
    {
        std::string GenerateHash( const std::string& );
        // Pass either CryptoPP::Base64Decoder or CryptoPP::Base64Encoder as _t
		template< typename _t > std::string Base64( const std::string& );
        std::string Encrypt( const std::string&, const std::string& );
    }

    namespace XOR
    {
        constexpr int PX_API LinearCongruentialGenerator( int iRounds )
        {
            return 1013904223 + 1664525 * ( iRounds > 0 ? LinearCongruentialGenerator( iRounds - 1 )
                                            : ( __TIME__[ 7 ] - '0' ) * 1 + ( __TIME__[ 6 ] - '0' ) * 10 + ( __TIME__[ 4 ] - '0' ) * 60 +
                                            ( __TIME__[ 3 ] - '0' ) * 600 + ( __TIME__[ 1 ] - '0' ) * 3600 + ( __TIME__[ 0 ] - '0' ) * 36000
                                            & 0xFFFFFFFF );
        }
    }
}

#include "Cryptography.inl"
