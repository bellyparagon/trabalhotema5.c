#include <stdio.h>

#define TAM 10     // Tamanho do tabuleiro 10x10
#define NAVIO 3    // Valor que representa uma parte do navio
#define TAMANHO_NAVIO 3  // Cada navio possui tamanho 3

// Função para verificar se um navio pode ser colocado sem sair do tabuleiro
int dentroDoTabuleiro(int linha, int coluna) {
    return (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM);
}

// Função para verificar se as posições estão livres (sem sobreposição)
int podeColocar(int tabuleiro[TAM][TAM], int coords[3][2]) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = coords[i][0];
        int c = coords[i][1];

        if (!dentroDoTabuleiro(l, c)) return 0;  // Fora dos limites
        if (tabuleiro[l][c] != 0) return 0;      // Já ocupado
    }
    return 1;
}

// Função para colocar o navio no tabuleiro
void colocarNavio(int tabuleiro[TAM][TAM], int coords[3][2]) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = coords[i][0];
        int c = coords[i][1];
        tabuleiro[l][c] = NAVIO;
    }
}

int main() {

    int tabuleiro[TAM][TAM];

    // Inicializando o tabuleiro com 0 (água)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // -------------------------------------------
    // POSICIONAMENTO DOS 4 NAVIOS (tamanho fixo 3)
    // Dois horizontais/verticais
    // Dois diagonais
    // -------------------------------------------

    // Navio 1 - Horizontal (linha 2, colunas 1 a 3)
    int navio1[3][2] = {
        {2, 1}, {2, 2}, {2, 3}
    };

    // Navio 2 - Vertical (coluna 6, linhas 5 a 7)
    int navio2[3][2] = {
        {5, 6}, {6, 6}, {7, 6}
    };

    // Navio 3 - Diagonal ↘ (cresce linha e coluna)
    int navio3[3][2] = {
        {0, 0}, {1, 1}, {2, 2}
    };

    // Navio 4 - Diagonal ↙ (linha cresce, coluna diminui)
    int navio4[3][2] = {
        {3, 9}, {4, 8}, {5, 7}
    };

    // Vetor com todos os navios
    int (*navios[4])[2] = { navio1, navio2, navio3, navio4 };

    // Colocando os 4 navios com validação
    for (int n = 0; n < 4; n++) {
        if (podeColocar(tabuleiro, navios[n])) {
            colocarNavio(tabuleiro, navios[n]);
        } else {
            printf("Erro ao posicionar o navio %d! Sobreposição ou fora dos limites.\n", n+1);
            return 1; // Encerra o programa caso dê erro
        }
    }

    // -------------------------------------------
    // EXIBIR TABULEIRO COMPLETO
    // -------------------------------------------
    printf("\n===== TABULEIRO 10x10 =====\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
