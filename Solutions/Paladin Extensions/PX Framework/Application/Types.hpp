/// Types.hpp

#pragma once

namespace PX::Types
{
	/** \brief Paladin virtual memory address variable. */
	typedef uintptr_t ptr_t;
	/** \brief Paladin virtual memory address variable. */
	typedef ptrdiff_t off_t;
	/** \brief Paladin callback function type. */
	typedef void ( PX_API* callback_t )( );
	/** \brief Paladin time datatype, wide enough to hold any time type, with sig figs up to a tenth of a microsecond. */
	typedef unsigned long long moment_t;
	/** \brief Paladin byte datatype. Stores one byte of data. */
	typedef unsigned char byte_t;
	/** \brief Paladin flag datatype. Stores flags usually from an enum. */
	typedef byte_t flags_t;
	/** \brief Paladin key datatype. Stores a virtual key code. */
	typedef unsigned int key_t;

	/** \brief Paladin constant char string. */
	typedef const char *cstr_t;
	/** \brief Paladin char-16 constant char string. */
	typedef const char16_t *cstr16_t;
	/** \brief Paladin char-32 constant char string. */
	typedef const char32_t *cstr32_t;
	/** \brief Paladin wide constant char string. */
	typedef const wchar_t *wcstr_t;
	/** \brief Paladin byte constant string */
	typedef const byte_t *bcstr_t;

	/** \brief Paladin string datatype */
	typedef std::basic_string< char > str_t;
	/** \brief Paladin char-16 string datatype */
	typedef std::basic_string< char16_t > str16_t;
	/** \brief Paladin char-32 string datatype */
	typedef std::basic_string< char32_t > str32_t;
	/** \brief Paladin wide string datatype */
	typedef std::basic_string< wchar_t > wstr_t;
	/** \brief Paladin wide string datatype */
	typedef std::basic_string< byte_t > bstr_t;

	/** \brief Unsigned char string literal identifier */
	/** \param chSource Character */
	/** \return byte_t version of array */
	byte_t operator""_b( char chSource );
	/** \brief Unsigned char string literal identifier */
	/** \param ch16Source Character */
	/** \return byte_t version of array */
	byte_t operator""_b( char16_t ch16Source );
	/** \brief Unsigned char string literal identifier */
	/** \param ch32Source Character */
	/** \return byte_t version of array */
	byte_t operator""_b( char32_t ch32Source );
	/** \brief Unsigned char string literal identifier */
	/** \param wchSource Character */
	/** \return byte_t version of array */
	byte_t operator""_b( wchar_t wchSource );
	/** \brief Unsigned char string literal identifier */
	/** \param szSource Array of characters */
	/** \param zSize Length of array */
	/** \return byte_t version of array */
	const byte_t *operator""_b( cstr_t szSource, std::size_t zSize );
	/** \brief Unsigned char string literal identifier */
	/** \param sz16Source Array of characters */
	/** \param zSize Length of array */
	/** \return byte_t version of array */
	const byte_t *operator""_b( cstr16_t sz16Source, std::size_t zSize );
	/** \brief Unsigned char string literal identifier */
	/** \param sz32Source Array of characters */
	/** \param zSize Length of array */
	/** \return byte_t version of array */
	const byte_t *operator""_b( cstr32_t sz32Source, std::size_t zSize );
	/** \brief Unsigned char string literal identifier */
	/** \param wszSource Array of characters */
	/** \param zSize Length of array */
	/** \return byte_t version of array */
	const byte_t *operator""_b( wcstr_t wszSource, std::size_t zSize );

	enum EKeyBindMode
	{
		KEYBIND_INACTIVE,
		KEYBIND_TOGGLE,
		KEYBIND_WHILE_PRESSED,
		KEYBIND_WHILE_NOT_PRESSED,
		KEYBIND_ENABLE,
		KEYBIND_DISABLE
	};

	struct toggle_t;

	inline std::vector< toggle_t* > vecToggles;
	inline void *pConfigStructure = nullptr;
	inline std::size_t zConfigStructureSize = 0;

	struct toggle_t
	{
		explicit operator bool( ) const
		{
			return bEnabled;
		}

		struct keybind_t
		{
			int iKeyBindMode = KEYBIND_INACTIVE;
			Types::key_t kKey { };
		};

		static void Initialize( void *_pConfigStructure, std::size_t _zConfigStructureSize )
		{
			pConfigStructure = _pConfigStructure;
			zConfigStructureSize = _zConfigStructureSize;
		}

