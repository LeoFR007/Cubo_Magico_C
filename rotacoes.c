#include "include/cubo.h"
#include "include/rotacoes.h"

//função que promove rotacao de 90° HORARIO em qualquer face
void rotaciona_90H(int m[6][3][3], int face){
    
    int tmp[6][3][3];
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tmp[face][j][2-i] = m[face][i][j]; 
        }
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            m[face][i][j] = tmp[face][i][j]; 
        }
    }
}

//ROTAÇÕES HORÁRIAS
//rotacao total do cubo ao girar NORTE HORARIO
void rotacaoNORTEH() {
    int tmp[3];
    for(int i = 0; i < 3; i++) tmp[i] = cubo[4][0][i];
    for(int i = 0; i < 3; i++) cubo[4][0][i] = cubo[3][0][i];
    for(int i = 0; i < 3; i++) cubo[3][0][i] = cubo[5][0][i];
    for(int i = 0; i < 3; i++) cubo[5][0][i] = cubo[2][0][i];
    for(int i = 0; i < 3; i++) cubo[2][0][i] = tmp[i];
    
    rotaciona_90H(cubo, 0);
}



//rotacao total do cubo ao girar SUL HORARIO
void rotacaoSULH() {
    int tmp[3];
    for(int i = 0; i < 3; i++) tmp[i] = cubo[4][2][i];
    for(int i = 0; i < 3; i++) cubo[4][2][i] = cubo[2][2][i];
    for(int i = 0; i < 3; i++) cubo[2][2][i] = cubo[5][2][i];
    for(int i = 0; i < 3; i++) cubo[5][2][i] = cubo[3][2][i];
    for(int i = 0; i < 3; i++) cubo[3][2][i] = tmp[i];

    rotaciona_90H(cubo, 1);
}

//rotacao total do cubo ao girar LESTE HORARIO
void rotacaoLESTEH() {
    int tmp[3];
    for(int i = 0; i < 3; i++) tmp[i] = cubo[4][i][2];
    for(int i = 0; i < 3; i++) cubo[4][i][2] = cubo[1][i][2];
    for(int i = 0; i < 3; i++) cubo[1][i][2] = cubo[5][2-i][0];
    for(int i = 0; i < 3; i++) cubo[5][2-i][0] = cubo[0][i][2];
    for(int i = 0; i < 3; i++) cubo[0][i][2] = tmp[i];

    rotaciona_90H(cubo, 3);
}

//rotacao total do cubo ao girar OESTE HORARIO
void rotacaoOESTEH() {
    int tmp[3];
    for(int i = 0; i < 3; i++) tmp[i] = cubo[4][i][0];
    for(int i = 0; i < 3; i++) cubo[4][i][0] = cubo[0][i][0];
    for(int i = 0; i < 3; i++) cubo[0][i][0] = cubo[5][2-i][2];
    for(int i = 0; i < 3; i++) cubo[5][2-i][2] = cubo[1][i][0];
    for(int i = 0; i < 3; i++) cubo[1][i][0] = tmp[i];

    rotaciona_90H(cubo, 2);
}

//rotacao total do cubo ao girar FRENTE HORARIO
void rotacaoFRENTEH() {
    int tmp[3];

    for(int i = 0; i < 3; i++) tmp[i] = cubo[0][2][i];

    for(int i = 0; i < 3; i++) cubo[0][2][i] = cubo[2][2-i][2];
    for(int i = 0; i < 3; i++) cubo[2][2-i][2] = cubo[1][0][2-i];
    for(int i = 0; i < 3; i++) cubo[1][0][2-i] = cubo[3][i][0];
    for(int i = 0; i < 3; i++) cubo[3][i][0] = tmp[i];

    rotaciona_90H(cubo, 4);
}


//rotacao total do cubo ao girar TRAS HORARIO
void rotacaoTRASH() {
    int tmp[3];
    for(int i = 0; i < 3; i++) tmp[i] = cubo[0][0][i];
    for(int i = 0; i < 3; i++) cubo[0][0][i] = cubo[3][i][2];
    for(int i = 0; i < 3; i++) cubo[3][i][2] = cubo[1][2][2-i];
    for(int i = 0; i < 3; i++) cubo[1][2][i] = cubo[2][i][0];
    for(int i = 0; i < 3; i++) cubo[2][i][0] = tmp[2-i];

    rotaciona_90H(cubo, 5);
}

//ROTAÇÕES ANTI-HORÁRIAS
void rotacaoNORTEAH() {
    rotacaoNORTEH();
    rotacaoNORTEH();
    rotacaoNORTEH();
}

void rotacaoSULAH() {
    rotacaoSULH();
    rotacaoSULH();
    rotacaoSULH();
}

void rotacaoLESTEAH() {
    rotacaoLESTEH();
    rotacaoLESTEH();
    rotacaoLESTEH();
}

void rotacaoOESTEAH() {
    rotacaoOESTEH();
    rotacaoOESTEH();
    rotacaoOESTEH();
}

void rotacaoFRENTEAH() {
    rotacaoFRENTEH();
    rotacaoFRENTEH();
    rotacaoFRENTEH();
}

void rotacaoTRASAH() {
    rotacaoTRASH();
    rotacaoTRASH();
    rotacaoTRASH();
}

