/*
 *
 *  Lucas Pires de Camargo Sarai - 10418013
 *  Vitor Alves Pereira - 10410862
 * 
 * Ciência da Computação
 * 3D
 * PAA2
 * 
 * Referências:
 *  KISHIMOTO, André. Herança: Estrutura de Dados II. São Paulo , SP - Brasil, 3 set. 2024. Disponível em: https://graduacao.mackenzie.br/mod/resource/view.php?id=327556. Acesso em: 17 set. 2024.
 *  KISHIMOTO, André. Árvore: Estrutura de Dados II. São Paulo , SP - Brasil, 3 set. 2024. Disponível em: https://graduacao.mackenzie.br/mod/resource/view.php?id=327563. Acesso em: 17 set. 2024.
 */


#include <stdio.h>

#define TAMANHO_MATRIZ 7
#define MAX_MOVIMENTOS 31

// Estrutura para armazenar os movimentos realizados
typedef struct {
    int x_inicial, y_inicial;
    int direcao;  // 0 = Cima, 1 = Baixo, 2 = Esquerda, 3 = Direita
} Movimento;

// Função para exibir o estado atual da matriz do tabuleiro
void show(int mtrx[7][7]) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (mtrx[i][j] == -1)
                printf("#");  // Parte inválida do tabuleiro
            else if (mtrx[i][j] == 1)
                printf("o");  // Pino
            else
                printf(" ");  // Espaço vazio
        }
        printf("\n");
    }
    printf("\n");
}

// Verifica se o jogo acabou (se existe apenas um pino no centro)
int gameOver(int mtrx[7][7]) {
    int count = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (mtrx[i][j] == 1)
                count++;
        }
    }
    // Verifica se há apenas um pino e se ele está no centro
    return (count == 1 && mtrx[3][3] == 1);
}

// Função para realizar o movimento
int move(int mtrx[7][7], int y, int x, int dir, Movimento movimentos[], int *contador) {
    int dy[] = {-2, 2, 0, 0};  // Direções verticais (cima, baixo)
    int dx[] = {0, 0, -2, 2};  // Direções horizontais (esquerda, direita)

    int ny = y + dy[dir];
    int nx = x + dx[dir];
    
    // Verifica se o movimento é válido
    if (ny >= 0 && ny < 7 && nx >= 0 && nx < 7 && 
        mtrx[ny][nx] == 0 && mtrx[y + dy[dir]/2][x + dx[dir]/2] == 1) {
        
        // Executa o movimento
        mtrx[ny][nx] = 1;
        mtrx[y + dy[dir]/2][x + dx[dir]/2] = 0;
        mtrx[y][x] = 0;

        // Armazena o movimento
        movimentos[*contador].x_inicial = x;
        movimentos[*contador].y_inicial = y;
        movimentos[*contador].direcao = dir;
        (*contador)++;

        return 1;  // Movimento realizado com sucesso
    }
    return 0;  // Movimento inválido
}

// Função para desfazer o movimento
void undo(int mtrx[7][7], int y, int x, int dir, Movimento movimentos[], int *contador) {
    int dy[] = {-2, 2, 0, 0};  // Direções verticais (cima, baixo)
    int dx[] = {0, 0, -2, 2};  // Direções horizontais (esquerda, direita)

    int ny = y + dy[dir];
    int nx = x + dx[dir];

    // Desfaz o movimento
    mtrx[ny][nx] = 0;
    mtrx[y + dy[dir]/2][x + dx[dir]/2] = 1;
    mtrx[y][x] = 1;

    // Remove o último movimento do vetor
    (*contador)--;
}

// Função de backtracking para resolver o jogo
int solve(int mtrx[7][7], Movimento movimentos[], int *contador, int estados[MAX_MOVIMENTOS][7][7]) {
    if (gameOver(mtrx)) {
        return 1;  // Solução encontrada
    }

    // Tenta mover cada pino em todas as direções
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (mtrx[i][j] == 1) {  // Pino encontrado
                for (int dir = 0; dir < 4; dir++) {  // Tenta mover o pino nas 4 direções
                    if (move(mtrx, i, j, dir, movimentos, contador)) {
                        
                        // Apenas armazena o estado se não exceder o limite de movimentos
                        if (*contador < MAX_MOVIMENTOS) {
                            for (int a = 0; a < 7; a++) {
                                for (int b = 0; b < 7; b++) {
                                    estados[*contador][a][b] = mtrx[a][b];
                                }
                            }
                        }

                        if (solve(mtrx, movimentos, contador, estados)) {  // Chamada recursiva
                            return 1;
                        }

                        // Desfaz o movimento se não encontrou solução
                        undo(mtrx, i, j, dir, movimentos, contador);
                    }
                }
            }
        }
    }
    return 0;  // Nenhuma solução encontrada
}

// Função para inverter o vetor de movimentos
void inverterMovimentos(Movimento movimentos[], int contador) {
    for (int i = 0; i < contador / 2; i++) {
        Movimento temp = movimentos[i];
        movimentos[i] = movimentos[contador - 1 - i];
        movimentos[contador - 1 - i] = temp;
    }
}

// Função para exibir a sequência de movimentos realizados e os estados do tabuleiro após cada movimento
void mostrarMovimentos(Movimento movimentos[], int contador, int estados[MAX_MOVIMENTOS][7][7]) {
    for (int i = 0; i < contador; i++) {
        printf("Movimento %d: Pino em (%d, %d) movido para ", i+1, movimentos[i].x_inicial, movimentos[i].y_inicial);
        switch (movimentos[i].direcao) {
            case 0: printf("Cima\n"); break;
            case 1: printf("Baixo\n"); break;
            case 2: printf("Esquerda\n"); break;
            case 3: printf("Direita\n"); break;
        }

        // Mostra o estado da matriz após o movimento
        show(estados[i]);
    }
}

int main() {
    // Tabuleiro inicial
    int mtrx[7][7] = {
        {-1, -1, 1, 1, 1, -1, -1},
        {-1, -1, 1, 1, 1, -1, -1},
        { 1,  1, 1, 1, 1,  1,  1},
        { 1,  1, 1, 0, 1,  1,  1},
        { 1,  1, 1, 1, 1,  1,  1},
        {-1, -1, 1, 1, 1, -1, -1},
        {-1, -1, 1, 1, 1, -1, -1}
    };

    Movimento movimentos[MAX_MOVIMENTOS];  // Vetor para armazenar até 31 movimentos
    int contador = 0;  // Contador de movimentos
    int estados[MAX_MOVIMENTOS][7][7];  // Vetor para armazenar os estados do tabuleiro após cada movimento

    printf("Tabuleiro inicial:\n");
    show(mtrx);

    // Armazena o estado inicial do tabuleiro na posição 0
    for (int a = 0; a < 7; a++) {
        for (int b = 0; b < 7; b++) {
            estados[contador][a][b] = mtrx[a][b];
        }
    }

    if (solve(mtrx, movimentos, &contador, estados)) {
        mostrarMovimentos(movimentos, contador, estados);  // Exibe os movimentos realizados e o tabuleiro após cada movimento
        show(mtrx);
    } else {
        printf("Nenhuma solução encontrada.\n");
    }

    return 0;
}
