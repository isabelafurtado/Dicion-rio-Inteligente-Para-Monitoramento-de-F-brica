typedef void(*t_imprimir_lse)(void*);
typedef int(*t_comparar_lse)(void*, void*);

typedef struct elem_lse t_elemento_lse;
struct elem_lse{
    void* carga_util;
    t_elemento_lse* prox;
};

typedef struct lse t_lse;
struct lse{
    t_elemento_lse* prim;
    t_elemento_lse* ult;
    int tamanho;
    t_imprimir_lse impressora;
    t_comparar_lse comparador;
};

t_lse* criar_lse(t_imprimir_lse impressora, t_comparar_lse comparador);
typedef void (*TImpressoraFileLSE)(void*,FILE*);

void inserir_inicio_lse(t_lse* lse, void* carga);
void inserir_final_lse(t_lse* lse, void* carga);
void inserir_conteudo_lse(t_lse* lse, void* carga);
void* remover_inicio_lse(t_lse* lse);
void* remover_final_lse(t_lse* lse);
void* remover_conteudo_lse(t_lse* lse, void* chave);

void* acessar_lse(t_lse* lse, int pos);
void* acessar_conteudo_lse(t_lse* lse, void* chave);
void imprimir_lse(t_lse* lse);
void imprimirFileLSE(t_lse *lse,TImpressoraFileLSE imprimir, FILE *saida);

void destroy_lse(t_lse* lse);
