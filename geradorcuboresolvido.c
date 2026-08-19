#include "cubo.h"
int cubo[6][3][3];
char *lugarface[6] = {"CIMA", "BAIXO", "ESQUERDA", "DIREITA", "FRENTE", "TRAS"};

int main() {

    cuboResolvido();
    imprimeCuboTerminal(); 

}