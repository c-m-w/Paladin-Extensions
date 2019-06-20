/// CWindow.hpp

#pragma once

enum EWindowFlags
{
	WINDOW_NONE,
	WINDOW_HEADER	= 1 << 0,
	WINDOW_SUBTITLE	= 1 << 1,
	WINDOW_ICON		= 1 << 2,
	WINDOW_CLOSABLE	= 1 << 3,
	WINDOW_MAX
};

class CWindow: public IContainer
{
private:

	std::string strTitle { };
	std::string strSubtitle { };
	EWindowFlags _Flags = WINDOW_NONE;

public:

	CWindow( EWindowFlags _Flags, const rectangle_t& recLocation );

	void SetTitle( const std::string& strNewTitle );
	void SetSubtitle( const std::string& strNewSubtitle );
	void CreateDrawables( ) override;
};
