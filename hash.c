// by Maria Eduarda Monteiro Mota
// by Isabela Monteiro Furtado 

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "math.h"
#include "hash.h"
#define LIMITE_FATOR_CARGA 0.7
#define TAMANHO_INICIAL_HASH 7

int cont_hash = 0;

void reset_cont_hash(){
    cont_hash = 0;
}

int contador_hash(){
    return cont_hash;
}

t_elem_hash* criar_elem_hash(int chave, void* carga) {
    t_elem_hash* e = (t_elem_hash *)malloc(sizeof(t_elem_hash));
    e->chave = chave;
    e->carga = carga;
    return e;
}

int comparar_elem_hash(void* e1, void* e2) {
    cont_hash++;
    t_elem_hash* ee1 = e1;
    t_elem_hash* ee2 = e2;
    return (ee1->chave - ee2->chave);
}

int comparar_elem_hash_chave(void* e1, void* e2) {
    t_elem_hash* ee1 = e1;
    int ee2 = *(int *)e2;
    return (ee1->chave - ee2);
}

void imprimir_elem_hash(void* ee) {
    t_elem_hash* e = ee;
    printf("%d %p\n", e->chave, e->carga);
}

void destroy_elem_hash(t_elem_hash* e) {
    free(e);
}


static t_hash *__criar_hash(unsigned tamanho, t_imprimir_hash impressao) {
    t_hash *tabela = (t_hash *) malloc(sizeof(t_hash));
    estatistica_hash* estatisticas = (estatistica_hash*)malloc(sizeof(estatistica_hash));

    tabela->tamanho = tamanho;
    tabela->fc = 0;
    tabela->impressora = impressao;
    tabela->vetor = (t_lse **) malloc(sizeof(t_lse*) * tabela->tamanho);
    estatisticas->qtd_busca = 0;
    estatisticas->qtd_insercao = 0;
    estatisticas->qtd_remocao = 0;
    estatisticas->soma_busca = 0;
    estatisticas->soma_insercao = 0;
    estatisticas->soma_remocao = 0;
    estatisticas->movimentos = 0;
    estatisticas->colisoes = 0;

    tabela->estatistica = estatisticas;


    for (int i = 0; i < tabela->tamanho; i++) {
        tabela->vetor[i] = criar_lse(imprimir_elem_hash, comparar_elem_hash);
    }
    return tabela;
}


t_hash *cria_hash(t_imprimir_hash impressao) {
    return __criar_hash(TAMANHO_INICIAL_HASH, impressao);
}


int funcao_hashing(t_hash* t, int chave) {
    return chave % t->tamanho;
}

static unsigned __proximo_primo(unsigned primo) {
    unsigned raiz = sqrt(primo);
    for (unsigned i = 2; i <= raiz; i++) {
        if (primo % i == 0) {
            primo++;
            raiz = sqrt(primo);
            i = 2;
        }
    }
    return primo;
}


t_hash* rehashing(t_hash *atual) {
    unsigned int novo_tamanho = __proximo_primo(atual->tamanho * 2);
    t_hash *nova_hash = __criar_hash(novo_tamanho, atual->impressora);
    int conta = 0;
    // assert(nova_hash != NULL);

    for (int i = 0; i < atual->tamanho; i++) {
        t_lse *bucket = atual->vetor[i];
        t_elem_hash *elem = remover_inicio_lse(bucket); ;
        
        while (elem != NULL) {
            int nova_pos = funcao_hashing(nova_hash, elem->chave);
            if(nova_hash->vetor[nova_pos]->tamanho > 0){
                atual->estatistica->colisoes++;
            }
            inserir_inicio_lse(nova_hash->vetor[nova_pos], elem);
            elem = remover_inicio_lse(bucket);
            conta++;
        }

        destroy_lse(bucket); 
    }
    printf("cc: %d\n", conta);

    nova_hash->estatistica->qtd_busca = atual->estatistica->qtd_busca;
    nova_hash->estatistica->qtd_insercao = atual->estatistica->qtd_insercao;
    nova_hash->estatistica->qtd_remocao = atual->estatistica->qtd_remocao;
    nova_hash->estatistica->soma_busca = atual->estatistica->soma_busca;
    nova_hash->estatistica->soma_insercao = atual->estatistica->soma_insercao;
    nova_hash->estatistica->soma_remocao = atual->estatistica->soma_remocao;
    nova_hash->estatistica->movimentos = atual->estatistica->movimentos + conta;
    nova_hash->estatistica->colisoes = atual->estatistica->colisoes;
    printf("nc: %d\n",nova_hash->estatistica->movimentos);

    free(atual->vetor);
    free(atual);
    return nova_hash;
}


t_hash* inserir_elem_hash(t_hash* t, int chave, void* carga) {
    if (t->fc >= LIMITE_FATOR_CARGA) {
        t = rehashing(t);
    }


    int pos = funcao_hashing(t, chave);
    t_lse* colisoes = t->vetor[pos];
    if(colisoes->tamanho > 0){
            t->estatistica->colisoes++;
        }
    t_elem_hash* novo = criar_elem_hash(chave, carga);
    inserir_final_lse(colisoes, novo);

    t->fc += 1.0 / t->tamanho; 

    return t;
}


void* buscar_hash(t_hash* hash, int chave) {
    reset_cont_hash();
    int pos = funcao_hashing(hash, chave);
    t_lse* colisoes = hash->vetor[pos];
    t_elem_hash* e = acessar_conteudo_lse(colisoes, &chave);
    return e ? e->carga : NULL;
}


void* remover_elem_hash(t_hash* t, int chave) {
    int pos = funcao_hashing(t, chave);
    t_lse* colisoes = t->vetor[pos];
    t_elem_hash* e = remover_conteudo_lse(colisoes, &chave);

    void* carga = NULL;
    if (e != NULL) {
        carga = e->carga;
        destroy_elem_hash(e);
        t->fc -= 1.0 / t->tamanho;
    }
    return carga;
}


void imprimir_hash(t_hash* t) {
    for (int i = 0; i < t->tamanho; i++) {
        printf("Bucket %d:\n", i);
        imprimir_lse(t->vetor[i]);
    }
}
