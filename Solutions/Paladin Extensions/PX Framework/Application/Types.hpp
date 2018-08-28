/// Types.hpp

#pragma once

namespace PX::Types
{
	/** \brief Paladin constant char string. */
	typedef const char* cstr_t;
	/** \brief Paladin wide constant char string. */
	typedef const wchar_t* wcstr_t;
	/** \brief Paladin address variable. */
	typedef uintptr_t ptr_t;
	/** \brief Paladin byte datatype. Stores one byte of data. */
	typedef unsigned char byte_t;
	/** \brief Paladin callback function type. */
	typedef void( PX_API* callback_t )( );
	/** \brief Paladin time datatype, long enough to hold any time type, down to microseconds. */
	typedef unsigned long long moment_t;

	struct SPostData
	{
		std::string strIdentifier, strValue;
		SPostData( std::string strIdentifier, std::string strValue )
		{
			this->strIdentifier = strIdentifier;
			this->strValue = strValue;
		}
	};
	/** \brief Paladin type for post data. */
	typedef std::deque< SPostData > post_data_t;

	struct SLink
	{
		char szTitle[ 32 ], szLink[ MAX_PATH ];
		SLink( cstr_t szTitle, cstr_t szLink )
		{
			strcpy( this->szTitle, szTitle );
			strcpy( this->szLink, szLink );
		}
	};
	typedef std::deque< SLink > links_t;

	struct SExtensionInfo
	{
		std::string strName, strStatus, strEstimatedNextUpdate, strLastUpdate, strVersion;
		bool bInitialized = true;

		SExtensionInfo( )
		{
			bInitialized = false;
		}

		SExtensionInfo( std::string _strName, std::string _strStatus, std::string _strEstimatedNextUpdate, std::string _strLastUpdate, std::string _strVersion )
		{
			strName = _strName;
			strStatus = _strStatus;
			strEstimatedNextUpdate = _strEstimatedNextUpdate;
			strLastUpdate = _strLastUpdate;
			strVersion = _strVersion;
		}
	};
	typedef std::deque< SExtensionInfo > extensions_t;

	struct vertex_t
	{
		float flVectors[ 4 ] { };
		DWORD dwColor;
		vertex_t( ) = default;
		vertex_t( float x, float y, DWORD _dwColor )
		{
			flVectors[ 0 ] = x;
			flVectors[ 1 ] = y;
			flVectors[ 2 ] = 0.f;
			flVectors[ 3 ] = 0.f;
			dwColor = _dwColor;
		}
	};

	struct module_t
	{
		std::wstring wstrName { };
		HMODULE hModule { };

		module_t( ) = default;
		module_t( std::wstring _wstrName );

		bool Succeeded( );
		ptr_t FindPattern( std::string strPattern );
	};
	
	/** \brief Type to hold colors. */
	typedef struct SColor
	{
		/** \brief Enumeration of colors to index the bColors array. */
		enum EColor
		{
			COLOR_RED,
			COLOR_GREEN,
			COLOR_BLUE,
			COLOR_ALPHA,
			COLOR_MAX
		};

	private:
		union UColor
		{
			unsigned u;
			byte_t b[ COLOR_MAX ];
		} *pColor = new UColor { UINT_MAX };

	public:
		SColor( ) = default;
		SColor( std::initializer_list< ptr_t > initInputs );
		SColor( std::initializer_list< int > initInputs );
		SColor( std::initializer_list< float > initInputs );
		//~color_t( );

		unsigned GetHex( ) const;
		void PutHex( unsigned uValue ) const;
		__declspec( property( get = GetHex, put = PutHex ) ) unsigned Hex;

		byte_t GetRed( ) const;
		byte_t GetGreen( ) const;
		byte_t GetBlue( ) const;
		byte_t GetAlpha( ) const;
		void PutRed( byte_t bValue ) const;
		void PutGreen( byte_t bValue ) const;
		void PutBlue( byte_t bValue ) const;
		void PutAlpha( byte_t bValue ) const;
		__declspec( property( get = GetRed, put = PutRed ) ) byte_t r;
		__declspec( property( get = GetGreen, put = PutGreen ) ) byte_t g;
		__declspec( property( get = GetBlue, put = PutBlue ) ) byte_t b;
		__declspec( property( get = GetAlpha, put = PutAlpha ) ) byte_t a;

		float GetRedFloat( ) const;
		float GetGreenFloat( ) const;
		float GetBlueFloat( ) const;
		float GetAlphaFloat( ) const;
		void PutRedFloat( float flValue ) const;
		void PutGreenFloat( float flValue ) const;
		void PutBlueFloat( float flValue ) const;
		void PutAlphaFloat( float flValue ) const;
		__declspec( property( get = GetRedFloat, put = PutRedFloat ) ) float rfl;
		__declspec( property( get = GetGreenFloat, put = PutGreenFloat ) ) float gfl;
		__declspec( property( get = GetBlueFloat, put = PutBlueFloat ) ) float bfl;
		__declspec( property( get = GetAlphaFloat, put = PutAlphaFloat ) ) float afl;

		byte_t CalculateLuminance( ) const;
		void SetLuminance( ) = delete;
		__declspec( property( get = CalculateLuminance, put = SetLuminance ) ) byte_t Luminance;

		byte_t operator[ ]( int iColor ) const;
		float operator[ ]( float flColor ) const;
		//bool operator==( const color_t& rhs ) const;
		//bool operator!=( const color_t& rhs ) const;
	} color_t;

	typedef struct SColorSequence
	{
		static color_t GetGradient( color_t clrStart, color_t clrEnd, float flProgress );
		typedef struct
		{
			color_t clrColor;
			moment_t mmtDuration = 0;
		} sequence_info_t;

	private:
		sequence_info_t sqInfo[ 7 ];
		moment_t mmtTotalDuration = 0;

	public:
		std::size_t sSequences = 0u;
		SColorSequence( )
		{
			PutNewColorSequence( { 0, 0, 0, 255 }, 1000 );
		}
		SColorSequence( color_t clrFirstSequence, moment_t mmtFirstSequence );
		SColorSequence( color_t* clrColors, moment_t* mmtDurations, std::size_t sSequences );

		color_t GetCurrentColor( );
		void PutCurrentColor( ) = delete;

		color_t& GetColor( unsigned uColor );
		moment_t& GetDuration( unsigned uDuration );

		void PutNewColorSequence( const color_t& clrNewColor, moment_t mmtDuration ); // todo: overload <<, make sequence_info_t public
		void DeleteColorSequence( unsigned uPosition ); // todo: overload >>
		
		//void operator<<( sequence_info_t );
		//void operator>>( unsigned uPosition );
	} color_sequence_t;
}

#if defined PX_USE_NAMESPACES
using namespace PX::Types;
#endif
