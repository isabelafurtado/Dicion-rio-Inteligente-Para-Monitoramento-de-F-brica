// by Maria Eduarda Monteiro Mota
// by Isabela Monteiro Furtado

#include "string.h"
#include "stdio.h"
#include "bomba.h"

// processar os comandos do arquivo de entrada
void processarComandosAvl(t_ArvoreAvl *tree, FILE *entrada, FILE *saida_avl) {

    fprintf(saida_avl,"---------------SISTEMA OPERACIONAL BOMBAS DE PRESSÃO - AVL---------------\n\n");

    int pump_id, class_id, maintenance_flag, comparacao_add, comparacao_search, comparacao_delete;
    double operational_hours, rpm, temperature, vibration, pressure, flow_rate;
    char comando[30], report_funcao[30];

    while (fscanf(entrada, "%s", comando) != EOF) {
        
        if (strcmp(comando, "ADD") == 0) {
            
            // lendo do arquivo de entrada
            fscanf(entrada, "%d %d %lf %lf %lf %lf %lf %lf %d",
                &pump_id, 
                &class_id,
                &temperature, 
                &vibration,
                &pressure,
                &flow_rate,
                &rpm,
                &operational_hours,
                &maintenance_flag
            );
            
            t_bomba_pression* info_bomba = criar_info_bomba(
                class_id,
                temperature, 
                vibration,
                pressure,
                flow_rate,
                rpm,
                operational_hours,
                maintenance_flag
            );

            inserir_bomba_avl(pump_id, info_bomba, tree);
            comparacao_add = contador_avl();


            fprintf(saida_avl, "Medições da Bomba adicionada:\n\tIdentificador da Bomba: %05d\n\tID da Classe: %d\n\tTemperatura: %.15lf\n\tVibração: %.15lf\n\tPressão: %.15lf\n\tTaxa de Fluxo da Bomba: %.15lf\n\tRPM: %.15lf\n\tOperação da Bomba em horas %.15lf\n\tManutenção Recente: %d\n",
                pump_id, 
                class_id,
                temperature, 
                vibration,
                pressure,
                flow_rate,
                rpm,
                operational_hours,
                maintenance_flag
            );

            fprintf(saida_avl, "\n\tNúmero de Comparações para Inserção: %d\n\n\n", comparacao_add);

        }
        else if (strcmp(comando, "SEARCH") == 0) {
            fscanf(entrada, "%d", &pump_id);
            reset_cont_avl();
            t_item_bomba *item_avl = (t_item_bomba*)buscar_avl(tree, &pump_id);
            comparacao_search = contador_avl();
            
            if (item_avl) {
                t_lse *bombas = item_avl->infos;
                fprintf(saida_avl, "Busca da Bomba com identificador %05d:\n", pump_id);
                imprimirFileLSE(bombas, imprimir_bomba_file, saida_avl);
            } else {
                fprintf(saida_avl, "Busca da Bomba com identificador %05d:\n\tNenhum registro de bomba encontrado\n", pump_id);
            }
            tree->estatisticas->soma_busca += contador_avl();
            tree->estatisticas->qtd_busca++;

            fprintf(saida_avl, "\n\tNúmero de Comparações na Busca: %d\n\n\n", comparacao_search);

        } 

        else if (strcmp(comando, "REMOVE") == 0) {
            fscanf(entrada, "%d", &pump_id);
            t_item_bomba* item = (t_item_bomba*)buscar_avl(tree, &pump_id);
            if (item != NULL){
                remover_elem_avl(tree, &pump_id);
                fprintf(saida_avl, "Remoção da Bomba com identificador %05d:\n", pump_id);
                imprimirFileLSE(item->infos, imprimir_bomba_file, saida_avl);
            }else{
                fprintf(saida_avl, "Remoção da Bomba com identificador %05d:\n\tNenhum registro de bomba encontrado\n", pump_id);
            }

            comparacao_delete = contador_avl();
            tree->estatisticas->soma_remocao += contador_avl();
            tree->estatisticas->qtd_remocao++;

            fprintf(saida_avl, "\n\tNúmero de Comparações para Remoção: %d\n\n", comparacao_delete);

        fprintf(saida_avl, "\n");   
        }

        else if (strcmp(comando, "REPORT") == 0) {
            fscanf(entrada, "%s %d", report_funcao, &pump_id);
            
            t_resultado_funcao *resultado = report_avl(pump_id, tree, report_funcao);
            
            if (resultado != NULL){
                fprintf(saida_avl, "%s - Bomba com Identificador %05d:\n\tTemperatura: %.15lf\n\tVibração: %.15lf\n\tPressão: %.15lf\n", report_funcao, pump_id, resultado->temperature, resultado->vibration, resultado->pressure);
            
            }else{
                fprintf(saida_avl, "Nenhum registro de bomba com identificador %05d\n", pump_id);
            }
        fprintf(saida_avl, "\n");   
        }

        else if (strcmp(comando, "END") == 0) {
            fprintf(saida_avl, "\n");
        }
    }

    fprintf(saida_avl, "Estatísticas de Comparação:\n");
    fprintf(saida_avl, "-----------------------------------------------------------\n");
    fprintf(saida_avl,"\tInserções: %d\n", tree->estatisticas->soma_insercao);
    fprintf(saida_avl,"\tBuscas: %d\n", tree->estatisticas->soma_busca);
    fprintf(saida_avl,"\tRemoções: %d\n\n", tree->estatisticas->soma_remocao);

}


