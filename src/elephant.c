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

struct ensemble_t get_neighbors_3(unsigned int idx)
{
  struct ensemble_t neighbors; 
  enum dir_t d;
  enum dir_t r;
  unsigned int k=0;
  unsigned int ind;
  unsigned int ind1;
  for(d = -3; d<=4; d+=2)
  {
    ind=get_neighbor(idx,d);
    for(r = -3; r<=4; r+=2)
    {
    ind1=get_neighbor(ind,r);
    if(ind1<UINT_MAX && idx!=ind1)
    {
      neighbors.n[k].i=ind1;
      neighbors.n[k].d=r;
      k++;
    }
    }
  }
  neighbors.n[k].i=UINT_MAX;
  k++;
  while(k<13)
  {
    neighbors.n[k].i=0;
    k++;
  }
  return neighbors;
}

struct ensemble_t deplacement_simple_3(struct world_t* world, unsigned int idx)
{
  unsigned int k = 0;
  unsigned int j =0;
  struct ensemble_t neighbors = get_neighbors_3(idx);
  struct ensemble_t deplacement_smpl;
  while(neighbors.n[k].i < UINT_MAX && k<13)
  {
    if(world_get_sort(world,neighbors.n[k].i)== 0)
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
  while(j<13)
  {
    deplacement_smpl.n[j].i=0;
    deplacement_smpl.n[j].d=0;
    j++;
  }
  return deplacement_smpl;
}

unsigned int nombre_semidiag(struct world_t*world,unsigned int index)
{
  struct ensemble_t mouvement1 = deplacement_simple_3(world,index);
  unsigned int compteur = 0;
  unsigned int j = 0;
  while (mouvement1.n[j].i < UINT_MAX && j<13)
  {
    compteur+=1;
    j++;
  }
  return compteur;
}

unsigned int mov_elephant(struct world_t *world, int index){
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
    return UINT_MAX;
}