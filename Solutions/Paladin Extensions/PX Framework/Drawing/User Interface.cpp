/// User Interface.cpp

#define PX_NUKLEAR_IMPLEMENTATION

#include "../PX Framework.hpp"

namespace Paladin
{
    namespace ui
    {
        void Button( )
        {
            nk_button_label( new nk_context, new char );
        }
    }
}
