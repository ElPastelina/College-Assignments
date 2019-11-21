#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct RegJogador
{
    char tela[10][10], acertos[10][10], nome[30];
    //vidas dos barcos
    int vidas; //21
};


//Inicializa as matrizes zerando os dados dos jogadores.
void inicializar(struct RegJogador *p1, struct RegJogador *p2)
{
    

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            p1->tela[i][j] = ' ';
            p2->tela[i][j] = ' ';
            p1->acertos[i][j] = ' ';
            p2->acertos[i][j] = ' ';
        }
    }
    p1->vidas = 21;
    p2->vidas = 21;
}

// Mostra a tela de determinado jogdador
// X = 0 (mostra a tela de veiculos)
// X = 1 (mostra a tela de acertos)
void mostra_tela(struct RegJogador *t, int x)  
{
    printf("\nX = Linha Y = Coluna");
    printf("\n\n  0  1  2  3  4  5  6  7  8  9");
    for (int i = 0; i < 10; i++)
    {
        printf("\n");
        printf("%d", i);
        for (int j = 0; j < 10; j++)
        {
            if (x == 0)
            {
                printf("[%c]", t->tela[i][j]);
            }
            else if (x == 1)
            {
                printf("[%c]", t->acertos[i][j]);
            }
            else
            {
                printf("Segundo parametro passado incorretamente (somente valido 0 ou 1)");
                system("pause");
            }
        }
    }
    printf("\n\nN = Navio B = Barco S = Submarino D = Destruido A = Agua\n");
}

// Insere os veiculos na tela.
void inserir(struct RegJogador *j)
{
    int x, y, num, erro;

    printf("\n\nDigite seu Nome: ");
    fflush(stdin);
    fgets(j->nome, 30, stdin);

    printf("\nVoce precisa posicionar: 3 - Navios (3 blocos) 4 - Barcos (2 blocos) 4 - Submarinos (1 bloco)\n\n");
    system("pause");
    
    // Posiciona os NAVIOS.
    for (int i = 0; i < 3; i++) 
    {
        erro = 0;
        do // Verifica se a insercao esta correta.
        {
            do //Verifica se a entrada nao exede os limites da tela.
            {
                system("cls");
                mostra_tela(j, 0);
                printf("\n\nNavio %d de 3\nDigite a cordenada X e Y: ", i + 1);
                scanf("%d %d", &x, &y);
                
            }while(x < 0 && x > 10 && y < 0 && y > 10);
            
            printf("\nDigite 1 para horizontal ou 2 para vertical: ");
            scanf("%d", &num);

            if(num == 1)
            {
                if(j->tela[x][y] == ' ' && j->tela[x][y+1] == ' ' && j->tela[x][y-1] == ' ')
                {
                    j->tela[x][y] = 'N';
                    j->tela[x][y+1] = 'N';
                    j->tela[x][y-1] = 'N';
                    erro = 0;
                }
                else
                {
                    printf("\n\nA posicao inserida excede os limites da tela, ou sobrepoem outra unidade.\n");
                    erro = 1;
                    system("pause");
                }
            }
            else if(num == 2)
            {
                if(j->tela[x][y] == ' ' && j->tela[x+1][y] == ' ' && j->tela[x-1][y] == ' ')
                {
                    j->tela[x][y] = 'N';
                    j->tela[x+1][y] = 'N';
                    j->tela[x-1][y] = 'N';
                    erro = 0;
                }
                else
                {
                    printf("\n\nA posicao inserida excede os limites da tela, ou sobrepoem outra unidade.\n");
                    erro = 1;
                    system("pause");
                }
            }
            else
            {
                printf("\nOpcao invalida.\n");
                erro = 1;
                system("pause");
            }
        }while(erro == 1);
    }

    // Posiciona os BARCOS.
    for (int i = 0; i < 4; i++) 
    {
        erro = 0;
        do // Verifica se a insercao esta correta.
        {
            do //Verifica se a entrada nao exede os limites da tela.
            {
                system("cls");
                mostra_tela(j, 0);
                printf("\n\nBarco %d de 4\nDigite a cordenada X e Y: ", i + 1);
                scanf("%d %d", &x, &y);
                
            }while(x < 0 && x > 10 && y < 0 && y > 10);
            
            printf("\nDigite 1 para horizontal ou 2 para vertical: ");
            scanf("%d", &num);

            if(num == 1)
            {
                if(j->tela[x][y] == ' ' && j->tela[x][y+1] == ' ')
                {
                    j->tela[x][y] = 'B';
                    j->tela[x][y+1] = 'B';
                    erro = 0;
                }
                else
                {
                    printf("\n\nA posicao inserida excede os limites da tela, ou sobrepoem outra unidade.\n");
                    erro = 1;
                    system("pause");
                }
            }
            else if(num == 2)
            {
                if(j->tela[x][y] == ' ' && j->tela[x+1][y] == ' ')
                {
                    j->tela[x][y] = 'B';
                    j->tela[x+1][y] = 'B';
                    erro = 0;
                }
                else
                {
                    printf("\n\nA posicao inserida excede os limites da tela, ou sobrepoem outra unidade.\n");
                    erro = 1;
                    system("pause");
                }
            }
            else
            {
                printf("\nOpcao invalida.\n");
                erro = 1;
                system("pause");
            }
        }while(erro == 1);
    }

    // Posiciona os SUBMARINOS.
    for (int i = 0; i < 4; i++) 
    {
        erro = 0;
        do // Verifica se a insercao esta correta.
        {
            do //Verifica se a entrada nao exede os limites da tela.
            {
                system("cls");
                mostra_tela(j, 0);
                printf("\nSubmarino %d de 4\nDigite a cordenada X e Y: ", i + 1);
                scanf("%d %d", &x, &y);
                
            }while(x < 0 && x > 10 && y < 0 && y > 10);

            
            if(j->tela[x][y] == ' ')
            {
                j->tela[x][y] = 'S';
                erro = 0;
            }
            else
            {
                printf("\n\nA posicao inserida excede os limites da tela, ou sobrepoem outra unidade.\n");
                erro = 1;
                system("pause");
            }
        }while(erro == 1);
    }
}

