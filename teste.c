#include <stdio.h>

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

// movePin(matriz, codigo, posição x, posição y) --> realiza a jogada
// solicitada e retorna um valor booleano se foi concluida(1) ou nao(0)
int movePin(int m[7][7], char playCode, int posY, int posX) {

  // Caso jogada vertical para cima
  if (playCode == 'u') {
    // printf("Posicao atual: (%d,%d)\n", posX, posY);
    // printf("Jogada: %c\n", playCode);
    // Posicao fora do tabuleiro
    if (posY - 2 < 0) {
     // printf("DEU RUIM em %c: posicao fora!\n", playCode);
      return 0;
    }

    // Nao existir pino que ira comer e pino que sera comido
    else if (m[posY - 2][posX] != 1 || m[posY - 1][posX] != 1) {
     // printf("DEU RUIM em %c: nao tem pinos suficientes!\n", playCode);
      return 0;
    }

    // Caso valido: fazer a jogada
    else {

      m[posY][posX] = 1;     // Espaço vazio recebe o pino
      m[posY - 1][posX] = 0; // Pino removido
      m[posY - 2][posX] = 0; // Posicao anterior do pino fica vazia
      //posY = posY - 1;
    }

    // Caso jogada vertical para baixo
  } else if (playCode == 'd') {
    // printf("Posicao atual: (%d,%d)\n", posX, posY);
    // printf("Jogada: %c\n", playCode);

    if (posY + 2 > 6) {
    //  printf("DEU RUIM em %c: posicao fora!\n", playCode);
      return 0;
    }

    // Nao existir pino que ira comer e pino que sera comido
    else if (m[posY + 2][posX] != 1 || m[posY + 1][posX] != 1) {
     // printf("DEU RUIM em %c: nao tem pinos suficientes!\n", playCode);
      return 0;

    } else {
      m[posY][posX] = 1;     // Espaço vazio recebe o pino
      m[posY + 1][posX] = 0; // Pino removido
      m[posY + 2][posX] = 0; // Posicao anterior do pino fica vazia
      //posY = posY + 1;
    }

    // Caso jogada vertical para esquerda
  } else if (playCode == 'l') {
    // printf("Posicao atual: (%d,%d)\n", posX, posY);
    // printf("Jogada: %c\n", playCode);

    if (posX - 2 < 0) {
     // printf("DEU RUIM em %c: posicao fora!\n", playCode);
      return 0;
    }

    // Nao existir pino que ira comer e pino que sera comido
    else if (m[posY][posX - 2] != 1 || m[posY][posX - 1] != 1) {
     // printf("DEU RUIM em %c: nao tem pinos suficientes!\n", playCode);
      return 0;

    } else {

      m[posY][posX] = 1;     // Espaço vazio recebe o pino
      m[posY][posX - 1] = 0; // Pino removido
      m[posY][posX - 2] = 0; // Posicao anterior do pino fica vazia
      //posX = posX - 1;
    }

    // Caso jogada horizontal para a direita
  } else {
    // printf("Posicao atual: (%d,%d)\n", posX, posY);
    // printf("Jogada: %c\n", playCode);

    if (posX + 2 > 6) {
      //printf("DEU RUIM em %c: posicao fora!\n", playCode);
      return 0;
    }

    // Nao existir pino que ira comer e pino que sera comido
    else if (m[posY][posX + 2] != 1 || m[posY][posX + 1] != 1) {
      //printf("DEU RUIM em %c: nao tem pinos suficientes!\n", playCode);
      return 0;

    } else {

      m[posY][posX] = 1;     // Espaço vazio recebe o pino
      m[posY][posX + 1] = 0; // Pino removido
      m[posY][posX + 2] = 0; // Posicao anterior do pino fica vazia
      //posX = posX + 1;
    }
  }
  return 1;
}

// movePin(matriz, codigo, posição x, posição y) --> realiza a jogada
// solicitada e retorna um valor booleano se foi concluida(1) ou nao(0)
void revertPlay(int m[7][7], char playCode, int posY, int posX) {

  // Caso jogada vertical para cima
  if (playCode == 'u') {
      if(m[posY][posX]==1)m[posY][posX] = 0;     
      if(posY-1>0 && m[posY - 1][posX]==0)m[posY - 1][posX] = 1; 
      if(posY-2>0 && m[posY - 2][posX]==0)m[posY - 2][posX] = 1; 
    }

    // Caso jogada vertical para baixo
    else if (playCode == 'd') {
    
      if(m[posY][posX]==1)m[posY][posX] = 0;     
      if(posY+1<6 && m[posY + 1][posX]==0)m[posY + 1][posX] = 1; 
      if(posY+2<6 && m[posY + 2][posX]==0)m[posY + 2][posX] = 1; 
      //posY = posY + 1;
    

    // Caso jogada vertical para esquerda
  } else if (playCode == 'l') {
      if(m[posY][posX]==1)m[posY][posX] = 0;     
      if(posX-1>0 && m[posY][posX-1]==0)m[posY][posX - 1] = 1; 
      if(posX-2>0 && m[posY][posX-2]==0)m[posY][posX - 2] = 1; 

    // Caso jogada horizontal para a direita
  } else {
      if(m[posY][posX]==1)m[posY][posX] = 0;     
      if(posX+1<6 && m[posY][posX+1]==0)m[posY][posX + 1] = 1; 
      if(posX+2<6 && m[posY][posX+2]==0)m[posY][posX + 2] = 1; 
      //posX = posX + 1;
    
  }
}


