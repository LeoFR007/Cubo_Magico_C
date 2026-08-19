#include "include/cubo.h"
#include "include/rotacoes.h"

FILE *cuboembaralhado;
int cubo[6][3][3];
char *lugarface[6] = {"CIMA", "BAIXO", "ESQUERDA", "DIREITA", "FRENTE", "TRAS"};

void imprimeCuboArquivo(FILE *arquivo) {
    for(int i = 0; i < faces; i++) {
        fprintf(arquivo, "Face: %s\n", lugarface[i]);
        for(int j = 0; j < linhascolunas; j++) {
            for(int k = 0; k < linhascolunas; k++) {
                fprintf(arquivo, "%3d", cubo[i][j][k]);
            }
            fprintf(arquivo, "\n");
        }
        fprintf(arquivo, "\n");
    }
}

void cuboResolvido() {
     Cor cor = BRANCO;
    for(int i = 0; i < faces; i++) {
        for(int j = 0; j < linhascolunas; j++) {
            for(int k = 0; k < linhascolunas; k++) {
                cubo[i][j][k] = cor;
            }
        }
        cor++;
    }
}

//função para embaralhar o cubo.
void embaralhador() {
    cuboResolvido();

    for(int i = 0; i < 100; i++) {
    
        switch(rand() % 12 + 1) {
            case 1: rotacaoNORTEH(); break;
            case 2: rotacaoNORTEAH(); break;
            case 3: rotacaoSULH(); break;
            case 4: rotacaoSULAH(); break;
            case 5: rotacaoLESTEH(); break;
            case 6: rotacaoLESTEAH(); break;
            case 7: rotacaoOESTEH(); break;
            case 8: rotacaoOESTEAH(); break;
            case 9: rotacaoFRENTEH(); break;
            case 10: rotacaoFRENTEAH(); break;
            case 11: rotacaoTRASH(); break;
            case 12: rotacaoTRASAH(); break;
        }
    }

    imprimeCuboArquivo(cuboembaralhado);
}

int main() {

    int n;
    printf("Digite quantos cubos você deseja criar: ");
    scanf("%d", &n);

    srand(time(NULL));
    system("rm -rf cubos_embaralhados");
    mkdir("cubos_embaralhados", 0777);

    for (int i = 0; i < n; i++) {
        char nome[40];
        sprintf(nome, "cubos_embaralhados/cubo_%d.txt", i + 1);

        cuboembaralhado = fopen(nome, "w");
            if(cuboembaralhado == NULL) {
                printf("Erro ao criar o arquivo %s\n", nome);
                return 1;
            }

        embaralhador();
        fclose(cuboembaralhado);
    }

    return 0;
}

