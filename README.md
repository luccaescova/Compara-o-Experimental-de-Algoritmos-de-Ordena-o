# Comparação Experimental de Algoritmos de Ordenação

Este projeto foi desenvolvido como parte das atividades práticas da disciplina de **Análise de Algoritmos**. O objetivo principal é implementar, testar e comparar o desempenho empírico (tempo de execução e quantidade de operações) de três algoritmos de ordenação com diferentes complexidades assintóticas no pior caso.

## 🚀 Algoritmos Escolhidos
Para garantir uma análise justa e em conformidade com as restrições da atividade, foram selecionados algoritmos de classes de complexidade distintas no pior caso:
1. **Insertion Sort**: Complexidade quadrática no pior caso — $O(n^2)$.
2. **Merge Sort**: Complexidade linearítmica no pior caso — $O(n \log n)$.
3. **Quick Sort**: Complexidade quadrática no pior caso — $O(n^2)$, mas com caso médio linearítmico — $O(n \log n)$ de alta eficiência prática.

---

## 📊 Estrutura dos Testes
O programa gera vetores preenchidos com números aleatórios através do algoritmo `std::mt19937` e realiza testes com três tamanhos de entrada:
* **1.000 elementos**
* **10.000 elementos**
* **100.000 elementos**

### Critérios de Isonomia:
* **Mesma Entrada:** Para cada tamanho de vetor, exatamente o mesmo arranjo inicial é enviado como cópia para os três algoritmos.
* **Repetibilidade:** Cada algoritmo é executado **3 vezes** por tamanho de entrada para mitigar variações causadas pelo sistema operacional.
* **Métricas Coletadas:** Tempo de cada execução (em segundos), tempo médio, desvio padrão e contagem de operações (deslocamentos no Insertion/Merge e trocas no Quick).

---

## 🛠️ Como Executar o Projeto

### Pré-requisitos
* Sistema Operacional Windows (devido ao uso da biblioteca `<windows.h>` para tratamento do padrão de caracteres UTF-8 no terminal).
* Compilador C++ com suporte ao padrão **C++11** ou superior (GCC/MinGW, Clang ou MSVC).

### Compilação via Terminal
Navegue até a pasta onde está o arquivo `main.cpp` e execute o comando abaixo:
```bash
g++ -std=c++11 main.cpp -o comparador
