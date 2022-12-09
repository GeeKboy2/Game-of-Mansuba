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

unsigned int get_neighbor_triangle(unsigned int idx, enum dir_t d){
    if(idx%2==0){ //sommet vers le haut = voisin en bas
        if(d==EAST){
            idx++;
            return idx;
        }
        if(d==WEST){
            idx--;
            return idx;
        }
        if(d==SOUTH){
            idx+=WIDTH;
            return idx;
        }else{
            return UINT_MAX;
        }
    }
    if(idx%2!=0){ //sommet vers le bas = voisin en haut
        if(d==EAST){
            idx++;
            return idx;
        }
        if(d==WEST){
            idx--;
            return idx;
        }
        if(d==NORTH){
            idx-=WIDTH;
            return idx;
        }else{
            return UINT_MAX;
        }
    }
    return UINT_MAX;
}

