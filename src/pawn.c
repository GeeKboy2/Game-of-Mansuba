//Regarde les déplacements simples réalisables
struct neighbors_t deplacement_simple(struct world_t* world, unsigned int idx)
{
  unsigned int k = 0;
  unsigned int j =0;
  struct neighbors_t neighbors = get_neighbors(idx);
  struct neighbors_t deplacement_smpl;
  while(neighbors.n[k].i < UINT_MAX && k<MAX_NEIGHBORS+1)
  {
    if(world_get_sort(world,neighbors.n[k].i)== 0)
    {
      deplacement_smpl.n[j].i = neighbors.n[k].i;
      deplacement_smpl.n[j].d = neighbors.n[k].d;
      j++;
    }
    k++;
  }
  deplacement_smpl.n[j].i=UINT_MAX;
  deplacement_smpl.n[j].d=0;
  j++;
  while(j<MAX_NEIGHBORS+1)
  {
    deplacement_smpl.n[j].i=0;
    deplacement_smpl.n[j].d=0;
    j++;
  }
  return deplacement_smpl;
}

//Regarde les sauts simple réalisables
struct neighbors_t saut_simple(struct world_t* world, unsigned int idx)
{
  unsigned int k = 0;
  unsigned int j = 0;
  struct neighbors_t neighbors = get_neighbors(idx);
  struct neighbors_t saut_simp; //Structure à retouner pour voir les directions et index des sauts 
  unsigned int position = get_neighbor(neighbors.n[k].i,neighbors.n[k].d);
  k++;
  while(neighbors.n[k].i < UINT_MAX && k<MAX_NEIGHBORS+1)
  {
    if(world_get_sort(world,neighbors.n[k].i) == 1)
    {
      position = get_neighbor(neighbors.n[k].i,neighbors.n[k].d);
      if(position<UINT_MAX)
      {
        if(world_get_sort(world,position) == 0)
        {
          saut_simp.n[j].i = neighbors.n[k].i;
          saut_simp.n[j].d = neighbors.n[k].d;
          j++;
        }
      }
    }
    k++;
  }
  saut_simp.n[j].i=UINT_MAX;
  saut_simp.n[j].d=0;
  j++;
  while(j<MAX_NEIGHBORS+1)
  {
    saut_simp.n[j].i=0;
    saut_simp.n[j].d=0;
    j++;
  }
  return saut_simp;
}

struct neighbors_t saut_multiple(struct world_t* world, unsigned int idx)
{
  unsigned int ancienne_position[WORLD_SIZE];
  for(int i = 0;i<WORLD_SIZE;i++){
    ancienne_position[i] = UINT_MAX;
  }
  struct neighbors_t saut_simp = saut_simple(world,idx);
  if(saut_simp.n[0].i == UINT_MAX){
    return saut_simp;
  }
  int l = 0;
  int compteur = 1;
  while(saut_simp.n[0].i != UINT_MAX && compteur != 0){
    compteur = 0;
    int saut_possible[MAX_NEIGHBORS];
    for(int j = 0; saut_simp.n[j].i != UINT_MAX; j++){ //Boucle pour voir les sauts possibles et éviter les retours en arrières
      int test = 1;
      for(int k = 0; ancienne_position[k] != UINT_MAX; k++){
        if(ancienne_position[k] == saut_simp.n[j].i){
          test = 0;
        }
      }
      if(test == 1){
        saut_possible[compteur]=saut_simp.n[j].i;
        compteur++;
      }
    }
    if(compteur != 0){
      srand(time(NULL));
      int rand_mvt = rand()%compteur;
      idx = saut_possible[rand_mvt];
      ancienne_position[l] = idx;
      l++;
      saut_simp = saut_simple(world,idx);
    }
  }
  saut_simp.n[0].i = idx;
  saut_simp.n[0].d = 0;
  saut_simp.n[1].i = UINT_MAX;
  return saut_simp;
}

unsigned int mov_pawn(struct world_t *world, int index){
    struct neighbors_t ds=deplacement_simple(world,index);
    struct neighbors_t ss=saut_simple(world,index);
    struct neighbors_t sm = saut_multiple(world,index);
    unsigned int compteur_ds=0;
    unsigned int compteur_ss=0;
    unsigned int nombre_mvt=nombre_mouvements(world,index);
    srand(time(NULL));
    if (nombre_mvt==0)
    {
      return index;
    }
    int rand_mvt=rand()%nombre_mvt;
    int somme=0;
    while(ds.n[compteur_ds].i!=UINT_MAX && compteur_ds < MAX_NEIGHBORS)
    {
      if(somme==rand_mvt)
      {
        return ds.n[compteur_ds].i;
      }
      compteur_ds++;
      somme++;
    }
    while (ss.n[compteur_ss].i!=UINT_MAX && compteur_ss < MAX_NEIGHBORS)
    {
      if(somme==rand_mvt)
      {
        return get_neighbor(ss.n[compteur_ss].i,ss.n[compteur_ss].d);
      }
      compteur_ss++;
      somme++;
    }
    if(somme == rand_mvt && sm.n[0].i != UINT_MAX)
    {
      return get_neighbor(sm.n[0].i,sm.n[0].d);
    }
    return index;
}

int position_init(struct world_t* world){
  int b = 0;
  int n = 0;
  for(int i = 0; i< WORLD_SIZE; i++){
    if(i%WIDTH==0){
      world_set(world,i,BLACK);
      world_set_sort(world,i,PAWN);
      n++;
    }
    if(i%WIDTH==WIDTH-1){
      world_set(world,i,WHITE);
      world_set_sort(world,i,PAWN);
      b++;
    }
  }
  return 0;
}