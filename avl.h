typedef void(*t_ImprimeAvl)(void* dado);
typedef int(*t_ComparaAvl)(void* dado_1, void* dado_2);

typedef struct elem_AVL t_ElemAvl;
typedef struct arvore_AVL t_ArvoreAvl;
typedef struct estatistica_s estatistica_avl;

struct estatistica_s{
    int soma_insercao;
    int soma_busca;
    int soma_remocao;
    int qtd_insercao;
    int qtd_busca;
    int qtd_remocao;
};

struct elem_AVL{
    void* carga;
    struct elem_AVL* esq;
    struct elem_AVL* dir;
    struct elem_AVL* pai;
    int fb;
};

struct arvore_AVL{
    t_ElemAvl* raiz;
    t_ComparaAvl comparar;
    t_ImprimeAvl imprimir;
    estatistica_avl *estatisticas;
    int tamanho;
};

//funções ja existentes
t_ArvoreAvl* criar_arvore_AVL(t_ComparaAvl comparacao, t_ImprimeAvl impressora);
int altura_avl(t_ArvoreAvl* avl);
void inserir_elem_avl(t_ArvoreAvl* arvore, void* dado);
void remover_elem_avl(t_ArvoreAvl *tree, void *chave);
void* buscar_avl(t_ArvoreAvl* tree, void* chave);
void podar_avl(t_ArvoreAvl* avl, void* chave);
void imprimir_avl(t_ArvoreAvl* tree);

void reset_cont_avl();
int contador_avl();