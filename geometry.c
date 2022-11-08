//
#include <stdio.h>
#include <string.h>
#include "./src/geometry.h"

const char* place_to_string(enum color_t c, enum sort_t s){
  char* color;
  char* sort;
  if(c == 0){
    color = "NO_COLOR";
  }
  if(c == 1){
    color = "BLACK";
  }
  if(c == 2){
    color = "WHITE";
  }
  else{
    return "INVALID_COLOR";
  }
  if(s == 0){
    sort = "NO_SORT";
  }
  if(s == 1){
    sort = "PAWN";
  }
  else{
    return "INVALID_SORT";
  }
  return strcat(color, sort);
}



