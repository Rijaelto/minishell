# makefile 
# usar tabulador (no espacios) en la línea de comando
# $@ nombreobjetivo X regla
# $^ dependencias en lista
# -c(stopstep) -g(infodepuracion) -Wall(avisoscompilacion) -pedantic(compruebaC)

CC=gcc
CFLAGS = -Wall -g -pedantic


minishell: minishell.o entrada_minishell.o libshell.a libmemoria.o ejecutar.o utilidades.o
	$(CC) $(CFLAGS) -o $@ minishell.o entrada_minishell.o libmemoria.o ejecutar.o utilidades.o -L. -lshell

minishell.o: minishell.c minishell.h entrada_minishell.h ejecutar.h utilidades.h
	$(CC) $(CFLAGS) -c minishell.c

entrada_minishell.o: entrada_minishell.c entrada_minishell.h
	$(CC) $(CFLAGS) -c entrada_minishell.c

ejecutar.o: ejecutar.c ejecutar.h parser.h libmemoria.h
	$(CC) $(CFLAGS) -c ejecutar.c 

libmemoria.o: libmemoria.c libmemoria.h
	$(CC) $(CFLAGS) -c libmemoria.c

utilidades.o: utilidades.c utilidades.h
	$(CC) $(CFLAGS) -c utilidades.c

clean:
	rm minishell minishell.o entrada_minishell.o libmemoria.o ejecutar.o utilidades.o





