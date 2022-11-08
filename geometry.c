//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./src/geometry.h"


const char* place_to_string(enum color_t c, enum sort_t s){
  if(c == 0 && s == 0){
    return "NO_COLOR and NO_SORT";
  }
  if(c == 1 && s == 0){
    return "BLACK and NO_SORT";
  }
  if(c == 2 && s == 0){
    return "WHITE and NO_SORT";
  }
  if(c == 0 && s == 1){
    return "NO_COLOR and PAWN";
  }
  if(c == 1 && s == 1){
    return "BLACK PAWN";
  }
  if(c == 2 && s == 1){
    return "WHITE PAWN";
  }
  else{
    return "BAD ARGUMENT";
  }
}
 

int main(int argc, char *argv[]){
  printf("%s\n", place_to_string(atoi(argv[1]),atoi(argv[2])));
}



const char* dir_to_string(enum dir_t d)
{
  char* str;
  printf("%d",d);
  if (d == 0)
  {
    str = "NO_DIR";
  }
  if (d == 1)
  {
    str = "EAST";
  }
  if (d == 2)
  {
    str = "NEAST";
  }
  if (d == 3)
  {
    str = "NORTH";
  }
  if (d == 4)
  {
    str = "NWEST";
  }
    if (d == -1)
  {
    str = "WEST";
  }
    if (d == -2)
  {
    str = "SWEST";
  }
  if (d == -3)
  {
    str = "SOUTH";
  }
    if (d == -4)
  {
    str = "SEAST";
  }
    if (d>4 || d<-4)
  {
    str = "INVALID DIRECTION";
  }
  return str;
}

