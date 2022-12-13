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



unsigned int get_neighbor_in_table(unsigned int idx ,enum dir_t d,unsigned int type_plateau){
    if(type_plateau==0){
        return get_neighbor(idx,d);
    }
    if(type_plateau==1){
        return get_neighbor_hex(idx,d);
    }
    if(type_plateau==2){
        return get_neighbor_triangle(idx,d);
    }
    return UINT_MAX;
}

enum color_t get_random_player()
{
  /*srand(time(NULL));
  return rand()%2+1;*/
  return BLACK;
}

enum color_t next_player(enum color_t current_player)
{
  if(current_player==BLACK)
  {
    current_player++;
    return current_player;
  }
  if(current_player==WHITE)
  {
    current_player--;
    return current_player;
  }
  return current_player;
}

int choose_random_piece_belonging_to(struct world_t* world, enum color_t current_player){
  int compteur = 0;
  for(int i = 0; i<WORLD_SIZE; i++){
    if(world_get(world,i) == current_player){
      compteur++;
    }
  }
  srand(time(NULL));
  int pos = (rand()%compteur)+1;
  int num = 0;
  int i = 0;
  while(num <= compteur && i< WORLD_SIZE){
    if(world_get(world,i) == current_player){
      num++;
    }
    if(num==pos)
    {
      return i;
    }
    i++;
  }
  i--;
  return i;
}

unsigned int choose_random_move_for_piece(struct world_t *world,int index)
{
  if(world_get_sort(world,index)==PAWN)
  {
    return mov_pawn(world,index);
  }
  if(world_get_sort(world,index)==TOUR)
  {
    return mov_tour(world,index);
  }
  if(world_get_sort(world,index)==ELEPHANT)
  {
    return mov_elephant(world,index);
  }
  return UINT_MAX;
}


void move_piece(struct world_t* world,unsigned int index_arrivee,unsigned int index_depart) // Mettre des unsigned int %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
{
   if(index_arrivee == UINT_MAX){ 
   }
   else{
   enum color_t color=world_get(world,index_depart);
   enum sort_t sort=world_get_sort(world,index_depart);
   world_set(world,index_depart,0);
   world_set_sort(world,index_depart,0);
   world_set(world,index_arrivee,color);
   world_set_sort(world,index_arrivee,sort);
  }
}

unsigned int condition_victoire(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN){
  if(MAX_TURNS <= TURN){
    printf("Nombre de tour maximum atteint, pas de vainqueur\n");
    return 0;
  }
  if(type_victoire[0] == 's'){
    for(int i = 0; i<WORLD_SIZE;i++){
      if(world_get(world,i)== WHITE && i%WIDTH==0){
	      printf("Victoire simple des blancs\n");
	      return 0;
      }
      if(world_get(world,i)==BLACK && i%WIDTH==WIDTH-1){
      	printf("Victoire simple des noirs\n");
	      return 0;
      }
    }
  }
  int compteur_blanc = 0;
  int compteur_noir = 0;
  if(type_victoire[0] == 'c'){
    for(int i = 0; i<WORLD_SIZE;i++){
      if(world_get(world,i)==WHITE && i%WIDTH==0){
	      compteur_blanc++;
      }
      if(world_get(world,i)==BLACK && i%WIDTH==WIDTH-1){
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
  return UINT_MAX;
}
