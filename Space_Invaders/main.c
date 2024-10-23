#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tiroX[3]={0, 0, 0}, tiroY[3]={0, 0, 0};
int monstrosX[6]={0, 0, 0, 0, 0, 0}, monstrosY[6]={0, 0, 0, 0, 0, 0};

int main(){
    srand(time(NULL));

    int opc;
    system("cls");

    printf("\n Space Invaders");

    printf("\n1.Jogar | 2.Sair");

    printf("\n\nDigite: ");
    scanf("%i", &opc);

    LimparBuffer();

    switch(opc){
    case 1:
        jogo(7, 3);
        break;
    case 2:
        break;
    default:
        system("cls");
        printf("\nOpcao nao encontrada\n");
        system("pause");
        main();
    }
}

void LimparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void jogo(int jX, int vida){
    system("cls");

    char opc, map[15][15];
    int i=0,j=0;

    //vida
    if(vida<=0){
        system("cls");
        printf("\n\tGAME OVER\n");
        exit(0);
    }

    //bala vs monstror
    for(i=0;i<6;i++){
        for(j=0;j<3;j++){
            if(monstrosX[i]== tiroX[j] && monstrosY[i]== tiroY[j] || monstrosX[i]== tiroX[j] && monstrosY[i]== tiroY[j-1]){
                monstrosX[i]=0;
                monstrosY[i]=0;

                tiroX[j]=0;
                tiroY[j]=0;
            }
        }
    }

    //bala
    for(i=0;i<3;i++){
        if(tiroY[i]<=13 && tiroY[i] >= 1){
            tiroY[i]--;
        }
        if(tiroY[i]<1){
            tiroX[i]=0;
            tiroY[i]=0;
        }
    }

    //Monstro
    for(i=0;i<6;i++){
        int chanc = (rand() %100)+1;

        if(chanc >= 75){
            int num_alea = rand() %6;
            int varia = (rand() %2)+1;


            if(monstrosX[num_alea]==0){
                monstrosX[num_alea]=(num_alea*2)+varia;
                monstrosY[num_alea]=1;
            }else if(monstrosY[i]!=0){
                monstrosY[i]++;
            }
            if(monstrosY[i]>=13){
                vida--;

                monstrosX[i]=0;
                monstrosY[i]=0;
            }
        }
    }

    for(j=0;j<15;j++){
        for(i=0;i<15;i++){
            map[i][j]=' ';

            map[jX][13]='H';

            map[monstrosX[0]][monstrosY[0]]='W';
            map[monstrosX[1]][monstrosY[1]]='W';
            map[monstrosX[2]][monstrosY[2]]='W';
            map[monstrosX[3]][monstrosY[3]]='W';
            map[monstrosX[4]][monstrosY[4]]='W';
            map[monstrosX[5]][monstrosY[5]]='W';

            map[tiroX[0]][tiroY[0]]='.';
            map[tiroX[1]][tiroY[1]]='.';
            map[tiroX[2]][tiroY[2]]='.';

            map[0][j]='#';
            map[14][j]='#';
            map[14][j]='#';
            map[i][0]='#';
            map[i][14]='#';

            printf("%c", map[i][j]);
        }
        printf("\n");
    }

    printf("Vida: %d/3", vida);

    printf("\nAcoes:\n|W| Atirar.\n|A| Andar para esquerda.\n|S| Ficar parado.\n|D| Andar para direita.\n|G| Sair.");

    printf("\n\nDigite: ");
    scanf("%c", &opc);

    LimparBuffer();

    if(opc >= 'a' && opc <= 'z'){
        opc -= 32;
    }

    switch(opc){
    case 'A':
        if(jX != 1){
            jX--;;
        }
        jogo(jX, vida);
    break;
    case 'D':
        if(jX != 13){
            jX++;
        }
        jogo(jX, vida);
    break;
    case 'S':
        jogo(jX, vida);
    break;
    case 'W':
        for(i=0;i<3;i++){
            if(tiroY[i]==0){
                tiroY[i]=13;
                tiroX[i]=jX;
                jogo(jX, vida);
            }
        }
        printf("\n\n\tRecarregando\n");
        system("pause");
        jogo(jX, vida);
    break;
    case 'G':
        system("cls");
        printf("\n\tSaindo...\n");
        exit(0);
    break;
    default:
        system("cls");
        printf("\nOpcao nao encontrada\n");
        system("pause");
        jogo(jX, vida);
    }
}
