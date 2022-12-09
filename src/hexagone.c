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

unsigned int get_neighbor_hex(unsigned int idx, enum dir_t d){
    if(idx/WIDTH == 0){
        if(d == NORTH || d == NEAST || d == NWEST){ // Pas de Nord pour les case en haut du plateau
            return UINT_MAX;
        }
    }
    if(idx/WIDTH == WIDTH - 2){
        if(d == SOUTH || d == SWEST || d == SEAST){ // Pas de Sud pour les case en bas du plateau
            return UINT_MAX;
        }
    }
    if(idx%WIDTH == 0){
        if(d == SWEST || d == NWEST || d == WEST){ // Pas d'Ouest pour les case à gauche du plateau
            return UINT_MAX;
        }
    }
    if(idx%WIDTH == WIDTH - 1){
        if(d == SEAST || d == NEAST || d == EAST){ // Pas d'Est pour les case à droite du plateau
            return UINT_MAX;
        }
    }
    if(((idx%WIDTH)%2) == 0){ //CASE EN BAS
        if(d == NWEST || d == NEAST){ // Structure à 6 voisins, on ne prends pas Nord Est et Nord Ouest
            return UINT_MAX;
        }
    }
    if(((idx%WIDTH)%2) == 1){ //CASE EN HAUT
        if(d == SWEST || d == SEAST){ // Structure à 6 voisins, on ne prends pas Sud Est et Sud Ouest
            return UINT_MAX;
        }
    }
    if(d == EAST){
        return idx + 1;
    }
    if(d==WEST){
        return idx - 1;
    }
    if(d==NORTH){
        return idx - WIDTH;
    }
    if(d == SOUTH){
        return idx + WIDTH;
    }
    
}
