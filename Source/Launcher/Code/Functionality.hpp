/// Functionality.hpp

#pragma once

class CFunctionality: public IBase
{
private:

	CApplicationWindow *pApplicationWindow = nullptr;
	CWindow *pWindow = nullptr;
	CContainer *pWaitingContainer = nullptr;
	CVectorGraphic *pLoadingLogo = nullptr;
	timer_t _LogoAlphaTimer = timer_t( FADE_TIME, BEHAVIOUR_REFLECT );
	CContainer *pLoginCodeContainers[ CAuthentication::MAX_LOGIN_CODE ] { };
	CText *pConnectionErrorNotificationTop = nullptr;
	CText *pConnectionErrorNotificationBottom = nullptr;
	CText *pServerErrorNotificationTop = nullptr;
	CText *pServerErrorNotificationBottom = nullptr;
	CText *pBannedNotificationTop = nullptr;
	CText *pBannedNotificationBottom = nullptr;
	CText *pInvalidKeyNotificationTop = nullptr;
	CText *pInvalidKeyNotificationBottom = nullptr;
	CInputBox *pInvalidKeyInput = nullptr;
	CButton *pInvalidKeyEnterKey = nullptr;
	CText *pInvalidHardwareNotificationTop = nullptr;
	CText *pInvalidHardwareNotificationBottom = nullptr;
	CText *pLoginNotificationTop = nullptr;
	CText *pLoginNotificationBottom = nullptr;
	CText *pStaffLoginNotificationTop = nullptr;
	CText *pStaffLoginNotificationBottom = nullptr;
	CContainer **pCurrentContainer = nullptr, **pLastContainer = nullptr;
	animated_value_t< vector2_t > *pLastContainerLocation = nullptr, *pNextContainerLocation = nullptr;
	animated_value_t< double > *pNextContainerAlphaFade = nullptr;
	ELoginCode _LoginCode = ELoginCode::NONE;
	moment_t mmtContainerChangeTime = 0ull;
	bool bConnected = false;
	bool bExit = false;
	bool bLogoFaded = false;

	bool Initialize( ) override;
	void Uninitialize( ) override;

	void ChangeCurrentContainer( CContainer *&pNew );
	void CheckContainerAnimation( );

public:

	constexpr static auto LAUNCHER_WIDTH = 8.0,
						  LAUNCHER_HEIGHT = 5.0,
						  FPS = 60.0;
	constexpr static auto FADE_TIME = 1500ull;
	constexpr static auto ANIMATION_TIME = 1000ull;
	constexpr static auto ANIMATION_EASE_IN = EASE_SINE2;
	constexpr static auto ANIMATION_EASE_OUT = EASE_INVSINE1;
	inline const static std::string TITLE = ENC( "Paladin Extensions" );
	inline const static std::string SUBTITLE = ENC( "Launcher" );

	void Run( );
	void DrawLoop( );
} inline _Functionality;
