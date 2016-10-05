// TAD que implementa as funções de árvores e arquivos binários

#include "arvore.h"

                //PROTÓTIPOS DE FUNÇÕES DAS ÁRVORES DE PARTIDOS

void par_ins(arvpar * p, int numero, char *nome, int posicao, char *sigla)
{
    if(numero == 0) return;
    if(*p == NULL){
        if((*p = (arvpar) malloc(sizeof(struct no_arvpar))) == NULL){
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }
        (*p)->numero = numero;
        (*p)->posicao = posicao;
        strcpy((*p)->nome, nome);
        strcpy((*p)->sigla, sigla);
        (*p)->esq = (*p)->dir = NULL;
    }
    else{
        if(numero < (*p)->numero) par_ins(&(*p)->esq, numero, nome, posicao, sigla);
        else par_ins(&(*p)->dir, numero, nome, posicao, sigla);
    }
}

void par_listar(arvpar p)
{
    if(p != NULL){
        par_listar(p->esq);
        printf("%d\t\t%s\t\t%s\n\n", p->numero, p->sigla, p->nome);
        par_listar(p->dir);
    }
}

bool par_find(arvpar p, int numero)
{
    if(p == NULL) return false;
    if(numero == p->numero) return true;
    if(numero < p->numero) return par_find(p->esq, numero);
    return par_find(p->dir, numero);
}

arvpar par_getmin(arvpar *p)
{
    if((*p)->esq == NULL){
        arvpar t = *p;
        *p = (*p)->dir;
        return t;
    }
    return par_getmin(&(*p)->esq);
}

void par_ins_arq(arvpar *p, int numero, char *nome, char *sigla)
{
    if(*p == NULL){
        FILE *fp;
        struct no_arvpar t;
        if((fp = fopen("partidos.dat", "a+b")) == NULL){
            fprintf(stderr, "Erro ao abrir o arquivo!\n");
            exit(1);
        }
        if((*p = (arvpar) malloc(sizeof(struct no_arvpar))) == NULL){
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }
        if(fread(&t, sizeof(struct no_arvpar), 1, fp) <= 0) t.posicao = 0;
        else{
            fseek(fp, -1 * sizeof(struct no_arvpar), SEEK_END);
            fread(&t, sizeof(struct no_arvpar), 1, fp);
            t.posicao += 1;
            fseek(fp, 0, SEEK_END);
        }
        t.esq = t.dir = NULL;
        t.numero = numero;
        strcpy(t.nome, nome);
        strcpy(t.sigla, sigla);
        fwrite(&t, sizeof(struct no_arvpar), 1, fp);
        fclose(fp);
        (*p)->esq = (*p)->dir = NULL;
        (*p)->numero = numero;
        (*p)->posicao = t.posicao;
        strcpy((*p)->nome, nome);
        strcpy((*p)->sigla, sigla);
    }
    else{
        if(numero < (*p)->numero) par_ins_arq(&(*p)->esq, numero, nome, sigla);
        else par_ins_arq(&(*p)->dir, numero, nome, sigla);
    }
}

void par_rem_arq(arvpar *p, int numero)
{
    if((*p)->numero == numero){
        FILE *fp;
        struct no_arvpar t;
        if((fp = fopen("partidos.dat", "r+b")) == NULL){
            fprintf(stderr, "Erro ao abrir o arquivo!\n");
            exit(1);
        }
        fseek(fp, (*p)->posicao * sizeof(struct no_arvpar), SEEK_SET);
        fread(&t, sizeof(struct no_arvpar), 1, fp);
        t.numero = 0;
        fseek(fp, (*p)->posicao * sizeof(struct no_arvpar), SEEK_SET);
        fwrite(&t, sizeof(struct no_arvpar), 1, fp);
        fclose(fp);

        arvpar n = *p;
        if((*p)->esq == NULL) *p = (*p)->dir;
        else{
            if((*p)->dir == NULL) *p = (*p)->esq;
            else{
                n = par_getmin(&(*p)->dir);
                (*p)->numero = n->numero;
            }
        }
        free(n);
    }
    else{
        if(numero < (*p)->numero) par_rem_arq(&(*p)->esq, numero);
        else par_rem_arq(&(*p)->dir, numero);
    }
}

