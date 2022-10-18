#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 19000
#define COMMUNICATION_DOMAIN AF_LOCAL

void print_error(char* msg) {
    printf("\033[0;31m");
    printf("X %s", msg);
    printf("\033[0m");
}

void print_confirmation(char* msg) {
    printf("\033[0;32m");
    printf("O %s", msg);
    printf("\033[0m");
}

int main() {
    printf("------------------------------------------------------------------\n");
    
    char* msg = "Le message à été transmis avec succès, et oui ça fonctionne";

    struct sockaddr_in server_address, client_adress;
    int server_address_len = sizeof(server_address);
    int server_socket, client_socket;

    if ((server_socket = socket(COMMUNICATION_DOMAIN, SOCK_STREAM, 0)) < 0) {
        print_error("Erreur lors de la création du socket");
        return -1;
    }
    print_confirmation("La socket à bien été créee.\n");

    server_address.sin_family = COMMUNICATION_DOMAIN;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(SERVER_PORT);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        print_error("Erreur lors de la liaison avec le port");
        return -1;
    }
    print_confirmation("La liaison avec le port à bien été effectuée.\n");

    if (listen(server_socket, 2) < 0) {
        print_error("Erreur lors de la mise en place du listener");
        return -1;
    }
    print_confirmation("Mise en place du listener.\n");
    printf("En attente de l'arrivée d'un client...");

    if ((client_socket = accept(server_socket, (struct sockaddr*)&server_address, (socklen_t*)&server_address_len)) < 0) {
        print_error("Erreur lors de l'ouverture de la connexion");
        return -1;
    }
    print_confirmation("Ouverture de la connexion.\n");



}