#pragma once

// cdll_int.h items
#define FORWARD_DECLARE_HANDLE(name) typedef struct name##__ *name
#define MAX_PLAYER_NAME_LENGTH		128
#define SIGNED_GUID_LEN 32
#define MAX_CUSTOM_FILES		4
typedef unsigned long CRC32_t;
#define DECLARE_POINTER_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
class Vector{public: float x, y, z;};
class QAngle{public: float x, y, z;};
enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,
};
class Frustum_t;
struct matrix3x4_t{	float m_flMatVal[ 3 ][ 4 ];};
struct color32{	unsigned char r, g, b, a;};
#define	MAX_EDICTS					(1<<11)
typedef int	string_t;
class Color {public: unsigned char _color[ 4 ]; };
template< class T, class I = int > class CUtlMemory
{
public:
	T* m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};
template< class T, class A = CUtlMemory<T> > class CUtlVector
{
	typedef A CAllocator;
public:
	typedef T ElemType_t;
	CAllocator m_Memory;
	int m_Size;
};
typedef void* ( *CreateInterfaceFn )( const char *pName, int *pReturnCode );
class bf_write
{
public:
	unsigned char*	m_pData;
	int				m_nDataBytes;
	int				m_nDataBits;
	int				m_iCurBit;
};
typedef int qboolean;
class bf_read;
typedef unsigned int HTOOLHANDLE;

// engine/ivdebugoverlay.h items
#define FMTFUNCTION( a, b )

// engine/IEngineTrace.h items
#define	MASK_ALL					(0xFFFFFFFF)
class Vector4D{public:	float x, y, z; };

// gametrace.h items
#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)
struct cplane_t
{
	Vector	normal;
	float	dist;
	unsigned char	type;			// for fast side tests
	unsigned char	signbits;		// signx + (signy<<1) + (signz<<1)
	unsigned char	pad[ 2 ];

#ifdef VECTOR_NO_SLOW_OPERATIONS
	cplane_t( )
	{ }

private:
	// No copy constructors allowed if we're in optimal mode
	cplane_t( const cplane_t& vOther );
#endif
};
class CBaseTrace
{
public:

	// Displacement flags tests.
	bool IsDispSurface( void )
	{
		return ( ( dispFlags & DISPSURF_FLAG_SURFACE ) != 0 );
	}
	bool IsDispSurfaceWalkable( void )
	{
		return ( ( dispFlags & DISPSURF_FLAG_WALKABLE ) != 0 );
	}
	bool IsDispSurfaceBuildable( void )
	{
		return ( ( dispFlags & DISPSURF_FLAG_BUILDABLE ) != 0 );
	}
	bool IsDispSurfaceProp1( void )
	{
		return ( ( dispFlags & DISPSURF_FLAG_SURFPROP1 ) != 0 );
	}
	bool IsDispSurfaceProp2( void )
	{
		return ( ( dispFlags & DISPSURF_FLAG_SURFPROP2 ) != 0 );
	}

public:

	// these members are aligned!!
	Vector			startpos;				// start position
	Vector			endpos;					// final position
	cplane_t		plane;					// surface normal at impact

	float			fraction;				// time completed, 1.0 = didn't hit anything

	int				contents;				// contents on other side of surface hit
	unsigned short	dispFlags;				// displacement flags for marking surfaces with data

	bool			allsolid;				// if true, plane is not valid
	bool			startsolid;				// if true, the initial point was in a solid area

	CBaseTrace( )
	{ }

private:
	// No copy constructors allowed
	CBaseTrace( const CBaseTrace& vOther );
};
struct csurface_t
{
	const char	*name;
	short		surfaceProps;
	unsigned short	flags;		// BUGBUG: These are declared per surface, not per material, but this database is per-material now
};

// icliententitylist.h items

// iclientnetworkable.h items
