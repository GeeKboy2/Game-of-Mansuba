#include "neighbors.h"
#include <stdio.h>
#include "geometry.h"
#include "world.h"
#include <limits.h>
//#include "rules.c"

//#define UINT_MAX -1

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
    // la ligne est q & la collone est r
    if (d==0)
      {
	return idx;
      }
    if(idx%WIDTH == 0){
       if (d==4 || d== -2 || d== -1)
	 {
	   return UINT_MAX;
	 }
    }
    if(idx%WIDTH == WIDTH - 1){
      if(d == 2 || d== 1 || d == -4){
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
    if (d>4 || d<-4)
    {
      printf("INVALID DIRECTION %d",d);
        return UINT_MAX;
    }
    int index=q*n+r;
    if (index<0 || index > WORLD_SIZE - 1){
      return UINT_MAX;
    }
    return index;
}



struct neighbors_t get_neighbors(unsigned int idx)
{
  struct neighbors_t neighbors; 
  int d;
  int k=0;
  for(d = -4; d<=4; d++)
  {
    unsigned int ind=get_neighbor(idx,d);
    if(ind!=UINT_MAX)
    {
      neighbors.n[k].i=ind;
      neighbors.n[k].d=d;
      k++;
    }
  }
  neighbors.n[k].i=UINT_MAX;
  while(k<MAX_NEIGHBORS)
  {
    neighbors.n[k].i=0;
    k++;
  }
  return neighbors;
}

//int saut_simple(struct world_t *world,int current_index)
//{
//  if(saut_simple)

//  return 
//}

int nombre_mouvements(struct world_t* world ,unsigned int idx,int mvt_seed,int new_index)
{
    struct neighbors_t voisins=get_neighbors(idx);
    int i=0;
    struct vector_t voisin;
    enum color_t couleur=world_get(world,idx);
    int nombre_mouvement=0;
    enum dir_t direction_saut=0;
    int indice_voisin_saut;
    while(i<MAX_NEIGHBORS)
    {   
        //parcour de tous les voisins proches
        voisin=voisins.n[i];
        if(world_get_sort(world,voisin.i)==0)
        {
            nombre_mouvement++;
            if(nombre_mouvement==mvt_seed)
            {
              world_set(world,idx,0);
              world_set_sort(world,idx,0);
              new_index=get_neighbor(idx,voisin.d);
            }
            // case vide a coté = deplacement
        }else{ // si case proche contient noir 
            if(world_get(world,voisin.i)!=couleur)
            {
                indice_voisin_saut=get_neighbor(voisin.i,direction_saut);
                if(world_get_sort(world,indice_voisin_saut)==0)//et celle d'apres est vide.
                {
                    nombre_mouvement++;
                    //saut_simple();
                    if(nombre_mouvement==mvt_seed)
                    {
                      printf("%d\n",mvt_seed);
                      world_set(world,voisin.i,0);// supprime le pion noir sauté.
                      world_set_sort(world,voisin.i,0);
                      new_index=indice_voisin_saut;
                    }
                }
            }
        }
        i++;
    }
  return nombre_mouvement;
}




/*

struct couple
{
  int mouvement;
  int nombre_piece_mangee;
}


struct deplacements{
  struct couple position[MAX_NEIGHBORS]; // [(mvt,nbr_manger), ...]
};


struct deplacements deplacement(struct world_t, int idx)
{
  struct mouvements mouvements;

  struct neighbors_t voisins=get_neighbors(idx);
  int i=0;

  struct vector_t voisin;
  int couleur=world_get(b,idx);
  enum dir_t direction_saut=0;
  int indice_voisin_saut;
  while(i<MAX_NEIGHBORS)
    {
      voisin=voisins.n[i];
      if(world_get_sort(b,voisin.i)==0)
        {
	  //case vide donc on peut se déplacer
	  
        }else{
	if(world_get(b,voisin.i)!=couleur)
	  {
	    indice_voisin_saut=get_neighbor(voisin.i,direction_saut);
	    if(world_get_sort(b,indice_voisin_saut)==0)
	      {
		//case apres un saut
		nombre_mouvement++;
	      }
	  }
      }
      i++;
    }
  return mouvements
    }
 
*/
