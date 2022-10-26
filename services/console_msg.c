#include <stdio.h>

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

void print_bad_input() {
    print_error("Saisie invalide. Réessayez.\n");
}

void print_action(char* msg) {
    printf("\033[0;33m");
    printf("%s", msg);
    printf("\033[0m");
}