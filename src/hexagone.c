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
  int idx=0;
    for(int i = 0; i <HEIGHT ; i++)
    {
      for(int j = 1; j <WIDTH ; j+=2) //On print les hauts ()
      {
        idx=i*WIDTH+j;
        if(world_get(world,idx)==BLACK)
        {
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s","    ⛀ ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s","    ♖ ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s","    ♘ ");
          }
        }
        if(world_get(world,idx)==WHITE)
        { 
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s","    ⛂ ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s","    ♜ ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s","    ♞ ");
          }
            
        }
        if(world_get(world,idx)==NO_COLOR)
        {
          printf("    . ");
        }
      }
      printf("\n");
      for(int k = 0; k <WIDTH ; k+=2) //On print les bas ()
      {
        
        idx=i*WIDTH+k;
        if(world_get(world,idx)==BLACK)
        {
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s"," ⛀    ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s"," ♖    ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s"," ♘    ");
          }
        }
        if(world_get(world,idx)==WHITE)
        { 
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s"," ⛂    ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s"," ♜    ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s"," ♞    ");
          } 
        }
        if(world_get(world,idx)==NO_COLOR)
        {
          printf(" .    ");
        }
      }
      printf("\n");
    }
}