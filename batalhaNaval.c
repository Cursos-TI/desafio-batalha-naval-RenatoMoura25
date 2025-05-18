#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 5
#define NAVIOS 3

void inicializar_tabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = '~';
        }
    }
}

void exibir_tabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    printf("  ");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void posicionar_navios(char tabuleiro[TAMANHO][TAMANHO]) {
    int contador = 0;
    while (contador < NAVIOS) {
        int linha = rand() % TAMANHO;
        int coluna = rand() % TAMANHO;

        if (tabuleiro[linha][coluna] == '~') {
            tabuleiro[linha][coluna] = 'N'; // N = Navio
            contador++;
        }
    }
}

void jogar() {
    char tabuleiro[TAMANHO][TAMANHO];
    char tabuleiro_oculto[TAMANHO][TAMANHO];
    int navios_restantes = NAVIOS;
    int tentativas = 0;

    inicializar_tabuleiro(tabuleiro);
    inicializar_tabuleiro(tabuleiro_oculto);

    posicionar_navios(tabuleiro);

    printf("Bem-vindo à Batalha Naval!\n");

    while (navios_restantes > 0) {
        int linha, coluna;
        exibir_tabuleiro(tabuleiro_oculto);

        printf("Escolha uma linha (0-%d): ", TAMANHO - 1);
        scanf("%d", &linha);
        printf("Escolha uma coluna (0-%d): ", TAMANHO - 1);
        scanf("%d", &coluna);

        if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO) {
            printf("Coordenadas inválidas! Tente novamente.\n");
            continue;
        }

        tentativas++;

        if (tabuleiro[linha][coluna] == 'N') {
            printf("Acertou um navio!\n");
            tabuleiro_oculto[linha][coluna] = 'X'; // X = Acertou
            tabuleiro[linha][coluna] = '~';
            navios_restantes--;
        } else if (tabuleiro_oculto[linha][coluna] == 'O' || tabuleiro_oculto[linha][coluna] == 'X') {
            printf("Você já atirou aqui!\n");
        } else {
            printf("Água!\n");
            tabuleiro_oculto[linha][coluna] = 'O'; // O = Água
        }
    }

    printf("Parabéns! Você venceu em %d tentativas.\n", tentativas);
}

int main() {
    srand(time(NULL));
    jogar();
    return 0;
}