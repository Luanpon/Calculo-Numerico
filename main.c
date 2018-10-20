#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void conversor(int base,int parte_inteira,float parte_fracionaria){

    int quociente;
    int resto;
    int dividendo = parte_inteira;
    int parte_inteira_convertida[80]={};
    int parte_fracionaria_convertida[20]={};
    int indice = 0;
    float parte_fracionaria2 = parte_fracionaria;
    float produto;

    while(dividendo>=base){

        quociente = dividendo/base;
        quociente = (int)quociente;
        resto = dividendo-(quociente*base);
        parte_inteira_convertida[indice]=resto;
        indice = indice+1;
        dividendo=quociente;

    }

    parte_inteira_convertida[indice]=quociente;

    while(indice>=0){
        printf("%i",parte_inteira_convertida[indice]);
        indice=indice-1;
    }

    indice=0;
    printf(".");

    while(parte_fracionaria2>0 && indice<20){

        produto = parte_fracionaria2*base;
        printf("%i",(int)produto);
        parte_fracionaria2 = produto-((int)produto);
        indice = indice+1;

    }

}

void conversao(){

    float decimal;
    int parte_inteira;
    float parte_fracionaria;

    printf(">CONVERSAO\n");
    printf("Digite um número decimal: ");
    scanf("%f",&decimal);
    printf("\n");

    // divisão do decimal em parte inteira e parte fracionária
    parte_inteira = (int)decimal;

    parte_fracionaria = decimal-((int)decimal);

    printf("Decimal: %f\n",decimal);
    printf("Binario: ");
    conversor(2,parte_inteira,parte_fracionaria);
    printf("\n");
    printf("Octal: ");
    conversor(8,parte_inteira,parte_fracionaria);
    printf("\n");
    printf("Hexadecimal: ");
    conversor(16,parte_inteira,parte_fracionaria);
    printf("\n");

}


float calcula_Ls(int grau,int coeficientes[]){

    int n=grau;
    int an,b,k,i;
    float ban,nk;

    b = 0;
    k = 0;
    an = coeficientes[n];

    for(i=grau;i>=0;i--){

        if(coeficientes[i]<b){
            b=coeficientes[i];
        }

        if(coeficientes[i]<0 && i>k){
            k=i;
        }

    }

    b = b*(-1);
    ban = (float)b/(float)an;
    nk = n-k;

    float L = 1 + pow(ban,1/nk);

    return L;

}

void lagrange(int grau,int coeficientes[]){

    int i,j;
    int coeficientes2[grau+1];
    float Ls[4];

    // calculo do L ---------------------------------------------------------------------------------------------------------

    for(i=grau;i>=0;i--){

        coeficientes2[i] = coeficientes[i];

    }

    if(coeficientes2[grau]<0){

        for(i=grau;i>=0;i--){

            coeficientes2[i] = coeficientes2[i] * (-1);

        }

    }

    Ls[0] = calcula_Ls(grau,coeficientes2);

    // calculo do L1 -------------------------------------------------------------------------------------------

    j=0;

    for(i=grau;i>=0;i--){

        coeficientes2[i] = coeficientes[j];
        j = j+1;

    }

    if(coeficientes2[grau]<0){

        for(i=grau;i>=0;i--){

            coeficientes2[i] = coeficientes2[i] * (-1);

        }

    }

    Ls[1] = calcula_Ls(grau,coeficientes2);

    // calculo do L2 -------------------------------------------------------------------------------------------

    for(i=grau;i>=0;i--){

        coeficientes2[i] = coeficientes[i];

        if(i%2!=0){

            coeficientes2[i] = coeficientes2[i] * (-1);

        }

    }

    if(coeficientes2[grau]<0){

        for(i=grau;i>=0;i--){

            coeficientes2[i] = coeficientes2[i] * (-1);

        }

    }

    Ls[2] = calcula_Ls(grau,coeficientes2);

    // calculo do L3 -------------------------------------------------------------------------------------------

    j=0;

    for(i=grau;i>=0;i--){

        coeficientes2[i] = coeficientes[j];

        if(i%2!=0){

            coeficientes2[i] = coeficientes2[i] * (-1);

        }

        j = j+1;

    }

    if(coeficientes2[grau]<0){

        for(i=grau;i>=0;i--){

            coeficientes2[i] = coeficientes2[i] * (-1);

        }

    }

    Ls[3] = calcula_Ls(grau,coeficientes2);

    //printf("\nLs: %f ; %f ; %f ; %f ",Ls[0],Ls[1],Ls[2],Ls[3]);

    printf("\n Intervalo onde se encontram as raizes reais positivas:");
    printf("\n %.6f <= X+ <= %.6f ",1/Ls[1],Ls[0]);
    printf("\n\n Intervalo onde se encontram as raizes reais negativas:");
    printf("\n %.6f <= X- <= %.6f ",Ls[2]*(-1),(-1/Ls[3]));

}


void equacao(){

    int grau=1;
    int i;

    printf("Digite o grau da equacao: ");
    scanf("%i",&grau);

    int coeficientes[grau+1];

    for(i=grau;i>=0;i--){

        printf("\nDigite o coeficiente a%i: ",i);
        scanf("%i",&coeficientes[i]);

        if((i==grau) && (coeficientes[i]<=0)){

            printf("\nCoeficiente an digitado eh menor que zero. Tente novamente com outro valor.\n");
            i = grau + 1;

        }

        if((i==0) && (coeficientes[i]==0)){

            printf("\nCoeficiente a0 digitado eh igual a zero. Tente novamente com outro valor.\n");
            i = i + 1;

        }

    }

    lagrange(grau,coeficientes);

}


int main()
{
    // variável para armazenar a escolha do usuário no menu
    char escolha[2];

    // menu principal
    printf("******************\n");
    printf("* MENU PRINCIPAL *\n");
    printf("******************\n");
    printf("\n");
    printf("C - Conversao\n");
    printf("S - Sistema Linear\n");
    printf("E - Equacao Algebrica\n");
    printf("F - Finalizar\n");
    printf("\n");
    printf("Escolha uma opcao: ");

    //recebendo a entrada do usuário e armazenando na variável escolha
    gets(escolha);
    printf("\n");

    //verificando se a entrada digitada pelo usuário é válida ou não e executando as funções de acordo
    // com a escolha do usuário, caso seja válida
    if(strcmp(escolha,"c")==0 || strcmp(escolha,"C")==0){

        conversao();
        printf("\n");
        printf("\n");
        main();

    }
    if(strcmp(escolha,"e")==0 || strcmp(escolha,"E")==0){

        equacao();
        printf("\n");
        printf("\n");

    }
    else{
        printf("Opcao invalida. Tente novamente.");
        printf("\n");
        printf("\n");
        main();
    }

    //system("pause");
    return 0;
}
