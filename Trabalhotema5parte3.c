#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro 10x10
#define NAVIO 3       // Valor que representa parte de navio no tabuleiro
#define AFETADO 5     // Valor que representa área afetada por habilidade
#define TAM_HAB 5     // Tamanho da matriz de habilidade (5x5)
#define HAB_CENTER (TAM_HAB/2) // Centro da matriz de habilidade (2 para 5x5)
#define TAM_NAVIO 3   // Tamanho fixo dos navios neste desafio

// Retorna 1 se coordenada válida dentro do tabuleiro, 0 caso contrário
int dentroDoTabuleiro(int l, int c){
    return (l >= 0 && l < TAM && c >= 0 && c < TAM);
}

/*
  Tenta colocar um navio de tamanho TAM_NAVIO no tabuleiro.
  direction: 0 = horizontal (dir direita),
             1 = vertical (dir baixo),
             2 = diagonal ↘ (linha+ / col+),
             3 = diagonal ↙ (linha+ / col-)
  startL, startC: coordenada da primeira célula do navio.
  Retorna 1 se colocado com sucesso, 0 se fora dos limites ou sobreposição.
*/
int colocarNavio(int tab[TAM][TAM], int startL, int startC, int direction) {
    int coords[TAM_NAVIO][2];

    // Calcula coordenadas das 3 partes do navio
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = startL, c = startC;
        if (direction == 0) {        // horizontal
            c = startC + i;
        } else if (direction == 1) { // vertical
            l = startL + i;
        } else if (direction == 2) { // diagonal ↘
            l = startL + i;
            c = startC + i;
        } else if (direction == 3) { // diagonal ↙
            l = startL + i;
            c = startC - i;
        }
        coords[i][0] = l;
        coords[i][1] = c;

        // valida limite
        if (!dentroDoTabuleiro(l, c)) return 0;
        // valida sobreposição
        if (tab[l][c] != 0) return 0;
    }

    // se passou nas validações, escreve no tabuleiro
    for (int i = 0; i < TAM_NAVIO; i++) {
        tab[ coords[i][0] ][ coords[i][1] ] = NAVIO;
    }
    return 1;
}

/*
  Gera dinamicamente a matriz de habilidade 'cone' (5x5),
  considerando o topo do cone em i = 0 (linha superior da matriz)
  e expandindo para baixo.
  Preenche hab[][] com 0/1.
*/
void gerarCone(int hab[TAM_HAB][TAM_HAB]) {
    // Para cada célula da matriz 5x5 decidimos se está afetada (1) ou não (0)
    // Lógica: quanto maior o índice de linha i (descendo), maior a largura do cone.
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // distância horizontal em relação ao centro da matriz
            int dx = j - HAB_CENTER;
            // nível (quão "abaixo" estamos do topo do cone)
            int nivel = i; // 0..4
            // condição: célula afetada se abs(dx) <= nivel
            // isso cria um cone que se abre para baixo (topo em i=0)
            if ( (nivel >= 0) && (abs(dx) <= nivel) ) hab[i][j] = 1;
            else hab[i][j] = 0;
        }
    }
}

/*
  Gera dinamicamente a matriz de habilidade 'cruz' (5x5)
  com ponto de origem no centro.
  Preenche hab[][] com 0/1.
*/
void gerarCruz(int hab[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // cruz: linha central ou coluna central (centro em index HAB_CENTER)
            if (i == HAB_CENTER || j == HAB_CENTER) hab[i][j] = 1;
            else hab[i][j] = 0;
        }
    }
}

/*
  Gera dinamicamente a matriz de habilidade 'octaedro' (vista frontal: losango/diamante)
  usando condição |dx| + |dy| <= R (R = 2 para TAM_HAB = 5).
  Preenche hab[][] com 0/1.
*/
void gerarOctaedro(int hab[TAM_HAB][TAM_HAB]) {
    int R = HAB_CENTER; // raio do diamante (2 para 5x5)
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int dy = i - HAB_CENTER;
            int dx = j - HAB_CENTER;
            if ( (abs(dx) + abs(dy)) <= R ) hab[i][j] = 1;
            else hab[i][j] = 0;
        }
    }
}

