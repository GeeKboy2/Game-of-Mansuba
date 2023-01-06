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

//Ce fichier concerne les fonctions associés aux pions.

//Regarde les déplacements simples réalisables
struct neighbors_t deplacement_simple(struct world_t* world, unsigned int idx)
{
  unsigned int k = 0;
  unsigned int j =0;
  struct neighbors_t neighbors = get_neighbors(idx);
  struct neighbors_t deplacement_smpl;
  while((neighbors.n[k].i != UINT_MAX) && (k<MAX_NEIGHBORS))
  {
    if(world_get_sort(world,neighbors.n[k].i) == NO_SORT )
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

unsigned int saut_multiple(struct world_t* world, unsigned int idx){
  unsigned int index_passe[WORLD_SIZE];
  for(int i=0;i<WORLD_SIZE;i++){
    index_passe[i]=UINT_MAX;
  }
  struct neighbors_t saut_simpl=saut_simple(world,idx);
  unsigned int compteur_saut=0;
  enum color_t color=world_get(world,idx);
  enum sort_t sort=world_get_sort(world,idx);
  if(saut_simpl.n[0].i==UINT_MAX){
    return UINT_MAX;
  }
  index_passe[compteur_saut]=idx;
  idx=saut_simpl.n[0].i;
  idx=get_neighbor_in_table(idx,saut_simpl.n[0].d,get_neighbors_seed());
  if(idx==UINT_MAX){
    return UINT_MAX;
  }
  world_set(world,idx,color);
  world_set_sort(world,idx,sort);
  compteur_saut++;
  index_passe[compteur_saut]=idx;
  while(idx!=UINT_MAX){
    world_set(world,idx,color);
    world_set_sort(world,idx,sort);
    saut_simpl=saut_simple(world,idx);
    idx=saut_simpl.n[0].i;
    if(idx==UINT_MAX){
      break;
    }
    idx=get_neighbor_in_table(idx,saut_simpl.n[0].d,get_neighbors_seed());
    compteur_saut++;
    index_passe[compteur_saut]=idx;
  }

  for(int i=1;i<WORLD_SIZE;i++){
    if(index_passe[i]!=UINT_MAX){
      world_set(world,index_passe[i-1],NO_COLOR);
      world_set_sort(world,index_passe[i-1],NO_SORT);
    }
  }
  return idx;
}

unsigned int mov_pawn(struct world_t *world, unsigned int index){
    if(world_get_sort(world, index) != PAWN ){
      return index;
    }
    struct neighbors_t ds=deplacement_simple(world,index);
    struct neighbors_t ss=saut_simple(world,index);
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
        printf("Je me déplace");
        return ds.n[compteur_ds].i;
      }
      compteur_ds++;
      somme++;
    }
    while (ss.n[compteur_ss].i!=UINT_MAX && compteur_ss < MAX_NEIGHBORS)
    {
      if(somme==rand_mvt)
      {
        printf("Je saute");
        return get_neighbor_in_table(ss.n[compteur_ss].i,ss.n[compteur_ss].d,get_neighbors_seed());
      }
      compteur_ss++;
      somme++;
    }
    if(somme == rand_mvt)
    {
      printf("Je saute beaucoup");
      return saut_multiple(world,index);
    }
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