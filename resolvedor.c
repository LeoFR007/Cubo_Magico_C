#include "include/cubo.h"
#include "include/rotacoes.h"
#include <string.h>
#include "include/curses.h"

int cubo[6][3][3];
char *lugarface[6] = {"CIMA", "BAIXO", "ESQUERDA", "DIREITA", "FRENTE", "TRAS"};

void imprimeCuboTerminal() {
    for(int i = 0; i < faces; i++) {
        printf("Face: %s\n", lugarface[i]);
        for(int j = 0; j < linhascolunas; j++) {
            for(int k = 0; k < linhascolunas; k++) {
                printf("%3d", cubo[i][j][k]);
            }
            printf("\n");
        }
    }
}

void lerCuboArquivo(FILE *cuboarquivo) {
    char linha[100];
    for(int i = 0; i < faces; i++) {
        fgets(linha, sizeof(linha), cuboarquivo); 
        for(int j = 0; j < linhascolunas; j++) {
            for(int k = 0; k < linhascolunas; k++) {
                fscanf(cuboarquivo, "%d", &cubo[i][j][k]);
            }
        }
            fgets(linha, sizeof(linha), cuboarquivo);
            fgets(linha, sizeof(linha), cuboarquivo);
    }
}

int cubo_resolvido() {
    for(int f = 0; f < 6; f++)
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if(cubo[f][i][j] != cubo[f][1][1])
                    return 0;

    return 1;
}

// ============================================================================
// IMPLEMENTAÇÃO DO RESOLVEDOR
// ============================================================================

PosCanto cantos[8] = {
    {0,2,2,4,0,2,3,0,0},
    {0,2,0,4,0,0,2,0,2},
    {0,0,2,5,0,0,3,0,2},
    {0,0,0,5,0,2,2,0,0},

    {1,0,2,4,2,2,3,2,0},
    {1,0,0,4,2,0,2,2,2},
    {1,2,2,5,2,0,3,2,2},
    {1,2,0,5,2,2,2,2,0}
};

int achar_canto(int corA, int corB, int corC, PosCanto *resultado) {
    for (int i = 0; i < 8; i++) {
        PosCanto p = cantos[i];

        int a = cubo[p.face1][p.lin1][p.col1];
        int b = cubo[p.face2][p.lin2][p.col2];
        int c = cubo[p.face3][p.lin3][p.col3];

        int temA = (a == corA || b == corA || c == corA);
        int temB = (a == corB || b == corB || c == corB);
        int temC = (a == corC || b == corC || c == corC);

        if (temA && temB && temC) {
            *resultado = p;
            return i;
        }
    }

    return -1;
}

void aplicar_movimentos(const char *seq) {
    int i = 0;
    while (seq[i] != '\0') {
        char movimento = seq[i++];
        if (movimento == ' ' || movimento == '\t' || movimento == '\n') continue;
        int count = 1;
        int antihorario = 0;
        if (seq[i] == '\'') {
            antihorario = 1;
            i++;
        } else if (seq[i] == '2') {
            count = 2;
            i++;
            if (seq[i] == '\'') { antihorario = 1; i++; }
        }
        for (int c = 0; c < count; c++) {
            switch (movimento) {
                case 'U': antihorario ? rotacaoNORTEAH() : rotacaoNORTEH(); break;
                case 'D': antihorario ? rotacaoSULAH()   : rotacaoSULH();   break;
                case 'R': antihorario ? rotacaoLESTEAH() : rotacaoLESTEH(); break;
                case 'L': antihorario ? rotacaoOESTEAH() : rotacaoOESTEH(); break;
                case 'F': antihorario ? rotacaoFRENTEAH(): rotacaoFRENTEH();break;
                case 'B': antihorario ? rotacaoTRASAH()  : rotacaoTRASH();  break;
                default: break;
            }
        }
    }
}

// ============================================================================
// FUNÇÕES DE VERIFICAÇÃO
// ============================================================================

