//
#include <stdio.h>
#include "geometry.h"

const char* place_to_string(enum color_t c, enum sort_t s){

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
