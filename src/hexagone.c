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
    for(int i = 0; i <HEIGHT ; i++)
    {
      for(int j = 1; j <HEIGHT ; j+=2) //On print les hauts ()
      {
        if(world_get(world,i)==BLACK)
        {
          if(world_get_sort(world,i)==PAWN)
          {
            printf("%s","    ⛀ ");
          }
          if(world_get_sort(world,i)==TOUR)
          {
            printf("%s","    ♖ ");
          }
          if(world_get_sort(world,i)==ELEPHANT)
          {
            printf("%s","    ♘ ");
          }
        }
        if(world_get(world,i)==WHITE)
        { 
          if(world_get_sort(world,i)==PAWN)
          {
            printf("%s","    ⛂ ");
          }
          if(world_get_sort(world,i)==TOUR)
          {
            printf("%s","    ♜ ");
          }
          if(world_get_sort(world,i)==ELEPHANT)
          {
            printf("%s","    ♞ ");
          }
            
        }
        if(world_get(world,i)==NO_COLOR)
        {
          printf("    . ");
        }
      }
      printf("\n");
      for(int k = 0; k <HEIGHT ; k+=2) //On print les bas ()
      {
          if(world_get(world,i)==BLACK)
        {
          if(world_get_sort(world,i)==PAWN)
          {
            printf("%s"," ⛀    ");
          }
          if(world_get_sort(world,i)==TOUR)
          {
            printf("%s"," ♖    ");
          }
          if(world_get_sort(world,i)==ELEPHANT)
          {
            printf("%s"," ♘    ");
          }
        }
        if(world_get(world,i)==WHITE)
        { 
          if(world_get_sort(world,i)==PAWN)
          {
            printf("%s"," ⛂    ");
          }
          if(world_get_sort(world,i)==TOUR)
          {
            printf("%s"," ♜    ");
          }
          if(world_get_sort(world,i)==ELEPHANT)
          {
            printf("%s"," ♞    ");
          } 
        }
        if(world_get(world,i)==NO_COLOR)
        {
          printf(" .    ");
        }
      }
      printf("\n");
    }
}