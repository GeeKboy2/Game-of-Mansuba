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

//In this file. All the laws of the game are defined.


struct piece_t{
  int blanc[WORLD_SIZE];
  int noir[WORLD_SIZE];
};

struct depart_t{
  struct piece_t piece;
};

//Call the correct get_neighbor function according the table type.
unsigned int get_neighbor_in_table(unsigned int idx ,enum dir_t d,unsigned int type_plateau){
    if(type_plateau==0){ //Square.
        return get_neighbor(idx,d);
    }
    if(type_plateau==1){ //Hexagonal.
        return get_neighbor_hex(idx,d);
    }
    if(type_plateau==2){ //Triangular.
        return get_neighbor_triangle(idx,d);
    }
    return UINT_MAX;
}

//Choose a random player to start the game.
enum color_t get_random_player()
{
  srand(time(NULL));
  return rand()%2+1;
}

//Switche the playing hand to the other player.
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

//Choose a random piece belonging to a player.
int choose_random_piece_belonging_to(struct world_t* world, enum color_t current_player){
  int compteur = 0;
  for(int i = 0; i<WORLD_SIZE; i++){ //Count the number of pieces in the world.
    if(world_get(world,i)==current_player && world_get_sort(world,i)!=NO_SORT){
      printf("found %d ",i);
      compteur++;
    }
  }
  if(compteur <4){
    exit(100);
  }
  srand(time(NULL));
  int pos = (rand()%compteur)+1;//Gets the number of a random piece.
  int num = 0;//Will be increacing until it reaches the number of the piece.
  int i = 0; //The index of the piece.
  while(num <= compteur && i< WORLD_SIZE){ //Travel the world.
    if(world_get(world,i)==current_player && world_get_sort(world,i)!=NO_SORT){ //Increasing num.
      num++;
    }
    if(num==pos) //We reached the piece the rand() gave us.(We are 100% sure this case will be true at some point)
    {
      return i; //Retun it's index.
    }
    i++; 
  }
  //The case i=WORLD_SIZE is already solved in the loop.
  i--; //This case will never be reached but in case i=WORLD_SIZE we substract one and return it.
  return i;
}

//This function calls the functions that chooses a random move for a piece according to its type.
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

//Move a piece from a starting position to an end position.
void move_piece(struct world_t* world,unsigned int index_arrivee,unsigned int index_depart) 
{
  printf("%d -> %d\n",index_depart,index_arrivee);
   if(index_arrivee == UINT_MAX){ 
   }
   else{
   enum color_t color=world_get(world,index_depart);
   enum sort_t sort=world_get_sort(world,index_depart);
   printf("copie de couleur et type de %d\n",index_depart);
   show_world(world);
   printf("-----------------\n");
   world_set(world,index_depart,0);
   world_set_sort(world,index_depart,0);
   printf("suppresion de piece\n");
   show_world(world);
   printf("-----------------\n");
   world_set(world,index_arrivee,color);
   world_set_sort(world,index_arrivee,sort);
   printf("ajout de piece a la pos %d\n",index_arrivee);
   show_world(world);
   printf("-----------------\n");
  }
}

//Define victory conditions according the type of victory.
unsigned int condition_victoire(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN){
  if(MAX_TURNS <= TURN){
    printf("MAX_TURNS reached.\n");
    return 0;
  }
  if(type_victoire[0] == 's'){
    for(int i = 0; i<WORLD_SIZE;i++){
      if(world_get(world,i)== WHITE && i%WIDTH==0){
	      printf("Simple Victory (WHITE)\n");
	      return 0;
      }
      if(world_get(world,i)==BLACK && i%WIDTH==WIDTH-1){
      	printf("Simple Victory (BLACK)\n");
	      return 0;
      }
    }
  }
  int compteur_blanc = 0; //Count the number of white pieces are in the
  int compteur_noir = 0;
  if(type_victoire[0] == 'c'){
    for(int i = 0; i<WORLD_SIZE;i++){
      if(world_get(world,i)==WHITE && i%WIDTH==0){ //Counting the number of white pieces.
	      compteur_blanc++;
      }
      if(world_get(world,i)==BLACK && i%WIDTH==WIDTH-1){ //Counting the number of black pieces.
	      compteur_noir++;
      }
    }
    if (compteur_blanc == HEIGHT){ //Max number of pieces reached.
      printf("Victoire complexe des blancs\n");
      return 0;
    }
    if(compteur_noir == HEIGHT){ //Max number of pieces reached.
      printf("Victoire complexe des noirs\n");
      return 0;
    }
  }
  return UINT_MAX;
}



void position_initialisation(enum init type_init,struct world_t* world){
  if(type_init==PIONS){ //Two columns of pawns.
    position_init(world);
  }else if(type_init==PAWNS_TOWERS_ELEPHANTS){ //Mix of pawns elephants and tours.
    position_init(world);
    world_set(world,0,BLACK);
    world_set_sort(world,0,TOUR);
    world_set(world,WIDTH-1,WHITE);
    world_set_sort(world,WIDTH-1,TOUR);

    world_set(world,WORLD_SIZE-WIDTH,BLACK);
    world_set_sort(world,WORLD_SIZE-WIDTH,ELEPHANT);
    world_set(world,WORLD_SIZE-1,WHITE);
    world_set_sort(world,WORLD_SIZE-1,ELEPHANT);
  }else {
    printf("INVALID INITIALISATION\n");
  }
}





