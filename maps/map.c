#include "../common.h"

Map create_map(char* path) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    print_error("Erreur lors de l'ouverture du fichier : \n");
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

  char c = 0;
  int line_num = 0;
  int column_num = 0;


  int has_read_width = 0;
  int has_read_height = 0;

  while(c != EOF) {
    c = fgetc(file);
    //printf("%c", c);
    // printf("ligne : %d ", line_num);
    // printf("column : %d\n", column_num);

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
      nb_bomb = c - '0';
      break;

    case 2:
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
      }
      break;

    default:
      tab = realloc(tab, sizeof(*tab)*map_height);
      tab[line_num -3] = malloc(sizeof(**tab)*map_width);
      tab[line_num -3][column_num] = c;
      printf("%c", tab[line_num -3][column_num]);
      if (column_num == map_width - 1) printf("\n");
      break;
    }
    column_num++;
  }

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
  printf("Hauteur de la carte : %d\n\n", map.height);
}

void display_map(Map map) {
  printf("bref : [%c]\n", map.tab[3][2]);
  for (int i = 0; i < map.height; i++) {
    for (int j = 0; j < map.width; j++) {
      printf("%c", map.tab[i][j]);
    }
    printf("\n");
  }
}