		static void Event( unsigned uKey, bool bPressed )
		{
			for ( auto u = 0u; u < vecToggles.size(); u++ )
			{
				auto& toggle = vecToggles[ u ];
				if ( ptr_t( toggle ) < ptr_t( pConfigStructure )
					 || ptr_t( toggle ) > ptr_t( pConfigStructure ) + zConfigStructureSize )
				{
					vecToggles.erase( vecToggles.begin( ) + u );
					u--;
					continue;
				}

				if ( toggle->UseKeyBinds( ) )
					for ( auto i = 0; i < 7; i++ )
						if ( toggle->GetBinds( )[ i ].kKey == uKey )
							switch ( toggle->GetBinds( )[ i ].iKeyBindMode )
							{
								case KEYBIND_TOGGLE:
								{
									if ( bPressed )
										toggle->Get( ) = !toggle->Get( );
								}
								break;

								case KEYBIND_WHILE_PRESSED:
								{
									toggle->Get( ) = bPressed;
								}
								break;

								case KEYBIND_WHILE_NOT_PRESSED:
								{
									toggle->Get( ) = !bPressed;
								}
								break;

								case KEYBIND_ENABLE:
								{
									if ( bPressed )
										toggle->Get( ) = true;
								}
								break;

								case KEYBIND_DISABLE:
								{
									if ( bPressed )
										toggle->Get( ) = false;
								}
								break;

								default:
									break;
							}
			}
		}

	private:
		bool bEnabled = false, bUseKeybinds = true;
		keybind_t bndBinds[ 7 ] { };

	public:

		toggle_t( );
		toggle_t( bool _bEnabled );
		~toggle_t( ) = default;

		void AddToList( );
		bool &Get( );
		bool &UseKeyBinds( );
		keybind_t* GetBinds( );

		toggle_t &operator=( bool _bEnabled );
		bool operator!( );
	};

	struct SPostData
	{
		str_t strIdentifier, strValue;

		SPostData( str_t strIdentifier, str_t strValue )
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
		str_t strName, strStatus, strEstimatedNextUpdate, strLastUpdate, strVersion;
		bool bInitialized = true;

		SExtensionInfo( ) PX_NOX
		{
			bInitialized = false;
		}

		SExtensionInfo( str_t _strName, str_t _strStatus, str_t _strEstimatedNextUpdate, str_t _strLastUpdate, str_t _strVersion )
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
		union
		{
			float flVectors[ 4 ] { };

			struct
			{
				float x, y, z, rhw;
			} _Vectors;
		};

		DWORD dwColor { };

		vertex_t( ) = default;

		vertex_t( float x, float y, DWORD _dwColor )
		{
			flVectors[ 0 ] = x;
			flVectors[ 1 ] = y;
			flVectors[ 2 ] = 0.f;
			flVectors[ 3 ] = 1.f;
			dwColor = _dwColor;
		}

		void Rotate2D( const vertex_t &vtxRotationPoint, float flAngle )
		{
			const auto flRadians = D3DXToRadian( flAngle );
			const auto flSin = sin( flRadians );
			const auto flCos = cos( flRadians );
			const D3DXVECTOR2 vecRelative { _Vectors.x - vtxRotationPoint._Vectors.x, _Vectors.y - vtxRotationPoint._Vectors.y };

			_Vectors.x = ( vecRelative.x * flCos ) - ( vecRelative.y * flSin ) + vtxRotationPoint._Vectors.x;
			_Vectors.y = ( vecRelative.x * flSin ) + ( vecRelative.y * flCos ) + vtxRotationPoint._Vectors.y;
		}
	};

	template< typename _t > struct drawing_t
	{
		std::vector< _t > vecVertices;

		drawing_t( ) = default;

		drawing_t( const _t *pVertices, std::size_t _sVertices )
		{
			for ( auto z = 0u; z < _sVertices; z++ )
				vecVertices.emplace_back( pVertices[ z ] );
		}
	};

	struct line_t: drawing_t< D3DXVECTOR2 >
	{
		DWORD dwColor;
		float flWidth;
		BOOL bAntiAlias;

		line_t( ) = default;
		line_t( const D3DXVECTOR2 *_pVertices, std::size_t _sVertices, float _flWidth, DWORD _dwColor, BOOL _bAntiAlias = TRUE );
	};

	struct polygon_t: drawing_t< vertex_t >
	{
		std::size_t sPrimitives { };
		D3DPRIMITIVETYPE ptType { };

		polygon_t( ) = default; // review why even have constructors here? just use initializer braces
		polygon_t( const vertex_t *_pVertices, std::size_t _sVertices, std::size_t _sPrimitives, D3DPRIMITIVETYPE _ptType = D3DPT_TRIANGLEFAN );
	};

