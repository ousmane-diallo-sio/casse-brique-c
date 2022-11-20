#include "play.h"

void start_game(Map map) {
  print_confirmation("----- Début de la partie -----\n");
}

void display_game(Map map) {
  print_action("---------- ----------\n\n");
  for (int i = 1; i <= map.player_count; i++) {
    printf("Nb de bombe (Joueur %d) : %d\n", i, map.players[i].nb_bomb);
  }
  display_map(map);
}

int trigger_command(char command) {
  int is_valid = 0;

  /*
  Vérifier que la command est valide.
  Si oui, vérifier si l'utilisateur peut réaliser l'action lié à la commande
  Exemple : Vérifier si l'utilisateur possède au moins une bombe avant de lui permettre d'en déposer
  */

  switch (command) {
    case 'h':
      printf("Haut");
      is_valid = 1;
      break;

    case 'b':
      printf("Bas");
      is_valid = 1;
      break;

    case 'g':
      printf("Gauche");
      is_valid = 1;
      break;

    case 'd':
      printf("Droite");
      is_valid = 1;
      break;
  }

  return is_valid;
}

int trigger_action(Map *map, char* action) {
  int is_valid = 0;

  if (strstr(action, "maps/") != NULL) {
    *map = create_map(action);
    display_game(*map);
    is_valid = 1;
  }

  return is_valid;
}