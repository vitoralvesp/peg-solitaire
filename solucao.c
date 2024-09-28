/*
 *
 *  Lucas Pires de Camargo Sarai - 10418013
 *  Vitor Alves Pereira - 10410862
 * 
 * Ciência da Computação
 * 3D
 * PAA2
 * 
 */


#include <stdio.h>

#define TAMANHO_MATRIZ 7
#define MAX_MOVIMENTOS 31

// Movimento
typedef struct {
    int coluna_inicial, linha_inicial;
    int direcao;
} Movimento;

// exibir(matriz) -> Exibe a matriz passada como argumento
void exibir(int mtr[7][7]) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (mtr[i][j] == -1)
                printf("#"); 
            else if (mtr[i][j] == 1)
                printf("o"); 
            else
                printf(" ");  
        }
        printf("\n");
    }
    printf("\n");
}

// fim_de_jogo(matriz) -> Verifica se existe apenas um pino e no centro do tabuleiro
int fim_de_jogo(int mtr[7][7]) {
    int count = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (mtr[i][j] == 1)
                count++;
        }
    }
    
    return (count == 1 && mtr[3][3] == 1);
}

// move(matriz,coordenadas,movimentos,contador) -> Realiza um movimento no tabuleiro
int mover(int mtr[7][7], int linha, int coluna, int dir, Movimento movimentos[], int *contador) {
    int dLinha[] = {-2, 2, 0, 0};  // Direcoes verticais (cima, baixo)
    int dColuna[] = {0, 0, -2, 2};  // Direcoes horizontais (esquerda, direita)

    int nlinha = linha + dLinha[dir];
    int nColuna = coluna + dColuna[dir];
    
    // Verifica se o movimento é valido
    if (nlinha >= 0 && nlinha < 7 && nColuna >= 0 && nColuna < 7 && 
        mtr[nlinha][nColuna] == 0 && mtr[linha + dLinha[dir]/2][coluna + dColuna[dir]/2] == 1) {
        
        // Executa o movimento
        mtr[nlinha][nColuna] = 1;
        mtr[linha + dLinha[dir]/2][coluna + dColuna[dir]/2] = 0;
        mtr[linha][coluna] = 0;

        // Armazena o movimento
        movimentos[*contador].coluna_inicial = coluna;
        movimentos[*contador].linha_inicial = linha;
        movimentos[*contador].direcao = dir;
        (*contador)++;

        return 1;  // Movimento valido
    }
    return 0;  // Movimento invalido
}

// desfazer(matriz,linha,coluna,direcao,movimentos,contador) -> Desfaz o ultimo movimento feito
void desfazer(int mtr[7][7], int linha, int coluna, int dir, Movimento movimentos[], int *contador) {
    int dLinha[] = {-2, 2, 0, 0};  // direcoes verticais (cima, baixo)
    int dColuna[] = {0, 0, -2, 2};  // direcoes horizontais (esquerda, direita)

    //Calcula a posicao inicial do pino movido
    int nlinha = linha + dLinha[dir];
    int nColuna = coluna + dColuna[dir];

    // Desfaz o movimento
    mtr[nlinha][nColuna] = 0;
    mtr[linha + dLinha[dir]/2][coluna + dColuna[dir]/2] = 1;
    mtr[linha][coluna] = 1;
    (*contador)--;
}

// resta_um(matriz,movimentos,contador,jogadas) -> Funcao principal que faz as jogadas
int resta_um(int mtr[7][7], Movimento movimentos[], int *contador, int jogadas[MAX_MOVIMENTOS][7][7]) {
    //Fim de jogo valido
    if (fim_de_jogo(mtr)) {
        return 1;  
    }

    // Caso geral: tentar uma jogada, encontrando um pino
    for (int ln = 0; ln < 7; ln++) {
        for (int col = 0; col < 7; col++) {
            if (mtr[ln][col] == 1) { 
                for (int dir = 0; dir < 4; dir++) {  // Tenta mover o pino nas 4 direcoes
                    if (mover(mtr, ln, col, dir, movimentos, contador)) {
                        
                        // Armazena o movimento valido
                        if (*contador < MAX_MOVIMENTOS) {
                            for (int a = 0; a < 7; a++) {
                                for (int b = 0; b < 7; b++) {
                                    jogadas[*contador][a][b] = mtr[a][b];
                                }
                            }
                        }

                        //Caso a proxima jogada encerre o jogo, finaliza a chamada
                        if (resta_um(mtr, movimentos, contador, jogadas)) {  
                            return 1;
                        }

                        // Desfaz o movimento, se nao eh o caminho apropriado
                        desfazer(mtr, ln, col, dir, movimentos, contador);
                    }
                }
            }
        }
    }
    return 0;  // Fim de jogo invalido
}

// mostrarJogadas(contador,jogadas) -> exibe cada jogada feita 
void mostrarJogadas(int jogadas[MAX_MOVIMENTOS][7][7],int contador) {
    for (int i = 0; i < contador; i++) {
        printf("-------------------------------\n");
        exibir(jogadas[i]);
        printf("-------------------------------\n");
    }
}

int main() {
    // Tabuleiro inicial
    int mtr[7][7] = {
        {-1, -1, 1, 1, 1, -1, -1},
        {-1, -1, 1, 1, 1, -1, -1},
        { 1,  1, 1, 1, 1,  1,  1},
        { 1,  1, 1, 0, 1,  1,  1},
        { 1,  1, 1, 1, 1,  1,  1},
        {-1, -1, 1, 1, 1, -1, -1},
        {-1, -1, 1, 1, 1, -1, -1}
    };

    Movimento movimentos[MAX_MOVIMENTOS];  // Armazena os movimentos Cima,Baixo,Esquerda,Direita
    int contMovimentos = 0; 
    int jogadas[MAX_MOVIMENTOS][7][7];  // Armazena os tabuleiros com jogadas validas

    printf("Tabuleiro inicial:\n");
    exibir(mtr);

    printf("O jogo pode demorar um pouco para comecar...\n");

    // Salva o estado inicial do jogo
    for (int a = 0; a < 7; a++) {
        for (int b = 0; b < 7; b++) {
            jogadas[contMovimentos][a][b] = mtr[a][b];
        }
    }

    //Verifica se uma solucao foi encontrada
    if (resta_um(mtr, movimentos, &contMovimentos, jogadas)) {
        mostrarJogadas(jogadas,contMovimentos);

        //Exibe a matriz resolvida
        exibir(mtr);

        printf("Total de jogadas: %d\n",contMovimentos);
    } else {
        printf("Nenhuma solução encontrada.\n");
    }

    return 0;
}