// // isWrongPlay(matriz, matriz de espaços) -> analisa se existe alguma jogada
// // possivel na atual
// //  configuracao da matriz
// int isWrongPlay(int m[7][7], int spaces[32][2], int size) {
//   for (int idx = 0; idx < size; idx++) {
//     int y = spaces[idx][0];
//     int x = spaces[idx][1];
//     if (y - 2 > 0 && m[y - 2][x] == 1 && m[y - 1][x] == 1)
//       return 0; // para cima
//     else if (y + 2 > 0 && m[y + 2][x] == 1 && m[y + 1][x] == 1)
//       return 0; // para baixo
//     else if (x - 2 > 0 && m[y][x - 2] == 1 && m[y][x - 1] == 1)
//       return 0; // para esquerda
//     else if (x + 2 > 0 && m[y][x + 2] == 1 && m[y][x + 1] == 1)
//       return 0; // para direita
//   }
//   return 1;
// }

// getSpaces(matriz) -> Retorna uma matriz com as coordenadas dos espaços
int getSpaces(int m[7][7], int spaces[][2]) {
  int idx = 0;
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (m[i][j] == 0) {
        spaces[idx][0] = i;
        spaces[idx][1] = j;
        idx++;
      }
    }
  }
  return idx;
}



// play(matriz, posição x, posição y, jogada, contador) --> Realiza as jogadas
// recursivamente, ate finalizar o jogo
void play(int m[7][7], int y, int x, char playCode,
          int *counter, int *validation) {
  int spaces[32][2];
  int tam;
  //printf("Espacos = %d\n",tam);
  // Caso so reste 1
  if (gameOver(m)) {
    show(m);
    *counter = 31;
    printf("FIM DE JOGO!!\n");    
  } 
  
  // Caso de passar de 31 jogadas
  else if (*counter > 31 || *counter<0)
    return;

  else if(!movePin(m,playCode, y, x)){
    // printf("#########JOGADA INVALIDA!!#########\n");
    // show(m);
    // printf("###################################\n");
   
    //printf("Retornando para o anterior!\n");
    //copy(lastM, m);
    //show(m);
    
    return;
  } 
      
  else {
    tam = getSpaces(m, spaces);
    *counter = *counter + 1;
    *validation = 1;
    // printf("Contagem = %d\n", *counter);
    // printf("Posicao atual: (ln %d,col %d)\n", y, x);
    // printf("Jogada: %c\n", playCode);
    //show(m);
    // printf("Jogada Válida! salvando...\n");
    // copy(m, lastM);
    // printf("last!--------------------\n");
    // show(lastM);
    // printf("--------------------\n");
    for(int idx = 0; idx < tam; idx++){
      play(m, spaces[idx][0], spaces[idx][1], 'u', counter,validation);
      if(!(*validation)) {
        revertPlay(m,'u',spaces[idx][0], spaces[idx][1]);
       // printf("Revertendo jogada %c\n",playCode);
        //show(m);
        *counter = *counter-1;

      }
      play(m, spaces[idx][0], spaces[idx][1], 'l', counter,validation);
      if(!(*validation)) {
        revertPlay(m,'l',spaces[idx][0], spaces[idx][1]);
       // printf("Revertendo jogada %c\n",playCode);
        //show(m);
        *counter = *counter-1;

      }
      play(m, spaces[idx][0], spaces[idx][1], 'd', counter,validation);
      if(!(*validation)) {
        revertPlay(m,'d',spaces[idx][0], spaces[idx][1]);
       // printf("Revertendo jogada %c\n",playCode);
        //show(m);
        *counter = *counter-1;

      }
      play(m, spaces[idx][0], spaces[idx][1], 'r', counter,validation);
      if(!(*validation)) {
        revertPlay(m,'r',spaces[idx][0], spaces[idx][1]);
       // printf("Revertendo jogada %c\n",playCode);
        //show(m);
        *counter = *counter-1;

      }
    }
    *validation = 0;
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

  
  show(mtrx);
 
  // int lastMtrx[7][7];
  // copy(mtrx, lastMtrx);
  // show(mtrx);

  int posX = 3, posY = 3, contador = 0, isChecked=1;

  play(mtrx, posY, posX, 'u', &contador,&isChecked);
  if(contador >= 31) printf("\n\nJogo encerrado por excesso de tentativas!!\n\n");

  return 0;
}
