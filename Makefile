CC=gcc
WIDTH ?= 5
HEIGHT ?= 4
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)
#-g3 sert au debuggage
# Utiliser $(CFLAGS) pour avoir tjs les mêmes flags et memes definitions de width et height dans tout les .o

all: project


%.o: %.c
	$(CC) -c $(CFLAGS) $<

project: geometry.o world.o neighbors.o hexagone.o triangle.o project.o # (Add your dependency here, e.g "project.o")
	$(CC) $(CFLAGS) geometry.o world.o neighbors.o hexagone.o triangle.o project.o -o project

#un seul .c pour faire un .o


world.o: src/world.c
	$(CC) $(CFLAGS) src/world.c -c -o world.o

hexagone.o: src/hexagone.c
	$(CC) $(CFLAGS) src/hexagone.c -c -o hexagone.o

triangle.o: src/triangle.c
	$(CC) $(CFLAGS) src/triangle.c -c -o triangle.o

geometry.o: src/geometry.c
	$(CC) $(CFLAGS) src/geometry.c -c -o geometry.o

neighbors.o: src/neighbors.c
	$(CC) $(CFLAGS) src/neighbors.c -c -o neighbors.o

project.o: src/project.c # (Add your dependency here, e.g "test.o")
	$(CC) $(CFLAGS) src/project.c -c -o project.o

test.o: tst/test.c
	$(CC) $(CFLAGS) $^ -o $@

#nom: dépendances (hors .h)
# commandes à executer

test:
	./project

clean:
	rm -f *.o *~ project
#utiliser avec :~/$ make clean