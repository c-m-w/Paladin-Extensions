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

	unsigned char operator[ ]( std::size_t zColor ) const;
	float operator[ ]( float flColor ) const;
	bool operator==( const color_t &rhs ) const;
	bool operator!=( const color_t &rhs ) const;
	color_t &operator=( const color_t &rhs );

	unsigned GetRGBA( ) const;
	unsigned PutRGBA( unsigned uData );
	__declspec( property( get = GetRGBA, put = PutRGBA ) ) unsigned rgba;
	unsigned GetARGB( ) const;
	unsigned PutARGB( unsigned uData );
	__declspec( property( get = GetARGB, put = PutARGB ) ) unsigned argb;

	unsigned char GetRed( ) const;
	unsigned char GetGreen( ) const;
	unsigned char GetBlue( ) const;
	unsigned char GetAlpha( ) const;
	unsigned char PutRed( unsigned char bData );
	unsigned char PutGreen( unsigned char bData );
	unsigned char PutBlue( unsigned char bData );
	unsigned char PutAlpha( unsigned char bData );
	__declspec( property( get = GetRed, put = PutRed ) ) unsigned char r;
	__declspec( property( get = GetGreen, put = PutGreen ) ) unsigned char g;
	__declspec( property( get = GetBlue, put = PutBlue ) ) unsigned char b;
	__declspec( property( get = GetAlpha, put = PutAlpha ) ) unsigned char a;

	float GetRedFraction( ) const;
	float GetGreenFraction( ) const;
	float GetBlueFraction( ) const;
	float GetAlphaFraction( ) const;
	float PutRedFraction( float flData );
	float PutGreenFraction( float flData );
	float PutBlueFraction( float flData );
	float PutAlphaFraction( float flData );
	__declspec( property( get = GetRedFraction, put = PutRedFraction ) ) float rfl;
	__declspec( property( get = GetGreenFraction, put = PutGreenFraction ) ) float gfl;
	__declspec( property( get = GetBlueFraction, put = PutBlueFraction ) ) float bfl;
	__declspec( property( get = GetAlphaFraction, put = PutAlphaFraction ) ) float afl;

	void *GetDataPointer( ) const;
	void *PutDataPointer( void * ) = delete;
	__declspec( property( get = GetDataPointer, put = PutDataPointer ) ) void *p;

	double Get709Luminance( ) const;
	double Put709Luminance( double ) = delete;
	__declspec( property( get = Get709Luminance, put = Put709Luminance ) ) double luma;

	double Get601Luminance( ) const;
	double Put601Luminance( double ) = delete;
	__declspec( property( get = Get601Luminance, put = Put601Luminance ) ) double luma601;
};

class CColor
{
public:
	static color_t GetGradient( color_t clrStart, color_t clrEnd, float flProgress );

	struct sequence_t
	{
		color_t clr { };
		Utilities::moment_t mmtDuration = 0;
	};

private:
	sequence_t pSequences[ 7 ];
	std::size_t zSequences = 0u;
	Utilities::moment_t mmtTotalDuration = 0;

public:
	CColor( ) = default;
	CColor( color_t clrFirstSequence, Utilities::moment_t mmtFirstSequence );
	CColor( std::vector< sequence_t > vecSequences );

	color_t GetColor( );
	void PutColor( ) = delete;
	__declspec( property( get = GetColor, put = PutColor ) ) color_t clr;

	sequence_t GetSequence( std::size_t zSequence );
	sequence_t operator[ ]( std::size_t zSequence );

	void PutNewColorSequence( sequence_t seq );
	CColor &operator<<( sequence_t seq );
	void DeleteColorSequence( std::size_t zSequence );
	CColor &operator>>( std::size_t zSequence );
};
