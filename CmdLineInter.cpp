#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
//#include <glib.h>
#include "CmdLineInter.h"
#include "CmdDeal.h"


 /******************************************************************************
 Search for a console command with matching name in the console command list.
 Return 0 if not found.
 ******************************************************************************/

char *strstrip(char *s) {
    size_t size;
    char *end;

    size = strlen(s);

    if (!size)
        return s;

    end = s + size - 1;
    while (end >= s && isspace(*end))
        end--;
    *(end + 1) = '\0';

    while (*s && isspace(*s))
        s++;

    return s;
}
static cmd_t *GetEntry(char *name)
{
    cmd_t *p = cmd_list;
    int i;
    for (i = 0; cmd_list[i].name != NULL; i++, p++)
        if (strcmp(name, p->name) == 0)
            return p;
    return 0;
}
static char *command_generator(const char *text, int state)
{
    static int list_index, len;
    char *name;
    /* If this is a new word to complete, initialize now.  This includes
       saving the length of TEXT for efficiency, and initializing the index
       variable to 0. */
    if (!state) {
        list_index = 0;
        len = strlen(text);
    }
    /* Return the next name which partially matches from the command list. */
    while ((name = (char *)cmd_list[list_index].name)) {
        list_index++;
        if (strncmp(name, text, len) == 0)
            return (strdup(name));
    }
    /* If no names matched, then return NULL. */
    return ((char *) NULL);
}
static char **command_completion(const char *text, int start, int end)
{
    char **matches;
    matches = (char **) NULL;
    /* If this word is at the start of the line, then it is a command
       to complete.  Otherwise it is the name of a file in the current
       directory. */
    if (start == 0)
        matches = (char**)rl_completion_matches(text, command_generator);
    return (matches);
}
void initialize_readline()
{
    /* Allow conditional parsing of the ~/.inputrc file. */
    rl_readline_name = "FileMan";
    /* Tell the completer that we want a crack first. */
    rl_attempted_completion_function = command_completion;
}
void execute_line(char *line)
{
    cmd_t *pcmd;
    int argc = 0;
    char *argv[MAX_ARGVS];
    char *q = strtok(line, " ");
    while (1) {
        if (q == 0)
            break;
        argv[argc++] = q;
        q = strtok(0, " ");
    }
    /* Look for the command in the console command list */
    pcmd = GetEntry(line);
    if (pcmd == 0) {
        fprintf(rl_outstream, "Bad Command! \r\n");
        fprintf(rl_outstream, "Type \"help\" to get help\r\n");
    } else {
    	//printf("this is cmd  %s\n", pcmd->name);
        pcmd->entry(argc, argv);
    }
}

char *formatCmdLine(int argc, char **argv, char *cmdline, int cmdLen)
{
	cmdline[0] = '\0';
	for (int i=1; i<argc; ++i)
	{
		strncat(cmdline, argv[i], cmdLen-1);
		strncat(cmdline, " ", cmdLen-1);
	}

	//trace_printf("line	|%s|", cmdline);
	return strstrip(cmdline);
}

int getCmdBufferLen(int argc, char **argv)
{
	int len = 8;
	for (int i=1; i<argc; ++i)
	{
		len += strlen(argv[i]);
		len += strlen(" ");
	}
	return len;
}

