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

//Regarde les déplacements simples réalisables
struct neighbors_t deplacement_simple(struct world_t* world, unsigned int idx)
{
  unsigned int k = 0;
  unsigned int j =0;
  struct neighbors_t neighbors = get_neighbors(idx);
  struct neighbors_t deplacement_smpl;
  while(neighbors.n[k].i != UINT_MAX && k<MAX_NEIGHBORS)
  {
    if(world_get_sort(world,neighbors.n[k].i)== NO_SORT)
    {
      deplacement_smpl.n[j].i = neighbors.n[k].i;
      deplacement_smpl.n[j].d = neighbors.n[k].d;
      j++;
    }
    k++;
  }
  deplacement_smpl.n[j].i=UINT_MAX;
  deplacement_smpl.n[j].d=0;
  j++;
  while(j<MAX_NEIGHBORS+1)
  {
    deplacement_smpl.n[j].i=0;
    deplacement_smpl.n[j].d=0;
    j++;
  }
  return deplacement_smpl;
}

//Regarde les sauts simple réalisables
struct neighbors_t saut_simple(struct world_t* world, unsigned int idx)
{
  unsigned int k = 0;
  unsigned int j = 0;
  struct neighbors_t neighbors = get_neighbors(idx);
  struct neighbors_t saut_simp; //Structure à retouner pour voir les directions et index des sauts 
  unsigned int position = get_neighbor_in_table(neighbors.n[k].i,neighbors.n[k].d,get_neighbors_seed());
  while(neighbors.n[k].i < UINT_MAX && k<MAX_NEIGHBORS+1)
  {
    if(world_get_sort(world,neighbors.n[k].i) != NO_SORT)
    {
      position = get_neighbor_in_table(neighbors.n[k].i,neighbors.n[k].d,get_neighbors_seed());
      if(position<UINT_MAX)
      {
        if(world_get_sort(world,position) == NO_SORT)
        {
          saut_simp.n[j].i = neighbors.n[k].i;
          saut_simp.n[j].d = neighbors.n[k].d;
          j++;
        }
      }
    }
    k++;
  }
  saut_simp.n[j].i=UINT_MAX;
  saut_simp.n[j].d=0;
  j++;
  while(j<MAX_NEIGHBORS+1)
  {
    saut_simp.n[j].i=0;
    saut_simp.n[j].d=0;
    j++;
  }
  return saut_simp;
}

/*
struct neighbors_t saut_multiple(struct world_t* world, unsigned int idx)
{
  unsigned int ancienne_position[WORLD_SIZE];
  for(int i = 0;i<WORLD_SIZE;i++){
    ancienne_position[i] = UINT_MAX;
  }
  struct neighbors_t saut_simp = saut_simple(world,idx);
  if(saut_simp.n[0].i == UINT_MAX){
    return saut_simp;
  }
  int l = 0;
  int compteur = 1;
  while(saut_simp.n[0].i != UINT_MAX && compteur != 0){
    compteur = 0;
    int saut_possible[MAX_NEIGHBORS];
    for(int j = 0; saut_simp.n[j].i != UINT_MAX; j++){ //Boucle pour voir les sauts possibles et éviter les retours en arrières
      int test = 1;
      for(int k = 0; ancienne_position[k] != UINT_MAX; k++){
        if(ancienne_position[k] == saut_simp.n[j].i){
          test = 0;
        }
      }
      if(test == 1){
        saut_possible[compteur]=saut_simp.n[j].i;
        compteur++;
      }
    }
    if(compteur != 0){
      srand(time(NULL));
      int rand_mvt = rand()%compteur;
      idx = saut_possible[rand_mvt];
      ancienne_position[l] = idx;
      l++;
      saut_simp = saut_simple(world,idx);
    }
  }
  saut_simp.n[0].i = idx;
  saut_simp.n[0].d = 0;
  saut_simp.n[1].i = UINT_MAX;
  return saut_simp;
}
*/

unsigned int saut_multiple2(struct world_t* world, unsigned int idx){
  unsigned int ancienne_position[WORLD_SIZE];
  for(int i = 0;i<WORLD_SIZE;i++){
    ancienne_position[i] = UINT_MAX;
  }
  unsigned int indice_saut[MAX_NEIGHBORS];
  unsigned int direction_saut[MAX_NEIGHBORS];
  struct neighbors_t saut_simp = saut_simple(world,idx);
  if(saut_simp.n[0].i == UINT_MAX){
    return UINT_MAX;
  }
  int compteur = 1;
  int j = 0;
  int test = 0;
  while(compteur != 0){             // Permet de regarder si un saut simple est possible et que ce n'est pas une ancienne position 
    compteur = 0;
    test = 0;
    for( int i = 0; saut_simp.n[i].i != UINT_MAX; i++){
      int k = 0;
      test = 0;
      while(ancienne_position[k] != UINT_MAX){
        if(saut_simp.n[i].i == ancienne_position[k]){
          test = -1;
        }
        k++;
      }
      if(test == 0){
        indice_saut[compteur] = saut_simp.n[i].i;
        direction_saut[compteur] = saut_simp.n[i].d;
        compteur++;
      }
    }
    if(compteur != 0){
      srand(time(NULL));
      int rand_mvt = rand()%compteur;
      ancienne_position[j] = idx;
      idx = get_neighbor(indice_saut[rand_mvt],direction_saut[rand_mvt]);
      saut_simp = saut_simple(world, idx);
      j++;
    }
  }
  return idx;

}

unsigned int mov_pawn(struct world_t *world, int index){
    struct neighbors_t ds=deplacement_simple(world,index);
    //struct neighbors_t ss=saut_simple(world,index);
    //struct neighbors_t sm = saut_multiple(world,index);
    unsigned int sm2 = saut_multiple2(world,index);
    unsigned int compteur_ds=0;
    unsigned int compteur_ss=0;
    unsigned int nombre_mvt=nombre_mouvements(world,index);
    srand(time(NULL));
    if (nombre_mvt==0)
    {
      return index;
    }
    int rand_mvt=(rand()%nombre_mvt);
    int somme=0;
    while(ds.n[compteur_ds].i!=UINT_MAX && compteur_ds < MAX_NEIGHBORS)
    {
      if(somme==rand_mvt)
      {
        printf("Le déplacement : %d\n", ds.n[compteur_ds].i);
        return ds.n[compteur_ds].i;
      }
      compteur_ds++;
      somme++;
    }
    /*while (ss.n[compteur_ss].i!=UINT_MAX && compteur_ss < MAX_NEIGHBORS)
    {
      if(somme==rand_mvt)
      {
        return get_neighbor_in_table(ss.n[compteur_ss].i,ss.n[compteur_ss].d,get_neighbors_seed());
      }
      compteur_ss++;
      somme++;
    }*/
    if(somme == rand_mvt && sm2 != UINT_MAX)
    {
      printf("Deplacement multiple : %d\n", sm2);
      return sm2;
    }
    printf("Le bug : %d\n", index);
    return index;
}

int position_init(struct world_t* world){
  int b = 0;
  int n = 0;
  for(int i = 0; i< WORLD_SIZE; i++){
    if(i%WIDTH==0){
      world_set(world,i,BLACK);
      world_set_sort(world,i,PAWN);
      n++;
    }
    if(i%WIDTH==WIDTH-1){
      world_set(world,i,WHITE);
      world_set_sort(world,i,PAWN);
      b++;
    }
  }
  return 0;
}