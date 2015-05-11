#include "entrada_minishell.h"
#include <stdlib.h>
#define Rojo     "\x1b[31m"
#define Verde   "\x1b[32m"
#define Azul    "\x1b[34m"
#define Magenta "\x1b[35m"
#define Cyan   "\x1b[36m"
#define Reset   "\x1b[0m"
#define prompt(clrprompt,text,clrusertext) printf("%s%s %s",clrprompt,text,clrusertext)

void imprimir_prompt(int color)
{


	char *clrprompt="\x1b[0m";
	char *clrusertext="\x1b[0m";


	switch(color) 
	{
	case 1:
	  clrprompt = "\x1b[31m";/*Rojo*/
	  break;
	case 2:
	  clrprompt = "\x1b[32m";/*Verde*/
	  break;
	case 3:
	  clrprompt = "\x1b[34m";/*Azul*/
	  break;
	case 4:
	  clrprompt = "\x1b[35m";/*Magenta*/
	  break;
	case 5:
	  clrprompt = "\x1b[36m";/*Cyan*/
	  break;
	default:
	  clrprompt = "\x1b[0m";/*Reset*/
	  break;
	}


   prompt(clrprompt,"minishell> ",clrusertext); /* se imprime en pantalla una cadena sencilla que servirá de prompt: entrada de órdenes en la consola, se cambia el color para que se pueda apreciar más facílmente donde empiezan las ordenes*/
   fflush(stdout);        /* vacía el buffer intermedio de salida y se envía el texto a la pantalla */

}

void eliminar_salto_linea(char *cad)
{
   int i, longitud;

   longitud=strlen(cad);  /* cad es una cadena de caracteres con la orden leída.*/
   for(i=longitud-1; i>=0;i--) /* se busca el carácter de final de línea introducido por fgets y se sustituye por '\0' para indicar el final de orden */
     if (cad[i]=='\n')         
     {
       cad[i]=0;
       break;
     }
}
       
void leer_linea_ordenes(char *buf)
{
    
   memset(buf, 0, sizeof(BUFSIZ));
   fgets(buf, BUFSIZ-1, stdin); /* fgets almacena la orden leída introduciendo también el carácter de fin de línea introducido */
   buf[BUFSIZ-1]=0; /* se almacena el carácter de fin de cadena al final de buf porque va a ser tratada por eliminar_salto_linea como cadena */
   eliminar_salto_linea(buf);  
}

