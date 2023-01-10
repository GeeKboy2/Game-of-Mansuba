#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "geometry.h"
#include "world.h"
#include "neighbors.h"
#include <unistd.h>
#include <time.h>
#include "limits.h"
#include "project.h"


struct jail_t prison;
struct jail_t* jail_init(){
  for(int i = 0; i < 2*HEIGHT; i++){
    prison.n[i].c = NO_COLOR;
    prison.n[i].s = NO_SORT;
    prison.index[i] = UINT_MAX;
  }
  return &prison;
}

void escape_attempt(struct jail_t* prison,struct world_t * world){
    unsigned int index;
    for(int i = 0; i < 2*HEIGHT; i++){
        if(prison->index[i]==UINT_MAX){
            continue;
        }
        if(world_get(world,prison->index[i])==NO_COLOR && world_get_sort(world,prison->index[i])==NO_SORT ){
            srand(time(NULL));
            if(rand()%2==0){
                index=prison->index[i];
                world_set(world,index,prison->n[i].c);
                world_set_sort(world,index,prison->n[i].s);
            }
        }
    }
}


void imprison(struct world_t* world,unsigned int index,struct jail_t* prison){
    enum color_t color=world_get(world,index);
    enum sort_t sort=world_get_sort(world,index);
    world_set(world,index,NO_COLOR);
    world_set_sort(world,index,NO_SORT);
    for(int i = 0; i < 2*HEIGHT; i++){
        if(prison->index[i]==UINT_MAX){
            prison->index[i]=index;
            prison->n[i].c=color;
            prison->n[i].s=sort;
            break;
        }
    }
}