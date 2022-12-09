#include "geometry.h"
#include "world.h"
#include "neighbors.h"

struct ensemble_t{
  struct vector_t n[12+1];
};

struct neighbors_t deplacement_simple(struct world_t* world, unsigned int idx);

struct neighbors_t saut_simple(struct world_t* world, unsigned int idx);

struct neighbors_t saut_multiple(struct world_t* world, unsigned int idx);

unsigned int nombre_mouvements(struct world_t* world, unsigned int idx);

int position_init(struct world_t* world);

int condition_victoire(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN);

struct ensemble_t get_neighbors_3(unsigned int idx);

struct ensemble_t deplacement_simple_3(struct world_t* world, unsigned int idx);

unsigned int nombre_semidiag(struct world_t*world,unsigned int index);

struct neighbors_t translation_cardinale(struct world_t *world, unsigned int idx);

void show_world_hexagone(struct world_t* world);

void show_world_triangle(struct world_t* world);

unsigned int get_neighbor_hex(unsigned int idx, enum dir_t d);

struct neighbors_t get_neighbors_hex(unsigned int idx);

unsigned int get_neighbor_triangle(unsigned int idx, enum dir_t d);

unsigned int mov_pawn(struct world_t *world, int index);

unsigned int mov_tour(struct world_t *world, int index);

unsigned int mov_elephant(struct world_t *world, int index);

void modif_rules(int argc, char *argv[],char* type_victoire,int RNG,int MAX_TURNS);
