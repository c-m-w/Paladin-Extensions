#pragma once

#define TE_EXPLFLAG_NONE		0x0	// all flags clear makes default Half-Life explosion
#define TE_EXPLFLAG_NOADDITIVE	0x1	// sprite will be drawn opaque (ensure that the sprite you send is a non-additive sprite)
#define TE_EXPLFLAG_NODLIGHTS	0x2	// do not render dynamic lights
#define TE_EXPLFLAG_NOSOUND		0x4	// do not play client explosion sound
#define TE_EXPLFLAG_NOPARTICLES	0x8	// do not draw particles
#define TE_EXPLFLAG_DRAWALPHA	0x10	// sprite will be drawn alpha
#define TE_EXPLFLAG_ROTATE		0x20	// rotate the sprite randomly
#define TE_EXPLFLAG_NOFIREBALL	0x40	// do not draw a fireball
#define TE_EXPLFLAG_NOFIREBALLSMOKE	0x80	// do not draw smoke with the fireball

#define	TE_BEAMPOINTS		0		// beam effect between two points
#define TE_SPRITE			1	// additive sprite, plays 1 cycle
#define TE_BEAMDISK			2	// disk that expands to max radius over lifetime
#define TE_BEAMCYLINDER		3		// cylinder that expands to max radius over lifetime
#define TE_BEAMFOLLOW		4		// create a line of decaying beam segments until entity stops moving
#define TE_BEAMRING			5		// connect a beam ring to two entities
#define TE_BEAMSPLINE		6		
#define TE_BEAMRINGPOINT	7
#define	TE_BEAMLASER		8		// Fades according to viewpoint
#define TE_BEAMTESLA		9

#define MAX_BEAM_ENTS   10
#define NOISE_DIVISIONS 128

#include "../Math/Vector.hpp"
#include "IClientMode.hpp"

class IClientEntity;
class ITraceFilter;
class Vector;

enum
{
	FBEAM_STARTENTITY = 0x00000001,
	FBEAM_ENDENTITY = 0x00000002,
	FBEAM_FADEIN = 0x00000004,
	FBEAM_FADEOUT = 0x00000008,
	FBEAM_SINENOISE = 0x00000010,
	FBEAM_SOLID = 0x00000020,
	FBEAM_SHADEIN = 0x00000040,
	FBEAM_SHADEOUT = 0x00000080,
	FBEAM_ONLYNOISEONCE = 0x00000100,		// Only calculate our noise once
	FBEAM_NOTILE = 0x00000200,
	FBEAM_USE_HITBOXES = 0x00000400,		// Attachment indices represent hitbox indices instead when this is set.
	FBEAM_STARTVISIBLE = 0x00000800,		// Has this client actually seen this beam's start entity yet?
	FBEAM_ENDVISIBLE = 0x00001000,		// Has this client actually seen this beam's end entity yet?
	FBEAM_ISACTIVE = 0x00002000,
	FBEAM_FOREVER = 0x00004000,
	FBEAM_HALOBEAM = 0x00008000,		// When drawing a beam with a halo, don't ignore the segments and endwidth
	FBEAM_REVERSED = 0x00010000,
	NUM_BEAM_FLAGS = 17	// KEEP THIS UPDATED!
};

struct BeamTrail_t;

class Beam_t
{
public:
	// has a vftable but not interested.

	// Bounding box...
	Vector			m_Mins;
	Vector			m_Maxs;
	void		   *m_queryHandleHalo;
	float			m_haloProxySize;

	// Data is below..

	// Next beam in list
	Beam_t*			next;

	// Type of beam
	int				type;
	int				flags;

	// Control points for the beam
	int				numAttachments;
	Vector			attachment[ MAX_BEAM_ENTS ];
	Vector			delta;

	// 0 .. 1 over lifetime of beam
	float			t;
	float			freq;

