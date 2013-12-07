#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int 
main(int argc, char *argv[])
{

  if (argc != 3) {
    fprintf(stderr, "Usage: %s string delim \n",
      argv[0]);
    exit(EXIT_FAILURE);
  }

  char *type, *ip, *port;
  
  type = strtok(argv[1], argv[2]);
  ip = strtok(NULL, argv[2]);
  port = strtok(NULL, argv[2]);
  printf("%s\n", type);
  printf("%s\n", ip);
  printf("%s\n", port);
}