int cruz_branca_completa() {
    int faces_ids[4] = {4, 3, 5, 2};
    int topo_linha[4] = {0, 1, 2, 1};
    int topo_coluna[4] = {1, 2, 1, 0};
    for (int i = 0; i < 4; i++) {
        int face = faces_ids[i];
        if (cubo[0][topo_linha[i]][topo_coluna[i]] != BRANCO) return 0;
        if (cubo[face][0][1] != cubo[face][1][1]) return 0;
    }
    return 1;
}

static int primeira_camada_completa() {
    if (!cruz_branca_completa()) return 0;

    // Canto CIMA-FRENTE-DIREITA: CIMA[2][2], FRENTE[0][2], DIREITA[0][0]
    if (cubo[0][2][2] != BRANCO)             return 0;
    if (cubo[4][0][2] != cubo[4][1][1])      return 0;
    if (cubo[3][0][0] != cubo[3][1][1])      return 0;

    // Canto CIMA-FRENTE-ESQUERDA: CIMA[2][0], FRENTE[0][0], ESQUERDA[0][2]
    if (cubo[0][2][0] != BRANCO)             return 0;
    if (cubo[4][0][0] != cubo[4][1][1])      return 0;
    if (cubo[2][0][2] != cubo[2][1][1])      return 0;

    // Canto CIMA-TRAS-DIREITA: CIMA[0][2], TRAS[0][0], DIREITA[0][2]
    if (cubo[0][0][2] != BRANCO)             return 0;
    if (cubo[5][0][0] != cubo[5][1][1])      return 0;
    if (cubo[3][0][2] != cubo[3][1][1])      return 0;

    // Canto CIMA-TRAS-ESQUERDA: CIMA[0][0], TRAS[0][2], ESQUERDA[0][0]
    if (cubo[0][0][0] != BRANCO)             return 0;
    if (cubo[5][0][2] != cubo[5][1][1])      return 0;
    if (cubo[2][0][0] != cubo[2][1][1])      return 0;

    return 1;
}

static int segunda_camada_completa() {
    if (!primeira_camada_completa()) return 0;

    // FRENTE-DIREITA
    if (cubo[4][1][2] != cubo[4][1][1]) return 0;
    if (cubo[3][1][0] != cubo[3][1][1]) return 0;
    // FRENTE-ESQUERDA
    if (cubo[4][1][0] != cubo[4][1][1]) return 0;
    if (cubo[2][1][2] != cubo[2][1][1]) return 0;
    // TRAS-DIREITA
    if (cubo[5][1][0] != cubo[5][1][1]) return 0;
    if (cubo[3][1][2] != cubo[3][1][1]) return 0;
    // TRAS-ESQUERDA
    if (cubo[5][1][2] != cubo[5][1][1]) return 0;
    if (cubo[2][1][0] != cubo[2][1][1]) return 0;

    return 1;
}

//etapa 1: resolver a cruz branca

static void copiar_cubo(int destino[6][3][3], int origem[6][3][3]) {
    memcpy(destino, origem, sizeof(int) * 6 * 3 * 3);
}

static int busca_cruz(int prof, int max_prof, int ultimo) {
    if (cruz_branca_completa()) return 1;
    if (prof >= max_prof) return 0;

    static const char *movs[12] = {
        "U","U'","D","D'","R","R'","L","L'","F","F'","B","B'"
    };

    for (int i = 0; i < 12; i++) {
        if (ultimo >= 0 && (i ^ 1) == ultimo) continue;
        if (i == ultimo) continue;

        aplicar_movimentos(movs[i]);

        if (busca_cruz(prof + 1, max_prof, i))
            return 1;

        aplicar_movimentos(movs[i ^ 1]);
    }

    return 0;
}

