/* Candidatos a Elei��o
 *
 * O TSE (Tribunal Superior Eleitoral) lhe contratou para desenvolver uma aplica��o em C para
 * cadastrar os partidos e candidatos �s elei��es municipais do pr�ximo dia 2 de outubro.
 * Utilizando �rvores Bin�rias de Busca e Arquivos Bin�rios, a aplica��o deve cadastrar, alterar,
 * excluir e listar partidos e candidatos � elei��o.
 *
 * Luiz Fernando Kazuaky Nakama (Ci�ncias da Computa��o)
 * Caio Cesar Lopes Teles de Menezes (Ci�ncias da Computa��o)
 * Victor de Almeida Chagas (Ci�ncias da Computa��o)
 *
 *
 * �ltima Data de Modifica��o: 04/10/2016
 */

#include "arvore.h"

void opcao(int, arvpar *, arvcan *);
void cadastro(int, arvpar *, arvcan *);
void remocao(int, arvpar *, arvcan *);
void alteracao(int, arvpar *, arvcan *);
void listar(int, arvpar, arvcan);
void staff();

/* Fun��o main comporta o menu do programa, fazendo a triagem de acordo com a
 * escolha do usu�rio, caso queira fazer todas as opera��es no(s) Partido(s) e com os Candidatos.
 */
int main()
{
    int op;
    FILE *fp;
    arvpar p = NULL;
    arvcan c = NULL;
    struct no_arvpar t;
    struct no_arvcan n;

    if((fp = fopen("partidos.dat", "a+b")) == NULL){
        fprintf(stderr, "Erro ao abrir o arquivo!\n");
        exit(1);
    }
    while(fread(&t, sizeof(struct no_arvpar), 1, fp) > 0){  //A �rvore de partidos � carregada com o conte�do do arquivo partidos.dat
        par_ins(&p, t.numero, t.nome, t.posicao, t.sigla);
    }
    fclose(fp);

    if((fp = fopen("candidatos.dat", "a+b")) == NULL){
        fprintf(stderr, "Erro ao abrir o arquivo!\n");
        exit(1);
    }
    while(fread(&n, sizeof(struct no_arvcan), 1, fp) > 0){  //A �rvore de candidatos � carregada com o conte�do do arquivo candidatos.dat
        can_ins(&c, n.numero, n.nome, n.posicao);
    }
    fclose(fp);

    do{
        printf("\n\n\t===================================\n");
        printf("\t\tCANDIDATOS A ELEICAO\n");
        printf("\t===================================\n");
        printf("\t\t1- Partido\n");
        printf("\t-----------------------------------\n");
        printf("\t\t2- Candidato\n");
        printf("\t-----------------------------------\n");
        printf("\t\t3- Staff\n");
        printf("\t-----------------------------------\n");
        printf("\t\t0- Sair do programa\n");
        printf("\t===================================\n");
        printf("\n\tOpcao -> ");
        scanf("%d", &op);
        system("cls");
        switch(op){
            case 1:
            case 2: opcao(op, &p, &c);
                break;
            case 3: staff();
                break;
            case 0:
                break;
            default: fprintf(stderr, "Opcao invalida!\n");
        }
        system("cls");
    } while(op != 0);

    return 0;
}

/* Fun��o void opcao faz a triagem de qual das opera��es o usu�rio deseja fazer no(s) Partido(s) e
 * Candidato(s), Cadastrar - Alterar - Excluir - Listar. E recebe como par�metro um int que � o
 * n�mero da op��o desejada pelo usu�rio e a refer�ncia para o ponteiro da �rvore de Partidos e Candidatos,
 * e n�o retorna nenhum valor ou par�metro.
 */
void opcao(int op1, arvpar *p, arvcan *c)
{
    int op2;
    char string[10];

    if(op1 == 1) strcpy(string, "Partido\0");
    else strcpy(string, "Candidato\0");

    do{
        printf("\n\n\t===================================\n");
        printf("\t\t    %s\n", string);
        printf("\t===================================\n");
        printf("\t\t1- Cadastrar %s\n", string);
        printf("\t-----------------------------------\n");
        printf("\t\t2- Excluir %s\n", string);
        printf("\t-----------------------------------\n");
        printf("\t\t3- Alterar %s\n", string);
        printf("\t-----------------------------------\n");
        printf("\t\t4- Listar %ss\n", string);
        printf("\t-----------------------------------\n");
        printf("\t\t0- Retornar ao Menu\n");
        printf("\t===================================\n");
        printf("\n\tOpcao -> ");
        scanf("%d", &op2);
        system("cls");
        switch(op2){
            case 1: cadastro(op1, &(*p), &(*c));
                break;
            case 2: remocao(op1, p, c);
                break;
            case 3: alteracao(op1, p, c);
                break;
            case 4: listar(op1, *p, *c);
                break;
            case 0:
                break;
            default: fprintf(stderr, "Opcao invalida!\n");
        }
    } while(op2 < 0 || op2 > 4);
}