	// Time when beam should die
	float			die;
	float			width;
	float			endWidth;
	float			fadeLength;
	float			amplitude;
	float			life;

	// Color
	float			r, g, b;
	float			brightness;

	// Speed
	float			speed;

	// Animation
	float			frameRate;
	float			frame;
	int				segments;

	// Attachment entities for the beam
	int				entity[ MAX_BEAM_ENTS ]; // the fucks an ehandle, rearrange if fucked.
	int				attachmentIndex[ MAX_BEAM_ENTS ];

	// Model info
	int				modelIndex;
	int				haloIndex;

	float			haloScale;
	int				frameCount;

	float			rgNoise[ NOISE_DIVISIONS + 1 ];

	// Popcorn trail for beam follows to use
	BeamTrail_t*	trail;

	// for TE_BEAMRINGPOINT
	float			start_radius;
	float			end_radius;

	// for FBEAM_ONLYNOISEONCE
	bool			m_bCalculatedNoise;

	float			m_flHDRColorScale;
};

struct BeamTrail_t
{
	// NOTE:  Don't add user defined fields except after these four fields.
	BeamTrail_t*	next;
	float			die;
	Vector			org;
	Vector			vel;
};

//-----------------------------------------------------------------------------
// Data type for beams.
//-----------------------------------------------------------------------------
struct BeamInfo_t
{
	int			m_nType;

	// Entities
	C_BaseEntity* m_pStartEnt;
	int			m_nStartAttachment;
	C_BaseEntity* m_pEndEnt;
	int			m_nEndAttachment;

	// Points
	Vector		m_vecStart;
	Vector		m_vecEnd;

	int			m_nModelIndex;
	const char	*m_pszModelName;

	int			m_nHaloIndex;
	const char	*m_pszHaloName;
	float		m_flHaloScale;

	float		m_flLife;
	float		m_flWidth;
	float		m_flEndWidth;
	float		m_flFadeLength;
	float		m_flAmplitude;

	float		m_flBrightness;
	float		m_flSpeed;

	int			m_nStartFrame;
	float		m_flFrameRate;

	float		m_flRed;
	float		m_flGreen;
	float		m_flBlue;

	bool		m_bRenderable;

	int			m_nSegments;

	int			m_nFlags;

	// Rings
	Vector		m_vecCenter;
	float		m_flStartRadius;
	float		m_flEndRadius;

	BeamInfo_t( )
	{
		m_nType = TE_BEAMPOINTS;
		m_nSegments = -1;
		m_pszModelName = NULL;
		m_pszHaloName = NULL;
		m_nModelIndex = -1;
		m_nHaloIndex = -1;
		m_bRenderable = true;
		m_nFlags = 0;
	}
};

class IViewRenderBeams
{
public:
	// Construction
public:
	IViewRenderBeams( void );
	virtual				~IViewRenderBeams( void );

	// Implement IViewRenderBeams
public:
	virtual	void		InitBeams( void );
	virtual	void		ShutdownBeams( void );
	virtual	void		ClearBeams( void );

	// Updates the state of the temp ent beams
	virtual void		UpdateTempEntBeams( );

	virtual void		DrawBeam( Beam_t *pbeam );
	virtual void		DrawBeam( void* pbeam, ITraceFilter *pEntityBeamTraceFilter = NULL );

	virtual	void		KillDeadBeams( IClientEntity *pDeadEntity );

	virtual	void		CreateBeamEnts( int startEnt, int endEnt, int modelIndex, int haloIndex, float haloScale,
										float life, float width, float endWidth, float fadeLength, float amplitude,
										float brightness, float speed, int startFrame,
										float framerate, float r, float g, float b, int type = -1 );
	virtual Beam_t		*CreateBeamEnts( BeamInfo_t &beamInfo );

