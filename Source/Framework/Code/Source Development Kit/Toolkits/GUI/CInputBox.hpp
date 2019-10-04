/// CInputBox.hpp

#pragma once

class CInputBox: public IWidget
{
public:

	enum EFilter: unsigned
	{
		FILTER_NONE = 0,
		FILTER_LETTERS = 1 << 0,
		FILTER_NUMERIC = 1 << 1,
		FILTER_SPECIAL_CHARACTERS = 1 << 2,
		FILTER_SPACE = 1 << 3
	};

	enum EMode: unsigned
	{
		MODE_INSERT,
		MODE_REPLACE
	};

private:

	void CreateDrawables( ) override;

	std::string strBuffer { };
	unsigned uInsertionPoint = 0u;
	unsigned uFirstInsertionPointVisible = 0u;
	int iSelection = 0;
	EFilter _CurrentFilter = FILTER_NONE;
	EMode _CurrentMode = MODE_INSERT;
	std::size_t zMaxLength = 32u;

public:

	static constexpr auto TEXT_HEIGHT = 0.125;
	static constexpr auto PADDING = 0.03125;
	static constexpr auto FONT = FONT_ROBOTO_MONO;
	static constexpr auto FONT_WEIGHT = WEIGHT_REGULAR;
	static constexpr auto ROUNDING = 0.25;

	static inline std::function< bool( char ) > FILTERS[ 4 ]
	{
		[ ]( char chCharacter ) // FILTER_LETTERS
		{
			return chCharacter >= 'A' && chCharacter <= 'Z'
					|| chCharacter >= 'a' || chCharacter <= 'z';
		},
		[ ]( char chCharacter ) // FILTER_NUMERIC
		{
			return chCharacter >= '0' && chCharacter <= '9';
		},
		[ ]( char chCharacter ) // FILTER_SPECIAL_CHARACTERS
		{
			return chCharacter >= '!' && chCharacter <= '/'
					|| chCharacter >= ':' && chCharacter <= '@'
					|| chCharacter >= '[' && chCharacter <= '`'
					|| chCharacter >= '{' && chCharacter <= '~';
		},
		[ ]( char chCharacter ) // FILTER_SPACE
		{
			return chCharacter == ' ';
		}
	};

	CInputBox( );

	void AddFilter( EFilter _NewFilter );
	void RemoveFilter( EFilter _FilterToRemove );
	void NewCharacter( char chInsertion );
	void SetMaxLength( std::size_t zNewLength );
	std::string GetBuffer( );
	void OnKeyTyped( char chCharacter ) override;
	void OnCopy( ) override;
	void OnPaste( ) override;
};
