#include <stdio.h>
#include <stdlib.h>
#include "./src/geometry.h"
#include "./src/world.h"
#include "world.c"

// Règle de base : Noir à gauche, Blanc à droite
void position_init(struct world_t* b){
  for(int i; i < WORLD_SIZE; i++){
    if(i%WIDTH == 0){
      enum color_t color=1;
      world_set(b,i,color);
      enum sort_t sort=1;
      world_set_sort(b,i,sort);
    }
    if(i%WIDTH == WIDTH - 1){
      enum color_t color=2;
      world_set(b,i,color);
      enum sort_t sort=1;
      world_set_sort(b,i,sort);
    }
  }
}

int main(int argc, char *argv[]){
  struct world_t* b;
  b = world_init();
  position_init(b);
  for(int i; i<WORLD_SIZE;i++){
    printf("i : %d, %d, %d\n",i, p.point[i].c,p.point[i].s); 
  }
}


