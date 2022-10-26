
#include <stdio.h>
#include <stdlib.h>
#include "services/console_msg.h"
#include "services/clean_stdin.h"
#include "network/client.h"
#include "network/server.h"

int main() {
    printf("------------------------------------------------------------------\n\n");

    char choix = '\0';
    
    do {
        printf("- Démarrer[d]\n");
        printf("- Démarrer le serveur[s]\n");
        printf("- Rejoindre un serveur[c]\n\n");
        print_action("Veuillez sélectionner un mode de jeu : ");
        choix = getchar();
        clean_stdin();
        if (choix != 'd' && choix != 's' && choix != 'c') {
            choix = '\0';
            print_bad_input();
        }
    } while (choix == '\0');

    switch (choix) {
        case 'd':
            print_confirmation("Vous avez choisi le mode de jeu en solo\n");
            printf("\nEn construction.");
            break;

        case 's':
            print_confirmation("Vous avez choisi d'héberger une partie\n");
            init_server();
            break;

        case 'c':
            print_confirmation("Vous avez choisi de rejoindre une partie\n");
            init_client();
            break;
    }

    return 0;

}