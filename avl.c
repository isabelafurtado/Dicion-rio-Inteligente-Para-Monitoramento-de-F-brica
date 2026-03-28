// by Maria Eduarda Monteiro Mota
// by Isabela Monteiro Furtado 

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "avl.h"
#define MAX(a,b) (a > b ? a : b)

int cont_avl = 0;

void reset_cont_avl(){
    cont_avl = 0;
}

int contador_avl(){
    return cont_avl;
}

static t_ElemAvl* __criar_elemento_AVL(void* dado){
    t_ElemAvl* novo = (t_ElemAvl*)malloc(sizeof(t_ElemAvl));

    novo->carga = dado;
    novo->fb = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    return novo;
}

t_ArvoreAvl* criar_arvore_AVL(t_ComparaAvl comparacao, t_ImprimeAvl impressora){
    t_ArvoreAvl* tree = (t_ArvoreAvl*)malloc(sizeof(t_ArvoreAvl));
    estatistica_avl* estatisticas = (estatistica_avl*)malloc(sizeof(estatistica_avl));

    tree->raiz = NULL;
    tree->comparar = comparacao;
    tree->imprimir = impressora;
    tree->tamanho = 0;

    estatisticas->qtd_busca = 0;
    estatisticas->qtd_insercao = 0;
    estatisticas->qtd_remocao = 0;
    estatisticas->soma_busca = 0;
    estatisticas->soma_insercao = 0;
    estatisticas->soma_remocao = 0;

    tree->estatisticas = estatisticas;

    return tree;
}

static int __tamanho_avl(t_ElemAvl* elem){
    if (elem==NULL)
        return 0;
    return __tamanho_avl(elem->dir)+__tamanho_avl(elem->esq)+1;
}

static int __altura(t_ElemAvl* elem){
    if(elem == NULL)
        return -1;
    int alt_esq = __altura(elem->esq);
    int alt_dir = __altura(elem->dir);

    return 1 + MAX(alt_dir, alt_esq);
}

int altura_avl(t_ArvoreAvl* avl){

    return __altura(avl->raiz);

}

static int __fator_balanceamento(t_ElemAvl* elem){
    return __altura(elem->dir) - __altura(elem->esq);
}

static t_ElemAvl* __rot_simples_esq(t_ElemAvl* elem){
    //guarda o que esta a direita do elemento desbalanceado(ed)
    t_ElemAvl* nova_raiz = elem->dir;
    //direita do ed recebe a esquerda da nova raiz
    elem->dir = nova_raiz->esq;

    //caso exista el->dir
    if(elem->dir){
        elem->dir->pai = elem;
    }
    //atualiza pai da nova raiz com o antigo pai do elm
    nova_raiz->pai = elem->pai;
    //pai do ed vai ser a nova raiz
    elem->pai = nova_raiz;
    //atualiza a esquerda da nova com raiz com nosso ed
    nova_raiz->esq = elem;

    return nova_raiz;
}

//mesmo esquema acima soq o simétrico 
static t_ElemAvl* __rot_simples_dir(t_ElemAvl* elem){
    t_ElemAvl* nova_raiz = elem->esq;
    elem->esq = nova_raiz->dir;

    if(elem->esq){
        elem->esq->pai = elem;
    }
    nova_raiz->pai = elem->pai;
    elem->pai = nova_raiz;
    nova_raiz->dir = elem;

    return nova_raiz;
}

//esquerda-direita caso: arvore esquerda-direita ta mais pesada?
static t_ElemAvl* __rot_dupla_esq(t_ElemAvl* elem){
    elem->esq = __rot_simples_esq(elem->esq);
    t_ElemAvl* nova_raiz = __rot_simples_dir(elem);

    return nova_raiz;
}

//direita_esquerda caso: arvore direita esquerda ta mais pesada?
static t_ElemAvl* __rot_dupla_dir(t_ElemAvl* elem){
    elem->dir = __rot_simples_dir(elem->dir);
    t_ElemAvl* nova_raiz = __rot_simples_esq(elem);
    
    return nova_raiz;
}

static t_ElemAvl* __inserir_elem_avl_rec(t_ElemAvl* raiz, t_ComparaAvl comparar, void* dado){
    if(raiz == NULL){
        t_ElemAvl* elem = __criar_elemento_AVL(dado);

        return elem;
        // cont++;
    }
    if(comparar(dado, raiz->carga) < 0){
        raiz->esq = __inserir_elem_avl_rec(raiz->esq, comparar, dado);
        raiz->esq->pai = raiz;

        if(__fator_balanceamento(raiz) == -2){
            if(__fator_balanceamento(raiz->esq) == -1){
                //filho desbalanceado na esquerda
                raiz = __rot_simples_dir(raiz);
            }
            else{
                raiz = __rot_dupla_esq(raiz);
            }
        }
    }
    else{
        raiz->dir = __inserir_elem_avl_rec(raiz->dir, comparar, dado);
        raiz->dir->pai = raiz;

        if(__fator_balanceamento(raiz) == 2){
            if(__fator_balanceamento(raiz->dir) == 1){
                raiz = __rot_simples_esq(raiz);
            }
            else{
                raiz = __rot_dupla_dir(raiz);
            }
        }
    }

    return raiz;
}

void inserir_elem_avl(t_ArvoreAvl* arvore, void* dado){
    // reset_cont();
    arvore->raiz = __inserir_elem_avl_rec(arvore->raiz, arvore->comparar, dado);
}

