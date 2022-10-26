#include "../common.h"
#include "../services/console_msg.h"
#include "../services/clean_stdin.h"

int init_server() {
    printf("\n------------------------------------------------------------------\n");
    
    char msg[51];
    print_action("Saisir du texte :\n");
    fgets(msg, 50, stdin);

    int remote_input;
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
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(SERVER_PORT);

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

    if ((client_socket = accept(server_socket, (struct sockaddr*)&server_address, (socklen_t*)&server_address_len)) < 0) {
        print_error("Erreur lors de l'ouverture de la connexion");
        return -1;
    }
    print_confirmation("Ouverture de la connexion.\n");

    remote_input = read(client_socket, buffer, 1024);
    printf("Contenu du buffer : %s\n", buffer);

    send(client_socket, msg, strlen(msg), 0);
    print_confirmation("Le message de bienvenue à été envoyé.\n");

    close(client_socket);
    shutdown(server_socket, SHUT_RDWR);

    print_confirmation("Fin de transmission. Fermeture du serveur.\n");

    return 0;

}