	virtual	void		CreateBeamEntPoint( int	nStartEntity, const Vector *pStart, int nEndEntity, const Vector* pEnd,
											int modelIndex, int haloIndex, float haloScale,
											float life, float width, float endWidth, float fadeLength, float amplitude,
											float brightness, float speed, int startFrame,
											float framerate, float r, float g, float b );
	virtual Beam_t		*CreateBeamEntPoint( BeamInfo_t &beamInfo );

	virtual	void		CreateBeamPoints( Vector& start, Vector& end, int modelIndex, int haloIndex, float haloScale,
										  float life, float width, float endWidth, float fadeLength, float amplitude,
										  float brightness, float speed, int startFrame,
										  float framerate, float r, float g, float b );
	virtual	Beam_t		*CreateBeamPoints( BeamInfo_t &beamInfo );

	virtual	void		CreateBeamRing( int startEnt, int endEnt, int modelIndex, int haloIndex, float haloScale,
										float life, float width, float endWidth, float fadeLength, float amplitude,
										float brightness, float speed, int startFrame,
										float framerate, float r, float g, float b, int flags );
	virtual Beam_t		*CreateBeamRing( BeamInfo_t &beamInfo );

	virtual void		CreateBeamRingPoint( const Vector& center, float start_radius, float end_radius, int modelIndex, int haloIndex, float haloScale,
											 float life, float width, float m_nEndWidth, float m_nFadeLength, float amplitude,
											 float brightness, float speed, int startFrame,
											 float framerate, float r, float g, float b, int flags );
	virtual Beam_t		*CreateBeamRingPoint( BeamInfo_t &beamInfo );

	virtual	void		CreateBeamCirclePoints( int type, Vector& start, Vector& end,
												int modelIndex, int haloIndex, float haloScale, float life, float width,
												float endWidth, float fadeLength, float amplitude, float brightness, float speed,
												int startFrame, float framerate, float r, float g, float b );
	virtual Beam_t		*CreateBeamCirclePoints( BeamInfo_t &beamInfo );

	virtual	void		CreateBeamFollow( int startEnt, int modelIndex, int haloIndex, float haloScale,
										  float life, float width, float endWidth, float fadeLength, float r, float g, float b,
										  float brightness );
	virtual Beam_t		*CreateBeamFollow( BeamInfo_t &beamInfo );

};

//class IViewRenderBeams
//{
//	//vtable len = 24
//public:
//	virtual void	InitBeams( void ) = 0;
//	virtual void	ShutdownBeams( void ) = 0;
//	virtual void	ClearBeams( void ) = 0;
//
//	// Updates the state of the temp ent beams
//	virtual void	UpdateTempEntBeams( ) = 0;
//
//	virtual void	DrawBeam( void* pbeam, ITraceFilter *pEntityBeamTraceFilter = NULL ) = 0;
//	virtual void	DrawBeam( Beam_t *pbeam ) = 0;
//
//	virtual void	KillDeadBeams( IClientEntity* pEnt ) = 0;
//
//	// New interfaces!
//	virtual Beam_t	*CreateBeamEnts( BeamInfo_t &beamInfo ) = 0;
//	virtual Beam_t	*CreateBeamEntPoint( BeamInfo_t &beamInfo ) = 0;
//	virtual	Beam_t	*CreateBeamPoints( BeamInfo_t &beamInfo ) = 0;
//	virtual Beam_t	*CreateBeamRing( BeamInfo_t &beamInfo ) = 0;
//	virtual Beam_t	*CreateBeamRingPoint( BeamInfo_t &beamInfo ) = 0;
//	virtual Beam_t	*CreateBeamCirclePoints( BeamInfo_t &beamInfo ) = 0;
//	virtual Beam_t	*CreateBeamFollow( BeamInfo_t &beamInfo ) = 0;
//
//	virtual void	FreeBeam( Beam_t *pBeam ) = 0;
//	virtual void	UpdateBeamInfo( Beam_t *pBeam, BeamInfo_t &beamInfo ) = 0;
//};