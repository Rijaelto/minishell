#include "libmemoria.h"
#include <stdlib.h>


void free_argumentos(char **args)
{
  int i=0;

  while(args[i])
    free(args[i++]);
  free(args);
}
