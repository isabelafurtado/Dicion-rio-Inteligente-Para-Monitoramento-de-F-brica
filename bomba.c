// by Maria Eduarda Monteiro Mota
// by Isabela Monteiro Furtado 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "bomba.h"

t_item_bomba *criar_bomba(int pump_id){
    t_item_bomba *item_bomba = (t_item_bomba*)malloc(sizeof(t_item_bomba));

    item_bomba->pump_id = pump_id;
    item_bomba->infos = criar_lse(imprimir_bomba, comparar_bomba);

    return item_bomba;
}

t_bomba_pression *criar_info_bomba(int class_id, double temperatura, double vibracao, double pressao, double fluxo, double rpm, double horas, int manutencao){
    t_bomba_pression *info_bomba = (t_bomba_pression*)malloc(sizeof(t_bomba_pression));

    info_bomba->class_id = class_id;
    info_bomba->temperature = temperatura;
    info_bomba->vibration = vibracao;
    info_bomba->pressure = pressao;
    info_bomba->flow_rate = fluxo;
    info_bomba->rpm = rpm;
    info_bomba->operational_hours = horas;
    info_bomba->maintenance_flag = manutencao;

    return info_bomba;
}

int comparar_bomba(void *bomba1, void  *bomba2){
    int result;
    t_item_bomba *b1 = bomba1;
    t_item_bomba *b2 = bomba2;

    if(b1->pump_id == b2->pump_id){
		result = 0;
	}else if(b1->pump_id > b2->pump_id){
		result = 1;
	}else{
		result = -1;
	}

	return result;
}

void imprimir_bomba(void *boom){
	if (boom != NULL){
    	t_bomba_pression *b = boom;

		printf("%d %.15lf %.15lf %.15lf %.15lf %.15lf %.15lf %d\n",
            b->class_id,
            b->temperature,
            b->vibration,
            b->pressure,
            b->flow_rate,
            b->rpm,
            b->operational_hours,
            b->maintenance_flag
        );
	}else{
		printf("\tInformações da bomba não registrada\n");
	}
}

void imprimir_bomba_file(void *boom, FILE *saida){
	if (boom != NULL){
    	t_bomba_pression *b = boom;

		fprintf(saida, "\t-------------------------------------------------\n\tID da Classe: %d\n\tTemperatura: %.15lf\n\tVibração: %.15lf\n\tPressão: %.15lf\n\tTaxa de Fluxo da Bomba: %.15lf\n\tRPM: %.15lf\n\tOperação da Bomba em horas %.15lf\n\tManutenção Recente: %d\n",
            b->class_id,
            b->temperature,
            b->vibration,
            b->pressure,
            b->flow_rate,
            b->rpm,
            b->operational_hours,
            b->maintenance_flag
        );
	}else{
		fprintf(saida, "\tInformações da bomba não registrada\n");
	}
}


void inserir_bomba_avl(int pump_id, t_bomba_pression *bomba, t_ArvoreAvl *avl){
    t_item_bomba *resultado = buscar_avl(avl, &pump_id);
    if (resultado == NULL){
        t_item_bomba *item_bomba = criar_bomba(pump_id);
        inserir_final_lse(item_bomba->infos, bomba);
        inserir_elem_avl(avl, item_bomba);
        // printf("\tInserindo nova bomba na AVL com pump_id: %05d\n", pump_id);
    }else{
        inserir_final_lse(resultado->infos, bomba);
        // printf("\tBomba existente encontrada com pump_id: %05d, inserindo dados adicionais.\n", pump_id);
    }
    
    avl->estatisticas->soma_insercao += contador_avl();
    avl->estatisticas->qtd_insercao++;

}

t_hash *inserir_bomba_hash(int pump_id, t_bomba_pression *bomba, t_hash *hash){

    t_item_bomba *resultado = buscar_hash(hash, pump_id);

    if (resultado == NULL) {
        t_item_bomba *item_bomba = criar_bomba(pump_id);
        inserir_final_lse(item_bomba->infos, bomba);
        // printf("\tInserindo nova bomba no hash para pump_id: %05d\n", pump_id);
        hash = inserir_elem_hash(hash, pump_id, item_bomba);
    } else {
        // se a bomba já existe
        inserir_final_lse(resultado->infos, bomba);
        // printf("\tBomba existente encontrada para pump_id: %05d, inserindo dados adicionais.\n", pump_id);
    }
    hash->estatistica->soma_insercao += contador_hash();
    hash->estatistica->qtd_insercao++;
    return hash;
}



