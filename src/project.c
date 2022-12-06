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
        if(world_get_sort(world,i)==1)
        {
          printf("%s"," ⛀ ");
        }
        if(world_get_sort(world,i)==2)
        {
          printf("%s"," ♖ ");
        }
        if(world_get_sort(world,i)==3)
        {
          printf("%s"," ♘ ");
        }
      }
      if(world_get(world,i)==1)
      { 
        if(world_get_sort(world,i)==1)
        {
          printf("%s"," ⛂ ");
        }
        if(world_get_sort(world,i)==2)
        {
          printf("%s"," ♜ ");
        }
        if(world_get_sort(world,i)==3)
        {
          printf("%s"," ♞ ");
        }
          
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
  srand(time(NULL));
  return rand()%2+1;
}

enum color_t next_player(enum color_t current_player)
{
  if(current_player==1)
  {
    current_player++;
    return current_player;
  }
  if(current_player==2)
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

int choose_random_move_for_piece(struct world_t *world,int index)
{
  if(world_get_sort(world,index)==1)
  {
    //printf("marche");
    struct neighbors_t ds=deplacement_simple(world,index);
    //printf("probleme deplacement simple");
    struct neighbors_t ss=saut_simple(world,index);
    struct neighbors_t sm = saut_multiple(world,index);
    //printf("saut simple");
    unsigned int compteur_ds=0;
    unsigned int compteur_ss=0;
    unsigned int nombre_mvt=nombre_mouvements(world,index);
    //printf("nombre mvt = %d\n",nombre_mvt);
    srand(time(NULL));
    if (nombre_mvt==0)
    {
      return index;
    }
    int rand_mvt=rand()%nombre_mvt;
    //printf("rand = %d\n",rand_mvt);
    int somme=0;
    while(ds.n[compteur_ds].i!=UINT_MAX && compteur_ds < MAX_NEIGHBORS)
    {
      if(somme==rand_mvt)
      {
        return ds.n[compteur_ds].i;
      }
      compteur_ds++;
      somme++;
      
      /*
      if(ds.n[compteur_ds].i==UINT_MAX)
      {
        compteur_ss++;
      }else{
        compteur_ds++;
      }
      if(ds.n[compteur_ds].i==UINT_MAX)
      {

      }else{
        return ds.n[compteur_ds].i;
      }
      */
    }
    while (ss.n[compteur_ss].i!=UINT_MAX && compteur_ss < MAX_NEIGHBORS)
    {
      if(somme==rand_mvt)
      {
        return get_neighbor(ss.n[compteur_ss].i,ss.n[compteur_ss].d);
      }
      compteur_ss++;
      somme++;
    }
    if(somme == rand_mvt && sm.n[0].i != UINT_MAX)
    {
      return get_neighbor(sm.n[0].i,sm.n[0].d);
    }
    return index;
  }
  if(world_get_sort(world,index)==2)
  {
    struct neighbors_t tour = translation_cardinale(world,index);
    if(tour.n[0].i == UINT_MAX){
      return index;
    }
    int nbre_mvt = 0;
    for(int j = 0; tour.n[j].i != UINT_MAX; j++){
      nbre_mvt = j+1;
    }
    srand(time(NULL));
    int rand_dir = rand()%nbre_mvt;
    int compteur_case = 0;
    unsigned int pos = get_neighbor(index,tour.n[rand_dir].d);
    while(pos != UINT_MAX && world_get_sort(world,pos) == 0){
      compteur_case++;
      pos = get_neighbor(pos,tour.n[rand_dir].d);
    }
    int rand_mvt = rand()%(compteur_case)+1;
    for(int k = 0; k < rand_mvt; k++){
      index = get_neighbor(index,tour.n[rand_dir].d);
    }
    return index;
  }
  if(world_get_sort(world,index)==3)
  {
    struct ensemble_t ds=deplacement_simple_3(world,index);
    unsigned int compteur_ds=0;
    unsigned int nombre_mvt=nombre_semidiag(world,index);

    srand(time(NULL));
    if (nombre_mvt==0)
    {
      return index;
    }
    int rand_mvt=rand()%nombre_mvt;
    int somme=0;
    while(ds.n[compteur_ds].i!=UINT_MAX && compteur_ds < 13)
    {
      if(somme==rand_mvt)
      {
        return ds.n[compteur_ds].i;
      }
      compteur_ds++;
      somme++;
    }
  }
  return -1;
}


void move_piece(struct world_t* world,int index_arrivee, int index_depart)
{
   if(index_arrivee == -1){
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

int position_init_tour(struct world_t* world){
    int b = 0;
    int n = 0;
    for(int i = 0; i< WORLD_SIZE; i++){
      if(i%WIDTH==0){
        //piece.noir[n]=i;
        world_set(world,i,2);
        world_set_sort(world,i,2);
        n++;
      }
      if(i%WIDTH==WIDTH-1){
        //piece.blanc[b]=i;
        world_set(world,i,1);
        world_set_sort(world,i,2);
        b++;
      }
    }
    return 0;
}

int condition_victoire(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN){
  if(MAX_TURNS <= TURN){
    printf("Nombre de tour maximum atteint, pas de vainqueur\n");
    return 0;
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

// Créé le monde et set les différents pions dans leur position initiale

int main(int argc,char *argv[]){
  char* type_victoire="s";
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
  struct world_t* world=world_init();
  position_init(world);

  world_set(world,0,2);
  world_set_sort(world,0,2);
  world_set(world,WIDTH-1,1);
  world_set_sort(world,WIDTH-1,2);

  world_set(world,WORLD_SIZE-WIDTH,2);
  world_set_sort(world,WORLD_SIZE-WIDTH,3);
  world_set(world,WORLD_SIZE-1,1);
  world_set_sort(world,WORLD_SIZE-1,3);
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
  show_world(world);
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
    show_world(world);
    printf("############################ turn %d/%d\n",nbr_turns,MAX_TURNS);
    sleep(0.1);
  }
  
  return 0;
}
