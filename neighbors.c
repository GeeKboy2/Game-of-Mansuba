#include <stdio.h>
#include "geometry.h"

void init_neighbors(unsigned int seed);
{
  
}


unsigned int get_neighbor(unsigned int idx, enum dir_t d);
{
    if (idx>(HEIGHT*WIDTH) || idx<0)
    {
        printf("INVALID INDEX");
        return UINT_MAX;
    }

    //idx = q*n + r
    unsigned int n=WIDTH;
    unsigned int q=idx/n;
    unsigned int r=idx-(q*n);
    // la ligne est q & la collone est r
    unsigned int i=0;
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
    return q*n+r
}






struct neighbors_t get_neighbors(unsigned int idx);
{
  struct neighbours_t neighbous;
  return neighbors
}
