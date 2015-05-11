#include "minishell.h"
#include "internas.h"
#include "ejecutar.h"
#include "utilidades.h"

/*
Programa principal minishell
*/


/*


Primero llamaremos a las funciones imprimir_prompt() y leer_linea_ordenes(), ambas se encuentran en entrada_minishell.c. Leeremos la orden introducida y saldremos si es exit, en caso contrario verificaremos si es una orden interna, que sera realizada por la funcion ord_interna(), que está en libshell.a, en caso contrario se llama a la función ejecutar_linea_ordenes(), que encontraremos en ejecutar.c
*/




int main (int argc, char *argv[])
{

	char buf[BUFSIZ]; /* Para guardar entrada de teclado */
	char *token;/* Para guardar la entrada con formato adecuado */
	const char delim[2] =";";/* Para comprobar si hay varias ordenes */
	int color=0;	
	

/* Se establece un manejador */
	struct sigaction sa;
	  sa.sa_handler = SIG_IGN;; /* función manejadora */
	  sa.sa_flags = 0;
	  sigemptyset(&sa.sa_mask);/* Limpiamos la mascara */
	  if (sigaction(SIGCHLD, &sa,NULL) == -1)
	  {
	    perror("Error al eliminar PID, estado de finalizacion y otros recursos de un proceso finalizado");
	    exit(-1);/* utilizamos exit(-1) para tratamiento del error*/
	  }
	

	
	/* función añadida para dar la bienvenida */
	menu_inicial();




	while (1)
	{
  	  imprimir_prompt(color); /*Iniciamos prompt y leemos la linea de ordenes del usuario*/
  	  leer_linea_ordenes(buf);
 	  token = strtok(buf, delim);/*Separamos la cadena*/

 	  while(token != NULL) 
 	  {
	    if (strcmp(token,"exit") == 0)/*Comparamos si es la orden es igual que exit o Exit, en ese caso la minishell se cerrara*/
	    {
	      exit(0);  
	    }
	    else if (strcmp(token,"Exit") == 0)
	    {
	      exit(0);  
	    }


	    /*Estos if nos sirven para saber el color que quiere el usuario y comunicar el cambio a imprimir_prompt()*/

	    else if (strcmp(token,"Rojo") == 0)
	    {
	      color=1;  
	    }
	    else if (strcmp(token,"Verde") == 0)
	    {
	      color=2;  
	    }
	    else if (strcmp(token,"Azul") == 0)
	    {
	      color=3;  
	    }
	    else if (strcmp(token,"Magenta") == 0)
	    {
	      color=4;  
	    }
 	    else if (strcmp(token,"Cyan") == 0)
	    {
	      color=5;  
	    }




	    if (ord_interna(token) == 0)/*Comparamos si es una orden interna, si lo es, la función la ejecuta automáticamente*/  
	    {
	      ejecutar_linea_ordenes(token);
              token = strtok(NULL, delim);/*Pasamos al siguiente token*/
	    }
	    else
	    {
	      token = strtok(NULL, delim);/*Pasamos al siguiente token*/
	    }
	  }
	}
	return 0;
}





/*


imprimir_prompt(): Imprime una cadena sencilla, está función modifica el color del texto, para que sea más sencillo diferenciar el contenido que pertenece a la minishell y facilitar las pruebas. La modificacion se encuentra en entrada_minishell.c
*/

/*


leer_linea_ordenes(): Guarda la línea de ordenes introducida por el usuario. Además de esto, durante su ejecucion se invoca a eliminar_salto_linea() que permite limpiar la cadena introducida e introducir el caracter de fin de orden.Se encuentra en entrada_minishell.c
*/

/*


ord_interna(): ejecuta una orden si es interna

- si la ejecuta devuelve 1
- si no la ejecuta, por tanto es externa, devuelve 0

Se encuentra dentro de libshell.a
*/

/*


ejecutar_linea_ordenes(): Se encarga de ejecutar las ordenes introducidas, en su ejecución también participa la funcion pid_t ejecutar_orden(). Se encuentra en ejecutar.c
*/



/*
POSIX: signation()

signation(): Es un mecanismo de comunicacion asincrono. Nos permite configurar la señal que queremos recibir, en este caso del proceso hijo.

En este caso hemos optado por especificar explicitamente SIGCHLD como manejador de SIG_IGN, como alternativa al uso de waitpid, aunque con la opción WNOHANG no es bloqueante. 

sa_handler es un puntero a la función manejadora, en este caso tratar_alarma()
sa_mask es la mascara con las señales, utilizamos la funcion sigemptyset(), como indica su nombre, establece una mascara vacia, sig empty set.

*/



/*


strtok(): Stringtoken, convierte una cadena en una serie tokens con el delimitador indicado, en este caso nos interesa utiliza ";"

Sus parametros son str y delim


*/


