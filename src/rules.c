#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "geometry.h"
#include "world.h"
#include "neighbors.h"
#include <unistd.h>
#include <time.h>
#include "limits.h"
#include "project.h"

enum plateau {
    CARRE = 0,
    HEXAGONE = 1,
    TRIANGLE = 2,
    MAX_PLATEAU = 3,
};

void modif_rules(int argc, char *argv[]){
    char* type_victoire="s";
    int RNG=2; //initialisation random
    int MAX_TURNS=2*WORLD_SIZE;
    for( int i = 0; i < argc - 1; i++){ // On va jusqu'à argc - 1 car si on a un paramètre en dernier argument, il n'y a pas de valeur implémenté derrière donc il est inutile
        if(argv[i] == "-t"){
            type_victoire = argv[i+1];
        }
        if(argv[i] == "-m"){
            MAX_TURNS = atoi(argv[i+1]);
        }
        if(argv[i] == "-s"){
            RNG = atoi(argv[i+1]);
        }
    }
}
