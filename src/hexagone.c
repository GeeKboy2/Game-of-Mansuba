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

void show_world_hexagone(struct world_t* world)
{
    for(int i = 0; i <WORLD_SIZE ; i++){
      if(world_get(world,i)==2 && (i%(WIDTH-1))%2 == 0)
      {
        printf("   ");
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
      if(world_get(world,i)==2 && (i%(WIDTH-1))%2 == 1)
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
        printf("   ");
      }
      if(world_get(world,i)==1 && (i%(WIDTH-1))%2 == 0)
      { 
        printf("   ");
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
      if(world_get(world,i)==1 && (i%(WIDTH-1))%2 == 1)
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
          printf("   ");
        }
      if(world_get(world,i)==0 && (i%(WIDTH-1))%2 == 0)
        {
          printf("   ");
          printf(" . ");
        }
        else if(world_get(world,i)==0 && (i%(WIDTH-1))%2 == 1)
        {
          printf(" . ");
          printf("   ");
        }
      if(i%WIDTH == WIDTH-1){
        printf("\n");
      }    
    }
}

unsigned int get_neighbor_hex(unsigned int idx, enum dir_t d){
    if(idx%2 == 0){

    }
    if(idx%2 == 1){

    }
}