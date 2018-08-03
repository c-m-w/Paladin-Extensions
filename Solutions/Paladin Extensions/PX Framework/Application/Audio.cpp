/// Audio.cpp

#include "../PX Framework.hpp"

namespace PX::Audio
{
	std::map< Types::cstr_t, sf::SoundBuffer > mpSounds;

	bool PX_API LoadSound( Types::cstr_t szSoundToAdd, sf::SoundBuffer& sbNewSoundBuffer )
	{
		const static auto strSoundDirectory = Files::GetDirectory( 1 ) + LR"(\Resources\Sound\)";
		const auto strBuffer = Tools::string_cast< std::string >( strSoundDirectory ) + szSoundToAdd;
		return sbNewSoundBuffer.loadFromFile( strBuffer );
	}

	bool PX_API FindSound( Types::cstr_t szSearch, sf::SoundBuffer& sfSound )
	{
		auto mpSearch = mpSounds.find( szSearch );
		if ( mpSearch == mpSounds.end( ) || !mpSearch->first )
			return false;
		sfSound = mpSearch->second;
		return true;
	}

	void PX_API PlaySound( Types::cstr_t szFileName )
	{
		sf::SoundBuffer sbSound;
		if ( !FindSound( szFileName, sbSound ) )
		{
			if ( !dbg::Assert( LoadSound( szFileName, sbSound ) ) )
				return;
			mpSounds.insert( std::pair< Types::cstr_t, sf::SoundBuffer >( szFileName, sbSound ) );
			PlaySound( szFileName );
			return;
		}

		auto fnPlaySound = [ ] ( sf::SoundBuffer sbBuffer )
		{
			static sf::Sound sSound;
			sSound.setBuffer( sbBuffer );
			sSound.setVolume( 50.f );
			sSound.play( );
			const auto mmtStart = Tools::GetMoment( );
			Tools::Wait( sbBuffer.getDuration( ).asMilliseconds( ) );
			sSound.resetBuffer( );
		};

		std::thread tSound( fnPlaySound, sbSound );
		tSound.detach( );
	}
}
