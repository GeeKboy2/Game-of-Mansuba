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



enum color_t get_random_player()
{
  srand(time(NULL));
  return rand()%2+1;
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

int condition_victoire(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN){
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
  return -1;
}


// Créé le monde et set les différents pions dans leur position initiale

int main(int argc,char *argv[]){
 
  char* type_victoire="s";
  int RNG=2; //initialisation random
  int MAX_TURNS=2*WORLD_SIZE;
  /*
  if(argc > 1){
    type_victoire = argv[6];
    MAX_TURNS = atoi(argv[4]);
    RNG = atoi(argv[2]);
    (void) RNG;
  }
  */
  MAX_TURNS = getopt(argc,argv,"-m:");
  struct world_t* world=world_init();
  position_init(world);

  world_set(world,0,BLACK);
  world_set_sort(world,0,TOUR);
  world_set(world,WIDTH-1,WHITE);
  world_set_sort(world,WIDTH-1,TOUR);

  world_set(world,WORLD_SIZE-WIDTH,BLACK);
  world_set_sort(world,WORLD_SIZE-WIDTH,ELEPHANT);
  world_set(world,WORLD_SIZE-1,WHITE);
  world_set_sort(world,WORLD_SIZE-1,ELEPHANT);
  ///////////////////////////////////////////////////////////test
  //int neigh=get_neighbor(10,-2);
  //printf("%d\n",neigh);
  //world_set(world,6,2);
  //world_set(world,13,2);
  //world_set(world,14,2);
  //world_set(world,19,2);
  //condition_victoire(world,"c",20);
  

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
  /*
  world_set(world,6,1);
  world_set_sort(world,6,1);
  world_set(world,13,2);
  world_set_sort(world,13,2);
  struct neighbors_t neigh=get_neighbors(7);
  for(int j=0;j<MAX_NEIGHBORS+1;j++)
  {
    printf("voisin %u de direction %u\n",neigh.n[j].i,neigh.n[j].d);
    //printf("voisin %u\n",get_neighbor(7,j-4));
  }
  */
 
  //printf("%d",MAX_NEIGHBORS);
  /*
  printf("voisin de 0 %d\n",get_neighbor(0,3));
  //printf("%d\n",next_player(1));
  */
  /*
  world_set(world,6,1);
  world_set_sort(world,6,1);
  printf("avant exemple nbr mvt\n");
  printf("nombre mvt = %d\n",nombre_mouvements(world,0));
  printf("avant choose random\n");
  printf("%d\n",choose_random_piece_belonging_to(world,1,));
  */
  ///////////////////////////////////////////////////////////test_fin
  //show_world(world);
  show_world_triangle(world);
  printf("############################\n");
  //init_neighbors(0); // Use seed 0 at the beginning of a game
  /*
  world_set(world,1,2);
  world_set_sort(world,1,2);
  world_set(world,3,2);
  world_set_sort(world,3,2);

  world_set(world,0,0);
  world_set_sort(world,0,0);

  world_set_sort(world,0,2);
  world_set_sort(world,WIDTH-1,2);
  */

  enum color_t current_player = get_random_player();
  int index_pion;
  int move;
  int nbr_turns=0;
  while(condition_victoire(world,type_victoire,MAX_TURNS,nbr_turns)!=0)
  {
    printf("c'est le tour du %d\n",current_player);
    index_pion = choose_random_piece_belonging_to(world, current_player);
    printf("la piece en mvt est %d\n",index_pion);
    move = choose_random_move_for_piece(world, index_pion);
    printf("elle va se deplacer vers %d\n",move);
    move_piece(world, move,index_pion);
    nbr_turns++;
    current_player = next_player(current_player);
    show_world_triangle(world);
    printf("############################ turn %d/%d\n",nbr_turns,MAX_TURNS);
    sleep(0.1);
  }

  return 0;
}
