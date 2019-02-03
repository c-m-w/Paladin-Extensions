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

	unsigned char operator[ ]( int iColor ) const;
	float operator[ ]( float flColor ) const;
	bool operator==( const color_t &rhs ) const;
	bool operator!=( const color_t &rhs ) const;

	unsigned GetRGBA( ) const;
	void PutRGBA( unsigned uData );
	__declspec( property( get = GetRGBA, put = PutRGBA ) ) unsigned rgba;
	unsigned GetARGB( ) const;
	void PutARGB( unsigned uData );
	__declspec( property( get = GetARGB, put = PutARGB ) ) unsigned argb;

	unsigned char GetRed( )  const;
	unsigned char GetGreen( )const;
	unsigned char GetBlue( ) const;
	unsigned char GetAlpha( )const;
	void PutRed( unsigned char bData );
	void PutGreen( unsigned char bData );
	void PutBlue( unsigned char bData );
	void PutAlpha( unsigned char bData );
	__declspec( property( get = GetRed, put = PutRed ) ) unsigned char r;
	__declspec( property( get = GetGreen, put = PutGreen ) ) unsigned char g;
	__declspec( property( get = GetBlue, put = PutBlue ) ) unsigned char b;
	__declspec( property( get = GetAlpha, put = PutAlpha ) ) unsigned char a;

	float GetRedFraction( )  const;
	float GetGreenFraction( )const;
	float GetBlueFraction( ) const;
	float GetAlphaFraction( )const;
	void PutRedFraction( float flData );
	void PutGreenFraction( float flData );
	void PutBlueFraction( float flData );
	void PutAlphaFraction( float flData );
	__declspec( property( get = GetRedFraction, put = PutRedFraction ) ) float rfl;
	__declspec( property( get = GetGreenFraction, put = PutGreenFraction ) ) float gfl;
	__declspec( property( get = GetBlueFraction, put = PutBlueFraction ) ) float bfl;
	__declspec( property( get = GetAlphaFraction, put = PutAlphaFraction ) ) float afl;

	void *GetDataPointer( ) const;
	void PutDataPointer( void * ) = delete;
	__declspec( property( get = GetDataPointer, put = PutDataPointer ) ) void *p;

	double Get709Luminance( ) const;
	void Put709Luminance( double ) = delete;
	__declspec( property( get = Get709Luminance, put = Put709Luminance ) ) double luma;

	double Get601Luminance( ) const;
	void Put601Luminance( double ) = delete;
	__declspec( property( get = Get601Luminance, put = Put601Luminance ) ) double luma601;
};

class CColor
{
public:
	static color_t GetGradient( color_t clrStart, color_t clrEnd, float flProgress );

private:
	struct
	{
		color_t clrColor;
		Utilities::moment_t mmtDuration = 0;
	} _Info[ 7 ];
	Utilities::moment_t mmtTotalDuration = 0;


};
