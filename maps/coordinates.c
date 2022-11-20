#include "coordinates.h"

Coordinates create_coordinates(int x, int y) {
  Coordinates out = {
    .x = x,
    .y = y
  };
  return out;
}

void print_coordinates_info(Coordinates coordinates) {
  printf("[X : %d, Y : %d]", coordinates.x, coordinates.y);
}