void processarComandosHash(t_hash *hash ,FILE *entrada, FILE *saida_hash) {
    fprintf(saida_hash,"---------------SISTEMA OPERACIONAL BOMBAS DE PRESSÃO - HASH---------------\n\n");
   
    int pump_id, class_id, maintenance_flag,comparacao_add, comparacao_search, comparacao_delete;
    double operational_hours, rpm, temperature, vibration, pressure, flow_rate;
    char comando[30], report_funcao[30];

    while (fscanf(entrada, "%s", comando) != EOF) {
        
        if (strcmp(comando, "ADD") == 0) {
            
            // lendo do arquivo de entrada
            fscanf(entrada, "%d %d %lf %lf %lf %lf %lf %lf %d",
                &pump_id, 
                &class_id,
                &temperature, 
                &vibration,
                &pressure,
                &flow_rate,
                &rpm,
                &operational_hours,
                &maintenance_flag
            );
            
            t_bomba_pression* info_bomba = criar_info_bomba(
                class_id,
                temperature, 
                vibration,
                pressure,
                flow_rate,
                rpm,
                operational_hours,
                maintenance_flag
            );

            hash = inserir_bomba_hash(pump_id, info_bomba, hash);
            comparacao_add = contador_hash();
            
            fprintf(saida_hash, "Medições da Bomba adicionada:\n\tIdentificador da Bomba: %05d\n\tID da Classe: %d\n\tTemperatura: %.15lf\n\tVibração: %.15lf\n\tPressão: %.15lf\n\tTaxa de Fluxo da Bomba: %.15lf\n\tRPM: %.15lf\n\tOperação da Bomba em horas %.15lf\n\tManutenção Recente: %d\n",
                pump_id, 
                class_id,
                temperature, 
                vibration,
                pressure,
                flow_rate,
                rpm,
                operational_hours,
                maintenance_flag
            );
            fprintf(saida_hash, "\n\tNúmero de Comparações para Inserção: %d\n\n", comparacao_add);
            
            fprintf(saida_hash, "\n");
        }        
        
        else if (strcmp(comando, "SEARCH") == 0) {
            fscanf(entrada, "%d", &pump_id);
            t_item_bomba *bomba = buscar_hash(hash, pump_id);
            comparacao_search = contador_hash();

            if (bomba != NULL) {
                fprintf(saida_hash, "Busca da Bomba com identificador %05d:\n", pump_id);
                imprimirFileLSE(bomba->infos, imprimir_bomba_file, saida_hash);
            } else {
                fprintf(saida_hash, "Busca da Bomba com identificador %05d:\n\tNenhum registro de bomba encontrado\n", pump_id);
            }  
            hash->estatistica->soma_busca += contador_hash();
            hash->estatistica->qtd_busca++;
         
            fprintf(saida_hash, "\n\tNúmero de Comparações na Busca: %d\n\n\n", comparacao_search);


        } else if(strcmp(comando, "REMOVE") == 0){
            fscanf(entrada, "%d", &pump_id);

            t_item_bomba* item_hash = (t_item_bomba*)buscar_hash(hash, pump_id);

            if (item_hash != NULL){
                remover_elem_hash(hash, pump_id);
                // imprimirLSE(item->infos, imprimir_bomba);
                fprintf(saida_hash, "Remoção da Bomba com identificador %05d:\n", pump_id);
                imprimirFileLSE(item_hash->infos, imprimir_bomba_file, saida_hash);
            }else{
                fprintf(saida_hash, "Remoção da Bomba com identificador %05d:\n\tNenhum registro de bomba encontrado\n", pump_id);
            }

            comparacao_delete = contador_hash();
            hash->estatistica->soma_remocao += contador_hash();
            hash->estatistica->qtd_remocao++;

            fprintf(saida_hash, "\n\tNúmero de Comparações para Remoção: %d\n\n", comparacao_delete);

        fprintf(saida_hash, "\n"); 
        }
        else if (strcmp(comando, "REPORT") == 0) {
            fscanf(entrada, "%s %d", report_funcao, &pump_id);
            
            t_resultado_funcao *resultado_hash = report_hash(pump_id, hash, report_funcao);
            
            if (resultado_hash != NULL){
                fprintf(saida_hash, "%s - Bomba com Identificador %05d:\n\tTemperatura: %.15lf\n\tVibração: %.15lf\n\tPressão: %.15lf\n", report_funcao, pump_id, resultado_hash->temperature,
                resultado_hash->vibration, resultado_hash->pressure);
            
            }else{
                fprintf(saida_hash, "Nenhum registro de bomba com identificador %05d\n", pump_id);
            }
        fprintf(saida_hash, "\n");   
        }
        else if (strcmp(comando, "END") == 0) {
            fprintf(saida_hash, "\n");
        }
    }
    fprintf(saida_hash, "Estatísticas de Comparação:\n");
    fprintf(saida_hash, "-----------------------------------------------------------\n");
    fprintf(saida_hash,"\tInserções: %d\n", hash->estatistica->soma_insercao);
    fprintf(saida_hash,"\tBuscas: %d\n", hash->estatistica->soma_busca);
    fprintf(saida_hash,"\tRemoções: %d\n\n", hash->estatistica->soma_remocao);

    fprintf(saida_hash, "\nEstatísticas da Hash:\n");
    fprintf(saida_hash, "-----------------------------------------------------------\n");

    fprintf(saida_hash,"\tColisoes: %d\n", hash->estatistica->colisoes);
    fprintf(saida_hash,"\tMovimentações: %d\n", hash->estatistica->movimentos);


}


