#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "geometry.h"
#include "world.h"
#include "neighbors.h"
#include <unistd.h>
#include <time.h>
#include "limits.h"
/*
#ifndef MAX_TURNS
#define MAX_TURNS (2*WORLD_SIZE)
#endif
*/
//#define TURN 0
//#define UINT_MAX 0

void show_world(struct world_t* world)
{
  for(int i = 0; i <WORLD_SIZE ; i++){
    if(world_get(world,i)==2)
      {
	printf("%s"," ⛀ ");
      }
    if(world_get(world,i)==1)
      {
	printf("%s"," ⛂ ");
      }
    if(world_get(world,i)==0)
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

int choose_random_piece_belonging_to(struct world_t* world, enum color_t current_player){
  int compteur = 0;
  for(int i = 0; i<WORLD_SIZE; i++){
    if(world_get(world,i) == current_player){
      compteur++;
    }
  }
  srand(time(NULL));
  int pos = rand()%compteur;
  int num = 0;
  int i = 0;
  while(num <= pos){
    if(world_get(world,i) == current_player){
      num++;
    }
    i++;
  }
  i--;
  return i;
}


void choose_random_move_for_piece(struct world_t *world,int index_pion)
{
  /*
  int mvt=-1;
  int nombre_mvt=nombre_mouvements(world,index_pion,mvt,index_pion);
  mvt=rand()%nombre_mvt;
  nombre_mvt=nombre_mouvements(world,index_pion,mvt,index_pion);
  return index_pion;
  */
}

void move_piece(struct world_t* world,int index_arrivee)
{
  world_set(world,index_arrivee,world_get(world,index_arrivee));
  world_set_sort(world,index_arrivee,world_get_sort(world,index_arrivee));
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

  (void) type_victoire;
  (void) MAX_TURNS;
  (void) RNG;
  }
  struct world_t* world=world_init();
  position_init(world);
  ///////////////////////////////////////////////////////////test
  //int neigh=get_neighbor(10,-2);
  //printf("%d\n",neigh);
  /*
  world_set(world,4,2);
  world_set(world,9,2);
  world_set(world,14,2);
  world_set(world,19,2);
  condition_victoire(world,"c",20);
  */

  /*
  int i = 0;
  while(i < WORLD_SIZE){
    struct neighbors_t dpl = deplacement_simple(world,i);
    printf("%d :\n", i);
    int j = 0;
    while(dpl.n[j].i != UINT_MAX){
      printf("%d\n", dpl.n[j].i);
      j++;
    }
    i = i + 10;
  }
  */
  world_set(world,1,1);
  world_set_sort(world,1,1);
  //world_set(world,2,1);
  //world_set_sort(world,2,1);
  world_set(world,6,1);
  world_set_sort(world,6,1);
  printf("%d\n",nombre_mouvements(world,0));
  ///////////////////////////////////////////////////////////test_fin
  show_world(world);
  printf("############################\n");
  //init_neighbors(0); // Use seed 0 at the beginning of a game
  /*
  enum color_t current_player = get_random_player();
  int index_pion;
  int move;
  while(condition_victoire(piece,type_victoire,MAX_TURNS)!=0)
  {
    index_pion = choose_random_piece_belonging_to(world, current_player);
    move = choose_random_move_for_piece(world, index_pion);
    move_piece(world, move);
    current_player = next_player(current_player);
    show_world(world);
    printf("############################\n");
    sleep(2);
  }
  
*/
  return 0;
}
