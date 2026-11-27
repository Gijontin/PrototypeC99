#ifndef PROJECT_H
#define PROJECT_H

/*

    MAIN INTENT TO JUST BE FOR main.c TO BE ABLE TO RECOGNISE EVERYTHING IT'S FED

*/

// Standard Lib. headers
#include <stdio.h>

// 3rd Party Standard Lib. headers
#include "raylib.h"

// My own core headers (utility, configs, globals etc...)
#include "config.h"
#include "cursor.h"

// ECS Components
#include "player.h"
#include "transform_Component.h"
#include "movement_Component.h"
#include "render_Component.h"

//Factories
#include "entity_Factory.h"

// System/Modules (kom ihåg att ha dem i rätt ordning av dependancies)
#include "input_System.h"
#include "movement_System.h"
#include "collision_System.h"
#include "resolve_System.h"
#include "render_System.h"
#include "dialogues.h"
#include "world.h"


// Generella macros eller något

#define PROJECT_VERSION "0.0.1"
#define TILE64 64

#endif