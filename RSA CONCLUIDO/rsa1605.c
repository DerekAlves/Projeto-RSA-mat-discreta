#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long int inverso(long long int e, long long int phi)
{
    long long int x;
    for(x = 1; x < phi; x++)
    {
        if((x * e) % phi == 1) break;
    }
    return x;
}


long long int exp_modular(long long int base, long long int e, long long int n)
{
    long long int c, i;
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

long long int primos(long long int i)
{
    long long int x, naoprimo;
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

long long int mdc(long long int a, long long int b)
{
	if(b == 0)
	{
		return a;
	}
	else
	{
		return mdc(b, a%b);
	}
}


int main()
{
    int x = 5, y;//
    int invalido;///CONTROLAR MENU

    long long int p, q, e;

    ///FILE*
    FILE* cpub;
	FILE* msg_c;
	FILE* msg_ad;
	FILE* msg_d;

    while(x != 4)
    {
        printf("\nGerar chave publica: digite '1'.\nCriptografar.......: digite '2'.\nDescriptografar....: digite '3'.\nEncerrar aplicacao.: digite '4'.\n");

        scanf("%d", &x);
        printf("-----------------------------------------\n");

        if(x == 1)
        {
            invalido = 1;

            while(invalido)
            {
                printf("\nDigite 'p', 'q' e 'e'\n");

                scanf("%lld%lld%lld", &p, &q, &e);
                if (primos(p) == 0 || primos(q) == 0) printf("Valor digitado invalido!\n");
                else
                {
                    if((e<1)||(e>((p - 1)*(q - 1)))) printf("Valor digitado invalido!\n");
                    else
                    {
                        if(mdc(e, ((p-1)*(q-1))) != 1) printf("Valor digitado invalido!\n");
                        else
                        {
                            if(p*q < 256) printf("Valor digitado invalido!\n");
                            else
                            {
                                printf("Valor Valido! Salvo em 'chave_publica.txt'.\n");
                                cpub = fopen("chave_publica.txt", "w");
                                fprintf(cpub, "CHAVE PUBLICA:\nn: %ld\ne: %ld\n", p*q, e);
                                fclose(cpub);
                                printf("-----------------------------------------\n");
                                printf("Deseja mostrar na tela?\nSe sim digite: '1', se nao digite: '0'.\n");
                                scanf("%d", &y);
                                if(y == 1) printf("Chave publica:\nn = %lld\ne = %lld\n", p*q, e);
                                printf("-----------------------------------------\n");
                                invalido = 0;
                            }
                        }
                    }
                }
            }
        }

        if(x == 2)
        {
            long long int n, e, tam, i, conversor, valor[100000];
            msg_c = fopen("criptografado.txt", "w");
            printf("\nDigite sua chave publica 'n' e 'e':\n");
            scanf("%lld%lld", &n, &e);
            printf("Digite sua mensagem:\n");
            scanf("\n");
            char frase[100000];
            gets(frase);
            tam = strlen(frase);
            for(i = 0, conversor = 0; i < tam; i++)
            {
                conversor = frase[i];
                valor[i]  = exp_modular(conversor, e, n);//verificar se os numeros gerados estão corretos
                fprintf(msg_c, "%lld ", valor[i]);
            }
            printf("Mensagem criptografada salva no arquivo 'criptografado.txt'.\n");
            printf("-----------------------------------------\n");
            printf("Deseja mostrar na tela como inteiro?\nSe sim digite '1', se nao digite '0'.\n");
            scanf("%d", &y);
            if(y == 1) for(i = 0; i < tam; i++) printf("%lld ", valor[i]);
            fclose(msg_c);
            printf("\n");
            printf("-----------------------------------------\n");
            y = 0;
        }
        if(x == 3)
        {

            long long int d, i;
            int tam;
            long long int mensagem[100000];
            char a[100000];
            msg_ad = fopen("descriptografar.txt", "r");
            printf("Se 'p', 'q' e 'e' ja foram inseridos digite '1', se nao digite '0' para inserir os valores.\n");
            scanf("%d", &y);
            if(y == 0)
            {
                printf("\nDigite 'p', 'q' e 'e':\n");
                scanf("%lli%lli%lli", &p, &q, &e);
            }

            d = inverso(e, ((p-1)*(q-1)));
            printf("%lld INVERSO\n", d);
            for(i = 0; !feof(msg_ad); i++)
            {
                fscanf(msg_ad, "%lli ", &mensagem[i]);
            }
            tam = i;

            for(i = 0; i < tam; i++) mensagem[i] = exp_modular(mensagem[i], d, p*q);

            msg_d = fopen("descriptografado.txt", "w");
            for(i = 0; i < tam; i++)
            {
                a[i] = mensagem[i];
                fprintf(msg_d, "%c", a[i]);
            }
            fclose(msg_d);

            printf("Mensagem salva no arquivo 'descriptografado.txt'\n");
            printf("-----------------------------------------\n");

            printf("Deseja mostrar na tela?\nSe sim digite '1', se nao digite '0'.\n");
            y = 0;
            scanf("%d", &y);
            if(y)
            {
                /*for(i = 0; i < tam; i++)
                {
                    printf("%lli ", mensagem[i]);
                    //printf("%c", mensagem[i]);
                }*/
                printf("\n");
                for(i = 0; i < tam; i++)
                {
                    printf("%c", mensagem[i]);
                }
                printf("\n");
                printf("-----------------------------------------\n");
            }
        }
    }

    return 0;
}
