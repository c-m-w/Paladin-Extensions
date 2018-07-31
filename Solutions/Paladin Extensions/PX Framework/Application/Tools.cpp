/// Tools.cpp

#include "../PX Framework.hpp"

namespace PX
{
	namespace Tools
	{
		std::wstring PX_API GetDirectory( unsigned uEscapeLevels )
		{
			auto wszBuffer = static_cast< wchar_t* >( malloc( MAX_PATH ) );
			GetModuleFileName( nullptr, wszBuffer, MAX_PATH );
			std::wstring wstrDirectory = wszBuffer;

			for ( auto i = 0u; i <= uEscapeLevels; i++ )
				wstrDirectory = wstrDirectory.substr( 0, wstrDirectory.find_last_of( L'\\' ) );

			return wstrDirectory;
		}
	}
}
