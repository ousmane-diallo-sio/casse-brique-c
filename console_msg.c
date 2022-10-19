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