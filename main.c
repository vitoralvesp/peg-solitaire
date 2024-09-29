/*
 *
 * Lucas Pires de Camargo Sarai - 10418013
 * Vitor Alves Pereira - 10410862
 * 
 * Ciência da Computação
 * 3D
 * PAA2
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_MATRIZES (31)
#define TAMANHO_MATRIZ (7)

//---------PILHA---------
typedef struct {
    int matrizes[MAX_MATRIZES][TAMANHO_MATRIZ][TAMANHO_MATRIZ]; 
    int contador; 
} Pilha;

// Criar uma pilha 
Pilha* create() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    p->contador = -1; // Pilha começa vazia
    return p;
}

//Destruir a pilha (liberar memória)
void destroy(Pilha *p) {
    if (p != NULL) {
        free(p);
    }
}

// Verificar se a pilha esta vazia
int isEmpty(Pilha *p) {
    return p->contador == -1;
}

// Verificar se a pilha está cheia
int isFull(Pilha *p) {
    return p->contador == MAX_MATRIZES - 1;
}

// Empilhar uma matriz 
void push(Pilha *p, int matriz[TAMANHO_MATRIZ][TAMANHO_MATRIZ]) {
    if (isFull(p)) {
        printf("Erro: Pilha cheia.\n");
        return;
    }
    p->contador++;
    for (int i = 0; i < TAMANHO_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_MATRIZ; j++) {
            p->matrizes[p->contador][i][j] = matriz[i][j];
        }
    }
}

//Desempilhar uma matriz
void pop(Pilha *p) {
    if (isEmpty(p)) {
        printf("Erro: Pilha vazia.\n");
        return;
    }
    p->contador--;
}

// Acessar a matriz no topo da pilha
int (*top(Pilha *p))[TAMANHO_MATRIZ] {
    if (isEmpty(p)) {
        printf("Erro: Pilha vazia.\n");
        return NULL;
    }
    return p->matrizes[p->contador];
}

int size(Pilha *p) {
  return p -> contador+1;
}


//-----------------------

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
int play(int m[7][7], Pilha *p, int y, int x, char playCode) {
    int spaces[32][2];
    int tam;

    // Fim de jogo valido
    if (gameOver(m)) {
        printf("Total = %d\n", size(p));
        while (!isEmpty(p)) {
            printf("-----------------------\n");
            show(top(p));
            printf("-----------------------\n");
            pop(p);
        }
        return 1;
    }

    // Tenta executar a jogada atual
    if (!movePin(m, playCode, y, x)) {
        return 0;  // Falha ao mover o pino
    }

    // Jogada válida, empilhar o estado atual do tabuleiro
    push(p, m);

    // Obtém todos os espaços vazios para novas jogadas
    tam = getSpaces(m, spaces);
    int aux;

    // Para cada espaço vazio, tenta as 4 direções possíveis ('u', 'l', 'd', 'r')
    for (int idx = 0; idx < tam; idx++) {
        // Tentar jogada para cima
        aux = play(m, p, spaces[idx][0], spaces[idx][1], 'u');
        if (aux == 1) return 1;  // Jogo concluído
        else if (aux == -1) revertPlay(m, 'u', spaces[idx][0], spaces[idx][1]);

        // Tentar jogada para esquerda
        aux = play(m, p, spaces[idx][0], spaces[idx][1], 'l');
        if (aux == 1) return 1;  // Jogo concluído
        else if (aux == -1) revertPlay(m, 'l', spaces[idx][0], spaces[idx][1]);

        // Tentar jogada para baixo
        aux = play(m, p, spaces[idx][0], spaces[idx][1], 'd');
        if (aux == 1) return 1;  // Jogo concluído
        else if (aux == -1) revertPlay(m, 'd', spaces[idx][0], spaces[idx][1]);

        // Tentar jogada para direita
        aux = play(m, p, spaces[idx][0], spaces[idx][1], 'r');
        if (aux == 1) return 1;  // Jogo concluído
        else if (aux == -1) revertPlay(m, 'r', spaces[idx][0], spaces[idx][1]);
    }

    // Se não encontrou solução, remover o estado atual da pilha
    pop(p);
    return -1;  // Fim de jogo inválido
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
  Pilha *p = create();

  push(p,mtrx);

  show(top(p));
  int posX = 3, posY = 3;

  //Caso encerre corretamente, exiba
  play(mtrx,p,posY,posX,'u');
    
  return 0;
}