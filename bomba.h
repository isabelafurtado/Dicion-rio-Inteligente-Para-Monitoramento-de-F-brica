#include "avl.h"
#include "hash.h"
// #include "lse_neutra.h"


typedef struct resultado_funcao t_resultado_funcao;
typedef struct item_bomba_s t_item_bomba;
typedef struct bomba_s t_bomba_pression;

struct resultado_funcao{
    double temperature;
    double vibration;
    double pressure;  
};

struct item_bomba_s{
    int pump_id;
    t_lse *infos;
};

struct bomba_s{
    int class_id;
    double temperature;
    double vibration;
    double pressure;
    double flow_rate;
    double rpm;
    double operational_hours;
    int maintenance_flag;
};

t_bomba_pression *criar_info_bomba(int class_id, double temperatura, double vibracao, double pressao, double fluxo, double rpm, double horas, int manutencao);
t_item_bomba *criar_bomba(int pump_id);
int comparar_bomba(void *bomba1, void  *bomba2);

void inserir_bomba_avl(int pump_id, t_bomba_pression *bomba, t_ArvoreAvl *avl);
t_hash* inserir_bomba_hash(int pump_id, t_bomba_pression *bomba, t_hash *hash);

void imprimir_bomba(void *bomba);
void imprimir_bomba_file(void *boom, FILE *saida);

t_resultado_funcao *report_avl(int pump_id, t_ArvoreAvl *tree, char *report_funcao);
t_resultado_funcao *report_hash(int pump_id, t_hash *hash, char *report_funcao);




