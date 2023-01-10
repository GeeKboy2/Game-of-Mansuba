#include "geometry.h"
#include "world.h"
#include "neighbors.h"

//In this file we have the rest of signatures that aren't in  the other *.h

struct pion{
  enum color_t c;
  enum sort_t s;
};

struct world_t{
  struct pion point[WORLD_SIZE];
};

struct elephant_set_t{
  struct vector_t n[12+1];
};

enum init{
  PAWNS = 0,
  PAWNS_TOWERS_ELEPHANTS = 1,
  MAX_INIT =2
};



enum color_t get_random_player();

enum color_t next_player(enum color_t current_player);

int choose_random_piece_belonging_to(struct world_t* world, enum color_t current_player);

unsigned int choose_random_move_for_piece(struct world_t *world,int index);

void move_piece(struct world_t* world,unsigned int index_arrivee,unsigned int index_depart);

unsigned int victory_condition(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN);

struct neighbors_t simple_movement(struct world_t* world, unsigned int idx);

struct neighbors_t simple_jump(struct world_t* world, unsigned int idx);

unsigned int multiple_jumps(struct world_t* world, unsigned int idx);

unsigned int number_of_movements(struct world_t* world, unsigned int idx);

int position_init(struct world_t* world);

unsigned int victory_condition(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN);

struct elephant_set_t get_neighbors_elephant(unsigned int idx);

struct elephant_set_t simple_movement_elephant(struct world_t* world, unsigned int idx);

unsigned int number_semidiag(struct world_t*world,unsigned int index);

struct neighbors_t cardinal_translation(struct world_t *world, unsigned int idx);

void show_world_square(struct world_t* world);

void show_world_hexagon(struct world_t* world);

void show_world_triangle(struct world_t* world);

void show_world(struct world_t* world);

unsigned int get_neighbor_hexagon(unsigned int idx, enum dir_t d);

struct neighbors_t get_neighbors_hex(unsigned int idx);

unsigned int get_neighbor_triangle(unsigned int idx, enum dir_t d);

unsigned int move_pawn(struct world_t *world, unsigned int index);

unsigned int move_tour(struct world_t *world, int index);

unsigned int move_elephant(struct world_t *world, int index);

unsigned int get_neighbor_in_table(unsigned int idx ,enum dir_t d,unsigned int type_plateau);

void position_initialisation(enum init type_init,struct world_t* world);

struct jail_t{
  struct pion n[2*HEIGHT];
  unsigned int index[2*HEIGHT];
};

struct jail_t* jail_init();

void imprison(struct world_t* world,unsigned int index,struct jail_t* jail);

void escape_attempt(struct jail_t* jail, struct world_t* world);
