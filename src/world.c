#include "world.h"
#include <stdio.h>
//#include "geometry.h"

struct pion{
  enum color_t c;
  enum sort_t s;
};

struct world_t{
  struct pion point[WORLD_SIZE];
};

struct world_t world;
struct world_t* world_init(){
  //struct world_t* world;
  for(int i = 0; i < WORLD_SIZE; i++){
    world.point[i].c = 0;
    world.point[i].s = 0;
  }
  return &world;
}

enum color_t world_get(const struct world_t* b, unsigned int idx){
  return b -> point[idx].c;
}

void world_set(struct world_t* b, unsigned int idx, enum color_t c){
  b->point[idx].c = c;
}

enum sort_t world_get_sort(const struct world_t* b, unsigned int idx){
  return b->point[idx].s;
}

void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c){
  b -> point[idx].s = c;
}

struct piece{
  int blanc[HEIGHT];
  int noir[HEIGHT];
};

//struct piece piece;
int position_init(struct world_t* world){
  int b = 0;
  int n = 0;
  for(int i = 0; i< WORLD_SIZE; i++){
    if(i%WIDTH==0){
      //piece.noir[n]=i;
      world_set(world,i,2);
      world_set_sort(world,i,1);
      n++;
    }
    if(i%WIDTH==WIDTH-1){
      //piece.blanc[b]=i;
      world_set(world,i,1);
      world_set_sort(world,i,1);
      b++;
    }
  }
  return 0;
}

#define TURN 0
int condition_victoire(struct world_t * world,char *type_victoire,int MAX_TURNS){
  if(MAX_TURNS == TURN){
    printf("Nombre de tour maximum atteint, pas de vainqueur\n");
  }
  if(type_victoire[0] == 's'){
    for(int i = 0; i<WORLD_SIZE;i++){
      if(world_get(world,i)==1 && i%WIDTH==0){
	      printf("Victoire simple des blancs\n");
	return 0;
      }
      if(world_get(world,i)==2 && i%WIDTH==WIDTH-1){
      	printf("Victoire simple des noirs\n");
	return 0;
      }
    }
  }
  int compteur_blanc = 0;
  int compteur_noir = 0;
  if(type_victoire[0] == 'c'){
    for(int i = 0; i<WORLD_SIZE;i++){
      if(world_get(world,i)==1 && i%WIDTH==0){
	      compteur_blanc++;
      }
      if(world_get(world,i)==2 && i%WIDTH==WIDTH-1){
	      compteur_noir++;
      }
    }
    if (compteur_blanc == HEIGHT){
      printf("Victoire complexe des blancs\n");
      return 0;
    }
    if(compteur_noir == HEIGHT){
      printf("Victoire complexe des noirs\n");
      return 0;
    }
  }
  return -1;
}

/* int main(int argc,char *argv[]){ */
/*   struct world_t* world = world_init(); */
/*   position_init(world); */
/*   for(int i = 0; i <WORLD_SIZE ; i++){ */
/*     if(i%WIDTH == 0){ */
/*       printf("|"); */
/*     } */
/*     printf("%d,%d|",world ->point[i].c,world->point[i].s); */
/*     if(i%WIDTH == WIDTH-1){ */
/*       printf("\n"); */
/*     }     */
/*   } */
/*   return 0; */
/* } */

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