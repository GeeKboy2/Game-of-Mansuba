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

//Renvoie les directions possibles pour le déplacement de la tour
struct neighbors_t translation_cardinale(struct world_t *world, unsigned int idx){
  struct neighbors_t mvt_tour;
  int j = 0;
  for(int i = -3;i < 4; i = i + 2){
    if(get_neighbor_in_table(idx,i,get_neighbors_seed())<UINT_MAX){
      if(get_neighbor_in_table(idx,i,get_neighbors_seed()) != UINT_MAX && world_get_sort(world, get_neighbor_in_table(idx,i,get_neighbors_seed())) == 0){
        mvt_tour.n[j].i = get_neighbor_in_table(idx,i,get_neighbors_seed());
        mvt_tour.n[j].d = i;
        j++; 
      }
    }
  }
  if(j == 0){
    mvt_tour.n[j].i = idx;
    mvt_tour.n[j].d = 0;
    j++;
  }
  mvt_tour.n[j].i = UINT_MAX;
  mvt_tour.n[j].d = 0;
  return mvt_tour;
}

//Renvoie l'index d'arrivée de la tour
unsigned int mov_tour(struct world_t *world, int index){
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
    unsigned int pos = get_neighbor_in_table(index,tour.n[rand_dir].d,get_neighbors_seed());
    while(pos != UINT_MAX && world_get_sort(world,pos) == NO_SORT){
      compteur_case++;
      pos = get_neighbor_in_table(pos,tour.n[rand_dir].d,get_neighbors_seed());
    }
    int rand_mvt = rand()%(compteur_case)+1;
    for(int k = 0; k < rand_mvt; k++){
      index = get_neighbor_in_table(index,tour.n[rand_dir].d,get_neighbors_seed());
    }
    return index;
}

int position_init_tour(struct world_t* world){
    int b = 0;
    int n = 0;
    for(int i = 0; i< WORLD_SIZE; i++){
      if(i%WIDTH==0){
        world_set(world,i,BLACK);
        world_set_sort(world,i,TOUR);
        n++;
      }
      if(i%WIDTH==WIDTH-1){
        world_set(world,i,WHITE);
        world_set_sort(world,i,TOUR);
        b++;
      }
    }
    return 0;
}