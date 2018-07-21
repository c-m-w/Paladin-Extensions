#pragma once

#include "SteamID.hpp"
//#include "protobuf/cstrike15_gcmessages.pb.h"
//#include "protobuf/gcsdk_gcmessages.pb.h"
//#include "protobuf/gcsystemmsgs.pb.h"

class ISteamUser;
class ISteamGameServer;
class ISteamFriends;
class ISteamUtils;
class ISteamMatchmaking;
class ISteamContentServer;
class ISteamMatchmakingServers;
class ISteamUserStats;
class ISteamApps;
class ISteamNetworking;
class ISteamRemoteStorage;
class ISteamScreenshots;
class ISteamMusic;
class ISteamMusicRemote;
class ISteamGameServerStats;
class ISteamHTTP;
class ISteamUnifiedMessages;
class ISteamController;
class ISteamUGC;
class ISteamAppList;
class ISteamHTMLSurface;
class ISteamInventory;
class ISteamVideo;

typedef DWORD* SteamPipeHandle, SteamUserHandle, SteamAPICallHandle;
typedef void( __cdecl *SteamAPIWarningMessageHook_t )( int, const char * );
typedef void( *SteamAPI_PostAPIResultInProcess_t )( SteamAPICallHandle callHandle, void*, DWORD unCallbackSize, int iCallbackNum );
typedef DWORD( *SteamAPI_CheckCallbackRegistered_t )( int iCallbackNum );

enum EMatchMakingRanks
{
	Unranked = 0,
	Silver_I,
	Silver_II,
	Silver_III,
	Silver_IV,
	Silver_Elite,
	Silver_Elite_Master,
	Gold_Nova_I,
	Gold_Nova_II,
	Gold_Nova_III,
	Gold_Nova_Master,
	Master_Guardian_I,
	Master_Guardian_II,
	Master_Guardian_Elite,
	Distinguished_Master_Guardian,
	Legendary_Eagle,
	Legendary_Eagle_Master,
	Supreme_Master_First_Class,
	The_Global_Elite
};

class ISteamClient
{
public:
	virtual SteamPipeHandle CreateSteamPipe( ) = 0;
	virtual bool BReleaseSteamPipe( SteamPipeHandle hSteamPipe ) = 0;
	virtual SteamUserHandle ConnectToGlobalUser( SteamPipeHandle hSteamPipe ) = 0;
	virtual SteamUserHandle CreateLocalUser( SteamPipeHandle *phSteamPipe, EAccountType eAccountType ) = 0;
	virtual void ReleaseUser( SteamPipeHandle hSteamPipe, SteamUserHandle hUser ) = 0;
	virtual ISteamUser *GetISteamUser( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamGameServer *GetISteamGameServer( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual void SetLocalIPBinding( DWORD unIP, WORD usPort ) = 0;
	virtual ISteamFriends *GetISteamFriends( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamUtils *GetISteamUtils( SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamMatchmaking *GetISteamMatchmaking( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamMatchmakingServers *GetISteamMatchmakingServers( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual void *GetISteamGenericInterface( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamUserStats *GetISteamUserStats( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamGameServerStats *GetISteamGameServerStats( SteamUserHandle hSteamuser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamApps *GetISteamApps( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamNetworking *GetISteamNetworking( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamRemoteStorage *GetISteamRemoteStorage( SteamUserHandle hSteamuser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamScreenshots *GetISteamScreenshots( SteamUserHandle hSteamuser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual void RunFrame( ) = 0;
	virtual DWORD GetIPCCallCount( ) = 0;
	virtual void SetWarningMessageHook( SteamAPIWarningMessageHook_t pFunction ) = 0;
	virtual bool ShutdownIfAllPipesClosed( ) = 0;
	virtual ISteamHTTP *GetISteamHTTP( SteamUserHandle hSteamuser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamUnifiedMessages *GetISteamUnifiedMessages( SteamUserHandle hSteamuser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamController *GetISteamController( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamUGC *GetISteamUGC( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamAppList *GetISteamAppList( SteamUserHandle hSteamUser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamMusic *GetISteamMusic( SteamUserHandle hSteamuser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamMusicRemote *GetISteamMusicRemote( SteamUserHandle hSteamuser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamHTMLSurface *GetISteamHTMLSurface( SteamUserHandle hSteamuser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual void Set_SteamAPI_CPostAPIResultInProcess( SteamAPI_PostAPIResultInProcess_t func ) = 0;
	virtual void Remove_SteamAPI_CPostAPIResultInProcess( SteamAPI_PostAPIResultInProcess_t func ) = 0;
	virtual void Set_SteamAPI_CCheckCallbackRegisteredInProcess( SteamAPI_CheckCallbackRegistered_t func ) = 0;
	virtual ISteamInventory *GetISteamInventory( SteamUserHandle hSteamuser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
	virtual ISteamVideo *GetISteamVideo( SteamUserHandle hSteamuser, SteamPipeHandle hSteamPipe, const char *pchVersion ) = 0;
};

enum EGCResults
{
	k_EGCResultOK = 0,
	k_EGCResultNoMessage = 1,			// There is no message in the queue
	k_EGCResultBufferTooSmall = 2,		// The buffer is too small for the requested message
	k_EGCResultNotLoggedOn = 3,			// The client is not logged onto Steam
	k_EGCResultInvalidMessage = 4,		// Something was wrong with the message being sent with SendMessage
};
