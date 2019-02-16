/// Color.hpp

#pragma once

/** \brief General color organization for arrays and unions */
enum EColor: unsigned char
{
	COLOR_ALPHA,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_RED,
	COLOR_MAX
};

/** \brief Structure used for managing a single color */
struct color_t
{
private:

	/** \brief Union to store color data */
	union
	{
		unsigned u;
		unsigned char b[ COLOR_MAX ];
	} _Data;

public:

	/** \brief Defaults structure to opaque white */
	color_t( );
	/** \brief Initializes data for structure with RGBA */
	/** \param uRGBA RGBA in unsigned form, in order of R << G << B << A */
	color_t( unsigned uRGBA );
	/** \brief Initializes data for structure with byte array */
	/** \param initData RGBA in byte form, in order of R, G, B, A. Unincluded members default to white. */
	color_t( std::initializer_list< unsigned char > initData );
	/** \brief Initializes data for structure with int array */
	/** \param initData RGBA in int form, in order of R, G, B, A. Unincluded members default to white. */
	color_t( std::initializer_list< int > initData );
	/** \brief Initializes data for structure with float array */
	/** \param initData RGBA in float form, in order of R, G, B, A. Unincluded members default to white. */
	color_t( std::initializer_list< float > initData );

	/** \brief Returns strength of specified color member */
	/** \param enumColor Color member to retrieve */
	/** \return Color member strength */
	[ [ nodiscard ] ] unsigned char operator[ ]( EColor enumColor ) const;
	/** \brief Returns strength of specified color member */
	/** \param iColor Color member to retrieve (use EColor for reference) */
	/** \return Color member strength */
	[ [ nodiscard ] ] unsigned char operator[ ]( int iColor ) const;
	/** \brief Returns strength of specified color member */
	/** \param flColor Color member to retrieve (use EColor for reference; like 2.f) */
	/** \return Color member strength in float form */
	[ [ nodiscard ] ] float operator[ ]( float flColor ) const;
	/** \brief Compares the colors of two color_ts */
	/** \param clrComparand Comparand */
	/** \return Color equality state */
	[ [ nodiscard ] ] bool operator==( const color_t &clrComparand ) const;
	/** \brief Compares the colors of two color_ts */
	/** \param clrComparand Comparand */
	/** \return Color inequality state */
	[ [ nodiscard ] ] bool operator!=( const color_t &clrComparand ) const;
	/** \brief Assigns color from color_t */
	/** \param clrAssigner Assigner */
	/** \return color after assignment */
	color_t &operator=( const color_t &clrAssigner );

	[ [ nodiscard ] ] unsigned GetRGBA( ) const;
	unsigned PutRGBA( unsigned uData );
	/** \brief Color data as RGBA */
	__declspec( property( get = GetRGBA, put = PutRGBA ) ) unsigned rgba;
	[ [ nodiscard ] ] unsigned GetARGB( ) const;
	unsigned PutARGB( unsigned uData );
	/** \brief Color data as ARGB */
	__declspec( property( get = GetARGB, put = PutARGB ) ) unsigned argb;

	[ [ nodiscard ] ] unsigned char GetRed( ) const;
	[ [ nodiscard ] ] unsigned char GetGreen( ) const;
	[ [ nodiscard ] ] unsigned char GetBlue( ) const;
	[ [ nodiscard ] ] unsigned char GetAlpha( ) const;
	unsigned char PutRed( unsigned char bData );
	unsigned char PutGreen( unsigned char bData );
	unsigned char PutBlue( unsigned char bData );
	unsigned char PutAlpha( unsigned char bData );
	/** \brief Color strength of red as byte */
	__declspec( property( get = GetRed, put = PutRed ) ) unsigned char r;
	/** \brief Color strength of green as byte */
	__declspec( property( get = GetGreen, put = PutGreen ) ) unsigned char g;
	/** \brief Color strength of blue as byte */
	__declspec( property( get = GetBlue, put = PutBlue ) ) unsigned char b;
	/** \brief Color strength of alpha as byte */
	__declspec( property( get = GetAlpha, put = PutAlpha ) ) unsigned char a;