void resolver_cruz_branca() {
    printf("=== RESOLVENDO CRUZ BRANCA ===\n");

    if (cruz_branca_completa()) {
        printf("=== CRUZ BRANCA JA COMPLETA ===\n");
        return;
    }

    int backup[6][3][3];
    copiar_cubo(backup, cubo);

    for (int prof = 1; prof <= 12; prof++) {
        copiar_cubo(cubo, backup);

        if (busca_cruz(0, prof, -1)) {
            printf("=== CRUZ BRANCA COMPLETA! ===\n");
            return;
        }
    }

    printf("=== CRUZ BRANCA NAO RESOLVIDA ===\n");
}

//etapa 2: resolver os cantos brancos
int canto_alvo_ok(int c2, int c3) {
    if ((c2 == MAGENTA && c3 == AZUL) || (c2 == AZUL && c3 == MAGENTA))
        return cubo[0][2][2] == BRANCO && cubo[4][0][2] == MAGENTA && cubo[3][0][0] == AZUL;

    if ((c2 == MAGENTA && c3 == VERDE) || (c2 == VERDE && c3 == MAGENTA))
        return cubo[0][2][0] == BRANCO && cubo[4][0][0] == MAGENTA && cubo[2][0][2] == VERDE;

    if ((c2 == VERMELHO && c3 == AZUL) || (c2 == AZUL && c3 == VERMELHO))
        return cubo[0][0][2] == BRANCO && cubo[5][0][0] == VERMELHO && cubo[3][0][2] == AZUL;

    if ((c2 == VERMELHO && c3 == VERDE) || (c2 == VERDE && c3 == VERMELHO))
        return cubo[0][0][0] == BRANCO && cubo[5][0][2] == VERMELHO && cubo[2][0][0] == VERDE;

    return 0;
}

void derrubar_canto_topo(int idx) {
    if (idx == 0) aplicar_movimentos("R D R'");
    else if (idx == 1) aplicar_movimentos("L' D' L");
    else if (idx == 2) aplicar_movimentos("B' D' B");
    else if (idx == 3) aplicar_movimentos("B D B'");
}

void resolver_canto_branco(int cor1, int cor2, int cor3) {
    PosCanto p;
    int idx;

    if (canto_alvo_ok(cor2, cor3)) return;

    idx = achar_canto(cor1, cor2, cor3, &p);
    if (idx < 0) return;

    if (idx >= 0 && idx <= 3) {
    if (!canto_alvo_ok(cor2, cor3)) {
        derrubar_canto_topo(idx);
    }
}

    int alvo_baixo;
    const char *alg;

    if ((cor2 == MAGENTA && cor3 == AZUL) || (cor2 == AZUL && cor3 == MAGENTA)) {
        alvo_baixo = 4;
        alg = "R' D' R D";
    } else if ((cor2 == MAGENTA && cor3 == VERDE) || (cor2 == VERDE && cor3 == MAGENTA)) {
        alvo_baixo = 5;
        alg = "L D L' D'";
    } else if ((cor2 == VERMELHO && cor3 == AZUL) || (cor2 == AZUL && cor3 == VERMELHO)) {
        alvo_baixo = 6;
        alg = "B' D' B D";
    } else {
        alvo_baixo = 7;
        alg = "B D B' D'";
    }

    for (int i = 0; i < 4; i++) {
        idx = achar_canto(cor1, cor2, cor3, &p);
        if (idx == alvo_baixo) break;
        aplicar_movimentos("D");
    }

    for (int i = 0; i < 8; i++) {
        if (canto_alvo_ok(cor2, cor3)) return;
        aplicar_movimentos(alg);
    }
}

