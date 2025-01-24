//This script was created by Sir Nacho

#define "cLibrary/nachoShell.h"


int main (int argc, char **argv) {

  //load any config files above

  nsh_loop();

  //Performs any shutdown or cleanup

  return EXIT_SUCCESS; //
}

char* getUsername() {
  char* username = getenv("USER");

  if (username != NULL) {
    return username;
  }
  else {
    printf("NachoShell: Unable to grab your username.");
    username = "NULL";
    return username;
  }
}

void nsh_loop(void){
  char *line;
  char **args;
  int status;
  //int shellLaunchStatus; //<-- This is to know if the shell is in debug or safe mode
  do {
    printf("(NachoShell) ");
    line = nsh_read_line();
    args = nsh_split_line(line);
    status = nsh_execute(args);

    free(line);
    free(args);
  } while (status);
}

char *nsh_read_line(void){
  int bufSize = NSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;
  
  //buffer check
  if (!buffer) {
    fprintf(stderr, "NachoShell: allocation error\n");
    exitEXIT_FAILURE;
  }

  while (1) {
    //reading a character
    c = getchar();

    //if hit with the EOF, replace with a null character and return.

    if (c == EOF || c=='\n'){
      buffer[position] = '\0';
      return buffer;
    }
    else {
      buffer[position] = c;

    }
    position++;

    //If exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += NSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "NachoShell: allocation error\n");
        exit EXIT_FAILURE;
      }
    }
  }
}