	struct text_t
	{
		int iFont { };
		int x, y;
		Types::wstr_t wstrText;
		bool bOutlined;
		DWORD dwFlags, dwColor, dwOutline;
		text_t( ) = default; // review why even have constructors here? just use initializer braces
		text_t( int _iFont, int _x, int _y, const wchar_t *_wszText, bool _bOutlined, DWORD _dwFlags, DWORD _dwColor, DWORD _dwOutline );
	};

	struct module_t
	{
		Types::wstr_t wstrName { };
		HMODULE hModule { };

		module_t( ) = default;
		module_t( Types::wstr_t _wstrName );

		bool Succeeded( );
		ptr_t FindPattern( str_t strPattern );
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
		} _Color;

	public:
		SColor( ) = default;
		/** \param initInputs Maximum 1 pointer to 4 byte memory region containing color in RGBA order */
		SColor( std::initializer_list< ptr_t > initInputs );
		/** \param initInputs Maximum 4 ints in RGBA order */
		SColor( std::initializer_list< int > initInputs );
		/** \param initInputs Maximum 4 floats in RGBA order */
		SColor( std::initializer_list< float > initInputs );
		//~color_t( );

		unsigned GetRGBA( ) const;
		unsigned GetARGB( ) const;
		unsigned PutHex( unsigned uValue );
		__declspec( property( get = GetRGBA, put = PutHex ) ) unsigned Hex;

		byte_t GetRed( ) const;
		byte_t GetGreen( ) const;
		byte_t GetBlue( ) const;
		byte_t GetAlpha( ) const;
		byte_t PutRed( byte_t bValue );
		byte_t PutGreen( byte_t bValue );
		byte_t PutBlue( byte_t bValue );
		byte_t PutAlpha( byte_t bValue );
		__declspec( property( get = GetRed, put = PutRed ) ) byte_t r;
		__declspec( property( get = GetGreen, put = PutGreen ) ) byte_t g;
		__declspec( property( get = GetBlue, put = PutBlue ) ) byte_t b;
		__declspec( property( get = GetAlpha, put = PutAlpha ) ) byte_t a;

		float GetRedFloat( ) const;
		float GetGreenFloat( ) const;
		float GetBlueFloat( ) const;
		float GetAlphaFloat( ) const;
		float PutRedFloat( float flValue );
		float PutGreenFloat( float flValue );
		float PutBlueFloat( float flValue );
		float PutAlphaFloat( float flValue );
		__declspec( property( get = GetRedFloat, put = PutRedFloat ) ) float rfl;
		__declspec( property( get = GetGreenFloat, put = PutGreenFloat ) ) float gfl;
		__declspec( property( get = GetBlueFloat, put = PutBlueFloat ) ) float bfl;
		__declspec( property( get = GetAlphaFloat, put = PutAlphaFloat ) ) float afl;

		byte_t CalculateLuminance( ) const;
		void SetLuminance( ) = delete;
		__declspec( property( get = CalculateLuminance, put = SetLuminance ) ) byte_t Luminance;

		byte_t operator[ ]( int iColor ) const;
		float operator[ ]( float flColor ) const;
		bool operator==( const SColor &rhs ) const;
		bool operator!=( const SColor &rhs ) const;
	} color_t;

	typedef struct SColorSequence
	{
		static color_t GetGradient( color_t clrStart, color_t clrEnd, float flProgress );

	private:
		typedef struct
		{
			color_t clrColor;
			moment_t mmtDuration = 0;
		} sequence_info_t;

		sequence_info_t sqInfo[ 7 ];
		moment_t mmtTotalDuration = 0;

	public:
		std::size_t zSequences = 0u;
		SColorSequence( ) PX_NOX;
		SColorSequence( color_t clrFirstSequence, moment_t mmtFirstSequence );
		SColorSequence( color_t *clrColors, moment_t *mmtDurations, std::size_t zSequences );

		color_t GetCurrentColor( );
		void PutCurrentColor( ) = delete;

		color_t &GetColor( unsigned uColor );
		moment_t &GetDuration( unsigned uDuration );

		void PutNewColorSequence( const color_t &clrNewColor, moment_t mmtDuration ); // todo: overload <<, make sequence_info_t public
		void DeleteColorSequence( unsigned uPosition ); // todo: overload >>

		//void operator<<( sequence_info_t );
		//void operator>>( unsigned uPosition );
	} color_sequence_t;
}

#include "Types.inl"

#if defined PX_USE_NAMESPACES
using namespace PX::Types;
#endif
