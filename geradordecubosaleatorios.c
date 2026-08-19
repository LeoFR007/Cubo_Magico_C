#include "include/cubo.h"

FILE *cuboembaralhado;
int cubo[6][3][3];
char *lugarface[6] = {"CIMA", "BAIXO", "ESQUERDA", "DIREITA", "FRENTE", "TRAS"};

//função para embaralhar o cubo.
void embaralhador() {
    Cor cor = BRANCO;

    int cores[48];
        for(int i = 0; i < 48; i++) {
            cores[i] = i / 8;
        }

        //embaralhador
        for(int i = 47; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = cores[i];
            cores[i] = cores[j];
            cores[j] = temp;
        }

        //pivos sao estabelecidos
        for(int i = 0; i < faces; i++) {
            cubo[i][1][1] = cor++;
        }

        //o resto dos adesivos (sem ser os pivôs) são embaralhados
        int n = 0;
        for(int i = 0; i < faces; i++) {
            for(int j = 0; j < linhascolunas; j++) {
                for(int k = 0; k < linhascolunas; k++) {
                    if((j == 1) && (k == 1)) {
                        continue;
                    }
                    cubo[i][j][k] = cores[n++];
                }
            }
        }

        imprimeCuboArquivo(cuboembaralhado);
}

int main(int argc, char **argv) {

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
        embaralhador();
        fclose(cuboembaralhado);
    }

    return 0;
}

