#include "./src/world.h"
#include <stdio.h>
#include <stdlib.h>
#include "./src/geometry.h"

struct pion{
  enum color_t c;
  enum sort_t s;
};

struct world_t{
  struct pion point[WORLD_SIZE];
};

struct world_t p;
struct world_t* world_init(){
  for(int i = 0; i < WORLD_SIZE; i++){
    p.point[i].c = 0;
    p.point[i].s = 0;
  }
  return &p;
}

enum color_t world_get(const struct world_t* b, unsigned int idx){
  return b -> point[idx].c;
}

void world_set(struct world_t* b, unsigned int idx, enum color_t c){
  b->point[idx].c = c;
}

enum sort_t world_get_sort(const struct world_t* b, unsigned int idx){
  return b -> point[idx].s;
}

void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c){
  b -> point[idx].s = c;
}


int main(int argc,char* argv[])
{
  return 0;
}