// função main
int main(int argc, char *argv[]) {
    
    t_ArvoreAvl *tree = criar_arvore_AVL(comparar_bomba, imprimir_bomba);
    t_hash *hash = cria_hash(imprimir_bomba);

    // declarando arquivos 
    FILE *entrada, *saida_avl, *saida_hash;
    
    if (argc > 1) {
        
        // abrindo arquivo de entrada no modo leitura
        printf("\nLendo arquivo de entrada: %s", argv[1]);
        entrada = fopen(argv[1], "r"); 

        // abrindo arquivos de saída modo escrita
        saida_avl = fopen("saida_avl.out", "w");
        saida_hash = fopen("saida_hash.out", "w");

        if (!entrada || !saida_avl || !saida_hash) {
            printf("\nErro ao abrir o arquivo de entrada. Execute o programa com o comando: ./prog entrada.in\n");
            return 1;
        }

        printf("\n\n---------------- Iniciando o processamento ----------------\n\n");

        // avl

        printf("Processando AVL\n\n");
        processarComandosAvl(tree, entrada, saida_avl);
        fclose(entrada);  
        fclose(saida_avl);  

        // hash
        entrada = fopen(argv[1], "r");
        printf("\nProcessando Hash\n\n");
        processarComandosHash(hash, entrada, saida_hash);
        fclose(entrada);  
        fclose(saida_hash);

    } 

    printf("\n---------------- Finalizando o processamento ----------------\n");

    return 0;
}

