#include "general.h"

int concat_int(int a, int b) {
    char s1[20];
    char s2[20];
 
    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);
 
    strcat(s1, s2);
 
    int out = atoi(s1);
 
    return out;
}