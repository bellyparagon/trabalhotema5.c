#include <stdio.h>

#define TAM 10       // Tamanho fixo do tabuleiro (10x10)
#define NAVIO 3      // Valor usado na matriz para representar um navio
#define TAM_NAVIO 3  // Todos os navios ocupam 3 posições

int main() {

    // -------------------------------
    // 1. Declaração do tabuleiro
    // -------------------------------
    int tabuleiro[TAM][TAM];

    // Inicializa todo o tabuleiro com 0 (água)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // -------------------------------
    // 2. Declarar navios
    // -------------------------------
    // Vetores representando navios (não guardam posições, só o valor NAVIO)
    int navioHorizontal[TAM_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAM_NAVIO]   = {NAVIO, NAVIO, NAVIO};

    // -------------------------------
    // 3. Coordenadas iniciais
    //    (definidas diretamente no código)
    // -------------------------------
    int linhaH = 2, colunaH = 4;  // Navio horizontal começa em (2,4)
    int linhaV = 5, colunaV = 1;  // Navio vertical começa em (5,1)

    // -------------------------------
    // 4. Validação dos navios
    // -------------------------------

    // Verifica se o navio horizontal cabe na linha
    if (colunaH + TAM_NAVIO > TAM) {
        printf("Erro: Navio horizontal nao cabe no tabuleiro!\n");
        return 1;
    }

    // Verifica se o navio vertical cabe na coluna
    if (linhaV + TAM_NAVIO > TAM) {
        printf("Erro: Navio vertical nao cabe no tabuleiro!\n");
        return 1;
    }

    // Verifica sobreposição simples
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaH][colunaH + i] != 0 ||
            tabuleiro[linhaV + i][colunaV] != 0) {

            printf("Erro: Sobreposicao detectada!\n");
            return 1;
        }
    }

    // -------------------------------
    // 5. Posicionar navio horizontal
    // -------------------------------
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
    }

    // -------------------------------
    // 6. Posicionar navio vertical
    // -------------------------------
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaV + i][colunaV] = navioVertical[i];
    }

    // -------------------------------
    // 7. Exibir o tabuleiro
    // -------------------------------
    printf("\nTABULEIRO FINAL:\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
