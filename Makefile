WIDTH ?= 5
HEIGHT ?= 4
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)

all: project

%.o: %.c
	gcc -c $(CFLAGS) $<

project: project.o 
	gcc $(CFLAGS) project.o -o project 

test_project: test.o 
	gcc $(CFLAGS) test.o -o test_project

clean:
	rm -f project test_project *.o *~
