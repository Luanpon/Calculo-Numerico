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

    printf("\n  Intervalo onde se encontram as raizes reais positivas:");
    printf("\n  %.6f <= X+ <= %.6f ",1/Ls[1],Ls[0]);
    printf("\n\n  Intervalo onde se encontram as raizes reais negativas:");
    printf("\n  %.6f <= X- <= %.6f ",Ls[2]*(-1),(-1/Ls[3]));

}

int bolzano(float a,float b,int coeficientes[],int grau){

    float pa = 0;
    float pb = 0;
    int i;

    for(i=grau;i>=0;i--){

        pa = pa + ((float)coeficientes[i] * (float)pow(a,i));
        pb = pb + ((float)coeficientes[i] * (float)pow(b,i));

    }

    if((pa*pb)<0){

        return 1;

    }
    if((pa*pb)>0){

        return 0;

    }

}

void bissecao(float a, float b,int coeficientes[],int grau){

    double pa,pb,pm,m,erro,a2,b2;
    int i,j;

    j=0;
    a2 = a;
    b2 = b;

    erro = (double)(b2-a2)/(double)2;

    while(j<1001 && erro>=pow(10,-8)){

        pa = 0;
        pb = 0;
        pm = 0;
        m = (b2+a2)/(double)2;
        erro = (b2-a2)/(double)2;

        for(i=grau;i>=0;i--){

            pa = pa + ((double)coeficientes[i] * (double)pow(a2,i));
            pb = pb + ((double)coeficientes[i] * (double)pow(b2,i));

        }

        for(i=grau;i>=0;i--){

            pm = pm + ((double)coeficientes[i] * (double)pow(m,i));

        }

        if(pa*pm>0){
            a2=m;
        }
        if(pa*pm<0){
            b2=m;
        }
        if(pa*pm==0){
            j = 10000;
        }

        j = j+1;

    }

    printf("\n\n Raiz aproximada do polinomio: %.30lf \n Valor do erro: %.30lf",m,erro);

}

void equacao(){

    int grau=1;
    int i,j,contador;
    float a,b;

    printf(" Digite o grau da equacao: ");
    scanf("%i",&grau);

    int coeficientes[grau+1];

    for(i=grau;i>=0;i--){

        printf("\n  Digite o coeficiente a%i: ",i);
        scanf("%i",&coeficientes[i]);

        if((i==grau) && (coeficientes[i]<=0)){

            printf("\n  ERRO: Coeficiente an digitado eh menor que zero. Tente novamente com outro valor.\n");
            i = grau + 1;

        }

        if((i==0) && (coeficientes[i]==0)){

            printf("\n  ERRO: Coeficiente a0 digitado eh igual a zero. Tente novamente com outro valor.\n");
            i = i + 1;

        }

        if(i==0){

            contador = 0;

            for(j=grau;j>=0;j--){

                if(coeficientes[j]>=0){

                    contador = contador + 1;

                }

            }

            if(contador==grau+1){

                printf("\n  ERRO: Todos os coeficientes digitados sao positivos. Necessario haver pelo menos um coeficiente negativo. Tente novamente com outros valores.\n");
                i = grau+1;

            }

        }

    }

    // calculo dos limites das raízes usando o teorema de lagrange

    printf("\n -> Teorema de Lagrange: \n");

    lagrange(grau,coeficientes);

    //verificando se a quantidade de raízes é ímpar ou par usando o Teorema de Bolzano

    printf("\n\n -> Teorema de Bolzano: \n");
    printf("\n  Escolha um intervalo");
    printf("\n\n   Digite o primeiro valor do intervalo: ");
    scanf("%f",&a);
    printf("   Digite o ultimo valor do intervalo: ");
    scanf("%f",&b);

    if(bolzano(a,b,coeficientes,grau)==0){

        printf(" \n  O polinomio possui uma quantidade par de raizes reais no intervalo ]%f,%f[",a,b);

    }
    if(bolzano(a,b,coeficientes,grau)==1){

        printf(" \n  O polinomio possui uma quantidade impar de raizes reais no intervalo ]%f,%f[",a,b);

        printf("\n\n -> Metodo da Bissecao:");

        bissecao(a,b,coeficientes,grau);

    }



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
