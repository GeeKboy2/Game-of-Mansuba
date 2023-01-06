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

struct ensemble_t{
  struct vector_t n[12+1];
};

enum init{
  PIONS = 0,
  PION_TOUR_ELEPHANT = 1,
  MAX_INIT =2
};



enum color_t get_random_player();

enum color_t next_player(enum color_t current_player);

int choose_random_piece_belonging_to(struct world_t* world, enum color_t current_player);

unsigned int choose_random_move_for_piece(struct world_t *world,int index);

void move_piece(struct world_t* world,unsigned int index_arrivee,unsigned int index_depart);

unsigned int condition_victoire(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN);

struct neighbors_t deplacement_simple(struct world_t* world, unsigned int idx);

struct neighbors_t saut_simple(struct world_t* world, unsigned int idx);

unsigned int saut_multiple(struct world_t* world, unsigned int idx);

unsigned int nombre_mouvements(struct world_t* world, unsigned int idx);

int position_init(struct world_t* world);

unsigned int condition_victoire(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN);

struct ensemble_t get_neighbors_3(unsigned int idx);

struct ensemble_t deplacement_simple_3(struct world_t* world, unsigned int idx);

unsigned int nombre_semidiag(struct world_t*world,unsigned int index);

struct neighbors_t translation_cardinale(struct world_t *world, unsigned int idx);

void show_world_carre(struct world_t* world);

void show_world_hexagone(struct world_t* world);

void show_world_triangle(struct world_t* world);

void show_world(struct world_t* world);

unsigned int get_neighbor_hex(unsigned int idx, enum dir_t d);

struct neighbors_t get_neighbors_hex(unsigned int idx);

unsigned int get_neighbor_triangle(unsigned int idx, enum dir_t d);

unsigned int mov_pawn(struct world_t *world, int index);

unsigned int mov_tour(struct world_t *world, int index);

unsigned int mov_elephant(struct world_t *world, int index);

unsigned int get_neighbor_in_table(unsigned int idx ,enum dir_t d,unsigned int type_plateau);

//unsigned int saut_multiple2(struct world_t* world, unsigned int idx);

void position_initialisation(enum init type_init,struct world_t* world);

struct prison_t{
  struct pion n[2*HEIGHT];
  unsigned int index[2*HEIGHT];
};

struct prison_t* prison_init();

void emprisoner(struct world_t* world,unsigned int index,struct prison_t* prison);

void tentative_evasion(struct prison_t* prison, struct world_t* world);
