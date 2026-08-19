#ifndef ROTACOES_H
#define ROTACOES_H
#include "cubo.h"

extern int cubo[6][3][3];
extern char *lugarface[6];

//função que promove rotacao de 90° HORARIO em qualquer face
void rotaciona_90H(int m[6][3][3], int face);

//rotacao total do cubo ao girar NORTE HORARIO
void rotacaoNORTEH();

//rotacao total do cubo ao girar NORTE ANTI-HORARIO
void rotacaoNORTEAH();

//rotacao total do cubo ao girar SUL HORARIO
void rotacaoSULH();

//rotacao total do cubo ao girar SUL ANTI-HORARIO
void rotacaoSULAH();

//rotacao total do cubo ao girar LESTE HORARIO
void rotacaoLESTEH();

//rotacao total do cubo ao girar LESTE ANTI-HORARIO
void rotacaoLESTEAH();

//rotacao total do cubo ao girar OESTE HORARIO
void rotacaoOESTEH();

//rotacao total do cubo ao girar OESTE ANTI-HORARIO
void rotacaoOESTEAH();

//rotacao total do cubo ao girar FRENTE HORARIO
void rotacaoFRENTEH();

//rotacao total do cubo ao girar FRENTE ANTI-HORARIO
void rotacaoFRENTEAH();

//rotacao total do cubo ao girar TRAS HORARIO
void rotacaoTRASH();

//rotacao total do cubo ao girar TRAS ANTI-HORARIO
void rotacaoTRASAH();

#endif