/* Fun��o void cadastro faz o cadastro, no(s) Partido(s) ou Candidato(s) dependendo da op��o
 * escolhida pelo usu�rio anteriormente, e recebe como par�metro um int que � o n�mero da op��o
 * desejada pelo usu�rio e a refer�ncia para o ponteiro da �rvore de Partidos e Candidatos,
 * e n�o retorna nenhum valor ou par�metro.
 */
void cadastro(int op, arvpar *p, arvcan *c)
{
    int numero;
    char nome[41];
    bool x;
    if(op == 1){
        char sigla[11];
        do{
            printf("Numero do partido (2 Digitos): ");
            scanf("%d", &numero);
            if((x = (numero <= 10 || numero >= 100 || par_find(*p, numero)))) printf("Numero Invalido!\n\n");
        } while(x);
        printf("\nNome do partido (MAX 30 CHARS): ");
        scanf(" %30[^\n]", nome);
        printf("\nSigla do partido (MAX 4 CHARS): ");
        scanf(" %4[^\n]", sigla);
        par_ins_arq(p, numero, nome, sigla);
    }
    else{
        int cargo, numcand;
        do{
            printf("Prefeito = 1\tVereador = 2\n");
            printf("\nCargo: ");
            scanf("%d", &cargo);
            if((x = (cargo < 1 || cargo > 2 ))) printf("Cargo Invalido!\n\n");
        } while(x);
        do{
            printf("\nNumero do partido (2 Digitos): ");
            scanf("%d", &numero);
            if((x = (numero <= 10 || numero >= 100 || !par_find(*p, numero) || (cargo == 1 && can_find(*c, numero))))) printf("Numero Invalido!\n\n");
        } while(x);
        printf("\n");
        sigla_find(*p, numero);
        if(cargo == 2){
            do{
                printf("\nNumero do candidato (3 Ultimos Digitos): ");
                scanf("%d", &numcand);
                if((x = (numcand < 100 || numcand >= 1000 || can_find(*c, numero * 1000 + numcand)))) printf("Numero Invalido!\n\n");
            } while(x);
            numero = numero * 1000 + numcand;
        }
        printf("\nNome do candidato(MAX 30 CHARS): ");
        scanf(" %30[^\n]", nome);
        can_ins_arq(c, numero, nome);
    }
}

/* Fun��o void remocao faz a remocao, no(s) Partido(s) ou Candidato(s) dependendo da op��o
 * escolhida pelo usu�rio anteriormente, e recebe como par�metro um int que � o n�mero da op��o
 * desejada pelo usu�rio e a refer�ncia para o ponteiro da �rvore de Partidos e Candidatos,
 * e n�o retorna nenhum valor ou par�metro.
 */
void remocao(int op, arvpar *p, arvcan *c)
{
    int numero, n;
    bool x;
    if(op == 1){
        do{
            printf("Numero do partido (2 Digitos): ");
            scanf("%d", &numero);
            if((x = (numero < 11 || numero > 99))) printf("Numero Invalido!\n\n");
            else{
                if((x = !par_find(*p, numero))){
                    printf("Digite [0] para retornar ao menu ou qualquer outra tecla para continuar: ");
                    scanf("%d", &op);
                    if(op == 0) return;
                }
            }
        } while(x);
        n = can_cont(*c, numero);
        while(n-- > 0) can_rem_aux(c, numero);
        par_rem_arq(p, numero);
        printf("\nO partido %d e todos os seus candidatos foram removidos!\n\n\nDigite [0] para retornar ao menu: ", numero);
        while(numero != 0) scanf("%d", &numero);
    }
    else{
        do{
            printf("Numero do candidato (2 ou 5 Digitos): ");
            scanf("%d", &numero);
            if((x = (numero < 11 || numero >= 100000))) printf("Numero Invalido!\n\n");
            else{
                if((x = !can_find(*c, numero))){
                    printf("Digite [0] para retornar ao menu ou qualquer outra tecla para continuar: ");
                    scanf("%d", &op);
                    if(op == 0) return;
                }
            }
        } while(x);
        can_rem_arq(c, numero);
    }
}

