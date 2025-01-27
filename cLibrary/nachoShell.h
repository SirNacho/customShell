#include <stdio.h>
#include <stdlib.h>

#define NSH_RL_BUFSIZE 1024
#define NSH_TOK_BUFSIZE 64
#define NSH_TOK_DELIM " \t\r\n\a"

extern void nsh_loop();
extern void nsh_read_line();
extern char **nsh_split_line(char *line);
