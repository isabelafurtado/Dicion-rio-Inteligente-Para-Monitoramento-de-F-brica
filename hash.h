#include "lse_neutra.h"

typedef void (*t_imprimir_hash)(void*); 
typedef struct elem_hash t_elem_hash;
typedef struct hash t_hash;
typedef struct estatistica_h estatistica_hash;

struct estatistica_h{
    int soma_insercao;
    int soma_busca;
    int soma_remocao;
    int qtd_insercao;
    int qtd_busca;
    int qtd_remocao;
    int movimentos;
    int colisoes;
};

struct elem_hash {
    int chave;
    void *carga;
};

struct hash {
    t_imprimir_hash impressora;
    t_lse** vetor;
    int tamanho;
    estatistica_hash *estatistica;
    double fc;
};

t_elem_hash* criar_elem_hash(int chave, void* carga);
int comparar_elem_hash(void* e1, void* e2);
void imprimir_elem_hash(void* ee);
void destroy_elem_hash(t_elem_hash* e);

t_hash* cria_hash(t_imprimir_hash impressao);
int funcao_hashing(t_hash* t, int chave);
t_hash* inserir_elem_hash(t_hash* t, int chave, void* carga);
void* buscar_hash(t_hash* hash, int chave);
void* remover_elem_hash(t_hash* t, int chave);
void imprimir_hash(t_hash* t);

void reset_cont_hash();
int contador_hash();