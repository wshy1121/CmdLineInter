#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "CmdDeal.h"
#include "user_manager.h"
#include "time_calc.h"

extern FILE *rl_outstream;

/*****************************************************************************
 *command help
 *The "help" command do nothing but just print the command and it's argvs
 *****************************************************************************/
static int help(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(rl_outstream, "The commands already implemented are:\r\n");
        fprintf(rl_outstream, "list:\t list the clients info\r\n");
        fprintf(rl_outstream, "disp:\t display the detail client inf\r\n");
        fprintf(rl_outstream, "$:\tRun system command;for example: $ ls\r\n");
    } else {
        int i;
        for (i = 0; i < argc; i++) {
            fprintf(rl_outstream, "%s\n", argv[i]);
        }
    }
    return 0;
}
/******************************************************************************
 *command syscall
 *The "syscall" command allow you to use system commands
 *Example:
 *>syscall ls /home  
 *****************************************************************************/
static int SystemCall(int argc, char **argv)
{
	fprintf(rl_outstream, "can not do SystemCall, this is limited\r\n");
	return 0;
	
    char cmd[MAX_CMD_SIZE];
    int i;
    if (argc < 2) {
        return -1;
    }
    strcpy(cmd, argv[1]);
    for (i = 2; i < argc; i++) {
        strcat(cmd, " ");
        strcat(cmd, argv[i]);
    }
    system(cmd);
    return 0;
}
static int cd(int argc, char **argv)
{
    if (argc < 2)
        return -1;
    chdir(argv[1]);
    return 0;
}

static int exit(int argc, char **argv)
{
	fprintf(rl_outstream, "exit exit\r\n");
	return 0;
}

static int listTraceInf(int argc, char **argv)
{
    IClientInf *clientInf = NULL;
    std::string clientInfStr;
    CUserManager::UserInfMap userInfMap;
    CUserManager::instance()->getClientInfs(userInfMap);
    CUserManager::UserInfMap::iterator iter = userInfMap.begin();     
    for( ; iter != userInfMap.end(); ++iter)
    {
        clientInf = iter->second;
        clientInf->formatInf(clientInfStr);
        fprintf(rl_outstream, "%s\r\n", clientInfStr.c_str());
        
    }
    return 0;
}

static int DispTraceInfStr(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(rl_outstream, "usage: disp clientId\r\n");
        return 0;
    }

    int clientId = atoi(argv[1]);
    std::string traceInfStr;
    CTimeCalcManager::instance()->getTraceInfStr(clientId, traceInfStr);
    fprintf(rl_outstream, "%s\r\n", traceInfStr.c_str());
    return 0;
}
/******************************************************************************
 List of all console commands.
 ******************************************************************************/
cmd_t cmd_list[] = {
    {"help", (executable *) help},
    {"q", (executable *) exit},
    {"exit", (executable *) exit},
    {"quit", (executable *) exit},
    {"$", SystemCall},
    {"cd", cd},
    {"list", listTraceInf},
    {"disp", DispTraceInfStr},
    {NULL, NULL}
};



