#include "stdio.h"

#ifndef COORDINATES_H
#define COORDINATES_H

typedef struct{
  int x;
  int y;
} Coordinates;

Coordinates create_coordinates(int x, int y);

void print_coordinates_info(Coordinates coordinates);

#endif