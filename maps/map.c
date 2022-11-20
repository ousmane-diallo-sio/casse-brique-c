#include "map.h"

Map create_map(char* path) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    print_error("Erreur lors de l'ouverture du fichier : \n");
    printf("%s", path);
    exit(EXIT_FAILURE);
  }
  print_confirmation("Ouverture du fichier : ");
  printf("%s\n", path);

  int nb_bomb = 0;
  int map_width = 0;
  int map_height = 0;
  char** tab;
  Player* players = malloc(sizeof(Player));
  int player_count = 0;
  char c = 0;
  int line_num = 0;
  int column_num = 0;


  int has_read_width = 0;
  int has_read_height = 0;

  while(c != EOF) {
    c = fgetc(file);

    if (c == '\n' || c == EOF) {
      line_num++;
      column_num = 0;
      continue;
    }

    switch (line_num) {
      case 0:
        nb_bomb = c - '0';
        break;

      case 1:
        if (c == ' ') has_read_width = 1;
        if (!has_read_width) {
          if (map_width == 0) {
            map_width = c - '0';
          } else{
            map_width = concat_int(map_width, c - '0');
          }
        } else if(c != ' ') {
          if (map_height == 0) {
            map_height = c - '0';
          } else{
            map_height = concat_int(map_height, c - '0');
          }
          tab = malloc((map_height * map_width) * sizeof(char));
          if (tab == NULL) {
            print_error("Problème lors de réallocation mémoire");
          }
          for (int i = 0; i < map_height; i++) {
            tab[i] = malloc(map_width * sizeof(char));
            if (tab[i] == NULL) {
              print_error("Problème lors de l'allocation mémoire");
            }
          }
        }
        break;
    }

    if (line_num >= 2) {
      tab[line_num -2][column_num] = c;
    }

    if (c == 'p') {
      Coordinates coordinates = {
        .x = column_num,
        .y = line_num -2
      };

      Player tmp = create_player(player_count +1, coordinates, nb_bomb, 1);
      players = realloc(players, player_count +2 * sizeof(Player));
      players[player_count] = tmp;
      player_count++;
    }

    column_num++;
  }

  Map out = {
    .path = path,
    .players = players,
    .player_count = player_count,
    .nb_bomb = nb_bomb,
    .width = map_width,
    .height = map_height,
    .tab = tab
  };

  fclose(file);

  return out;
}

void print_map_info(Map map) {
  printf("\n");
  printf("Largeur de la carte : %d\n", map.width);
  printf("Hauteur de la carte : %d\n", map.height);
  printf("Nombre de joueurs : %d\n", map.player_count);
  printf("Nb de bombes par défaut : %d\n", map.nb_bomb);
  printf("\n");
}

void display_map(Map map) {
  int player_count = 0;
  for (int i = 0; i < map.height; i++) {
    for (int j = 0; j < map.width; j++) {
      char c = map.tab[i][j];
      if (c == 'p') {
        printf("%d", map.players[player_count].num_player);
        player_count++;
      } else {
        printf("%c", c);
      }
    }
    printf("\n");
  }
}

int is_coordinate_in_map(Map map, Coordinates coordinates) {
  if (coordinates.x >= 0 && coordinates.y >= 0) {
    if (coordinates.x < map.width && coordinates.y < map.height) {
      return 1;
    }
  }
  return 0;
}

int is_coordinate_open(Map map, Coordinates coordinates) {
  if (is_coordinate_in_map(map, coordinates) == 1) {
    if (map.tab[coordinates.y][coordinates.x] == ' ') {
      return 1;
    }
    return 0;
  }
  print_error("Ces coordonnés se trouvent en dehors de la carte\n");
  return -1;
}

Map* getAllMaps() {
  char* maps[] = {"maps/map1.csv", "maps/map2.csv", "maps/map3.csv"};
  int maps_len = 3;
  Map *out = malloc(sizeof(Map) * maps_len);
  for (int i = 0; i < maps_len; i++) {
    out[i] = create_map(maps[i]);
  }
  return out;
}

int getNumberOfMaps() {
  return 3;
}

Map chooseMap() {
  char choix = '\0';
  Map* maps = getAllMaps();

  do{
    print_action("\nChoisissez une des cartes suivantes : \n\n");
    for (int i = 0; i < getNumberOfMaps(); i++) {
      printf("Map %d (%d joueurs) : %s [%d]\n", i +1, maps[i].player_count, maps[i].path, i +1);
    }

    choix = getchar();
    clean_stdin();

    if (choix - '0' < 1 || choix - '0' > getNumberOfMaps()) {
      choix = '\0';
      print_bad_input();
    }
  } while(choix == '\0');

  return maps[atoi(&choix) -1];
}