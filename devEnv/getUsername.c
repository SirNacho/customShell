#include <stdio.h>
#include <stdlib.h>

int main (){
  char* username = getenv("USER");

  if (username != NULL) {
    printf("Yo, %s\n", username);
  }
  else {
    printf("What you mean I can't retrieve your username?\n");
  }

  return EXIT_SUCCESS;
}
