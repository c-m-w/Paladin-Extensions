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

	constexpr static auto HEIGHT = 0.4167;
	constexpr static auto ICON_SIZE = 0.4167;
	constexpr static auto TEXT_HEIGHT = 1.0 / 6.0;

	CWindowHeader( bool bUseIcon, const std::string& strTitle, const std::string& strSubtitle, const Utilities::callback_t& _OnMinimize, const Utilities::callback_t& _OnClose );

	void Initialize( ) override;
};
