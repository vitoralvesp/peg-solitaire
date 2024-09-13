#include <stdio.h>

/* Funcao desnecessaria??*/
/*
//isWrongPlay(matrix[7][7], posicao X, posicao Y) --> Retorna valor booelano
indicando se eh uma jogada valida ou nao

int isWrongPlay(int m[7][7], int posX, int posY){

  //Vendo se existem nao pinos que possam pular para a posicao analisada
  if((posY-2 < 0 || m[posX][posY-2]!=1) &&
     (posY+2 > 6 || m[posX][posY+2]!=1) &&
     (posX-2 < 0 || m[posX-2][posY]!=1)&&
     (posX+2 > 6 || m[posX+2][posY]!=1)){ return 1;}

  //Vendo se nao existem pinos para serem comidos
  else if(m[posX][posY-1]!=1&&
          m[posX][posY+1]!=1 &&
          m[posX-1][posY]!=1&&
          m[posX+1][posY]!=1){ return 1;}

  //Caso jogada valida
  else return 0;

}
*/

// show(matriz) --> demonstra o conteúdo da matriz
void show(int mtrx[7][7]) {

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {

      if (mtrx[i][j] == -1)
        printf("#");
      else if (mtrx[i][j] == 1)
        printf("o");
      else
        printf(" ");
    }

    printf("\n");
  }

  printf("\n");
}

// copy(matriz origem, matriz destino) --> passa os valores da matriz origem
// para a matriz destino, gerando uma copia
void copy(int origin[7][7], int dest[7][7]) {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      dest[i][j] = origin[i][j];
    }
  }
}

// game_over(matrix[7][7]) --> verifica se o jogo já se encerrou
// Percorre a matriz e verifica se existe apenas um pino e na posicao central
int gameOver(int m[7][7]) {
  if (m[4][4] == 0)
    return 0;
  else {
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 7; j++) {
        // Pular posicao central ou posicoes invalidas
        if ((i == 4 && j == 4) || (m[i][j] == -1))
          continue;
        else if (m[i][j] == 1)
          return 0;
      }
    }
  }
  return 1;
}

// changePin(matriz, codigo, posição x, posição y) --> realiza a jogada
// solicitada e retorna um valor booleano se foi concluida(1) ou nao(0)
int changePin(int m[7][7], char playCode, int *posX, int *posY) {

  // Caso jogada vertical para cima
  if (playCode == 'u') {

    // Posicao fora do tabuleiro
    if (*posY - 2 < 0)
      return 0;

    // Nao existir pino que ira comer e pino que sera comido
    else if (m[*posX][*posY - 2] != 1 || m[*posX][*posY - 1] != 1)
      return 0;

    // Caso valido: fazer a jogada
    else {
      m[*posX][*posY] = 1;     // Espaço vazio recebe o pino
      m[*posX][*posY - 1] = 0; // Pino removido
      m[*posX][*posY - 2] = 0; // Posicao anterior do pino fica vazia
      *posY = *posY-1;
    }

    // Caso jogada vertical para baixo
  } else if (playCode == 'd') {
    if (*posY + 2 > 6)
      return 0;
    else if (m[*posX][*posY + 2] != 1 || m[*posX][*posY + 1] != 1)
      return 0;
    else {
      m[*posX][*posY] = 1;     // Espaço vazio recebe o pino
      m[*posX][*posY + 1] = 0; // Pino removido
      m[*posX][*posY + 2] = 0; // Posicao anterior do pino fica vazia
      *posY = *posY+1;
    }

    // Caso jogada vertical para esquerda
  } else if (playCode == 'l') {
    if (*posX - 2 < 0)
      return 0;
    else if (m[*posX - 2][*posY] != 1 || m[*posX - 1][*posY] != 1)
      return 0;
    else {
      m[*posX][*posY] = 1;     // Espaço vazio recebe o pino
      m[*posX - 1][*posY] = 0; // Pino removido
      m[*posX - 2][*posY] = 0; // Posicao anterior do pino fica vazia
      *posX = *posX-1;
    }

    // Caso jogada horizontal para a direita
  } else {
    if (*posX + 2 > 6)
      return 0;
    else if (m[*posX + 2][*posY] != 1 || m[*posX + 1][*posY] != 1)
      return 0;
    else {
      m[*posX][*posY] = 1;     // Espaço vazio recebe o pino
      m[*posX + 1][*posY] = 0; // Pino removido
      m[*posX + 2][*posY] = 0; // Posicao anterior do pino fica vazia
      *posX = *posX+1;
    }
  }
  return 1;
}

// play(matriz, posição x, posição y, jogada, contador) --> Realiza as jogadas recursivamente, ate finalizar o jogo
void play(int m[7][7], int *x, int *y, char playCode, int *counter) {
  if (gameOver(m))
    show(m);
  else if (*counter > 31 || !changePin(m, playCode, x, y))
    return;
  else {
    *counter = *counter + 1;
    play(m,x,y,'u',counter);
    play(m,x,y,'l',counter);
    play(m,x,y,'d',counter);
    play(m,x,y,'r',counter);
  }
}

int main() {

  int result;

  // matrix --> #: -1, Vazio: 0, Preenchido: 1
  int mtrx[7][7] = {{-1, -1, 1, 1, 1, -1, -1}, 
                    {-1, -1, 1, 1, 1, -1, -1},
                    {1, 1, 1, 1, 1, 1, 1},     
                    {1, 1, 1, 0, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1},     
                    {-1, -1, 1, 1, 1, -1, -1},
                    {-1, -1, 1, 1, 1, -1, -1}};

  result = 0;
  while (result == 0) {

    printf("Processando...\n");
    result = play(mtrx);
  }

  (result == 1) ? printf("Done!") : printf("ERROR WHILE PROCESSING MATRIX!!!");

  return 0;
}