#include <stdio.h>
#include <stdlib.h>
// re-do the main saving the game state into a file
// system("cls") to clean the screen

struct Reg{
   char tela[3][3];
   int proximoJogador, numJogadas, fim;
};

void display(struct Reg *p){

   system("cls");
   printf("   0   1   2   Y\n");
   printf(" 0 %c | %c | %c \n",p->tela[0][0],p->tela[0][1],p->tela[0][2]);
   printf("  ---|---|--- \n ");
   printf("1 %c | %c | %c \n",p->tela[1][0],p->tela[1][1],p->tela[1][2]);
   printf("  ---|---|--- \n ");
   printf("2 %c | %c | %c \n",p->tela[2][0],p->tela[2][1],p->tela[2][2]);

   printf("X\n");

}

void teste_trinca(char c, struct Reg *temp){

   // horizontal
   if (temp->tela[0][0] == c && temp->tela[0][1] == c && temp->tela[0][2] == c){
      printf("%c VENCEU!\n", c);
      temp->fim = 1;
   }
   if (temp->tela[1][0] == c && temp->tela[1][1] == c && temp->tela[1][2] == c){
      printf("%c VENCEU!\n", c);
      temp->fim = 1;
   }
   if (temp->tela[2][0] == c && temp->tela[2][1] == c && temp->tela[2][2] == c){
      printf("%c VENCEU!\n", c);
      temp->fim = 1;
   }
   // vertical
   if (temp->tela[0][0] == c && temp->tela[1][0] == c && temp->tela[2][0] == c){
      printf("%c VENCEU!\n", c);
      temp->fim = 1;
   }
   if (temp->tela[0][1] == c && temp->tela[1][1] == c && temp->tela[2][1] == c){
      printf("%c VENCEU!\n", c);
      temp->fim = 1;
   }
   if (temp->tela[0][2] == c && temp->tela[1][2] == c && temp->tela[2][2] == c){
      printf("%c VENCEU!\n", c);
      temp->fim = 1;
   }
   // diagonal
   if (temp->tela[0][0] == c && temp->tela[1][1] == c && temp->tela[2][2] == c){
      printf("%c VENCEU!\n", c);
      temp->fim = 1;
   }
   if (temp->tela[2][0] == c && temp->tela[1][1] == c && temp->tela[0][2] == c){
      printf("%c VENCEU!\n", c);
      temp->fim = 1;
   }
}

void play0(int *x, int *y, struct Reg *p){

   display(p);
   printf("Jogador 1: Digite a coordenada **X**: ");
   scanf("%d",&*x);
   printf("Jogador 1: Digite a coordenada **Y**: ");
   scanf("%d",&*y);
}

void play1(int *x, int *y, struct Reg *p){

   display(p);      
   printf("Jogador 2: Digite a coordenada **X**: ");
   scanf("%d",&*x);
   printf("Jogador 2: Digite a coordenada **Y**: ");
   scanf("%d",&*y);
}

// Funcao para salvar o estado do jogo.
void salvarJogo(struct Reg *temp){
   char x;

   FILE *file;

   printf("Salvar e sair? [s]/[n]\n");
   fflush(stdin);
   scanf("%c", &x);

   if(x == 's' || x == 'S'){
      if((file = fopen("log.bin", "wb")) != NULL){
         fwrite(temp, sizeof(struct Reg), 1, file);
         fclose(file);
         exit(1);
      }
      else{
         printf("Erro ao abrir ao salvar o jogo.\n");
         exit(1);
      }
   }
}

// funcao para zerar o jogo.
void zerarJogo(struct Reg *temp){

   for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
         temp->tela[i][j] = ' ';

   temp->proximoJogador = 0;
   temp->numJogadas = 0;
}

int main(){

   int x, y, fim = 0;
   struct Reg playerReg;
   FILE *fptr;

   //playerReg = (struct Reg *) malloc (sizeof(struct Reg));

   // Cria o arquivo caso nao exista.
   if ((fptr = fopen("log.bin", "rb")) == NULL){
      if ((fptr = fopen("log.bin", "wb")) != NULL){
         fptr = fopen("log.bin", "wb");
         zerarJogo(&playerReg);
         fwrite(&playerReg, sizeof(struct Reg), 1, fptr);
      }
      else{
         printf("Erro ao criar o arquivo.\n");
      }  
   }
   else{
      fptr = fopen("log.bin", "rb");
      fread(&playerReg, sizeof(struct Reg), 1, fptr);
      printf("%d :: %d\n", playerReg.proximoJogador, playerReg.fim);
   }

   while (playerReg.fim == 0){

      if (playerReg.fim == 0 && playerReg.numJogadas < 9){
         //Virifica o jogador
         if (playerReg.proximoJogador == 0){
            play0(&x, &y, &playerReg);
            // valida as cordenada.
            if (playerReg.tela[x][y] == ' '){
               playerReg.tela[x][y] = 'X';
               playerReg.numJogadas++;
               playerReg.proximoJogador = 1;
               display(&playerReg);
               // Verifica o numero de jogadas antes de testar.
               if (playerReg.numJogadas >= 5){
                  teste_trinca('X', &playerReg);
               }
            }
            else{
               fflush(stdin);
               printf("Posicao invalida, escolha outra.\n");
               getchar();
            }
            // Salva o jogo caso nao tenha acabado.
            if (playerReg.fim != 1){
               salvarJogo(&playerReg);
            }
         }

         //Virifica o jogador
         if (playerReg.fim == 0 && playerReg.proximoJogador == 1){
            play1(&x, &y, &playerReg);
            // valida as cordenada.
            if (playerReg.tela[x][y] == ' '){
               playerReg.tela[x][y] = 'O';
               playerReg.numJogadas++;
               playerReg.proximoJogador = 0;
               display(&playerReg);
               // Verifica o numero de jogadas antes de testar.
               if (playerReg.numJogadas >= 5){
                  teste_trinca('O', &playerReg);
               }
            }
            else{
               fflush(stdin);
               printf("Posicao invalida, escolha outra.\n");
               getchar();
            }
            // Salva o jogo caso nao tenha acabado.
            if (playerReg.fim != 1){
               salvarJogo(&playerReg);
            }
         }
      }
   }
   printf("Fim de jogo.\n");
   
   if (playerReg.fim == 1){
      // Zera o arquivo ao acabar o jogo.
      zerarJogo(&playerReg);
      fptr = fopen("log.bin", "wb");
      fwrite(&playerReg, sizeof(struct Reg), 1, fptr);
      fclose(fptr);
   }
}