void resolver_cantos_brancos() {
    printf("=== RESOLVENDO CANTOS BRANCOS ===\n");

    for (int tentativa = 0; tentativa < 20; tentativa++) {
        if (primeira_camada_completa())
            break;

        resolver_canto_branco(BRANCO, MAGENTA, AZUL);
        resolver_canto_branco(BRANCO, MAGENTA, VERDE);
        resolver_canto_branco(BRANCO, VERMELHO, AZUL);
        resolver_canto_branco(BRANCO, VERMELHO, VERDE);
    }

    if (primeira_camada_completa())
        printf("=== PRIMEIRA CAMADA COMPLETA! ===\n");
    else
        printf("=== PRIMEIRA CAMADA NAO RESOLVIDA ===\n");
}

//etapa 3: resolver a segunda camada
static int busca_segunda_camada(int prof, int max_prof) {
    if (segunda_camada_completa()) return 1;
    if (prof >= max_prof) return 0;

    static const char *algs[] = {
        "D' R' D R D F D' F'",
        "D L D' L' D' F' D F",

        "D' B' D B D R D' R'",
        "D F D' F' D' R' D R",

        "D' L' D L D B D' B'",
        "D R D' R' D' B' D B",

        "D' F' D F D L D' L'",
        "D B D' B' D' L' D L",

        "D", "D'", "D2"
    };

    int n = sizeof(algs) / sizeof(algs[0]);

    for (int i = 0; i < n; i++) {
        int backup[6][3][3];
        copiar_cubo(backup, cubo);

        aplicar_movimentos(algs[i]);

        if (busca_segunda_camada(prof + 1, max_prof))
            return 1;

        copiar_cubo(cubo, backup);
    }

    return 0;
}

void resolver_camada_meio() {
    printf("=== RESOLVENDO SEGUNDA CAMADA ===\n");

    if (segunda_camada_completa()) {
        printf("=== SEGUNDA CAMADA JA COMPLETA ===\n");
        return;
    }

    int backup[6][3][3];
    copiar_cubo(backup, cubo);

    for (int prof = 1; prof <= 6; prof++) {
        copiar_cubo(cubo, backup);

        if (busca_segunda_camada(0, prof)) {
            printf("=== SEGUNDA CAMADA COMPLETA! ===\n");
            return;
        }
    }

    copiar_cubo(cubo, backup);
    printf("=== SEGUNDA CAMADA NAO RESOLVIDA ===\n");
}

//etapa 4: fazer a cruz amarela
int cruz_amarela_completa() {
    if (!segunda_camada_completa()) return 0;

    return cubo[1][0][1] == AMARELO &&
           cubo[1][1][0] == AMARELO &&
           cubo[1][1][2] == AMARELO &&
           cubo[1][2][1] == AMARELO;
}

static int busca_cruz_amarela(int prof, int max_prof) {
    if (cruz_amarela_completa()) return 1;
    if (prof >= max_prof) return 0;

    static const char *algs[] = {
            "F' R' D' R D F",
            "R' B' D' B D R",
            "B' L' D' L D B",
            "L' F' D' F D L",

            "F L D L' D' F'",
            "R F D F' D' R'",
            "B R D R' D' B'",
            "L B D B' D' L'",

            "D", "D'", "D2"
        };

    int n = sizeof(algs) / sizeof(algs[0]);

    for(int i = 0; i < n; i++) {
        int backup[6][3][3];
        copiar_cubo(backup, cubo);

        aplicar_movimentos(algs[i]);

        if (busca_cruz_amarela(prof + 1, max_prof))
            return 1;

        copiar_cubo(cubo, backup);
    }

    return 0;
}

void resolver_cruz_amarela() {
    printf("=== RESOLVENDO CRUZ AMARELA ===\n");

    for(int prof = 1; prof <= 6; prof++) {
        if (busca_cruz_amarela(0, prof)) {
            printf("=== CRUZ AMARELA COMPLETA! ===\n");
            return;
        }
    }

    printf("=== CRUZ AMARELA NAO RESOLVIDA ===\n");
}

//etapa 5: resolver a face amarela
int face_amarela_completa() {
    if (!cruz_amarela_completa()) return 0;

    return cubo[1][0][0] == AMARELO &&
           cubo[1][0][2] == AMARELO &&
           cubo[1][2][0] == AMARELO &&
           cubo[1][2][2] == AMARELO;
}

