#include "player.h"

Player create_player(int num_player, Coordinates coordinates, int nb_bomb, int level_bomb){
  Player out = {
    .num_player = num_player,
    .coordinates = coordinates,
    .nb_bomb = nb_bomb,
    .level_bomb = level_bomb
    };
  return out;
}

void set_x_coordinate(Player player, int x){
  Coordinates tmp = {
    .x = x,
    .y = player.coordinates.y
  };

  player.coordinates = tmp;
}

void set_y_coordinate(Player player, int y){
  Coordinates tmp = {
    .x = player.coordinates.x,
    .y = y
  };
  
  player.coordinates = tmp;
}