/* Fun��o void alteracao faz a alteracao, no(s) Partido(s) ou Candidato(s) dependendo da op��o
 * escolhida pelo usu�rio anteriormente, e recebe como par�metro um int que � o n�mero da op��o
 * desejada pelo usu�rio e a refer�ncia para o ponteiro da �rvore de Partidos e Candidatos,
 * e n�o retorna nenhum valor ou par�metro.
 */
void alteracao(int op, arvpar *p, arvcan *c)
{
    int numero;
    char nome[41];
    bool x;
    if(op == 1){
        char sigla[11];
        do{
            printf("Numero do partido (2 Digitos): ");
            scanf("%d", &numero);
            if((x = (numero < 11 || numero > 99))) printf("Numero Invalido!\n\n");
            else{
                if((x = !par_find(*p, numero))){
                    printf("Digite [0] para retornar ao menu ou qualquer outra tecla para continuar: ");
                    scanf("%d", &op);
                    if(op == 0) return;
                }
            }
        } while(x);
        printf("\nNome do partido (MAX 30 CHARS): ");
        scanf(" %30[^\n]", nome);
        printf("\nSigla do partido (MAX 4 CHARS): ");
        scanf(" %4[^\n]", sigla);
        par_alterar_arq(p, numero, nome, sigla);

    }
    else{
        int cargo;
        do{
            printf("Prefeito = 1\tVereador = 2\n");
            printf("\nCargo: ");
            scanf("%d", &cargo);
            if((x = (cargo < 1 || cargo > 2 ))) printf("Cargo Invalido!\n\n");
        } while(x);
        do{
            printf("\nNumero do candidato (2 ou 5 Digitos): ");
            scanf("%d", &numero);
            if((x = ((cargo == 1 && numero < 11) || (cargo == 1 && numero > 99) || numero >= 100000 || (cargo == 2 && numero < 10000)))) printf("Numero Invalido!\n\n");
            else{
                if((x = !can_find(*c, numero))){
                    printf("Digite [0] para retornar ao menu ou qualquer outra tecla para continuar: ");
                    scanf("%d", &op);
                    if(op == 0) return;
                }
            }
        } while(x);
        printf("\nNome do candidato (MAX 30 CHARS): ");
        scanf(" %30[^\n]", nome);
        can_alterar_arq(c, numero, nome);
    }
}

/* Fun��o void listar faz a listagem, do(s) Partido(s) ou Candidato(s) dependendo da op��o
 * escolhida pelo usu�rio anteriormente, e recebe como par�metro um int que � o n�mero da op��o
 * desejada pelo usu�rio e um ponteiro da �rvore de Partidos e Candidatos, e n�o retorna nenhum valor ou par�metro.
 */
void listar(int op, arvpar p, arvcan c)
{
    int cargo;
    bool x;
    if(op == 1){
        printf("\n==================================================================\n");
        printf("Numero\t\tSigla\t\tNome\n");
        printf("==================================================================\n");
        par_listar(p);
    }
    else{
        do{
            printf("Prefeito = 1\tVereador = 2\n");
            printf("\nCargo: ");
            scanf("%d", &cargo);
            if((x = (cargo < 1 || cargo > 2 ))) printf("Cargo Invalido!\n\n");
        } while(x);
        if(cargo == 1){
            printf("\n=================================================================\n");
            printf("Sigla\t\tNumero\t\tNome\n");
            printf("=================================================================\n");
            pre_listar(c, p);
        }
        else{
            int numero;
            printf("\nNumero do partido (2 Digitos): ");
            scanf("%d", &numero);
            if(par_find(p, numero)){
                printf("\n=========================================================================================\n");
                printf("\t\tPartido\t\t\tNumero\t\tNome\n");
                printf("=========================================================================================\n");
                ver_listar(c, p, numero);
            }
            else printf("Partido inexistente!\n");
        }
    }
    printf("\nDigite [0] para retornar ao menu: ");
    while(op != 0) scanf("%d", &op);
}

/* Fun��o void staff lista os membros do grupo respons�vel pelo trabalho,
 * n�o recebe nenhum par�metro e n�o retorna nada
 */
void staff()
{
    int op;
    printf("\n\t==================================\n");
    printf("\t\t      STAFF\n");
    printf("\t==================================\n\n");
    printf("\tLuiz Fernando Kazuaky Nakama\n\n");
    printf("\tCaio Cesar Lopes Teles de Menezes\n\n");
    printf("\tVictor de Almeida Chagas\n");
    printf("\n\n\n\tDigite [0] para retornar ao menu: ");
    while(op != 0) scanf("%d", &op);
}
