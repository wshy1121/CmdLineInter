#ifndef _CMD_DEAL_H_
#define _CMD_DEAL_H_

/* The maximum number of command's args */
#define MAX_ARGVS 16
/* The maximum size of command */
#define MAX_CMD_SIZE 50
/******************************************************************************
 An entry in the console command list consists of a command name and its
 entry point.
 ******************************************************************************/
typedef int executable(int argc, char **argv);
typedef struct {
    const char *name;
    executable *entry;
} cmd_t;

extern cmd_t cmd_list[];

#endif



