#ifndef BOTMANAGER_H_
#define BOTMANAGER_H_

#include "../Game_local.h"

/*
===============================================================================

	afiBotManager
	Bot client management

===============================================================================
*/

typedef struct botInfo_s {
	bool		inUse;
	int			clientNum;
	int			entityNum;
	idCmdArgs	cmdArgs;
	botInfo_s()
	{
		inUse = false;
		clientNum = -1;
		entityNum = -1;
		cmdArgs.Clear();
	}
	
} botInfo_t;

class afiBotManager {
public:
	// Bot Inteface
	static void				PrintInfo( void );
	static void				Initialize( void );
	static void				UpdateUserInfo( void );

	static void				Cmd_BotInfo_f( const idCmdArgs& args );
	static void				Cmd_AddBot_f( const idCmdArgs& args );
	static void				Cmd_RemoveBot_f( const idCmdArgs& args );
	static void				Cmd_RemoveAllBots_f( const idCmdArgs & args );
	static void				AddBot( const idCmdArgs& args );
	static void				DropABot( void );
	static void				RemoveBot( int clientNum );
	static int				IsClientBot( int clientNum );
	static void				SetBotDefNumber( int clientNum, int botDefNumber );
	static int				GetBotDefNumber( int clientNum );
	static idStr			GetBotClassname( int clientNum );
	static void				SpawnBot( int clientNum );
	static void				OnDisconnect( int clientNum );
//
	static void				InitBotsFromMapRestart();
	static idCmdArgs *		GetPersistArgs( int clientNum );
	static usercmd_t *		GetUserCmd( int clientNum );
	static void				SetUserCmd( int clientNum, usercmd_t * usrCmd );
	static void				WriteUserCmdsToSnapshot(idBitMsg& msg);
	static void				ReadUserCmdsFromSnapshot(const idBitMsg& msg);


							afiBotManager();
							~afiBotManager();

protected:
	static usercmd_t		botCmds[MAX_CLIENTS];
private:
	static botInfo_t		botInfo[MAX_CLIENTS];
	static int				numQueBots;
	static idCmdArgs		cmdQue[MAX_CLIENTS];
	static idCmdArgs		persistArgs[MAX_CLIENTS];
	static bool				botSpawned[MAX_CLIENTS];
	static int				botEntityDefNumber[MAX_CLIENTS];
};


#endif 
