#include "headers/common.h"
#include "console_msg.c"

int main() {

    int my_socket = 0;
    int remote_input;
    int client_fd;
    
    struct sockaddr_in server_address;

    char* msg = "Message de la part du client.";
    char buffer[1024] = {0};

    if ((my_socket = socket(COMMUNICATION_DOMAIN, SOCK_STREAM, 0)) < 0) {
        print_error("Erreur lors de la création du socket");
        return -1;
    }
    print_confirmation("La socket à bien été créee.\n");

    server_address.sin_family = COMMUNICATION_DOMAIN;
    server_address.sin_port = htons(SERVER_PORT);

    if (inet_pton(COMMUNICATION_DOMAIN, "127.0.0.1", &server_address.sin_addr) <= 0) {
        print_error("Adresse IP invalide.");
        return -1;
    }
    print_confirmation("Vérification de l'adresse IP du serveur.\n");

    if ((client_fd = connect(my_socket, (struct sockaddr*)&server_address, sizeof(server_address))) < 0) {
        print_error("Erreur lors de l'ouverture de la connexion. Vérifiez que le serveur est bien actif.");
        return -1;
    }
    print_confirmation("Ouverture de la connexion.\n");

    send(my_socket, msg, strlen(msg), 0);
    print_confirmation("Le message à bien été transmis.\n");

    remote_input = read(my_socket, buffer, 1024);
    printf("Contenu du buffer : %s\n", buffer);

    close(client_fd);

    return 0;
}