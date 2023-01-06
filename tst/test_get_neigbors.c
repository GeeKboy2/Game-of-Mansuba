#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "geometry.h"
#include "world.h"
#include "neighbors.h"
#include <unistd.h>
#include <time.h>
#include "limits.h"
#include "project.h"
#include <getopt.h>

void print_get_neighbors(unsigned int index){
    struct neighbors_t print;
    print = get_neighbors(index);
    printf("On regarde les voisins du pion à la position : %d", i);
    for(int j = 0; j < MAX_NEIGHBORS; j++){
        printf("Le voisin à la direction %c a l'indice %d",dir_to_string(print.n[j].d, print.n[j].i));
    }
}