#include <stdio.h>

// show(matriz) --> demonstra o conteúdo da matriz
void show(int mtrx[7][7]) {

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {

            if (mtrx[i][j] == -1) printf("#");
            else if (mtrx[i][j] == 1) printf("o");
            else printf(" ");

        }

        printf("\n");

    }

    printf("\n");

}

//game_over(matrix[7][7]) --> verifica se o jogo já se encerrou
//Percorre a matriz e verifica se existe apenas um pino e na posicao central
int gameOver(int m[7][7]){
  if(m[4][4] == 0) return 0;
  else{
    for(int i = 0; i< 7; i++){
      for(int j = 0; j<7;j++){
        //Pular posicao central ou posicoes invalidas
        if((i == 4 && j == 4 )||(m[i][j]==-1)) continue;
        else if(m[i][j] == 1) return 0;
      }
    }
  }
  return 1;
}

/* Funcao desnecessaria??*/
/*
//isWrongPlay(matrix[7][7], posicao X, posicao Y) --> Retorna valor booelano indicando se eh uma jogada valida ou nao

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

// //changePin(matriz, codigo, posição x, posição y) --> realiza a jogada solicitada e retorna um valor booleano se foi concluida(1) ou nao(0)
// int changePin(int m[7][7], int playCode, int posX, int posY){
  
// }

// // play(matriz, posição x, posição y) --> busca recursivamente como deixar somente o
// // pino central como 1 e o restante, com excessão do -1, como 0.  
// void play(int m[7][7]) {
//   if(gameOver(m)) {
//      show(m);
//      return;
//    }else if(wrongPlay(m,i,j)) return;
//    else{
//
//
//
//    }    
//}


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