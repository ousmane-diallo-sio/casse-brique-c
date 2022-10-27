#include <stdio.h>
#include <stdlib.h>

void main()
{
    int i,j;
    char t[10][10];
    for (i=0;i<10;i++) {
        for (j=0;j<10;j++) {
            t[i][j]=' ';
        }
    }
    for (i=0;i<10;i++) {
        t[i][i]='*';
    }
    j=9;
    for (i=0;i<10;i++) {
        t[i][j]='*';
        j--;
    }

    for (i=0;i<10;i++) {
        for (j=0;j<10;j++) {
            printf("%c",t[i][j]);
        }
        printf("\n");
    }
}