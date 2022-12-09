void show_world(struct world_t* world)
{
    for(int i = 0; i <WORLD_SIZE ; i++){
      if(world_get(world,i)==BLACK)
      {
        if(world_get_sort(world,i)==PAWN)
        {
          printf("%s"," ⛀ ");
        }
        if(world_get_sort(world,i)==TOUR)
        {
          printf("%s"," ♖ ");
        }
        if(world_get_sort(world,i)==ELEPHANT)
        {
          printf("%s"," ♘ ");
        }
      }
      if(world_get(world,i)==WHITE)
      { 
        if(world_get_sort(world,i)==PAWN)
        {
          printf("%s"," ⛂ ");
        }
        if(world_get_sort(world,i)==TOUR)
        {
          printf("%s"," ♜ ");
        }
        if(world_get_sort(world,i)==ELEPHANT)
        {
          printf("%s"," ♞ ");
        }
          
      }
      if(world_get(world,i)==NO_COLOR)
      {
        printf(" . ");
      }
      if(i%WIDTH == WIDTH-1)
      {
        printf("\n");
      }    
    }
}

void show_world_hexagone(struct world_t* world)
{
  int idx=0;
    for(int i = 0; i <HEIGHT ; i++)
    {
      for(int j = 1; j <WIDTH ; j+=2) //On print les hauts ()
      {
        idx=i*WIDTH+j;
        if(world_get(world,idx)==BLACK)
        {
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s","    ⛀ ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s","    ♖ ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s","    ♘ ");
          }
        }
        if(world_get(world,idx)==WHITE)
        { 
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s","    ⛂ ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s","    ♜ ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s","    ♞ ");
          }
            
        }
        if(world_get(world,idx)==NO_COLOR)
        {
          printf("    . ");
        }
      }
      printf("\n");
      for(int k = 0; k <WIDTH ; k+=2) //On print les bas ()
      {
        
        idx=i*WIDTH+k;
        if(world_get(world,idx)==BLACK)
        {
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s"," ⛀    ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s"," ♖    ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s"," ♘    ");
          }
        }
        if(world_get(world,idx)==WHITE)
        { 
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s"," ⛂    ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s"," ♜    ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s"," ♞    ");
          } 
        }
        if(world_get(world,idx)==NO_COLOR)
        {
          printf(" .    ");
        }
      }
      printf("\n");
    }
}

void show_world_triangle(struct world_t* world)
{
    for(int i = 0; i <WORLD_SIZE ; i++){
        if(i%2!=0){
            if(world_get(world,i)==BLACK)
            {
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛀/");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♖/");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♘/");
            }
            }
            if(world_get(world,i)==WHITE)
            { 
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛂/");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♜/");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♞/");
            }
            
            }
            if(world_get(world,i)==NO_COLOR)
            {
                printf("./");
            }
            if(i%WIDTH == WIDTH-1)
            {
            printf("\n");
            }    
        }
        if (i%2==0){
            if(world_get(world,i)==BLACK)
            {
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛀\\");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♖\\");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♘\\");
            }
            }
            if(world_get(world,i)==WHITE)
            { 
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛂\\");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♜\\");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♞\\");
            }
            
            }
            if(world_get(world,i)==NO_COLOR)
            {
                printf(".\\");
            }
            if(i%WIDTH == WIDTH-1)
            {
            printf("\n");
            }                
        }
      
        
    }
}