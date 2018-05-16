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
	printf("\nGerar chave publica: digite 1\nCriptografar: digite 2\nDescriptografar: digite 3\n");

	int x;

	scanf("%d", &x);

	if(x == 1)
	{
        int invalido = 1;
		int p, q, e;

        while(invalido)
        {
            printf("\nDigite 'p', 'q' e 'e'\n");

    		scanf("%d%d%d", &p, &q, &e);
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
                            printf("Chave publica:\nn = %d\ne = %d\n", p*q, e);
                            invalido = 0;
                        }
                    }
                }
            }
        }
	}

    if(x == 2)
    {
        printf("\nDigite sua chave publica 'n' e 'e':\nDigite sua mensagem:\n");
        long int n, e, tam, i, conversor, valor[100000];
        scanf("%ld%ld\n", &n, &e);
        char frase[100000];
        gets(frase);
        tam = strlen(frase);
        for(i = 0, conversor = 0; i < tam; i++)
        {
            conversor = frase[i];
            valor[i]  = exp_modular(conversor, e, n);//verificar se os numeros gerados estão corretos
            printf("%c", valor[i]);
        }
        printf("\n");
    }
    return 0;
}