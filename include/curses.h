#ifndef CURSES_H
#define CURSES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>// biblioteca para visualização do cubo mágico no terminal
#include "cubo.h"

//#define UP 0  << ja esta na biblioteca cubo.h
//#define LEFT 1   <<  ''      ''
//#define FRONT 2  <<  ''      ''
//#define RIGHT 3  <<  ''      ''
//#define BACK 4   <<  ''      ''
//#define DOWN 5   <<  ''      ''       

void iniciar_visualizacao();
void finalizar_visualizacao();
int pegar_cor(int c);
void desenhar_quadrado(int y, int x, int cor);
void desenhar_face(int face, int y, int x, const char *nome);
void desenhar_cubo(const char *jogada);

//int main() { // << tudo removido pois ja vai estar no algoritmoresolvedor.c, no cso removi o main 
//    char cubo[6][3][3] = {
//       { {'U', 'U', 'U'}, {'U', 'U', 'U'}, {'U', 'U', 'U'} }, // UP
//        { {'L', 'L', 'L'}, {'L', 'L', 'L'}, {'L', 'L', 'L'} }, // LEFT
//        { {'F', 'F', 'F'}, {'F', 'F', 'F'}, {'F', 'F', 'F'} }, // FRONT
//        { {'R', 'R', 'R'}, {'R', 'R', 'R'}, {'R', 'R', 'R'} }, // RIGHT
//        { {'B', 'B', 'B'}, {'B', 'B', 'B'}, {'B', 'B', 'B'} }, // BACK
//        { {'D', 'D', 'D'}, {'D', 'D', 'D'}, {'D', 'D', 'D'} }  // DOWN
//    };

//    const char *jogada = "Nenhuma jogada realizada";

//    iniciar_visualizacao();
//   desenhar_cubo(cubo, jogada);

//    getch();

//  finalizar_visualizacao();
//
//    return 0;
//}

void iniciar_visualizacao() {
    initscr();// inicia o modo de visualização do ncurses
    cbreak();// permite que os caracteres sejam lidos imediatamente sem esperar por Enter
    noecho();// evita que os caracteres digitados sejam exibidos na tela
    curs_set(0);

    if(has_colors())
    {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_WHITE); // LADO BRANCO
        init_pair(2, COLOR_BLACK, COLOR_MAGENTA); // LADO MAGENTA
        init_pair(3, COLOR_BLACK, COLOR_GREEN); // LADO VERDE
        init_pair(4, COLOR_BLACK, COLOR_RED); // LADO VERMELHO
        init_pair(5, COLOR_BLACK, COLOR_BLUE); // LADO AZUL
        init_pair(6, COLOR_BLACK, COLOR_YELLOW); // LADO AMARELO
        init_pair(7, COLOR_WHITE, COLOR_BLACK); // COR PADRÃO        
    }
}

void finalizar_visualizacao() {
    endwin();
}

//int pegar_cor(char c) { // moddificado para receber a cor em int em vez de char para funcionar com o cubo.h
int pegar_cor(int c) {
    switch(c)
    {
        case BRANCO:   // CASE U
            return 1;
        case AMARELO:  // CASE L
            return 2;
        case VERDE:    // CASE F
            return 3;
        case AZUL:     // CASE R
            return 4;
        case MAGENTA:  // CASE B
            return 5;
        case VERMELHO: // CASE D
            return 6;
        default:       // CASE DE COR PADRAO 
            return 7;
    }
}

//void desenhar_quadrado(int y, int x, char cor) { // modificado de "char cor" para "int cor"
void desenhar_quadrado(int y, int x, int cor) {
    int par = pegar_cor(cor);

    attron(COLOR_PAIR(par));

    //mvprintw(y, x, "   "); // modificado
    //mvprintw(y + 1, x, " %c ", cor); // modificado
    mvprintw(y, x, " %d ", cor);// modifiquei os mv de cima para conseguir centralizar a letra e separar melhor os quadrados
    
    attroff(COLOR_PAIR(par));
}

//void desenhar_face(char cubo [6][3][3], int face, int y, int x, const char *nome) {  // modificcado para remover o parametro char cubo 
void desenhar_face(int face, int y, int x, const char *nome) {
    mvprintw(y - 1, x + 4, "%s", nome);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
        desenhar_quadrado(y + i * 2, x + j * 4, cubo[face][i][j]);//modifiqui de 6 para 4 para ficar mais compacto
        }
    }
}

//void desenhar_cubo(char cubo [6][3][3], const char *jogada) { // modifiquei par aajustar chmadas e remover o parametro char cubo
void desenhar_cubo(const char *jogada) {

    clear();

    mvprintw(1, 2, "VISUALIZADOR");
    mvprintw(2, 2, "Estado atual: %s", jogada);


    //         UP
    
    //LEFT    FRONT   RIGHT   BACK // visualização do cubo mágico no terminal
    
    //        DOWN
    

    desenhar_face(CIMA, 5, 14, "(UP)");// troquei a posição 42 para 14 
    desenhar_face(ESQUERDA, 13, 1, "(LEFT)");// troquei a posição 2 para 1 
    desenhar_face(FRENTE, 13, 14, "(FRONT)");// troquei a posição 32 para 14
    desenhar_face(DIREITA, 13, 27, "(RIGHT)");// troquei a posição 62 para 27 
    desenhar_face(TRAS, 13, 40, "(BACK)");// troquei a posição 90 para 40
    desenhar_face(BAIXO, 21, 14, "(DOWN)");// troquei a posição 32 para 14 para ficar mais centralizado

    mvprintw(29, 2, "Pressione 'Q' para continuar as rotações e resolver o cubo!");
    refresh();// atualiza a tela para mostrar as mudanças (resolução do cubo)
}

#endif // CURSES_H
// as anotaçoes feitas nos códigos são para explicar o que eu mexi ai caso voces não entendam, acho
//acho que esta facil de ver, ai voces me perguntam depois