void par_alterar_arq(arvpar *p, int numero, char *nome, char *sigla)
{
    if((*p)->numero == numero){
        FILE *fp;
        struct no_arvpar t;
        if((fp = fopen("partidos.dat", "r+b")) == NULL){
            fprintf(stderr, "Erro ao abrir o arquivo!\n");
            exit(1);
        }
        t.posicao = (*p)->posicao;
        t.esq = t.dir = NULL;
        t.numero = numero;
        strcpy(t.nome, nome);
        strcpy(t.sigla, sigla);
        fseek(fp, (*p)->posicao * sizeof(struct no_arvpar), SEEK_SET);
        fwrite(&t, sizeof(struct no_arvpar), 1, fp);
        fclose(fp);
        strcpy((*p)->nome, nome);
        strcpy((*p)->sigla, sigla);
    }
    else{
        if(numero < (*p)->numero) par_alterar_arq(&(*p)->esq, numero, nome, sigla);
        else par_alterar_arq(&(*p)->dir, numero, nome, sigla);
    }
}

void sigla_find(arvpar p, int numero)
{
    if(p->numero == numero){
        printf("Sigla: %s\n", p->sigla);
    }
    else{
        if(numero < p->numero) sigla_find(p->esq, numero);
        else sigla_find(p->dir, numero);
    }
}


                //PROTÓTIPOS DE FUNÇÕES DAS ÁRVORES DE CANDIDATOS

void can_ins(arvcan *c, int numero, char *nome, int posicao)
{
    if(numero == 0) return;
    if(*c == NULL){
        if((*c = (arvcan) malloc(sizeof(struct no_arvcan))) == NULL){
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }
        (*c)->esq = (*c)->dir = NULL;
        (*c)->numero = numero;
        (*c)->posicao = posicao;
        strcpy((*c)->nome, nome);
    }
    else{
        if(numero < (*c)->numero) can_ins(&(*c)->esq, numero, nome, posicao);
        else can_ins(&(*c)->dir, numero, nome, posicao);
    }
}

void pre_listar(arvcan c, arvpar p)
{
    if(c != NULL){
        pre_listar(c->esq, p);
        if(c->numero > 10 && c->numero < 100){
            if(p->numero == c->numero){
                printf("%s\t\t%d\t\t%s\n\n", p->sigla, c->numero, c->nome);
            }
            else{
                if(c->numero < p->numero) pre_listar(c, p->esq);
                else pre_listar(c, p->dir);
            }
        }
        pre_listar(c->dir, p);
    }
}

void ver_listar(arvcan c, arvpar p, int numero)
{
    if(p->numero == numero){
        if(c != NULL){
            ver_listar(c->esq, p, numero);
            if(numero == c->numero / 1000){
                printf("%30s\t\t%d\t\t%s\n\n", p->nome, c->numero, c->nome);
            }
            ver_listar(c->dir, p, numero);
        }
    }
    else{
        if(numero < p->numero) ver_listar(c, p->esq, numero);
        else ver_listar(c, p->dir, numero);
    }
}

bool can_find(arvcan c, int numero)
{
    if(c == NULL) return false;
    if(numero == c->numero) return true;
    if(numero < c->numero) return can_find(c->esq, numero);
    return can_find(c->dir, numero);
}

arvcan can_getmin(arvcan *c)
{
    if((*c)->esq == NULL){
        arvcan t = *c;
        *c = (*c)->dir;
        return t;
    }
    return can_getmin(&(*c)->esq);
}

