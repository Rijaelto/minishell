#ifndef PARSER_H
#define PARSER_H
enum TEstado {
   INICIO_ARG, ARG
};


 
char ** parser_orden (const char *orden, int *indentrada, int *indsalida, int *background);


#endif 