/*
  Sobrepõe a matriz de habilidade (hab 5x5 com 0/1) no tabuleiro.
  origemL, origemC são coordenadas no tabuleiro onde o centro da hab será posicionado.
  Regras:
   - Se a célula da habilidade == 1 e a posição resultante estiver dentro do tabuleiro:
       * Se tab[pos] == 0 (água) => marca com AFETADO (5)
       * Se tab[pos] == NAVIO (3) => mantém NAVIO (prioridade de exibição do navio)
   - Usa loops aninhados e condicionais obrigatoriamente.
*/
void sobreporHabilidade(int tab[TAM][TAM], int hab[TAM_HAB][TAM_HAB], int origemL, int origemC) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (hab[i][j] == 1) {
                int alvoL = origemL + (i - HAB_CENTER);
                int alvoC = origemC + (j - HAB_CENTER);
                // valida limites simplificada
                if (dentroDoTabuleiro(alvoL, alvoC)) {
                    if (tab[alvoL][alvoC] == 0) {
                        tab[alvoL][alvoC] = AFETADO;
                    } else {
                        // Se já for NAVIO (3), mantemos 3 — navio tem prioridade visual
                        // Comentário: se preferir sobrescrever navio, altere aqui.
                    }
                }
            }
        }
    }
}

/*
  Imprime o tabuleiro no console com printf.
  Exibe os valores numéricos conforme solicitado: 0, 3, 5
*/
void imprimirTabuleiro(int tab[TAM][TAM]) {
    printf("\nTABULEIRO (0 = agua, 3 = navio, 5 = area afetada):\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // inicializa tabuleiro com 0 (água)
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;

    // ---------------------------------------------------
    // Colocar 4 navios (tamanho 3) com validação simples
    // Dois tradicionais (h/v) e dois diagonais
    // Escolha de posições definida diretamente no código (conforme simplificação)
    // ---------------------------------------------------
    // Exemplo de posições:
    // Navio A: horizontal começando em (2,1) direção 0
    // Navio B: vertical   começando em (5,6) direção 1
    // Navio C: diagonal ↘ começando em (0,0) direção 2
    // Navio D: diagonal ↙ começando em (3,9) direction 3

    int sucesso = 1;
    sucesso &= colocarNavio(tabuleiro, 2, 1, 0); // horiz
    sucesso &= colocarNavio(tabuleiro, 5, 6, 1); // vert
    sucesso &= colocarNavio(tabuleiro, 0, 0, 2); // diag ↘
    sucesso &= colocarNavio(tabuleiro, 3, 9, 3); // diag ↙

    if (!sucesso) {
        printf("Erro ao posicionar navios: coordenadas invalidas ou sobreposicao.\n");
        return 1;
    }

    // ---------------------------------------------------
    // Gerar dinamicamente as matrizes de habilidade (5x5)
    // ---------------------------------------------------
    int habCone[TAM_HAB][TAM_HAB];
    int habCruz[TAM_HAB][TAM_HAB];
    int habOcta[TAM_HAB][TAM_HAB];

    gerarCone(habCone);
    gerarCruz(habCruz);
    gerarOctaedro(habOcta); // note: function name below is gerarOctaedro

    // ---------------------------------------------------
    // Pontos de origem (centro) para cada habilidade no tabuleiro
    // (definidos diretamente no código conforme simplificação)
    // ---------------------------------------------------
    int origemConeL = 1, origemConeC = 2; // colocar cone "embaixo" a partir de (1,2)
    int origemCruzL = 6, origemCruzC = 6;
    int origemOctaL = 4, origemOctaC = 3;

    // ---------------------------------------------------
    // Sobrepor as habilidades no tabuleiro
    // ---------------------------------------------------
    sobreporHabilidade(tabuleiro, habCone, origemConeL, origemConeC);
    sobreporHabilidade(tabuleiro, habCruz, origemCruzL, origemCruzC);
    sobreporHabilidade(tabuleiro, habOcta, origemOctaL, origemOctaC);

    // ---------------------------------------------------
    // Imprimir tabuleiro final
    // ---------------------------------------------------
    imprimirTabuleiro(tabuleiro);

    return 0;
}
