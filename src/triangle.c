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

