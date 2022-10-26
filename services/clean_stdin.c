#include <stdio.h>

int clean_stdin()
{
    while (getchar()!='\n');
    return 1;
}