	[ [ nodiscard ] ] float GetRedFraction( ) const;
	[ [ nodiscard ] ] float GetGreenFraction( ) const;
	[ [ nodiscard ] ] float GetBlueFraction( ) const;
	[ [ nodiscard ] ] float GetAlphaFraction( ) const;
	float PutRedFraction( float flData );
	float PutGreenFraction( float flData );
	float PutBlueFraction( float flData );
	float PutAlphaFraction( float flData );
	/** \brief Color strength of red as float */
	__declspec( property( get = GetRedFraction, put = PutRedFraction ) ) float rfl;
	/** \brief Color strength of green as float */
	__declspec( property( get = GetGreenFraction, put = PutGreenFraction ) ) float gfl;
	/** \brief Color strength of blue as float */
	__declspec( property( get = GetBlueFraction, put = PutBlueFraction ) ) float bfl;
	/** \brief Color strength of alpha as float */
	__declspec( property( get = GetAlphaFraction, put = PutAlphaFraction ) ) float afl;

	[ [ nodiscard ] ] void *GetDataPointer( ) const;
	void *PutDataPointer( void * ) = delete;
	/** \brief Color data pointer */
	__declspec( property( get = GetDataPointer, put = PutDataPointer ) ) void *p;

	[ [ nodiscard ] ] double Get709Luminance( ) const;
	double Put709Luminance( double ) = delete;
	/** \brief Luminance in 709 color depth */
	__declspec( property( get = Get709Luminance, put = Put709Luminance ) ) double luma;

	[ [ nodiscard ] ] double Get601Luminance( ) const;
	double Put601Luminance( double ) = delete;
	/** \brief Luminance in 601 color depth */
	__declspec( property( get = Get601Luminance, put = Put601Luminance ) ) double luma601;
};

/** \brief Multicolor manager, usable by sequences of length 7 */
class CColor
{
public:

	/** \brief Returns gradient between two colors */
	/** \param clrStart Color that gradient begins at */
	/** \param clrEnd Color that gradient ends at */
	/** \param dbProgress Progress to end */
	/** \return Color at specified progress */
	[ [ nodiscard ] ] static color_t GetGradient( color_t clrStart, color_t clrEnd, double dbProgress );

	/** \brief Structure to contain data of one sequence */
	struct sequence_t
	{
		color_t clr { };
		Utilities::moment_t mmtDuration = 0;
	};

private:

	/** \brief Data of all sequences managed */
	sequence_t pSequences[ 7 ];
	/** \brief Number of sequences initialized */
	std::size_t zSequences = 0u;
	/** \brief Total duration of all sequences combined */
	Utilities::moment_t mmtTotalDuration = 0;

public:

	CColor( ) = default;
	/** \brief Initializes sequence data with one sequences */
	/** \param clrFirstSequence Color of sequence to initialize */
	/** \param mmtFirstSequence Duration of sequence to initialize */
	CColor( color_t clrFirstSequence, Utilities::moment_t mmtFirstSequence );
	/** \brief Initializes sequences data with sequences */
	/** \param vecSequences Sequences data to initialize */
	CColor( std::vector< sequence_t > vecSequences );

	[ [ nodiscard ] ] color_t GetColor( );
	void PutColor( ) = delete;
	/** \brief Color of current moment of sequences */
	__declspec( property( get = GetColor, put = PutColor ) ) color_t clr;

	/** \brief Returns sequence data at specified member position */
	/** \param zSequence Position to retrieve */
	/** \return Sequence data */
	[ [ nodiscard ] ] sequence_t GetSequence( std::size_t zSequence );
	/** \brief Returns sequence data at specified member position */
	/** \param zSequence Position to retrieve */
	/** \return Sequence data */
	[ [ nodiscard ] ] sequence_t operator[ ]( std::size_t zSequence );

	/** \brief Pushes sequence into sequence top */
	/** \param seq Sequence data to push */
	void PutNewColorSequence( sequence_t seq );
	/** \brief Pushes sequence into sequence top */
	/** \param seq Sequence data to push */
	/** \return this after push */
	CColor &operator<<( sequence_t seq );
	/** \brief Deletes sequence from sequences */
	/** \param zSequence Sequence to delete */
	void DeleteColorSequence( std::size_t zSequence );
	/** \brief Deletes sequence from sequences */
	/** \param zSequence Sequence to delete */
	/** \return this after delete */
	CColor &operator>>( std::size_t zSequence );
};

using sequence_t = CColor::sequence_t;