void can_ins_arq(arvcan *c, int numero, char *nome)
{
    if(*c == NULL){
        FILE *fp;
        struct no_arvcan t;
        if((fp = fopen("candidatos.dat", "a+b")) == NULL){
            fprintf(stderr, "Erro ao abrir o arquivo!\n");
            exit(1);
        }
        if((*c = (arvcan) malloc(sizeof(struct no_arvcan))) == NULL){
                fprintf(stderr, "Erro de alocacao de memoria!\n");
                exit(1);
            }
        if(fread(&t, sizeof(struct no_arvcan), 1, fp) <= 0) t.posicao = 0;
        else{
            fseek(fp, -1 * sizeof(struct no_arvcan), SEEK_END);
            fread(&t, sizeof(struct no_arvcan), 1, fp);
            t.posicao += 1;
            fseek(fp, 0, SEEK_END);
        }
        t.esq = t.dir = NULL;
        t.numero = numero;
        strcpy(t.nome, nome);
        fwrite(&t, sizeof(struct no_arvcan), 1, fp);
        fclose(fp);
        (*c)->esq = (*c)->dir = NULL;
        (*c)->numero = numero;
        (*c)->posicao = t.posicao;
        strcpy((*c)->nome, nome);
    }
    else{
        if(numero < (*c)->numero) can_ins_arq(&(*c)->esq, numero, nome);
        else can_ins_arq(&(*c)->dir, numero, nome);
    }
}

void can_rem_arq(arvcan *c, int numero)
{
    if((*c)->numero == numero){
        FILE *fp;
        struct no_arvcan t;
        if((fp = fopen("candidatos.dat", "r+b")) == NULL){
            fprintf(stderr, "Erro ao abrir o arquivo!\n");
            exit(1);
        }
        fseek(fp, (*c)->posicao * sizeof(struct no_arvcan), SEEK_SET);
        fread(&t, sizeof(struct no_arvcan), 1, fp);
        t.numero = 0;
        fseek(fp, (*c)->posicao * sizeof(struct no_arvcan), SEEK_SET);
        fwrite(&t, sizeof(struct no_arvcan), 1, fp);
        fclose(fp);

        arvcan n = *c;
        if((*c)->esq == NULL) *c = (*c)->dir;
        else{
            if((*c)->dir == NULL) *c = (*c)->esq;
            else{
                n = can_getmin(&(*c)->dir);
                (*c)->numero = n->numero;
            }
        }
        free(n);
    }
    else{
        if(numero < (*c)->numero) can_rem_arq(&(*c)->esq, numero);
        else can_rem_arq(&(*c)->dir, numero);
    }
}

void can_rem_aux(arvcan *c, int numero)
{
    if(*c != NULL){
        if((*c)->numero == numero || (*c)->numero / 1000 == numero) can_rem_arq(&(*c), (*c)->numero);
        else{
            if(numero < (*c)->numero || numero < (*c)->numero / 1000) can_rem_aux(&(*c)->esq, numero);
            else can_rem_aux(&(*c)->dir, numero);
        }
    }
}

int can_cont(arvcan c, int numero)
{
    int cont = 0;
    if(c == NULL) return 0;
    if(c->numero == numero || c->numero / 1000 == numero) cont++;
    if(numero < c->numero || numero < c->numero / 1000) return cont += can_cont(c->esq, numero);
    else return cont += can_cont(c->dir, numero);
}

void can_alterar_arq(arvcan *c, int numero, char *nome)
{
    if((*c)->numero == numero){
        FILE *fp;
        struct no_arvcan t;
        if((fp = fopen("candidatos.dat", "r+b")) == NULL){
            fprintf(stderr, "Erro ao abrir o arquivo!\n");
            exit(1);
        }
        t.posicao = (*c)->posicao;
        t.esq = t.dir = NULL;
        t.numero = numero;
        strcpy(t.nome, nome);
        fseek(fp, (*c)->posicao * sizeof(struct no_arvcan), SEEK_SET);
        fwrite(&t, sizeof(struct no_arvcan), 1, fp);
        fclose(fp);
        strcpy((*c)->nome, nome);
    }
    else{
        if(numero < (*c)->numero) can_alterar_arq(&(*c)->esq, numero, nome);
        else can_alterar_arq(&(*c)->dir, numero, nome);
    }
}
