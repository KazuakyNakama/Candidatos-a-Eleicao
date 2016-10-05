// TAD que define os prot�tipos de fun��es de �rvores e arquivos bin�rios

#ifndef _ARVORE_H
#define _ARVORE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Estrutura de dados da �rvore de Partidos
typedef struct no_arvpar * arvpar;
struct no_arvpar{
    arvpar esq;
    arvpar dir;
    int numero;
    char nome[31];
    int posicao;
    char sigla[5];
};

//Estrutura de dados da �rvore de Candidatos
typedef struct no_arvcan * arvcan;
struct no_arvcan{
    arvcan esq;
    arvcan dir;
    int numero;
    char nome[31];
    int posicao;
};


                //PROT�TIPOS DE FUN��ES DAS �RVORES DE PARTIDOS

//Fun��o que insere um n� na �rvore bin�ria de partidos
void par_ins(arvpar *, int, char *, int, char *);

//Fun��o que lista os elementos da �rvore bin�ria de partidos
void par_listar(arvpar);

//Fun��o que procura um n�mero na �rvore bin�ria de partidos
bool par_find(arvpar, int);

//Fun��o que retira e devolve o menor elemento da sub�rvore de partidos
arvpar par_getmin(arvpar *);

//Fun��o que insere um partido no arquivo partidos.dat e na �rvore de partidos
void par_ins_arq(arvpar *, int, char *, char *);

//Fun��o que remove um partido do arquivo partidos.dat e da �rvore de partidos
void par_rem_arq(arvpar *, int);

//Fun��o que altera os dados de um partido no arquivo partidos.dat
void par_alterar_arq(arvpar *, int, char *, char *);

//Fun��o que printa a sigla de um partido
void sigla_find(arvpar, int);


                //PROT�TIPOS DE FUN��ES DAS �RVORES DE CANDIDATOS

//Fun��o que insere um n� na �rvore bin�ria de candidatos
void can_ins(arvcan *, int, char *, int);

//Fun��o que lista todos os prefeitos
void pre_listar(arvcan, arvpar);

//Fun��o que lista vereadores de um determinado partido
void ver_listar(arvcan, arvpar, int);

//Fun��o que procura um n�mero na �rvore bin�ria de candidatos
bool can_find(arvcan, int);

//Fun��o que retira e devolve o menor elemento da sub�rvore de candidatos
arvcan can_getmin(arvcan *);

//Fun��o que insere um candidato no arquivo candidatos.dat
void can_ins_arq(arvcan *, int, char *);

//Fun��o que remove um candidato do arquivo candidatos.dat
void can_rem_arq(arvcan *, int);

//Fun��o que auxilia a remo��o de todos os candidatos do arquivo candidatos.dat, de um determinado partido
void can_rem_aux(arvcan *, int);

//Fun��o que retorna a quantidade de candidatos de um partido
int can_cont(arvcan, int);

//Fun��o que altera os dados de um candidato no arquivo candidatos.dat
void can_alterar_arq(arvcan *, int, char *);

#endif // _ARVORE_H
