#include <stdio.h>
#include <stdlib.h>
#include "./src/geometry.h"
#include "./src/world.h"
#include "world.c"

struct piece{
  int blanc[HEIGHT];
  int noir[HEIGHT];
};

struct piece piece;
void position_init(){
  int b = 0;
  int n = 0;
  for(int i = 0; i< WORLD_SIZE; i++){
    if(i%WIDTH==0){
      piece.noir[n]=i;
      n++;
    }
    if(i%WIDTH==WIDTH-1){
      piece.blanc[b]=i;
      b++;
    }
  }
}

int main(int argc,char *argv[]){
  position_init();
  for(int i = 0;i<HEIGHT;i++){
    printf("BLANC[%d] = %d | NOIR[%d] = %d\n",i,piece.blanc[i],i,piece.noir[i]);
  }
  return 0;
}

/*
// Règle de base : Noir à gauche, Blanc à droite
void position_init(struct world_t* b){
  enum color_t color;
  enum sort_t sort=1;
  for(int i = 0; i < WORLD_SIZE; i++){
    if(i%WIDTH == 0){
      color=1;
      world_set(b,i,color);      
      world_set_sort(b,i,sort);
    }
    if(i%WIDTH == WIDTH - 1){
      color=2;
      world_set(b,i,color);
      world_set_sort(b,i,sort);
    }
  }
}

void test_position_init(){
  struct world_t* b;
  b = world_init();
  position_init(b);
  for(int i; i<WORLD_SIZE;i++){
    printf("i : %d --> %d, %d\n",i, b->point[i].c,b->point[i].s); 
  }
}

*/
