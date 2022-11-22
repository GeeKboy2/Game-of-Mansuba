#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./geometry.h"
#include "./world.h"
#include "./neighbors.h"
#include "./rules.c"
/*
#ifndef MAX_TURNS
#define MAX_TURNS (2*WORLD_SIZE)
#endif
*/
//#define TURN 0

void show_world(struct world_t* world)
{
  for(int i = 0; i <WORLD_SIZE ; i++){
    if(world ->point[i].c ==2)
      {
	printf("%s"," ⛀ ");
      }
    if(world ->point[i].c==1)
      {
	printf("%s"," ⛂ ");
      }
    if(world ->point[i].c==0)
      {
	printf(" . ");
      }
    if(i%WIDTH == WIDTH-1){
      printf("\n");
    }    
  }
}


enum color_t get_random_player()
{
  return rand()%2;
}


enum color_t next_player(enum color_t current_player)
{
  if(current_player==0)
  {
    return current_player++;
  }else{
    return current_player--;
  }

}

// Créé le monde et set les différents pions dans leur position initiale

int main(int argc,char *argv[]){
  char* type_victoire="c";
  int RNG=2; //initialisation random
  int MAX_TURNS=2*WORLD_SIZE;

  if(argc>1){
  type_victoire= argv[6];
  MAX_TURNS=atoi(argv[4]);
  RNG=atoi(argv[2]);

  //(void) type_victoire;
  //(void) MAX_TURNS;
  (void) RNG;
  }
  struct world_t* world = world_init();
  position_init(world);
  show_world(world);
  init_neighbors(0); // Use seed 0 at the beginning of a game
  enum color_t current_player = get_random_player();
  while(ConditionVictoire(piece,type_victoire,MAX_TURNS)!=0);
    p = choose_random_piece_belonging_to(world, current_player);
    m = choose_random_move_for_piece(world, p);
    move_piece(world, m);
    current_player = next_player(current_player);
  
  return 0;
}
