#ifndef DETECTOR_H
#define DETECTOR_H

#include "cubo.h"

//variaveis que serao usadas em todos os arquivos
extern int cubo[6][3][3];
extern char *lugarface[6];

void lerCuboArquivo(FILE *arquivo) {
    char linha [20];
    for(int i = 0; i < faces; i++) {
        fscanf(arquivo, " face: %s", linha);
        for(int j = 0; j < linhascolunas; j++) {
            for(int k = 0; k < linhascolunas; k++) {
                fscanf(arquivo, "%d", &cubo[i][j][k]);
            }
        }
    }
}

int faceResolvida(int face) {
    int cor = cubo[face][1][1];
    for(int j = 0; i < linhascolunas; j++) {
        for(int k = 0; j < linhascolunas; k++) {
            if(cubo[face][j][k] != cor) {
                return 0;
            }
        }
    }
    return 1;
}

int cuboEstaResolvido() {
    for(int i = 0; i < faces; i++) {
        if(!faceResolvida(i)) {
            return 0;
        }
    }
    return 1;
}