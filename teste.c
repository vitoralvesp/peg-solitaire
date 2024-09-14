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
  if (m[3][3] == 0)
    return 0;
  else {
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 7; j++) {
        // Pular posicao central ou posicoes invalidas
        if ((i == 3 && j == 3) || (m[i][j] == -1))
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
int changePin(int m[7][7], char playCode, int *posY, int *posX) {

  // Caso jogada vertical para cima
  if (playCode == 'u') {
    printf("Posicao atual: (%d,%d)\n", *posX, *posY);
    printf("Jogada: %c\n", playCode);
    // Posicao fora do tabuleiro
    if (*posY - 2 < 0) {
      printf("DEU RUIM em %c: posicao fora!\n", playCode);
      return 0;
    }

    // Nao existir pino que ira comer e pino que sera comido
    else if (m[*posY - 2][*posX] != 1 || m[*posY - 1][*posX] != 1) {
      printf("DEU RUIM em %c: nao tem pinos suficientes!\n", playCode);
      return 0;
    }

    // Caso valido: fazer a jogada
    else {

      m[*posY][*posX] = 1;     // Espaço vazio recebe o pino
      m[*posY - 1][*posX] = 0; // Pino removido
      m[*posY - 2][*posX] = 0; // Posicao anterior do pino fica vazia
      *posY = *posY - 1;
    }

    // Caso jogada vertical para baixo
  } else if (playCode == 'd') {
    printf("Posicao atual: (%d,%d)\n", *posX, *posY);
    printf("Jogada: %c\n", playCode);
    
    if (*posY + 2 > 6) {
      printf("DEU RUIM em %c: posicao fora!\n", playCode);
      return 0;
    }

    // Nao existir pino que ira comer e pino que sera comido
    else if (m[*posY + 2][*posX] != 1 || m[*posY + 1][*posX] != 1) {
      printf("DEU RUIM em %c: nao tem pinos suficientes!\n", playCode);
      return 0;
      
    } else {
      m[*posY][*posX] = 1;     // Espaço vazio recebe o pino
      m[*posY + 1][*posX] = 0; // Pino removido
      m[*posY + 2][*posX] = 0; // Posicao anterior do pino fica vazia
      *posY = *posY + 1;
    }

    // Caso jogada vertical para esquerda
  } else if (playCode == 'l') {
    printf("Posicao atual: (%d,%d)\n", *posX, *posY);
    printf("Jogada: %c\n", playCode);
    
    if (*posX - 2 < 0) {
      printf("DEU RUIM em %c: posicao fora!\n", playCode);
      return 0;
    }

    // Nao existir pino que ira comer e pino que sera comido
    else if (m[*posY][*posX - 2] != 1 || m[*posY][*posX - 1] != 1) {
      printf("DEU RUIM em %c: nao tem pinos suficientes!\n", playCode);
      return 0;
      
    } else {

      m[*posY][*posX] = 1;     // Espaço vazio recebe o pino
      m[*posY][*posX - 1] = 0; // Pino removido
      m[*posY][*posX - 2] = 0; // Posicao anterior do pino fica vazia
      *posX = *posX - 1;
    }

    // Caso jogada horizontal para a direita
  } else {
    printf("Posicao atual: (%d,%d)\n", *posX, *posY);
    printf("Jogada: %c\n", playCode);
    
    if (*posX + 2 > 6) {
      printf("DEU RUIM em %c: posicao fora!\n", playCode);
      return 0;
    }

    // Nao existir pino que ira comer e pino que sera comido
    else if (m[*posY][*posX + 2] != 1 || m[*posY][*posX + 1] != 1) {
      printf("DEU RUIM em %c: nao tem pinos suficientes!\n", playCode);
      return 0;
      
    } else {

      m[*posY][*posX] = 1;     // Espaço vazio recebe o pino
      m[*posY][*posX + 1] = 0; // Pino removido
      m[*posY][*posX + 2] = 0; // Posicao anterior do pino fica vazia
      *posX = *posX + 1;
    }
  }
  return 1;
}

// play(matriz, posição x, posição y, jogada, contador) --> Realiza as jogadas
// recursivamente, ate finalizar o jogo
void play(int m[7][7], int lastM[7][7], int y, int x, char playCode,
          int *counter) {
  //Caso so reste 1
  if (gameOver(m)) {
    show(m);
    *counter = 31;
    printf("FIM DE JOGO!!\n");

  //Caso da jogada invalida ou passar de 31 jogadas
  } else if (*counter > 31 || !changePin(m, playCode, &y, &x)) {
    if (*counter > 31 || playCode != 'r')
      return;
    else {
      copy(lastM, m);
    }
  }

  else {
    *counter = *counter + 1;
    // printf("Contagem = %d\n", *counter);
    show(m);
    copy(m, lastM);
    play(m, lastM, y, x, 'u', counter);
    play(m, lastM, y, x, 'l', counter);
    play(m, lastM, y, x, 'd', counter);
    play(m, lastM, y, x, 'r', counter);
  }
}

int main() {

  int result;

  // matrix --> #: -1, Vazio: 0, Preenchido: 1
  int mtrx[7][7] = {{-1, -1, 1, 1, 1, -1, -1}, {-1, -1, 1, 1, 1, -1, -1},
                    {1, 1, 1, 1, 1, 1, 1},     {1, 1, 1, 0, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1},     {-1, -1, 1, 1, 1, -1, -1},
                    {-1, -1, 1, 1, 1, -1, -1}};
  int lastMtrx[7][7];
  copy(mtrx, lastMtrx);
  show(mtrx);

  int posX = 3, posY = 3, contador = 0;
 
  play(mtrx,lastMtrx, posY, posX, 'u', &contador);

  return 0;
}