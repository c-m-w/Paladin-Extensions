/// CWindowHeader.hpp

#pragma once

class CWindowHeader: public IContainer
{
private:

	void CreateDrawables( ) override;

	bool bUseIcon = false;
	std::string strTitle { };
	std::string strSubtitle { };
	Utilities::callback_t _OnMinimize { };
	Utilities::callback_t _OnClose { };

public:

	constexpr static auto HEIGHT = 40;
	constexpr static auto ICON_SIZE = 40;
	constexpr static auto TEXT_HEIGHT = 16;

	CWindowHeader( bool bUseIcon, const std::string& strTitle, const std::string& strSubtitle, const Utilities::callback_t& _OnMinimize, const Utilities::callback_t& _OnClose );

	void Initialize( ) override;
};
