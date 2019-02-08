/// Color.hpp

#pragma once

enum EColor
{
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_ALPHA,
	COLOR_MAX
};

struct color_t
{
private:

	union
	{
		unsigned u;
		unsigned char b[ COLOR_MAX ];
	} _Data;

public:

	color_t( );
	color_t( unsigned uData );
	color_t( std::initializer_list< unsigned char > initData );
	color_t( std::initializer_list< int > initData );
	color_t( std::initializer_list< float > initData );

	[ [ nodiscard ] ] unsigned char operator[ ]( std::size_t zColor ) const;
	[ [ nodiscard ] ] float operator[ ]( float flColor ) const;
	[ [ nodiscard ] ] bool operator==( const color_t &rhs ) const;
	[ [ nodiscard ] ] bool operator!=( const color_t &rhs ) const;
	color_t &operator=( const color_t &rhs );

	[ [ nodiscard ] ] unsigned GetRGBA( ) const;
	unsigned PutRGBA( unsigned uData );
	__declspec( property( get = GetRGBA, put = PutRGBA ) ) unsigned rgba;
	[ [ nodiscard ] ] unsigned GetARGB( ) const;
	unsigned PutARGB( unsigned uData );
	__declspec( property( get = GetARGB, put = PutARGB ) ) unsigned argb;

	[ [ nodiscard ] ] unsigned char GetRed( ) const;
	[ [ nodiscard ] ] unsigned char GetGreen( ) const;
	[ [ nodiscard ] ] unsigned char GetBlue( ) const;
	[ [ nodiscard ] ] unsigned char GetAlpha( ) const;
	unsigned char PutRed( unsigned char bData );
	unsigned char PutGreen( unsigned char bData );
	unsigned char PutBlue( unsigned char bData );
	unsigned char PutAlpha( unsigned char bData );
	__declspec( property( get = GetRed, put = PutRed ) ) unsigned char r;
	__declspec( property( get = GetGreen, put = PutGreen ) ) unsigned char g;
	__declspec( property( get = GetBlue, put = PutBlue ) ) unsigned char b;
	__declspec( property( get = GetAlpha, put = PutAlpha ) ) unsigned char a;

	[ [ nodiscard ] ] float GetRedFraction( ) const;
	[ [ nodiscard ] ] float GetGreenFraction( ) const;
	[ [ nodiscard ] ] float GetBlueFraction( ) const;
	[ [ nodiscard ] ] float GetAlphaFraction( ) const;
	float PutRedFraction( float flData );
	float PutGreenFraction( float flData );
	float PutBlueFraction( float flData );
	float PutAlphaFraction( float flData );
	__declspec( property( get = GetRedFraction, put = PutRedFraction ) ) float rfl;
	__declspec( property( get = GetGreenFraction, put = PutGreenFraction ) ) float gfl;
	__declspec( property( get = GetBlueFraction, put = PutBlueFraction ) ) float bfl;
	__declspec( property( get = GetAlphaFraction, put = PutAlphaFraction ) ) float afl;

	[ [ nodiscard ] ] void *GetDataPointer( ) const;
	void *PutDataPointer( void * ) = delete;
	__declspec( property( get = GetDataPointer, put = PutDataPointer ) ) void *p;

	[ [ nodiscard ] ] double Get709Luminance( ) const;
	double Put709Luminance( double ) = delete;
	__declspec( property( get = Get709Luminance, put = Put709Luminance ) ) double luma;

	[ [ nodiscard ] ] double Get601Luminance( ) const;
	double Put601Luminance( double ) = delete;
	__declspec( property( get = Get601Luminance, put = Put601Luminance ) ) double luma601;
};

class CColor
{
public:

	[ [ nodiscard ] ] static color_t GetGradient( color_t clrStart, color_t clrEnd, float flProgress );

	struct sequence_t
	{
		color_t clr { };
		unsigned __int64 uDuration = 0;
	};

private:

	sequence_t pSequences[ 7 ];
	std::size_t zSequences = 0u;
	unsigned __int64 uTotalDuration = 0;

public:

	CColor( ) = default;
	CColor( color_t clrFirstSequence, unsigned __int64 uFirstSequence );
	CColor( std::vector< sequence_t > vecSequences );

	[ [ nodiscard ] ] color_t GetColor( );
	void PutColor( ) = delete;
	__declspec( property( get = GetColor, put = PutColor ) ) color_t clr;

	[ [ nodiscard ] ] sequence_t GetSequence( std::size_t zSequence );
	[ [ nodiscard ] ] sequence_t operator[ ]( std::size_t zSequence );

	void PutNewColorSequence( sequence_t seq );
	CColor &operator<<( sequence_t seq );
	void DeleteColorSequence( std::size_t zSequence );
	CColor &operator>>( std::size_t zSequence );
};
