/*
===========================================================================
File: BotManager.h
Author: John Wileczek
Description: Bot client management involving adding, removing, and event
dispatch to bots.
===========================================================================
*/
#ifndef BOTMANAGER_H_
#define BOTMANAGER_H_

#include "../Game_local.h"
#include "../MultiplayerGame.h"

class afiBotBrain;
class idEntity;
class afiBotPlayer;

typedef afiBotBrain* (*CreateBotBrain_t)(botImport_t* dllSetup);

enum	BotType { CODE,SCRIPT,DLL };

typedef struct botInfo_s {
	idStr				botName;
	idStr				authorName;
	afiBotBrain*		brain;
	object				botClassInstance;
	object				scriptInstances[MAX_CLIENTS];
	
	int					clientNum;
	int					entityNum;
	int					botType;
	idCmdArgs			cmdArgs;
	botInfo_s() {
		brain = NULL;
		botName = "";
		authorName = "";
		clientNum = -1;
		entityNum = -1;
		cmdArgs.Clear();
		botType = CODE;
	}

	~botInfo_s() {
		
		brain = NULL;
		botName = "";
		authorName = "";
		clientNum = -1;
		entityNum = -1;
	}
	
} botInfo_t;

/*
===============================================================================

	afiBotManager
	Responsible for the loading,adding,removing, and event dispatch for bots.

===============================================================================
*/
class  afiBotManager {
public:
	 static void				PrintInfo( void );
	 static void				Initialize( void );
	 static void				Shutdown( void );
	 static void				UpdateUserInfo( void );
	 static void				ConsolePrint(const char* string);

	 static void				Cmd_BotInfo_f( const idCmdArgs& args );
	 static void				Cmd_AddBot_f( const idCmdArgs& args );
	 static void				Cmd_RemoveBot_f( const idCmdArgs& args );
	 static void				Cmd_RemoveAllBots_f( const idCmdArgs & args );
	 static void				AddBot( const idCmdArgs& args );
	 static void				DropABot( void );
	 static void				RemoveBot( int clientNum );
	 static int					IsClientBot( int clientNum );
	 static void				SetBotDefNumber( int clientNum, int botDefNumber );
	 static int					GetBotDefNumber( int clientNum );
	 static idStr				GetBotClassname( int clientNum );
	 static void				SpawnBot( int clientNum );
	 static void				OnDisconnect( int clientNum );
	
	 static idEntity*			GetFlag(int team);
	 static int					GetFlagStatus(int team);
	 static void				ProcessChat(const char* text);
	 static void				InitBotsFromMapRestart();
	 static idCmdArgs *			GetPersistArgs( int clientNum );
	 static usercmd_t *			GetUserCmd( int clientNum );
	 static void				SetUserCmd( int clientNum, usercmd_t * usrCmd );
	 static void				WriteUserCmdsToSnapshot(idBitMsg& msg);
	 static void				ReadUserCmdsFromSnapshot(const idBitMsg& msg);
	 static void				AddBotInfo(botInfo_t* newBotInfo);
	 static afiBotBrain*		SpawnBrain(idStr botName, int clientNum);
	 static botInfo_t*			FindBotProfile(idStr botName);
	 static botInfo_t*			FindBotProfileByIndex(int clientNum);
								afiBotManager();
								~afiBotManager();

protected:
	static usercmd_t			botCmds[MAX_CLIENTS];
private:
	static idList<botInfo_t*>	loadedBots;
	static int					numQueBots;
	static idCmdArgs			cmdQue[MAX_CLIENTS];
	static idCmdArgs			persistArgs[MAX_CLIENTS];
	static bool					botSpawned[MAX_CLIENTS];
	static int					botEntityDefNumber[MAX_CLIENTS];
	static afiBotBrain*			brainFastList[MAX_CLIENTS];
};




#endif 