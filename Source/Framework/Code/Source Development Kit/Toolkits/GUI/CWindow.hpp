/// CWindow.hpp

#pragma once

class CWindow: public CContainer
{
private:

	bool bUseIcon = false;
	std::string strTitle { };
	std::string strSubtitle { };
	Utilities::callback_t _OnMinimize = nullptr;
	Utilities::callback_t _OnClose = nullptr;
	CContainer* pPopupContainer = nullptr;
	CWindow* pPopup = nullptr;
	animated_value_t< Utilities::vector2_t >* pLocationAnimation = nullptr;
	animated_value_t< double >* pAlphaAnimation = nullptr;


public:

	constexpr static auto POPUP_FADE_TIME = 750ull;
	constexpr static auto POPUP_MOVE_TIME = 1500ull;

	CWindow( const rectangle_t& recLocation );

	void ShowIcon( );
	void SetTitle( const std::string& strNewTitle );
	void SetSubtitle( const std::string& strNewSubtitle );
	void SetMinimizeCallback( Utilities::callback_t _OnMinimizeCallback );
	void SetCloseCallback( Utilities::callback_t _OnCloseCallback );
	void Popup( CWindow* pNewPopup, bool bAbleToClosePopup );
	void ClosePopup( );
	void Initialize( ) override;
};
