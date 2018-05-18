#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long int exp_modular(long int base, long int e, long int n)
{
    long int c, i;
    if (n == 1)
    {
        return 0;
    }
    c = 1;
    for(i = 0; i < e; i++)
    {
        c = (c * base) % n;
    }
    return c;
}

int primos(int i)
{
    int x, naoprimo;
    x = 2;
    naoprimo = 0;
    while(x<=i/2 && !naoprimo)
    {
        if(i % x == 0)
            {
                naoprimo = 1;
            }
        else
            {
                x++;
            }
    }
        if(naoprimo || i == 1 || i == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
}

int mdc(int a, int b)
{
	if(b==0)
	{
		return("%d\n", a);
	}
	else
	{
		return mdc(b, a%b);
	}
}


int main()
{
    int x = 5, y;
    int invalido;
	FILE* cpub;
	long int p, q, e;
    while(x != 4)
    {
        printf("\nGerar chave publica: digite 1\nCriptografar: digite 2\nDescriptografar: digite 3\nEncerrar aplicacao: digite 4\n");

        scanf("%d", &x);

        if(x == 1)
        {
            invalido = 1;

            while(invalido)
            {
                printf("\nDigite 'p', 'q' e 'e'\n");

                scanf("%ld%ld%ld", &p, &q, &e);
                if (primos(p) == 0 || primos(q) == 0) printf("Valor digitado invalido\n");
                else
                {
                    if((e<1)||(e>((p - 1)*(q - 1)))) printf("Valor digitado invalido\n");
                    else
                    {
                        if(mdc(e, ((p-1)*(q-1))) != 1) printf("Valor digitado invalido\n");
                        else
                        {
                            if(p*q < 256) printf("Valor digitado invalido\n");
                            else
                            {
                                printf("Valor Valido! Salvo em 'Chave_Publica.txt'.\n");
                                cpub = fopen("Chave_Publica.txt", "w");
                                fprintf(cpub, "CHAVE PUBLICA:\nn: %ld\ne: %ld\n", p*q, e);
                                printf("Mostrar na tela?\nSe sim digite: '1', se nao digite: '0'.\n");
                                scanf("%d", &y);
                                if(y == 1) printf("Chave publica:\nn = %ld\ne = %ld\n", p*q, e);
                                invalido = 0;
                            }
                        }
                    }
                }
            }
        }

        if(x == 2)
        {
            long int n, e, tam, i, conversor, valor[100000];
            printf("\nDigite sua chave publica 'n' e 'e':\n");
            scanf("%ld%ld", &n, &e);
            printf("Digite sua mensagem:\n");
            scanf("\n");
            char frase[100000];
            gets(frase);
            tam = strlen(frase);
            for(i = 0, conversor = 0; i < tam; i++)
            {
                conversor = frase[i];
                valor[i]  = exp_modular(conversor, e, n);//verificar se os numeros gerados estão corretos
                printf("%ld ", valor[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
