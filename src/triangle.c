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




void show_world_triangle(struct world_t* world)
{
    for(int i = 0; i <WORLD_SIZE ; i++){
        if(i%2!=0){
            if(world_get(world,i)==BLACK)
            {
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛀/");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♖/");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♘/");
            }
            }
            if(world_get(world,i)==WHITE)
            { 
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛂/");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♜/");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♞/");
            }
            
            }
            if(world_get(world,i)==NO_COLOR)
            {
                printf("./");
            }
            if(i%WIDTH == WIDTH-1)
            {
            printf("\n");
            }    
        }
        if (i%2==0){
            if(world_get(world,i)==BLACK)
            {
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛀\\");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♖\\");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♘\\");
            }
            }
            if(world_get(world,i)==WHITE)
            { 
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛂\\");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♜\\");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♞\\");
            }
            
            }
            if(world_get(world,i)==NO_COLOR)
            {
                printf(".\\");
            }
            if(i%WIDTH == WIDTH-1)
            {
            printf("\n");
            }                
        }
      
        
    }
}

