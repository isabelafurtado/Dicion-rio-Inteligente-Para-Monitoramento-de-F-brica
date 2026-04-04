# 🏭 Dicionário Inteligente para Monitoramento Industrial

Este projeto foi desenvolvido para a disciplina de **Algoritmos e Estruturas de Dados II**. O objetivo central é a implementação e comparação de desempenho entre duas estruturas de dados fundamentais: **Árvores AVL** e **Tabelas Hash**.

## 📋 Sobre o Projeto
O sistema simula um ambiente de fábrica onde sensores coletam dados contínuos de bombas de pressão. O desafio é gerenciar esse volume massivo de informações de forma que a recuperação de dados para análise em tempo real seja eficiente.

### O Dataset
Os dados processados são provenientes de sensores instalados em bombas, contendo:
* **Pump_ID**: Identificador global da bomba (Chave primária).
* **Class_ID**: Identificador da categoria.
* **Medições**: Temperatura, Vibração, Pressão, Fluxo (Flow Rate) e RPM.
* **Operational_Hours**: Horas acumuladas de funcionamento.
* **Maintenance_Flag**: Indicador se a bomba sofreu manutenção no período (0 ou 1).

---

## 🛠️ Estruturas Implementadas

O projeto utiliza duas abordagens para o dicionário, permitindo a comparação de métricas:

### 1. Árvore AVL (`avl.c`)
Uma árvore binária de busca que se mantém balanceada através de rotações (simples e duplas) sempre que o fator de balanceamento atinge $-2$ ou $2$.
* **Garantia**: Busca, inserção e remoção em tempo logarítmico $O(\log n)$.

### 2. Tabela Hash (`hash.c`)
Implementada com tratamento de colisões por encadeamento externo (usando uma Lista Simplesmente Encadeada).
* **Rehashing**: A tabela redimensiona automaticamente quando o fator de carga (`fc`) atinge **0.7**.
* **Função de Espalhamento**: Utiliza o método da divisão ($Chave \mod Tamanho$) com redimensionamento baseado em números primos para reduzir colisões.

---

## 🚀 Comandos Suportados
O programa processa arquivos de entrada com os seguintes comandos:

| Comando | Descrição |
| :--- | :--- |
| **ADD** | Adiciona uma nova medição completa de uma bomba. |
| **SEARCH** | Busca e exibe todas as medições associadas a um `Pump_ID`. |
| **REMOVE** | Remove uma bomba e todo o seu histórico do dicionário. |
| **REPORT** | Gera relatórios estatísticos (**MEAN**, **MAX**, **MIN**) para Temperatura, Vibração e Pressão. |

---

## 📊 Análise de Desempenho
Para fins acadêmicos, ambas as estruturas implementam um sistema de **estatísticas** que contabiliza:
* Quantidade de buscas, inserções e remoções.
* Soma de comparações feitas (para cálculo de custo médio).
* Número de colisões e movimentos de dados (exclusivo da Hash).

---

## 📁 Organização do Código
* `avl.c` / `avl.h`: Lógica de balanceamento e manipulação da árvore.
* `hash.c` / `hash.h`: Lógica de hashing, tratamento de colisão e rehashing.
* `lse_neutra.c` / `lse_neutra.h`: Lista encadeada genérica (void*) para armazenamento de histórico.
* `bomba.c` / `bomba.h`: Abstração dos dados da bomba e integração com as estruturas.

---

## 🔨 Como Compilar e Rodar

1. Certifique-se de ter o `gcc` instalado.
2. Compile todos os módulos:
   ```bash
   gcc -o monitoramento_fabrica main.c avl.c hash.c lse_neutra.c bomba.c -lm
