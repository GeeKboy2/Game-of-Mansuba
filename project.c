#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "geometry.h"
#include "world.h"
#include "neighbors.h"
#include "geometry.c"
#include "world.c"
#include "neighbors.c"
#include "rules.c"

// Créé le monde et set les différents pions dans leur position initiale

int main(int argc,char *argv[]){
  struct world_t* world = world_init();
  position_init(world);
  for(int i = 0; i <WORLD_SIZE ; i++){
    if(i%WIDTH == 0){
      printf("|");
    }
    printf("%d,%d|",world ->point[i].c,world->point[i].s);
    if(i%WIDTH == WIDTH-1){
      printf("\n");
    }    
  }
  return 0;
}
