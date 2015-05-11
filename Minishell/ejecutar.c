#include "minishell.h"
#include "parser.h"
#include "ejecutar.h"
#include "libmemoria.h"


/*


Estas dos funciones trabajan juntas, explicamos su funcionamiento en general ahora y de manera pormenorizada en cada una de ellas. En la parte inferior se encuentran las explicaciones de las funciones y servicios POSIX
*/



/* 


ejecutar_linea_ordenes() Invocar a la función ejecutar_orden(), despues debe comprobar la existencia o no del símbolo "ampersand", "&"(la variable es backgr) al final de la orden. Esta información es devuelta por la función ejecutar_orden() (1 si hay, 0 si no). 

En función del chequeo, ejecutar_linea_ordenes() actuara de la siguiente manera: 

- Si no está, debemos esperar a que termine el proceso hijo(primer plano)(le han devuelto 0). 

- Si está, no debemos esperar a que termine el proceso (segundo plano)(le han devuelto 1).

ejecutar_orden() actuara creando una minishell hija para ejecutar la orden.

- Primero convertiremos la orden en una estructura adecuada mediante la función parser_orden() y esto sera almacenado en args. 

- Usaremos un fork() y en el caso del hijo reemplazaremos su contenido con las ordenes de args(exec()), en el caso del padre únicamente devolveremos el pid.

- Llamaremos a la funcion free_argumentos() para liberar memoria (esta en la libreria libmemoria.c). 
*/



/*


Esta función debe dar formato a la orden recibida, crear un proceso hijo con esos datos y liberar la memoria que se haya utilizado. 
*/

pid_t ejecutar_orden (const char *orden, int *pbackgr)
{
	char **args;/*Esto es un puntero con las ordenes*/
	pid_t pid;/*El pid del proceso*/	
	int indice_entrada;/*indices de entrada y de salida*/
	int indice_salida;
	

	/*Se le da formato con la función parser_orden*/
	if ((args=parser_orden(orden,&indice_entrada,&indice_salida,pbackgr))== NULL)/*pbackgr 1 si hay "&" y 0 si no hay "&"*/
	{
    	  return(-1);
   	}


	else
	{
	  pid = fork();/*Creamos el hijo*/


	  if (pid == 0)   /*Parte hijo*/
	  {
	   /*Reemplazamos el codigo del hijo con el de la orden*/
	    
	      if (execvp(args[0], args) == -1)
		{
	        perror("Comando no valido\n");/*Tratamos el posible error*/
	        exit(-1);
		}
	  }
	  if (pid == -1)/*Error en el fork*/
	  {
  	    perror("Error al crear un proceso secundario\n");
	    exit(-1);
	  }

	 
	  free_argumentos(args);/*Liberamos la memoria*/
	}

return pid;

   /* si la orden tiene redirecciones o tuberias, puede incluir aqui, fuera del */
   /* ambito de esta practica, el codigo para tratamiento de esas redirecciones.*/                     
	
	
}










/*


Esta función recibe la orden que le mandamos, es un paso intermedio antes de realizarla. Envia la información a ejecutar_orden y recibe de ella si hay "&" o no hay "&" y actuar en consecuencia.
*/

 
void ejecutar_linea_ordenes(const char *orden)
{
	pid_t pid;
	int backgr;
	int status;
	/*Llamada a la función ejecutar_orden()*/

	/*
	La función nos indicara si hay "&" devolviendo un 1, nos dara un 0 si no, en backgr
	-Con un 0 es primer plano, no hay &, se debe esperar a que finalice.
	-Con un 1 es en segundo plano, hay &, no se debe esperar a que finalice.
	*/

	pid=ejecutar_orden(orden,&backgr);


	/*Comprobamos el &*/	
 	if ((backgr==1) & (pid >0)) /*Tiene &. No debemos esperar a que termine el hijo para seguir, background*/
	{
	  printf("PID del proceso en segundo plano: %d\n", pid);
	}
	else
	{ 
	  waitpid(pid,&status,0);/*Esperamos a que el hijo termine mediante un servicio POSIX*/
	  /*No tiene &.Debemos esperar a que termine, foreground*/
	  
	}



	/* si la orden es compuesta, puede incluir aqui, fuera del ambito*/
	/* de esta practica, el codigo para tratamiento de tuberias.     */

}  






/*


parser_orden(): convierte la orden en una estructura de array de punteros a cadenas. Crea un array dinámico.

- Una cadena por argumento implicado en la orden.
- Si hay redirecciones, dos cadenas, una con la redireccción y otra con el nombre.
- Si hay "ampersand", "&", lo elimina pero indica la eliminación.

- Devuelve en los parametros indentrada y indsalida el del array de la cadena, si no hay redireción el parametro es -1. 
- pbackgr 1 si hay "&" y 0 si no hay "&".
*/

/*


free_argumentos(): se encarga de liberar la estructura de argumentos de tipo array dinámico creada por parser_orden(). Esta incluida en la libreria libmemoria.c, se le envían los argumentos (args) y los va liberando mediante free().
*/

/*
POSIX: fork(), execvp(), exit(), waitpid()
*/

/*


fork(): Crea un hijo
- si sale bien retorna el PID del hijo y al hijo 0
- si falla devuelve -1 y no crea hijo 
*/

/*


exec(): Reemplaza el codigo del proceso por otro
- si falla devuelve un -1

Usamos execvp(). El primer parámetro se trata del nombre del programa y se confía en el contenido de la variable de entorno $PATH.
*/

/*


exit(): finaliza la ejecución del proceso
- indica como ha finalizado en un int(status)
*/

/*


wait(): Obtiene la informacion de finalización de un proceso
- Si sale bien devuelve el PID del hijo que ha finalizado y el estado(int status)
- si no hay hijos o han terminado devuelve -1

Usamos waitpid() porque vamos a esperar la finalizacion de un proceso hijo en concreto que se especifica en pid.


*/

