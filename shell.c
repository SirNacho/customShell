//This script was created by Sir Nacho

#include "cLibrary/nachoShell.h"

extern void nsh_loop (){
  char *line;
  char **args;
  int status;

  do {
    printf("(nachoShell) ");
    line = nsh_read_line();
    args = nsh_split_line(line);
    status = nsh_execute(args);

    free(line);
    free(args);
  } while (status);
}

extern char *nsh_read_line(){
  int bufsize = NSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  
  //checks and reallocate more space if needed...
  if (!buffer) {
    fprintf(stderr, "nachoShell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while(1){
    c = getChar();

    if (c == EOF || c == '\n') {
      buffer[position] = '\0'; //If get hit by EOF, we must replace it with a null character.
      return buffer;
    }
    else {
      buffer[position] = c;
    }
    position++;

    //If exceeded buffer, reallocate the space
    if (position >= bufsize) {
      bufsize += NSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "nachShell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

extern char *nsh_split_line(char *line){
  int bufsize = NSH_TOK_BUFSIZE, position = 0;
  char ** tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens){
    fprintf(stderr, "nachoShell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strlok(line, NSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += NSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "nachoShell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, NSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  returns tokens;
}

extern int nsh_launch(char **args){
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0){
    if (execvp(args[0], args) == -1) {perror("nsh");}
    exit(EXIT_FAILURE);
  }
  else if (pid < 0){perror("nsh");}
  else{
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    }while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int main(int argc, char **argv){
  
//load Config files, if any...
  
  nsh_loop();

  return (EXIT_SUCCESS);
}


