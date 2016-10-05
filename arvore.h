// TAD que define os protótipos de funções de árvores e arquivos binários

#ifndef _ARVORE_H
#define _ARVORE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Estrutura de dados da Árvore de Partidos
typedef struct no_arvpar * arvpar;
struct no_arvpar{
    arvpar esq;
    arvpar dir;
    int numero;
    char nome[31];
    int posicao;
    char sigla[5];
};

//Estrutura de dados da Árvore de Candidatos
typedef struct no_arvcan * arvcan;
struct no_arvcan{
    arvcan esq;
    arvcan dir;
    int numero;
    char nome[31];
    int posicao;
};


                //PROTÓTIPOS DE FUNÇÕES DAS ÁRVORES DE PARTIDOS

//Função que insere um nó na árvore binária de partidos
void par_ins(arvpar *, int, char *, int, char *);

//Função que lista os elementos da árvore binária de partidos
void par_listar(arvpar);

//Função que procura um número na árvore binária de partidos
bool par_find(arvpar, int);

//Função que retira e devolve o menor elemento da subárvore de partidos
arvpar par_getmin(arvpar *);

//Função que insere um partido no arquivo partidos.dat e na árvore de partidos
void par_ins_arq(arvpar *, int, char *, char *);

//Função que remove um partido do arquivo partidos.dat e da árvore de partidos
void par_rem_arq(arvpar *, int);

//Função que altera os dados de um partido no arquivo partidos.dat
void par_alterar_arq(arvpar *, int, char *, char *);

//Função que printa a sigla de um partido
void sigla_find(arvpar, int);


                //PROTÓTIPOS DE FUNÇÕES DAS ÁRVORES DE CANDIDATOS

//Função que insere um nó na árvore binária de candidatos
void can_ins(arvcan *, int, char *, int);

//Função que lista todos os prefeitos
void pre_listar(arvcan, arvpar);

//Função que lista vereadores de um determinado partido
void ver_listar(arvcan, arvpar, int);

//Função que procura um número na árvore binária de candidatos
bool can_find(arvcan, int);

//Função que retira e devolve o menor elemento da subárvore de candidatos
arvcan can_getmin(arvcan *);

//Função que insere um candidato no arquivo candidatos.dat
void can_ins_arq(arvcan *, int, char *);

//Função que remove um candidato do arquivo candidatos.dat
void can_rem_arq(arvcan *, int);

//Função que auxilia a remoção de todos os candidatos do arquivo candidatos.dat, de um determinado partido
void can_rem_aux(arvcan *, int);

//Função que retorna a quantidade de candidatos de um partido
int can_cont(arvcan, int);

//Função que altera os dados de um candidato no arquivo candidatos.dat
void can_alterar_arq(arvcan *, int, char *);

#endif // _ARVORE_H
