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
#include<unistd.h>

#define MAX_LENGTH (7*7-4*2*2-1-1)

int history[MAX_LENGTH][7][7];
int history_length;
int moves_played;

int verify(int mtrx[7][7]);
int move_is_valid(int mtrx[7][7], int i, int j, int direction);
void move_pin(int mtrx[7][7], int i, int j, int direction);
void add_to_history(int mtrx[7][7]);
void show(int mtrx[7][7]);
int play(int mtrx[7][7]);


int main() {

    // mtrx --> tabuleiro resta-um 7 x 7
    int mtrx[7][7] = {
        {-1, -1, 1, 1, 1, -1, -1},
        {-1, -1, 1, 1, 1, -1, -1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {-1, -1, 1, 1, 1, -1, -1},
        {-1, -1, 1, 1, 1, -1, -1}};

    printf("---\nINICIANDO O JOGO\nOBS: Demora uns segundos para comecar a imprimir.\n---\n");

    if (play(mtrx)) {
        for (int i = 0; i < history_length; i++)
            show(history[i]);
        show(mtrx);
        printf(">> Jogo Concluido! %d tentativas de movimentos\n", moves_played);
    } else printf(">> Sem soluçao: %d tentativas de movimentos\n", moves_played);
    
    return 0;

}

// verify(tabuleiro) --> verifica se há apenas um pino no centro do tabuleiro
int verify(int mtrx[7][7])
{
    int total_pins = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
            if (mtrx[i][j] == 1) total_pins++;
    }
    return (total_pins == 1 && mtrx[3][3] == 1) ? 1 : 0;
}


// move_is_valid(tabuleiro, pos. y, pos. x, direção) --> retorna 1 se o movimento é válido e 0 caso contrário
int move_is_valid(int mtrx[7][7], int i, int j, int direction)
{
    if (i >= 0 && i < 7 && j >= 0 && j < 7 && mtrx[i][j] == 1) {
        // movimento para cima
        if (direction == 1) return (i > 1 && mtrx[i - 1][j] == 1 && mtrx[i - 2][j] == 0);

        // movimento para baixo
        if (direction == 2) return (i < 7 - 2 && mtrx[i + 1][j] == 1 && mtrx[i + 2][j] == 0);

        // movimento para esquerda
        if (direction == 3) return (j > 1 && mtrx[i][j - 1] == 1 && mtrx[i][j - 2] == 0);

        // movimento para esquerda
        if (direction == 4) return (j < 7 - 2 && mtrx[i][j + 1] == 1 && mtrx[i][j + 2] == 0);

    }
    return 0;
 
}


// move_pin(tabuleiro, pos. y, pos. x, direção) --> move o pino para cima, para baixo, para a esquerda ou para a direita.
void move_pin(int mtrx[7][7], int i, int j, int direction) {
    
    mtrx[i][j] = 0;
    if (direction == 1) {
        mtrx[i - 1][j] = 0;
        mtrx[i - 2][j] = 1;

    } else if (direction == 2) {
        mtrx[i + 1][j] = 0;
        mtrx[i + 2][j] = 1;

    } else if (direction == 3) {
        mtrx[i][j - 1] = 0;
        mtrx[i][j - 2] = 1;

    } else if (direction == 4) {
        mtrx[i][j + 1] = 0;
        mtrx[i][j + 2] = 1;

    }

}


// add_to_history(tabuleiro) --> adiciona uma jogada válida ao histórico de jogadas válidas
void add_to_history(int mtrx[7][7]) {
    if (history_length < MAX_LENGTH) {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++)
                history[history_length][i][j] = mtrx[i][j];
        }
        history_length++;

    } else {
        printf(">> Tamanho do histórico muito pequeno para o número de tentativas de jogadas...\n");
        exit(1);
    }
}


// undo_move(tabuleiro) --> atualiza o tabuleiro com a última jogada válida salvo no histórico de jogadas válidas
int undo_move(int mtrx[7][7]) {
    if (history_length > 0) {
        history_length--;
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++)
                mtrx[i][j] = history[history_length][i][j];
        }
    }
    return 0;
}


// show(tabuleiro) --> imprime o tabuleiro; 1 é o pino, 0 é o espaço e -1 é a extremidade/limite do tabuleiro
void show(int mtrx[7][7])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (mtrx[i][j] == -1)
                printf("#");
            else if (mtrx[i][j] == 0)
                printf(" ");
            else
                printf("o");
        }
        printf("\n");
    }
    printf("\n");
}


// play(tabuleiro) --> função recursiva que utiliza backtracking para solucionar o jogo resta-um
int play(int mtrx[7][7]) {

    if (verify(mtrx)) {
        return 1;

    } else {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                if (mtrx[i][j] == 1) {
                    // Tenta todos os movimentos possíveis para cada pino
                    for (int direction = 1; direction <= 4; direction++) {
                        if (move_is_valid(mtrx, i, j, direction)) {
                            moves_played++;
                            add_to_history(mtrx);
                            move_pin(mtrx, i, j, direction);
                            if (play(mtrx))
                                return 1;
                            undo_move(mtrx);
                        }
                    }
                }
            }
        }
    }
    return 0;
}