static int busca_face_amarela(int prof, int max_prof) {
    if (face_amarela_completa()) return 1;
    if (prof >= max_prof) return 0;

    static const char *algs[] = {
        "R D R' D R D2 R'",
        "L' D' L D' L' D2 L",
        "F D F' D F D2 F'",
        "B' D' B D' B' D2 B",
        "D", "D'", "D2"
    };

    int n = sizeof(algs) / sizeof(algs[0]);

    for(int i = 0; i < n; i++) {
        int backup[6][3][3];
        copiar_cubo(backup, cubo);

        aplicar_movimentos(algs[i]);

        if (busca_face_amarela(prof + 1, max_prof))
            return 1;

        copiar_cubo(cubo, backup);
    }

    return 0;
}

void resolver_face_amarela() {
    printf("=== RESOLVENDO FACE AMARELA ===\n");

    for(int prof = 1; prof <= 6; prof++) {
        if (busca_face_amarela(0, prof)) {
            printf("=== FACE AMARELA COMPLETA! ===\n");
            return;
        }
    }

    printf("=== FACE AMARELA NAO RESOLVIDA ===\n");
}

//etapa 6: resolver cantos amarelos
int cantos_amarelos_posicionados() {
    if (!face_amarela_completa()) return 0;

    return cubo[4][2][0] == cubo[4][1][1] &&
           cubo[4][2][2] == cubo[4][1][1] &&
           cubo[3][2][0] == cubo[3][1][1] &&
           cubo[3][2][2] == cubo[3][1][1] &&
           cubo[5][2][0] == cubo[5][1][1] &&
           cubo[5][2][2] == cubo[5][1][1] &&
           cubo[2][2][0] == cubo[2][1][1] &&
           cubo[2][2][2] == cubo[2][1][1];
}

static int busca_cantos_amarelos(int prof, int max_prof) {
    if (cantos_amarelos_posicionados()) return 1;
    if (prof >= max_prof) return 0;

        static const char *algs[] = {
            "R D' L' D R' D' L D",
            "L' D R D' L D R' D'",

            "F D' B' D F' D' B D",
            "B' D F D' B D F' D'",

            "R' F R' B2 R F' R' B2 R2",
            "R2 B2 R F R' B2 R F' R",

            "D", "D'", "D2"
        };

    int n = sizeof(algs) / sizeof(algs[0]);

    for (int i = 0; i < n; i++) {
        int backup[6][3][3];
        copiar_cubo(backup, cubo);

        aplicar_movimentos(algs[i]);

        if (busca_cantos_amarelos(prof + 1, max_prof))
            return 1;

        copiar_cubo(cubo, backup);
    }

    return 0;
}

void resolver_cantos_amarelos() {
    printf("=== POSICIONANDO CANTOS AMARELOS ===\n");

    for (int prof = 1; prof <= 6; prof++) {
        if (busca_cantos_amarelos(0, prof)) {
            printf("=== CANTOS AMARELOS POSICIONADOS! ===\n");
            return;
        }
    }

    printf("=== CANTOS AMARELOS NAO POSICIONADOS ===\n");
}

//etapa 7: resolver a ultima camada

static int busca_arestas_amarelas(int prof, int max_prof) {
    if (cubo_resolvido()) return 1;
    if (prof >= max_prof) return 0;

    static const char *algs[] = {
        "F2 D L R' F2 L' R D F2",
        "F2 D' L R' F2 L' R D' F2",

        "R2 D F B' R2 F' B D R2",
        "R2 D' F B' R2 F' B D' R2",

        "D", "D'", "D2"
    };

    int n = sizeof(algs) / sizeof(algs[0]);

    for (int i = 0; i < n; i++) {
        int backup[6][3][3];
        copiar_cubo(backup, cubo);

        aplicar_movimentos(algs[i]);

        if (busca_arestas_amarelas(prof + 1, max_prof))
            return 1;

        copiar_cubo(cubo, backup);
    }

    return 0;
}

