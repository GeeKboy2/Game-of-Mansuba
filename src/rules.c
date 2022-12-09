#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "geometry.h"
#include "world.h"
#include "neighbors.h"
#include <unistd.h>
#include <time.h>
#include "limits.h"
#include "project.h"

enum plateau {
    CARRE = 0,
    HEXAGONE = 1,
    TRIANGLE = 2,
    MAX_PLATEAU = 3,
};


