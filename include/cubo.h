#ifndef CUBO_H
#define CUBO_H

//bibliotecas padrao
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

//definicoes da matriz
#define faces 6
#define linhascolunas 3

//variaveis que serao usadas nos arquivos
extern int cubo[6][3][3];
extern char *lugarface[6];

//enums para facilitar rotacoes do cubo
typedef enum {BRANCO, AMARELO, VERDE, AZUL, MAGENTA, VERMELHO} Cor;
typedef enum {NORTE, SUL, LESTE, OESTE} Rotação;
typedef enum {HORARIO, ANTIHORARIO} Direção;
typedef enum {CIMA, BAIXO, ESQUERDA, DIREITA, FRENTE, TRAS} Face;

//função para imprimir o cubo no terminal
void imprimeCuboTerminal();

//função que imprime os cubos em diferentes arquivos de texto
void imprimeCuboArquivo(FILE *arquivo);

//função que gera cubo resolvido
void cuboResolvido();

//função que lê o cubo de um arquivo de texto
void lerCuboArquivo(FILE *cuboarquivo);

//FUNÇÕES PARA O RESOLVEDOR
typedef struct {
    int face1, lin1, col1;
    int face2, lin2, col2;
    int face3, lin3, col3;
} PosCanto;

extern PosCanto cantos[8];

//verificação
int achar_canto(int corA, int corB, int corC, PosCanto *resultado);
void aplicar_movimentos(const char *seq);

//1
int cruz_branca_completa();
void resolver_cruz_branca();

//2
int canto_alvo_ok(int c2, int c3);
void derrubar_canto_topo(int idx);
void resolver_canto_branco(int cor1, int cor2, int cor3);
void resolver_cantos_brancos();

//3
void resolver_camada_meio();

//4
int cruz_amarela_completa();
void resolver_cruz_amarela();

//5
int face_amarela_completa();
void resolver_face_amarela();

//6
int cantos_amarelos_posicionados();
void resolver_cantos_amarelos();

//7
void resolver_arestas_amarelas();

#endif
