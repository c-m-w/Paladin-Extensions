/// Debug.hpp

#pragma once

namespace PX
{
    namespace dbg
    {
        // INFO: Asserts parameter to empty initialization version of parameter
        template< typename _t > bool PX_API Assert( _t );

        PX_DEF endl = '\n';

        // INFO: Used to change console print color of debug output
        struct out_clr_t
        {
            WORD m_wDesiredAttributes;
            explicit PX_API out_clr_t( const WORD );
        };

        // INFO: Managed debug output; used like std::cout
        class out_t
        {
        public:
            out_t& PX_API operator<<( const out_clr_t& );
            template< typename _t > out_t& PX_API operator<<( const _t& );
        } PX_SDK out;

        void PX_API PrintLastError( );
    }
}

#include "Debug.inl"
