#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./geometry.h"
#include "./world.h"
#include "./neighbors.h"
#include "./rules.c"

// Créé le monde et set les différents pions dans leur position initiale

int main(int argc,char *argv[]){
  char* type_victoire="c";
  int MAX_TURNS=2*WIDTH*HEIGHT;
  int RNG=2; //initialisation random

  if(argc>1){
  type_victoire= argv[6];
  MAX_TURNS=atoi(argv[4]);
  RNG=atoi(argv[2]);
  }
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
