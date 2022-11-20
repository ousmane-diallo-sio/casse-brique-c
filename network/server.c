#include "server.h"

int init_server() {

    Map map;
    Player player;
    int game_ongoing = 0;
    
    FILE *ipconfig = popen("ipconfig getifaddr en0", "r");
    if (ipconfig == NULL) {
        print_error("Impossible d'obtenir l'adresse IP de cette machine");
        exit(1);
    }

    char server_ip[25];
    fgets(server_ip, 25, ipconfig);

    int server_port = 18000;

    char buffer[1024] = { 0 };

    struct sockaddr_in server_address, client_adress;
    int server_address_len = sizeof(server_address);
    int server_socket, client_socket;

    if ((server_socket = socket(COMMUNICATION_DOMAIN, SOCK_STREAM, 0)) < 0) {
        print_error("Erreur lors de la création du socket");
        return -1;
    }
    print_confirmation("La socket à bien été créee.\n");

    server_address.sin_family = COMMUNICATION_DOMAIN;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(server_port);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        print_error("Erreur lors de la liaison avec le port");
        return -1;
    }
    print_confirmation("La liaison avec le port à bien été effectuée.\n");

    if (listen(server_socket, 3) < 0) {
        print_error("Erreur lors de la mise en place du listener");
        return -1;
    }
    print_confirmation("Mise en place du listener. En attente de l'arrivée d'un client...\n");
    printf("\nAdresse IP -> %s\n", server_ip);
    printf("Numéro de port -> %d\n", server_port);

    if ((client_socket = accept(server_socket, (struct sockaddr*)&server_address, (socklen_t*)&server_address_len)) < 0) {
        print_error("Erreur lors de l'ouverture de la connexion");
        return -1;
    }
    print_confirmation("Ouverture de la connexion.\n");

    map = chooseMap();
    player = map.players[0];

    send(client_socket, map.path, strlen(map.path), 0);
    display_map(map);

    game_ongoing = 1;

    do{
        send_input(client_socket);
        wait_for_input(client_socket, buffer, &map);
    } while(game_ongoing == 1);

    close(client_socket);
    shutdown(server_socket, SHUT_RDWR);

    print_confirmation("Fin de transmission. Fermeture du serveur.\n");

    return 0;

}


void send_input(int remote_socket) {
    char command = '\0';
    print_action("Saississez une commande :\n");
    // do{
    //     command = getchar();
    //     if (trigger_command(command) == 0) {
    //         command = '\0';
    //         print_bad_input();
    //     }
    // } while (command == '\0');
    //send(remote_socket, &command, strlen(&command), 0);

    char msg[51];
    fgets(msg, 50, stdin);
    send(remote_socket, msg, strlen(msg), 0);
}

void wait_for_input(int remote_socket, char* buffer, Map *map) {
    printf("En attente de l'adversaire...\n");
    read(remote_socket, buffer, 1024);
    printf("Contenu du buffer : %s\n", buffer);
    if (buffer[1] != 0) {
        trigger_action(map, buffer);
    } else {
        trigger_command(buffer[0]);
    }
}