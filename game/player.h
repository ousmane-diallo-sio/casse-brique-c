#include "../maps/coordinates.h"

#ifndef PLAYER_H
#define PLAYER_H

typedef struct{
  int num_player;
  Coordinates coordinates;
  int nb_bomb;
  int level_bomb;
} Player;

Player create_player(int num_player, Coordinates coordinates, int nb_bomb, int level_bomb);

void set_x_coordinate(Player player, int x);

void set_y_coordinate(Player player, int y);

#endif