#include <stdio.h>
#include <stdlib.h>

int a[3][3][3] = {
    {{1, 1, 1},{1, 1, 1},{1, 1, 1}},
    {{1, 1, 1},{1, 1, 1},{1, 1, 1}},
    {{1, 1, 1},{1, 1, 1},{1, 1, 1}}
};

int b[3][3][3] = {
    {{2, 2, 2},{2, 2, 2},{2, 2, 2}},
    {{2, 2, 2},{2, 2, 2},{2, 2, 2}},
    {{2, 2, 2},{2, 2, 2},{2, 2, 2}}
};

int pivot[3][3][3] = {
    {{0, 0, 0},{0, 0, 0},{0, 0, 0}},
    {{0, 0, 0},{0, 0, 0},{0, 0, 0}},
    {{0, 0, 0},{0, 0, 0},{0, 0, 0}}
};

void funcao(){
    
    pivot[0][0][0] = 0;
    pivot[0][0][1] = 0;
    pivot[0][0][2] = 0;
    pivot[0][1][0] = 0;
    pivot[0][1][1] = 0;
    pivot[0][1][2] = 0;
    pivot[0][2][0] = 0;
    pivot[0][2][1] = 0;
    pivot[0][2][2] = 0;
    
    pivot[1][0][0] = 0;
    pivot[1][0][1] = 0;
    pivot[1][0][2] = 0;
    pivot[1][1][0] = 0;
    pivot[1][1][1] = 0;
    pivot[1][1][2] = 0;
    pivot[1][2][0] = 0;
    pivot[1][2][1] = 0;
    pivot[1][2][2] = 0;
    
    pivot[2][0][0] = 0;
    pivot[2][0][1] = 0;
    pivot[2][0][2] = 0;
    pivot[2][1][0] = 0;
    pivot[2][1][1] = 0;
    pivot[2][1][2] = 0;
    pivot[2][2][0] = 0;
    pivot[2][2][1] = 0;
    pivot[2][2][2] = 0;

}

int main(int argc, char** argv){
        
    pivot[0][0][0] = a[0][0][0];
    pivot[1][0][0] = a[1][0][0];

    a[0][0][0] = b[0][0][0];
    a[1][0][0] = b[1][0][0];

    b[0][0][0] = pivot[0][0][0];
    b[1][0][0] = pivot[1][0][0];

   

    printf("Valor de que escolhi : %d  %d\n", pivot[0][0][0],pivot[0][1][0]);
    printf("Valor de que escolhi : %d  %d\n", pivot[1][0][0],pivot[1][1][0]);
    
    funcao();
    
    printf("\n");
    printf("\n");

    printf("Valor de que escolhi : %d  %d\n", b[0][0][0],b[0][1][0]);
    printf("Valor de que escolhi : %d  %d\n", b[1][0][0],b[1][1][0]);

    printf("\n");
    printf("\n");

    printf("Valor de que escolhi : %d  %d\n", a[0][0][0],a[0][1][0]);
    printf("Valor de que escolhi : %d  %d\n", a[1][0][0],a[1][1][0]);

    printf("\n");
    printf("\n");

    funcao();

    printf("Valor de que escolhi : %d  %d\n", pivot[0][0][0],pivot[0][1][0]);
    printf("Valor de que escolhi : %d  %d\n", pivot[1][0][0],pivot[1][1][0]);
    
return 0;
}