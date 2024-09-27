#include <stdio.h>

#define MAX_LENGTH (1000)

int history[MAX_LENGTH][7][7];
int history_length = 1;

int verify(int mtrx[7][7]);
int move_is_valid(int mtrx[7][7], int i, int j);
int move_pin(int mtrx[7][7], int i, int j, int direction);
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
    
    if (play(mtrx) == 1) printf("Jogo Concluido!!!");
    else printf("Erro!!!");

    return 0;

}


int verify(int mtrx[7][7])
{
    int total_pins = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (mtrx[i][j] == 1)
            {
                total_pins++;
            }
        }
    }
    return (total_pins == 1 && mtrx[3][3] == 1) ? 1 : 0;
}


int move_is_valid(int mtrx[7][7], int i, int j)
{
    
    // Verifica se a posição está dentro do tabuleiro e se há uma peça nessa posição
    if (i < 0 || i >= 7 || j < 0 || j >= 7 || mtrx[i][j] == 0 || mtrx[i][j] == -1) {
        return 0; // Movimento inválido
    }

    // Verifica os quatro movimentos possíveis (cima, baixo, esquerda, direita)
    if (i > 1 && mtrx[i - 1][j] != 0 && mtrx[i - 2][j] == 0) {
        return 1; // Salto válido para cima
    }
    if (i < 7 - 2 && mtrx[i + 1][j] != 0 && mtrx[i + 2][j] == 0) {
        return 2; // Salto válido para baixo
    }
    if (j > 1 && mtrx[i][j - 1] != 0 && mtrx[i][j - 2] == 0) {
        return 3; // Salto válido para a esquerda
    }
    if (j < 7 - 2 && mtrx[i][j + 1] != 0 && mtrx[i][j + 2] == 0) {
        return 4; // Salto válido para a direita
    }

    return 0; // Movimento inválido
 
}

int move_pin(int mtrx[7][7], int i, int j, int direction) {
    
    if (direction == 1) {
        printf("movendo para cima\n");
        mtrx[i][j] = 0;
        mtrx[i - 1][j] = 0;
        mtrx[i - 2][j] = 1;
        add_to_history(mtrx);
        return 1;

    } else if (direction == 2) {
        printf("movendo para baixo\n");
        mtrx[i][j] = 0;
        mtrx[i + 1][j] = 0;
        mtrx[i + 2][j] = 1;
        add_to_history(mtrx);
        return 1;

    } else if (direction == 3) {
        printf("movendo para a esquerda\n");
        mtrx[i][j] = 0;
        mtrx[i][j - 1] = 0;
        mtrx[i][j - 2] = 1;
        add_to_history(mtrx);
        return 1;

    } else if (direction == 4) {
        printf("movendo para a direita\n");
        mtrx[i][j] = 0;
        mtrx[i][j + 1] = 0;
        mtrx[i][j + 2] = 1;
        add_to_history(mtrx);
        return 1;

    }

    return -1;

}

void add_to_history(int mtrx[7][7]) {
    if (history_length < MAX_LENGTH - 1) {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                history[history_length][i][j] = mtrx[i][j];
            }
        }
        history_length++;
    }
}

int undo_move(int mtrx[7][7]) {
    if (history_length > 1) {
        history_length--;
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                mtrx[i][j] = history[history_length][i][j];
            }
        }
    }
    return 0;
}


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

int play(int mtrx[7][7]) {
    
    if (verify(mtrx)) {
        return 1;

    } else {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                int direction = move_is_valid(mtrx, i, j);
                if (direction != 0) {
                    move_pin(mtrx, i, j, direction);
                    show(mtrx);
                    if (play(mtrx)) return 1;
                    else undo_move(mtrx);
                }
            }
        }
    }
    return -1;
}
