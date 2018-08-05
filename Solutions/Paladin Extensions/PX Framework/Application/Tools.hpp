/// Tools.hpp

#pragma once

namespace PX::Tools
{
	// INFO: Inheritable struct that manages a single instantiated object of child class/structure
	// *_Child*: Child class/structure to be restricted
	template< class _Child > struct SSingleton
	{
		SSingleton( ) = default;
		~SSingleton( ) = default;

		SSingleton( SSingleton&& ) = delete;
		SSingleton( const SSingleton& ) = delete;

		SSingleton& operator=( SSingleton&& ) = delete;
		SSingleton& operator=( const SSingleton& ) = delete;

		static _Child& PX_API Get( );
	};

	/** \brief Plays a sound. */
	/**	\param szFileName File name of the sound. */
	void PX_API EmitSound( Types::wcstr_t szFileName );

	/** \brief Creates shellcode from a byte array. */
	/**	\param bByteArray Array of bytes to convert. */
	/**	\return Converted byte array. */
	std::string PX_API FormatShellcode( Types::byte_t* bByteArray );
	
	/** \brief Paladin time datatype, long enough to hold any time type, down to microseconds. */
	typedef unsigned long long moment_t;
	// INFO: Gets the local time
	// *type name*: Time info format type
	template< typename = std::chrono::milliseconds > moment_t PX_API GetMoment( );
	// INFO: Sleeps the thread that has called for the amount of time, in the unit of time specified.
	// *type name*: The unit of time to wait for ( std::chrono ).
	template< typename = std::chrono::milliseconds > void PX_API Wait( moment_t );

	/** \brief Type to hold colors. */
	struct color_t
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
			Types::byte_t b[ COLOR_MAX ];
		};
		UColor* pColor;

	public:
		color_t( );
		explicit color_t( Types::ptr_t* ptrNewAddress );
		explicit color_t( Types::byte_t* bNewColors );
		explicit color_t( int* iNewColors );
		color_t( const float* flNewColors, const unsigned __int8 nColorsCount );
		color_t( Types::byte_t bRed, Types::byte_t bGreen, Types::byte_t bBlue, Types::byte_t bAlpha );
		color_t( Types::byte_t bRed, Types::byte_t bGreen, Types::byte_t bBlue );
		color_t( int iRed, int iGreen, int iBlue, int iAlpha );
		color_t( int iRed, int iGreen, int iBlue );
		color_t( float flRed, float flGreen, float flBlue, float flAlpha );
		color_t( float flRed, float flGreen, float flBlue );
		~color_t( ) = default;

		unsigned GetHex( ) const;
		void PutHex( unsigned uValue ) const;
		__declspec( property( get = GetHex, put = PutHex ) ) unsigned Hex;

		Types::byte_t GetRed( ) const;
		Types::byte_t GetGreen( ) const;
		Types::byte_t GetBlue( ) const;
		Types::byte_t GetAlpha( ) const;
		void PutRed( Types::byte_t bValue ) const;
		void PutGreen( Types::byte_t bValue ) const;
		void PutBlue( Types::byte_t bValue ) const;
		void PutAlpha( Types::byte_t bValue ) const;
		__declspec( property( get = GetRed, put = PutRed ) ) Types::byte_t r;
		__declspec( property( get = GetGreen, put = PutGreen ) ) Types::byte_t g;
		__declspec( property( get = GetBlue, put = PutBlue ) ) Types::byte_t b;
		__declspec( property( get = GetAlpha, put = PutAlpha ) ) Types::byte_t a;

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

		Types::byte_t CalculateLuminance( ) const;
		void SetLuminance( ) = delete;
		__declspec( property( get = CalculateLuminance, put = SetLuminance ) ) Types::byte_t Luminance;

		Types::byte_t operator[ ]( int iColor ) const;
		float operator[ ]( float flColor ) const;
		bool operator==( const color_t& rhs ) const;
		bool operator!=( const color_t& rhs ) const;
		color_t operator+=( const color_t& rhs );
		//color_t operator+=( int iRed, int iGreen, int iBlue, int iAlpha );
		template< typename _t >color_t operator/( _t _Divisor );
	};

	struct color_sequence_t
	{
	private:
		std::deque< color_t > clrColors;
		std::deque< moment_t > mmtDurations;
		mutable moment_t mmtTotalDuration { };
	public:
		static color_t GetGradient( color_t clrStart, color_t clrEnd, float flProgress );
		color_sequence_t( );
		color_sequence_t( color_t clrFirstSequence, moment_t mmtFirstSequence );
		//color_sequence_t( std::deque< color_t > dqColors, std::deque< moment_t > dqDurations );

		color_t GetCurrentColor( ) const;
		void PutCurrentColor( ) = delete;

		color_t& GetColor( int iColor = -1 );
		moment_t& GetDuration( unsigned uDuration );

		void PutNewColorSequence( color_t clrNewColor, moment_t mmtDuration ); // todo: overload <<
		void DeleteColorSequence( unsigned uPosition ); // todo: overload >>

		unsigned CountSequences( );

		__declspec( property( get = CountSequences ) ) unsigned uSequenceCount;
	};

	// Get main screen dimensions
	unsigned* GetScreenDimensions( );

	// INFO: Casts strings\n
	// INFO: Supports any combination of conversion from "std::string" and "std::wstring" to "std::string" and "std::wstring"
	// *_To*: Desired string type
	// *_From*: Current string
	template< typename _To, typename _From > _To PX_API string_cast( const _From& );
	// INFO: Casts strings\n
	// INFO: Supports any combination of conversion from "const char*" and "const wchar_t*" to "std::string" and "std::wstring"
	// *_To*: Desired string type
	// *_From*: Current string
	template< typename _To, typename _From > _To PX_API string_cast( _From* );
}

#include "Tools.inl"
