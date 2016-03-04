#ifndef _CMD_LINE_INTER_H_
#define _CMD_LINE_INTER_H_
#include <readline/readline.h>
#include <readline/history.h>
void initialize_readline();
void execute_line(char *line);
char *formatCmdLine(int argc, char **argv, char *cmdline, int cmdLen);
int getCmdBufferLen(int argc, char **argv);
char *strstrip(char *s);
#endif