t_resultado_funcao *report_avl(int pump_id, t_ArvoreAvl *tree, char *report_funcao){
    t_item_bomba *buscado = buscar_avl(tree, &pump_id);
    t_resultado_funcao *result = (t_resultado_funcao*)malloc(sizeof(t_resultado_funcao)); 

    result->temperature = 0;
    result->vibration = 0;
    result->pressure = 0;

    if(buscado != NULL){
        t_lse *lista = buscado->infos;
        t_elemento_lse *cam = lista->prim;
        if(strcmp(report_funcao, "MAX") == 0){
            t_bomba_pression *aux = (t_bomba_pression*)cam->carga_util;
            result->temperature = aux->temperature;
            result->vibration = aux->vibration;
            result->pressure = aux->pressure;

            cam = cam->prox;

            while(cam != NULL){
                aux = (t_bomba_pression*)cam->carga_util;

                if(aux->temperature > result->temperature){
                    result->temperature = aux->temperature;
                }
                if(aux->vibration > result->vibration){
                    result->vibration = aux->vibration;
                }
                if(aux->pressure > result->pressure){
                    result->pressure = aux->pressure;
                }

                cam = cam->prox;
            }

        }
        else if(strcmp(report_funcao, "MIN") == 0){
            t_bomba_pression *aux = cam->carga_util;
            result->temperature = aux->temperature;
            result->vibration = aux->vibration;
            result->pressure = aux->pressure;

            cam = cam->prox;

            while(cam != NULL){
                aux = cam->carga_util;

                if(aux->temperature < result->temperature){
                    result->temperature = aux->temperature;
                }
                if(aux->vibration < result->vibration){
                    result->vibration = aux->vibration;
                }
                if(aux->pressure < result->pressure){
                    result->pressure = aux->pressure;
                }

                cam = cam->prox;
            }

        }
        else if(strcmp(report_funcao, "MEAN") == 0){
            t_bomba_pression *aux = cam->carga_util;

            while(cam != NULL){
                aux = cam->carga_util;
                result->temperature += aux->temperature;
                result->vibration += aux->vibration;
                result->pressure += aux->pressure;

                cam = cam->prox;
            }

            result->temperature /= lista->tamanho;
            result->vibration /= lista->tamanho;
            result->pressure /= lista->tamanho;

        }
    }

    return result;
} 
t_resultado_funcao *report_hash(int pump_id, t_hash *hash, char *report_funcao){
    t_item_bomba *buscado = buscar_hash(hash, pump_id);
    t_resultado_funcao *result = (t_resultado_funcao*)malloc(sizeof(t_resultado_funcao)); 

    result->temperature = 0;
    result->vibration = 0;
    result->pressure = 0;

    if(buscado != NULL){
        t_lse *lista = buscado->infos;
        t_elemento_lse *cam = lista->prim;
        if(strcmp(report_funcao, "MAX") == 0){
            t_bomba_pression *aux = (t_bomba_pression*)cam->carga_util;
            result->temperature = aux->temperature;
            result->vibration = aux->vibration;
            result->pressure = aux->pressure;

            cam = cam->prox;

            while(cam != NULL){
                aux = (t_bomba_pression*)cam->carga_util;

                if(aux->temperature > result->temperature){
                    result->temperature = aux->temperature;
                }
                if(aux->vibration > result->vibration){
                    result->vibration = aux->vibration;
                }
                if(aux->pressure > result->pressure){
                    result->pressure = aux->pressure;
                }

                cam = cam->prox;
            }

        }
        else if(strcmp(report_funcao, "MIN") == 0){
            t_bomba_pression *aux = cam->carga_util;
            result->temperature = aux->temperature;
            result->vibration = aux->vibration;
            result->pressure = aux->pressure;

            cam = cam->prox;

            while(cam != NULL){
                aux = cam->carga_util;

                if(aux->temperature < result->temperature){
                    result->temperature = aux->temperature;
                }
                if(aux->vibration < result->vibration){
                    result->vibration = aux->vibration;
                }
                if(aux->pressure < result->pressure){
                    result->pressure = aux->pressure;
                }

                cam = cam->prox;
            }

        }
        else if(strcmp(report_funcao, "MEAN") == 0){
            t_bomba_pression *aux = cam->carga_util;

            while(cam != NULL){
                aux = cam->carga_util;
                result->temperature += aux->temperature;
                result->vibration += aux->vibration;
                result->pressure += aux->pressure;

                cam = cam->prox;
            }

            result->temperature /= lista->tamanho;
            result->vibration /= lista->tamanho;
            result->pressure /= lista->tamanho;

        }
    }

    return result;
} 



