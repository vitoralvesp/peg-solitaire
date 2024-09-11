#include <stdio.h>

// show(matriz) --> demonstra o conteúdo da matriz
void show(int mtrx[7][7]) {

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {

            if (mtrx[i][j] == -1) printf(" ");
            else if (mtrx[i][j] == 1) printf("B");
            else printf("W");

        }

        printf("\n");

    }

    printf("\n");

}

// check_availability(matriz, posição x, posição y) --> retorna 1
// se é possível realizar uma jogada para horizontal ou vertical ou 
// 0 caso contrário
int check_availability(int mtrx[7][7], int i, char j) {

    if (mtrx[i][j] == 0) return 1;
    return 0;

}

// check_all(matriz) --> confere todos os elementos da matriz para
// determinar se apenas o pino central é igual a 1
int check_all(int mtrx[7][7]) {

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++)
            if (mtrx[i][j] == 1 && !(mtrx[2][2] == 1)) return 0;
    }

    return 1;

}

// move_pin(matriz, posição x, posição j, direção) --> move um pino para um
// espaço vazio no tabuleiro 
int move_pin(int mtrx[7][7], int i, int j, int dir) {

    if (dir == 0) {
        mtrx[i][j] = 1;
        mtrx[i+2][j] = 0;
        return 1;
    } else {
        mtrx[i][j] = 1;
        mtrx[i][j+2] = 0;
        return 1;
    }

    return -1;

}


// play(matriz, posição x, posição y) --> busca recursivamente como deixar somente o
// pino central como 1 e o restante, com excessão do -1, como 0.  
int play(int mtrx[7][7]) {

    int i, j;
    i = 0;
    j = 0;

    if (!check_all(mtrx)) return 1;
    else {

        show(mtrx);
        
        if (mtrx[i][j] != -1 && (i < 7 && j < 7)) {
            move_pin(mtrx, i, j, 0);
            move_pin(mtrx, i, j, 1);
        }
        
        play(mtrx);
        i++;
        j++;


    }

    return -1;

}


int main() {

    int result;

    // matrix --> #: -1, Vazio: 0, Preenchido: 1 
    int mtrx[7][7] = {
        {-1, -1, 1, 1, 1, -1, -1},
        {-1, -1, 1, 1, 1, -1, -1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {-1, -1, 1, 1, 1, -1, -1},
        {-1, -1, 1, 1, 1, -1, -1}
    };

    result = 0;
    while (result == 0) {

        printf("Processando...\n");
        result = play(mtrx);
    
    }

    (result == 1) ? printf("Done!") : printf("ERROR WHILE PROCESSING MATRIX!!!");


    return 0;

}