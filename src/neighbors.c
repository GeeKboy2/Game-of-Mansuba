#include "neighbors.h"
#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"
#include "world.h"
#include <limits.h>
#include <time.h>
#include "project.h"

unsigned int get_neighbor(unsigned int idx, enum dir_t d)
{
    if (idx>(HEIGHT*WIDTH))
    {
        printf("INVALID INDEX");
        return UINT_MAX;
    }

    //idx = q*n + r
    unsigned int n=WIDTH;
    unsigned int q=idx/n;
    unsigned int r=idx%n;
    // La ligne est q & la colonne est r.
    
    if(idx%WIDTH == 0){
       if (d==4 || d== -2 || d== -1)
	 {
	   return UINT_MAX;
	 }
    }
    if(idx%WIDTH == WIDTH - 1){ //Bordure.
      if(d == 2 || d== 1 || d == -4){
	    return UINT_MAX;
      }
    }
    if(idx/WIDTH == 0){ //Bordure.
      if(d==2 || d== 3 || d==4){
        return UINT_MAX;
      }
    }
    if(idx/WIDTH == WIDTH-2){ //Bordure.
      if(d==-2 || d==-3 || d==-4 )
      {
        return UINT_MAX;
      }
    }
    
    if (d==4)
	 {
	   q--;
	   r--;
	 }
    if (d==-2)
	 {
	   r--;
	   q++;
	 }
    if (d==-1)
	 {
	   r--;
	 }
    if (d==1)
    {
        r++;
    }
    if (d==2)
    {
        r++;
        q--;
    }
    if (d==3)
    {
        q--;
    }
    if (d==-3)
    {
        q++;
    }
    if (d==-4)
    { 
        q++;
        r++;
    }
    if (d>4 || d<-4 || d==0 )
    {
      //printf("INVALID DIRECTION %d",d);
      return UINT_MAX;
    }
    unsigned int index=q*n+r;
    if (index > WORLD_SIZE - 1){
      return UINT_MAX;
    }
    return index;
}

struct neighbors_t get_neighbors(unsigned int idx)
{
  struct neighbors_t neighbors; 
  enum dir_t d;
  unsigned int k=0;
  for(d = -4; d<=4; d++) //Ajout de tout les voisins possible.
  {
    unsigned int ind=get_neighbor(idx,d);
    if(ind<UINT_MAX)
    {
      neighbors.n[k].i=ind;
      neighbors.n[k].d=d;
      k++;
    }
  }
  neighbors.n[k].i=UINT_MAX; //marquer la fin des voisins par UINT_MAX.
  k++;
  while(k<MAX_NEIGHBORS+1) //Completion par des zeros.
  {
    neighbors.n[k].i=0;
    k++;
  }
  return neighbors;
}

//Compte le nombre de mouvement possible pour une position idx
unsigned int nombre_mouvements(struct world_t* world, unsigned int idx)
{
  struct neighbors_t mouvement1 = deplacement_simple(world,idx); //Stockage des deplacement simples.
  struct neighbors_t mouvement2 = saut_simple(world,idx);        //Stockage des sauts simples.
  struct neighbors_t mouvement3 = saut_multiple(world,idx);      //Stockage des sauts multiples.
  unsigned int compteur = 0;
  unsigned int j = 0;
  //Comptage de nombre de mouvement.
  while (mouvement1.n[j].i < UINT_MAX && j<MAX_NEIGHBORS+1)
  {
    compteur+=1;
    j++;
  }
  j = 0;
  while(mouvement2.n[j].i < UINT_MAX && j<MAX_NEIGHBORS+1)
  {
    compteur+=1;
    j++;
  }
  if(mouvement3.n[0].i != UINT_MAX){
    compteur++;
  }
  return compteur;
}