//atualização do fator de balenceamento para que a arvore tenha a altura minima 
static t_ElemAvl* __remover_elem_avl_rec(t_ElemAvl* raiz, t_ComparaAvl comparar, void* chave, int* flag) {
    cont_avl++;
    if (raiz == NULL) {
        *flag = 0;
        return NULL;
    }

    if (comparar(raiz->carga, chave) < 0) {
        raiz->esq = __remover_elem_avl_rec(raiz->esq, comparar, chave, flag);

        if (__fator_balanceamento(raiz) == 2) {
            if (__fator_balanceamento(raiz->dir) == 1) {
                raiz = __rot_simples_esq(raiz);
            } else {
                raiz = __rot_dupla_dir(raiz);
            }
        }
    }
    else if (comparar(raiz->carga, chave) > 0) {
        raiz->dir = __remover_elem_avl_rec(raiz->dir, comparar, chave, flag);

        if (__fator_balanceamento(raiz) == -2) {
            if (__fator_balanceamento(raiz->esq) == -1) {
                raiz = __rot_simples_dir(raiz);
            } else {
                raiz = __rot_dupla_esq(raiz);
            }
        }
    } 
    else {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz->carga); 
            free(raiz);
            *flag = 1;
            return NULL;
        }else if (raiz->esq != NULL && raiz->dir == NULL) {
            raiz->esq->pai = raiz->pai;
            t_ElemAvl *esq = raiz->esq;
            free(raiz->carga); 
            free(raiz);
            *flag = 1;
            raiz = esq;
        }else if (raiz->esq == NULL && raiz->dir != NULL) {
            raiz->dir->pai = raiz->pai;
             t_ElemAvl *dir = raiz->dir;
            free(raiz->carga);
            free(raiz);
            *flag = 1;
            raiz = dir;
        }else{
            t_ElemAvl *aux = raiz->esq;
            while (aux->dir != NULL) {
                aux = aux->dir;
            }

            // troca
            void *carga_tmp = aux->carga;
            aux->carga = raiz->carga;
            raiz->carga = carga_tmp;

            raiz->esq = __remover_elem_avl_rec(raiz->esq, comparar, chave, flag);
        }
        
        if (__fator_balanceamento(raiz) == 2) {
            if (__fator_balanceamento(raiz->dir) == 1) {
                raiz = __rot_simples_esq(raiz);
            } else {
                raiz = __rot_dupla_dir(raiz);
            }
        }
    }
    return raiz;
}

void remover_elem_avl(t_ArvoreAvl *tree, void *chave){
    reset_cont_avl();
    assert(tree != NULL);
    int flag = 0;
    tree->raiz = __remover_elem_avl_rec(tree->raiz, tree->comparar,chave, &flag);
    if(flag == 1){
        tree->tamanho--;
    }
}

t_ElemAvl * __buscar_avl_rec(t_ElemAvl *raiz, t_ComparaAvl comparar, void* chave) {
    cont_avl++;
    if (!raiz)
        return NULL;

    int cmp = comparar(chave, raiz->carga);

    if (cmp == 0){
        return raiz;
        
    }else if (cmp < 0){
        return __buscar_avl_rec(raiz->esq, comparar, chave);
        
    }else{
        return __buscar_avl_rec(raiz->dir, comparar, chave);
    }
}

void* buscar_avl(t_ArvoreAvl* avl, void* chave) {
    reset_cont_avl();
    t_ElemAvl *no = __buscar_avl_rec(avl->raiz, avl->comparar, chave);
    return no ? no->carga : NULL;
}
static t_ElemAvl* __podar_avl(t_ElemAvl* elem){
    if(elem == NULL){
        return NULL;
    }
    elem->esq = __podar_avl(elem->esq);
    elem->dir = __podar_avl(elem->dir);
    free(elem->carga);
    free(elem);
    return NULL;
}

void podar_avl(t_ArvoreAvl* tree, void* chave){
    t_ElemAvl* no_elem = __buscar_avl_rec(tree->raiz, tree->comparar, chave);
    //no a partir de onde o elemento vai ser removido
    if(no_elem != NULL){
        if(no_elem->pai != NULL){
        //se o elemento não for a raiz
            tree->tamanho -= __altura(no_elem);
            //diminui o tamanho da arvore 
            t_ElemAvl* pai = no_elem->pai;
            //guarda o pai do elemento a ser removido
            if(pai->dir == no_elem){
                //se o no estiver a direita do pai
                pai->dir = __podar_avl(no_elem);
            }
            else{
                //no está a esquerda do pai
                pai->esq = __podar_avl(no_elem);
            }
        }
        else{
        //se for a raiz 
            tree->raiz = __podar_avl(no_elem);
            tree->tamanho = 0;
        }
    }
}

static void __imprimir_avl(t_ElemAvl* raiz, t_ImprimeAvl imprimir){
    if (raiz) {//imprimir ate que a raiz seja null
    //primeiro lado esquerdo pois sao os maiores elementos
        __imprimir_avl(raiz->esq, imprimir);
    //dps a carga central
        imprimir(raiz->carga);
    //dps os menores numeros
        __imprimir_avl(raiz->dir, imprimir);
    }
}

void imprimir_avl(t_ArvoreAvl* avl) {
    __imprimir_avl(avl->raiz, avl->imprimir);
}
