#include "./src/neighbors.h"
#include <stdio.h>
#include "./src/geometry.h"
#include "./src/world.h"
#include <limits.h>




unsigned int get_neighbor(unsigned int idx, enum dir_t d)
{
    if (idx>(HEIGHT*WIDTH) || idx<0)
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
    if (d==1)
    {
        r++;
    }
    if (d==2)
    {
        r++;
        q++;
    }
    if (d==3)
    {
        q++;
    }
    if (d==4)
    {
        q++;
        r--;
    }
    if (d==-1)
    {
        r--;
    }
    if (d==-2)
    {
        r--;
        q--;
    }
    if (d==-3)
    {
        q--;
    }
    if (d==-4)
    {
        q--;
        r++;
    }
    if (d>4 || d<-4)
    {
        printf("INVALID DIRECTION");
        return UINT_MAX;
    }
    return q*n+r;
}




/*


struct neighbors_t get_neighbors(unsigned int idx)
{
  struct neighbors_t neighbors; 
  unsigned int q=idx/WIDTH;
  unsigned int r=idx%WIDTH;
  unsigned int l=q;
  unsigned int j=r;
  unsigned int k=0;
  j++;
  if(j>=0 && j<=WIDTH)
    {
      neighbors.n[k].i=l*WIDTH+j;
      neighbors.n[k].d=1;
      k++;
    }
  j=q;
  l--;
  j++;
  if(j>=0 && j<=WIDTH)
    {
      if(l>=0 && l<=HEIGHT)
	{
	  neighbors.n[k].i=l*WIDTH+j;
	  k++;
	}
    }
  l=q;
  j=r;
  l--;
  if(j>=0 && j<=WIDTH)
    {
      neighbors.n[k].i=l*WIDTH+j;
      k++;
    }
  l=q;
  l--;
  j--;
  if(j>=0 && j<=WIDTH)
    {
      if(l>=0 && l<=HEIGHT)
	{
	  neighbors.n[k].i=l*WIDTH+j;
	  k++;
	}
    }
  l=q;
  j=r;
  j--;
  if(j>=0 && j<=WIDTH)
    {
      neighbors.n[k].i=l*WIDTH+j;
      k++;
    }
  j=r;
  l++;
  j--;
  if(j>=0 && j<=WIDTH)
    {
      if(l>=0 && l<=HEIGHT)
	{
	  neighbors.n[k].i=l*WIDTH+j;
	  k++;
	}
    }
  l=q;
  j=r;
  l++;
  if(l>=0 && l<=HEIGHT)
    {
      neighbors.n[k].i=l*WIDTH+j;
      k++;
    }
  l=q;
  l++;
  j++;
  if(j>=0 && j<=WIDTH)
    {
      if(l>=0 && l<=HEIGHT)
	{
	  neighbors.n[k].i=l*WIDTH+j;
	  k++;
	}
    }
  neighbors.n[k].i=UINT_MAX;
  k++;
  while(k<MAX_NEIGHBORS)
    {
      neighbors.n[k].i=0;
      k++;
    }
  return neighbors;
}
*/


struct neighbors_t get_neighbors(unsigned int idx)
{
  struct neighbors_t neighbors; 
  int d;
  int k=0;
  for(d = 0; d< MAX_DIR; d++)
  {
    int ind=get_neighbor(idx,d);
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



int mouvements(const struct world_t* b ,unsigned int idx)
{
    struct neighbors_t voisins=get_neighbors(idx);
    int i=0;
    struct vector_t voisin;
    int couleur=world_get(b,idx);
    int nombre_mouvement=0;
    enum dir_t direction_saut=0;
    int indice_voisin_saut;
    while(i<MAX_NEIGHBORS)
    {
        voisin=voisins.n[i];
        if(world_get_sort(b,voisin.i)==0)
        {
            nombre_mouvement++;
        }else{
            if(world_get(b,voisin.i)!=couleur)
            {
                indice_voisin_saut=get_neighbor(voisin.i,direction_saut);
                if(world_get_sort(b,indice_voisin_saut)==0)
                {
                    nombre_mouvement++;
                }
            }
        }
        i++;
    }
    return nombre_mouvement;
}
