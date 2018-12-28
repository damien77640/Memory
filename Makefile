but : Main

OFILES = 	main.o \
					rectouche.o \
					fin.o \
					jeu.o

CC = gcc

#-------------------------

rectouche.o : rectouche.h

main.o : jeu.h

fin.o : main.h

jeu.o : fin.h rectouche.h

#-------------------------

Main : $(OFILES)
			$(CC) -o Main $(OFILES) $(CFLAGS) -lgraph -ansi

clean :
	-rm -f $(OFILES) Main

run :
	./Main

.PHONY : but clean run
