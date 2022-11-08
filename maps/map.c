#include "../common.h"

Map create_map(char* path) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    print_error("Erreur lors de l'ouverture du fichier : ");
    printf("%s", path);
    exit(EXIT_FAILURE);
  }
  print_confirmation("Ouverture du fichier : ");
  printf("%s\n", path);

  char* map_name = malloc(sizeof(char));
  int map_name_len = 0;
  int nb_bomb = 0;
  int map_width = 0;
  int map_height = 0;
  char** tab = malloc(sizeof(char));

  char ch = 0;
  int line_num = 0;
  int column_num = 0;

  while(ch != EOF) {
    char c = fgetc(file);
    if (c == '\n') {
      line_num++;
      column_num = 0;
      continue;
    }
    switch (line_num) {
    case 0:
      map_name = realloc(map_name, sizeof(char));
      map_name[map_name_len] = c;
      map_name_len++;
      break;
    
    case 1:
      nb_bomb = (int) c;
      break;

    case 2:
      if (c != ' ') {
        if (map_width == 0) {
          map_width = c;
        } else {
          map_height = c;
        }
      }

    default:
      tab = realloc(tab, sizeof(char));
      tab[column_num][line_num] = c;
      break;
    }
    column_num++;
  }

  map_height = line_num - 3;

  Map out = {
    .path = path,
    .name = map_name,
    .nb_bomb = nb_bomb,
    .width = map_width,
    .height = map_height,
    .tab = tab
  };

  fclose(file);

  return out;
}

void print_map_info(Map map) {
  printf("\nNom de la carte : %s\n", map.name);
  printf("Nb de bombes par défaut : %d\n", map.nb_bomb);
  printf("Largeur de la carte : %d\n", map.width);
  printf("Hauteur de la carte : %d\n", map.height);
}

void display_map(Map map) {
  for (int i = 1; i < map.height; i++) {
    for (int j = 1; i < map.width; i++) {
      printf("%c", map.tab[i][j]);
    }
  }
}