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

project: geometry.o world.o neighbors.o hexagone.o triangle.o show_world.o pawn.o tour.o rules.o elephant.o project.o# (Add your dependency here, e.g "project.o")
	$(CC) $(CFLAGS) geometry.o world.o neighbors.o hexagone.o triangle.o show_world.o pawn.o tour.o rules.o elephant.o project.o -o project -lm

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

show_world.o: src/show_world.c
	$(CC) $(CFLAGS) src/show_world.c -c -o show_world.o

pawn.o: src/pawn.c
	$(CC) $(CFLAGS) src/pawn.c -c -o pawn.o

tour.o: src/tour.c
	$(CC) $(CFLAGS) src/tour.c -c -o tour.o

elephant.o: src/elephant.c
	$(CC) $(CFLAGS) src/elephant.c -c -o elephant.o

rules.o: src/rules.c
	$(CC) $(CFLAGS) src/rules.c -c -o rules.o

project.o: src/project.c # (Add your dependency here, e.g "test.o")
	$(CC) $(CFLAGS) src/project.c -c -o project.o

test.o: tst/test.c
	$(CC) $(CFLAGS) $^ -o $@

#nom: dépendances (hors .h)
# commandes à executer

test:
	./project -m 50 -t s -s 0

clean:
	rm -f *.o *~ project
#utiliser avec :~/$ make clean