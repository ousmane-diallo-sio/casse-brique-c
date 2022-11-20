#include "../game/player.h"
#include "coordinates.h"
#include "../common.h"

#ifndef MAP_H
#define MAP_H

typedef struct {
  char* path;
  Player* players;
  int player_count;
  int nb_bomb;
  int width;
  int height;
  char** tab; // [y][x]
} Map;

Map create_map(char* path);

void print_map_info(Map map);

void display_map(Map map);

int is_coordinate_in_map(Map map, Coordinates coordinates);

// Le joueur peut-il se déplacer à cette position
int is_coordinate_open(Map map, Coordinates coordinates);

Map* getAllMaps();

int getNumberOfMaps();

Map chooseMap();

#endif
