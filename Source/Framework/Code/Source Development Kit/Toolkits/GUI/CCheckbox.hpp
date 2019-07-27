/// CCheckbox.hpp

#pragma once

class CCheckbox: public IContainer
{
private:

	CVectorGraphic* pIcon = nullptr;
	animated_value_t< Utilities::vector2_t >* _LocationAnimation = nullptr;
	animated_value_t< Utilities::vector2_t >* _SizeAnimation = nullptr;
	std::string strSubject = ENC( "Subject" );
	CText* pSubject = nullptr;
	bool* pEnabled = nullptr;

public:

	static constexpr auto TEXT_HEIGHT = 0.11458333333;
	static constexpr auto ICON_HEIGHT = 0.125;
	static constexpr auto SPACING = 0.05208333333;
	static constexpr auto FONT = FONT_ROBOTO;
	const static inline std::string strEnabledIcon = ENC( R"(Icons\Check Square.svg)" );
	const static inline std::string strDisabledIcon = ENC( R"(Icons\Square.svg)" );

	CCheckbox( ) = default;

	void Initialize( ) override;
	void SetSubject( const std::string& strNewSubject );
	void SetVariable( bool* pNewEnabled );
	Utilities::vector2_t CalculateRequiredSpace( );
};
