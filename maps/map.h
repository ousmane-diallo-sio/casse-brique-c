typedef struct {
  char* path;
  char* name;
  int nb_bomb;
  int width;
  int height;
  char** tab;
} Map;

Map create_map(char* path);

void print_map_info(Map map);

void display_map(Map map);