void resolver_arestas_amarelas() {
    printf("=== POSICIONANDO ARESTAS AMARELAS ===\n");

    for (int prof = 1; prof <= 5; prof++) {
        if (busca_arestas_amarelas(0, prof)) {
            printf("=== CUBO RESOLVIDO! ===\n");
            return;
        }
    }

    printf("=== ARESTAS AMARELAS NAO POSICIONADAS ===\n");
}

int main() {
    int escolha;
    printf("Escolha qual cubo deseja resolver:\n");
    scanf("%d", &escolha);

    char nome[40];
    sprintf(nome, "cubos_embaralhados/cubo_%d.txt", escolha);

    FILE *cuboarquivo = fopen(nome, "r");
    if (cuboarquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
 
    lerCuboArquivo(cuboarquivo);
    fclose(cuboarquivo);


    //          printf("\nCubo embaralhado:\n\n"); << removido para anexar com o ncurses
    //          imprimeCuboTerminal(); << removido para anexar com o ncurses 

    iniciar_visualizacao();
    desenhar_cubo("Cubo embaralhado");
    getch(); // espera por uma tecla antes de continuar

    resolver_cruz_branca();
    //          printf("\nApos cruz branca:\n\n"); << removido para anexar com o ncurses
    //          imprimeCuboTerminal();<< removido para anexar com o ncurses
    desenhar_cubo("Apos cruz branca");
    getch(); // espera por uma tecla antes de continuar
    if (!cruz_branca_completa()) {
        finalizar_visualizacao();       
        printf("\nERRO: cruz branca nao foi resolvida. Parando aqui.\n");
        return 1;
    }

    resolver_cantos_brancos();
    desenhar_cubo("Apos cantos brancos");
    getch(); // espera por uma tecla antes de continuar

    if(!primeira_camada_completa()) {
        finalizar_visualizacao();   
        printf("\nERRO: primeira camada nao foi resolvida. Parando aqui.\n");
        return 1;
    }

    resolver_camada_meio();
    desenhar_cubo("Apos segunda camada");
    getch(); // espera por uma tecla antes de continuar
    if (!segunda_camada_completa()) {
        finalizar_visualizacao();
        printf("\nERRO: segunda camada nao foi resolvida. Parando aqui.\n");
        return 1;
    }

    resolver_cruz_amarela();
    desenhar_cubo("Apos cruz amarela");
    getch(); // espera por uma tecla antes de continuar
    if(!cruz_amarela_completa()) {
        finalizar_visualizacao();
        printf("\nERRO: cruz amarela nao foi resolvida. Parando aqui.\n");
        return 1;
    }

    resolver_face_amarela();
    desenhar_cubo("Apos face amarela");
    getch(); // espera por uma tecla antes de continuar
    if(!face_amarela_completa()) {
        finalizar_visualizacao();
        printf("\nERRO: face amarela nao foi resolvida. Parando aqui.\n");
        return 1;
    }

    resolver_cantos_amarelos();
    desenhar_cubo("Apos posicionar cantos amarelos");
    getch(); // espera por uma tecla antes de continuar
    if(!cantos_amarelos_posicionados()) {
        finalizar_visualizacao();
        printf("\nERRO: cantos amarelos nao foram posicionados. Parando aqui.\n");
        return 1;
    }

    resolver_arestas_amarelas();
    desenhar_cubo("Apos posicionar arestas amarelas");
    getch(); // espera por uma tecla antes de continuar

    if(cubo_resolvido()) {
       desenhar_cubo("Cubo resolvido!");
       getch(); // espera por uma tecla antes de continuar
    }
       finalizar_visualizacao();

    return 0;
}