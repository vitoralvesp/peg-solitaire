#include <stdio.h>
#include <string.h>

#define MAX_SIZE (10000)

int move_pin(int mtrx[7][7], int spaces[49][2], int total_spaces, int i, int all_plays_history_arr[MAX_SIZE][7][7], int *all_plays_history_length);
int undo_move(int mtrx[7][7], int all_plays_history_arr[MAX_SIZE][7][7], int *all_plays_history_length);
int get_spaces(int mtrx[7][7], int spaces[49][2]);
int verify(int mtrx[7][7]);
void all_plays_history(int mtrx[7][7], int all_plays_history_arr[MAX_SIZE][7][7], int *all_plays_history_length);
void show(int mtrx[7][7]);
int play(int mtrx[7][7], int all_plays_history_arr[MAX_SIZE][7][7], int *all_plays_history_length);

int main()
{

    // mtrx --> tabuleiro resta-um 7 x 7
    int mtrx[7][7] = {
        {-1, -1, 1, 1, 1, -1, -1},
        {-1, -1, 1, 1, 1, -1, -1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {-1, -1, 1, 1, 1, -1, -1},
        {-1, -1, 1, 1, 1, -1, -1}};

    int all_plays_history_arr[MAX_SIZE][7][7];
    int a = 1;
    int *all_plays_history_length = &a;
    /*
    int spaces[49][2];

    show(mtrx);

    int spaces_length = get_spaces(mtrx, spaces);
    int move_status = move_pin(mtrx, spaces, spaces_length, all_plays_history_arr, all_plays_history_length);

    show(all_plays_history_arr[all_plays_history_length-1]);
    */
    play(mtrx, all_plays_history_arr, all_plays_history_length);

    return 0;
}

// verify(tabuleiro) --> verifica se há somente um pino no centro do tabuleiro
int verify(int mtrx[7][7])
{
    int count = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (mtrx[i][j] == 1)
            {
                count++;
            }
        }
    }
    return (count == 1 && mtrx[3][3] == 1) ? 1 : 0;
}

// getSpaces(tabuleiro, vetor de referência aos espaços disponíveis no tabuleiro) --> adiciona as coordenadas x e y de cada espaço disponível no tabuleiro
int get_spaces(int mtrx[7][7], int spaces[49][2])
{

    int idx = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (mtrx[i][j] == 0)
            {
                spaces[idx][0] = i;
                spaces[idx][1] = j;
                idx++;
            }
        }
    }

    return idx; // idx --> total de espaços
}

// move_pin(tabuleiro, espaços disponíveis no tabuleiro, total de espaços disponíveis) --> realiza jogadas nas quatro direções possíveis: acima, abaixo, à esquerda e à direita.
int move_pin(int mtrx[7][7], int spaces[49][2], int total_spaces, int i, int all_plays_history_arr[MAX_SIZE][7][7], int *all_plays_history_length)
{

    int curr_x = 0;
    int curr_y = 0;

    for (int i = 0; i < total_spaces; i++)
    {

        /* TENTATIVAS */
        curr_y = spaces[i][0];
        curr_x = spaces[i][1];

        // move up
        if (mtrx[curr_y - 1][curr_x] == 1 && mtrx[curr_y - 2][curr_x] == 1)
        {
            printf("move up...\n");
            mtrx[curr_y][curr_x] = 1;
            mtrx[curr_y - 1][curr_x] = 0;
            mtrx[curr_y - 2][curr_x] = 0;
            all_plays_history(mtrx, all_plays_history_arr, all_plays_history_length);
            show(mtrx);
            return 1;
        }

        // move left
        if (mtrx[curr_y][curr_x - 1] == 1 && mtrx[curr_y][curr_x - 2] == 1)
        {
            printf("move left...\n");
            mtrx[curr_y][curr_x] = 1;
            mtrx[curr_y][curr_x - 1] = 0;
            mtrx[curr_y][curr_x - 2] = 0;
            all_plays_history(mtrx, all_plays_history_arr, all_plays_history_length);
            show(mtrx);
            return 1;
        }

        // move right
        if (mtrx[curr_y][curr_x + 1] == 1 && mtrx[curr_y][curr_x + 2] == 1)
        {
            printf("move right...\n");
            mtrx[curr_y][curr_x] = 1;
            mtrx[curr_y][curr_x + 1] = 0;
            mtrx[curr_y][curr_x + 2] = 0;
            all_plays_history(mtrx, all_plays_history_arr, all_plays_history_length);
            show(mtrx);
            return 1;
        }

        // move down
        if (mtrx[curr_y + 1][curr_x] == 1 && mtrx[curr_y + 2][curr_x] == 1)
        {
            printf("move down...\n");
            mtrx[curr_y][curr_x] = 1;
            mtrx[curr_y + 1][curr_x] = 0;
            mtrx[curr_y + 2][curr_x] = 0;
            all_plays_history(mtrx, all_plays_history_arr, all_plays_history_length);
            show(mtrx);
            return 1;
        }
    }

    return -1;
}

int undo_move(int mtrx[7][7], int all_plays_history_arr[MAX_SIZE][7][7], int *all_plays_history_length)
{
    (*all_plays_history_length)--; // Decrementa o comprimento do histórico
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            mtrx[i][j] = all_plays_history_arr[*all_plays_history_length][i][j];
        }
    }
}

// all_plays_history(tabuleiro, vetor do histórico das jogadas) --> contém o histórico das jogadas que deram certo
void all_plays_history(int mtrx[7][7], int all_plays_history_arr[MAX_SIZE][7][7], int *all_plays_history_length)
{

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            all_plays_history_arr[*all_plays_history_length + 1][i][j] = mtrx[i][j];
        }
    }
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

int play(int mtrx[7][7], int all_plays_history_arr[MAX_SIZE][7][7], int *all_plays_history_length)
{
    int spaces[49][2];
    int total_spaces = get_spaces(mtrx, spaces);

    // Verifica se o estado atual é uma solução válida
    if (verify(mtrx) == 1)
    {
        // show(mtrx);
        return 1;
    }

    for (int i = 0; i < total_spaces; i++)
    {
        // Tenta mover pino e armazena a jogada no histórico
        if (move_pin(mtrx, spaces, total_spaces, i, all_plays_history_arr, all_plays_history_length))
        {
            (*all_plays_history_length)++;

            // Chama recursivamente para tentar o próximo movimento
            if (play(mtrx, all_plays_history_arr, all_plays_history_length))
            {
                return 1; // Se encontrar uma solução, termina
            }

            // Se não encontrar uma solução, desfaz a jogada
            undo_move(mtrx, all_plays_history_arr, all_plays_history_length);
        }
    }

    return 0;
}
