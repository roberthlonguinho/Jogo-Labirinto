#include <stdio.h>
#include <unistd.h>
#define MAX 200

struct Stack {
  char elems[MAX]; // Vetor de elementos da pilha
  int top;         // O Valor do índice do topo
};

void push(struct Stack *pilha, char elem) {
  pilha->top++;                    //(*pilha).top++;
  pilha->elems[pilha->top] = elem; //(*pilha).elems[(*pilha).top] = elem;
}

char pop(struct Stack *pilha) {
  char elem;
  elem = pilha->elems[pilha->top];
  pilha->top--;
  return elem;
}

int labirinto[10][9] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 0, 0, 0, 0, 1, 1, 1},
    {2, 0, 0, 1, 1, 0, 1, 1, 1}, {1, 1, 0, 1, 0, 0, 1, 0, 1},
    {1, 1, 1, 0, 0, 1, 1, 0, 1}, {1, 0, 0, 0, 1, 1, 1, 0, 0},
    {1, 0, 1, 0, 0, 1, 0, 0, 1}, {1, 0, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1}};

void desenhaLabirinto(int labirinto[10][9]) {
  int i, j;
  system("clear");
  for (i = 0; i < 10; i++) {  // Percorrendo as linhas da matriz
    for (j = 0; j < 9; j++) { // Percorrendo as colunas
      if (labirinto[i][j] == 0) {
        printf(" ");
      } else if (labirinto[i][j] == 1) {
        printf("#");
      } else if (labirinto[i][j] == 2) {
        printf("i");
      } else if (labirinto[i][j] == 3) {
        printf(".");
      }else if(labirinto[i][j] == 4){
        printf(" ");
      }
    }
    printf("\n");
  }
}

int main(void) {
  struct Stack pilha;
  char direcao;
  pilha.top = -1; // Inicializando a pilha como vazia
  desenhaLabirinto(labirinto);
  int x = 0, y = 2; // Coordenadas do personagem no labirinto
  while (x < 8) {   // Enquanto não encontrou a saída do labirinto
    if (labirinto[y][x + 1] ==
        0) { // Se o caminho a direita do jogador está livre
      push(&pilha, 'd');
      labirinto[y][x] = 3; // Marcando por onde o personagem passou
      x++;
    } else if (labirinto[y + 1][x] ==
               0) { // Se o caminho abaixo do jogador está livre
      push(&pilha, 'b');
      labirinto[y][x] = 3;
      y++;
    } else if (labirinto[y][x - 1] ==
               0) { // Se o caminho a esquerda do jogador está livre
      push(&pilha, 'e');
      labirinto[y][x] = 3;
      x--;
    } else if (labirinto[y - 1][x] ==
               0) { // Se o caminho acima do jogador está livre
      push(&pilha, 'c');
      labirinto[y][x] = 3;
      y--;
    } else { // Não encontrou nenhum caminho livre a partir da posição atual -
             // Tem que retornar para a posição que estava antes
      direcao = pop(&pilha);
      labirinto[y][x] = 4;
      switch (direcao) {
      case 'd':
        x--;
        break;
      case 'e':
        x++;
        break;
      case 'b':
        y--;
        break;
      case 'c':
        y++;
        break;
      }
    }
    labirinto[y][x] = 2;
    sleep(1); // Espera 1s
    desenhaLabirinto(labirinto);
  }
  printf("UFAAAAAAAA..... Sai do labirinto!!!!!!"); return 0;
}