void mete_bala(struct RegJogador *att, struct RegJogador *def, int *fim)
{
    int x, y;

    system("cls");
    printf("\nE a vez de %s", att->nome);

    printf("\nSua tela:\n");
    //mostra_tela(att, 0);

    printf("\n\nSeus acertos:\n");
    mostra_tela(att, 1);
    
    do
    {
        printf("\n\nDigite uma coordenada X e Y para atacar: ");
        scanf("%d %d", &x, &y);
    } while (x < 0 && x > 10 && y < 0 && y > 10);
    
    if(def->tela[x][y] != ' ') // Caso nao atinja a agua
    {
        att->acertos[x][y] = def->tela[x][y];
        def->vidas--;
        def->tela[x][y] = 'D';
        if (def->vidas == 0)
        {
            *fim = 1;
            printf("\n\nVencedor: %s", att->nome);
            system("pause");
        }
    }
    else if (def->tela[x][y] == ' ') // Se atingir a agua
    {
        att->acertos[x][y] = 'A';
    }
    else
    {
        printf("Voce acertou no mesmo lugar mais de uma vez. Melhora essa mira ai.");
    }
}

void main()
{
    int fim = 0;
    struct RegJogador jogador1, jogador2;

    inicializar(&jogador1, &jogador2);
    printf("\n============ BATALHA NAVAL ============\n\n");
    // Faz a insercao dos veiculos dos jogadores
    printf("JOGADOR 1");
    inserir(&jogador1); 
    printf("JOGADOR 2");
    inserir(&jogador2);

    do
    {
        if(fim != 1)
        {
            mete_bala(&jogador1, &jogador2, &fim);
        }
        if(fim != 1)
        {
            mete_bala(&jogador2, &jogador1, &fim);
        }
    } while (fim != 1);
    printf("\nFim de jogo.");
    system("pause");
}