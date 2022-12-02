#include "geometry.h"
#include "world.h"
#include "neighbors.h"

struct neighbors_t deplacement_simple(struct world_t* world, unsigned int idx);

struct neighbors_t saut_simple(struct world_t* world, unsigned int idx);

struct neighbors_t saut_multiple(struct world_t* world, unsigned int idx);

unsigned int nombre_mouvements(struct world_t* world, unsigned int idx);

int position_init(struct world_t* world);

int condition_victoire(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN);

struct neighbors_t translation_cardinale(struct world_t *world, unsigned int idx);