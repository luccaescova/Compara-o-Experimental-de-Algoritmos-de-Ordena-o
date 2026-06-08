#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <windows.h>

// Estrutura para armazenar as métricas de cada execução
struct Metricas {
    double tempos[3];
    double media;
    double desvio_padrao;
    unsigned long long operacoes; // Trocas ou Movimentações
};

// ==========================================
// 1. INSERTION SORT (Trocas/Movimentações)
// ==========================================
unsigned long long insertionSort(std::vector<int>& arr) {
    unsigned long long mov = 0;
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int chave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
            mov++; // Deslocamento de elemento
        }
        arr[j + 1] = chave;
        if (j + 1 != i) mov++; // Inserção da chave na posição correta
    }
    return mov;
}

// ==========================================
// 2. MERGE SORT (Movimentações de Intercalação)
// ==========================================
void merge(std::vector<int>& arr, int esq, int meio, int dir, unsigned long long& mov) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) { L[i] = arr[esq + i]; mov++; }
    for (int j = 0; j < n2; j++) { R[j] = arr[meio + 1 + j]; mov++; }

    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { arr[k] = L[i]; i++; }
        else { arr[k] = R[j]; j++; }
        k++; mov++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; mov++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; mov++; }
}

void mergeSortAux(std::vector<int>& arr, int esq, int dir, unsigned long long& mov) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        mergeSortAux(arr, esq, meio, mov);
        mergeSortAux(arr, meio + 1, dir, mov);
        merge(arr, esq, meio, dir, mov);
    }
}

unsigned long long mergeSort(std::vector<int>& arr) {
    unsigned long long mov = 0;
    mergeSortAux(arr, 0, arr.size() - 1, mov);
    return mov;
}

// ==========================================
// 3. QUICK SORT (Contagem de Trocas)
// ==========================================
int partition(std::vector<int>& arr, int baixo, int alto, unsigned long long& trocas) {
    int pivo = arr[alto];
    int i = (baixo - 1);
    for (int j = baixo; j <= alto - 1; j++) {
        if (arr[j] < pivo) {
            i++;
            std::swap(arr[i], arr[j]);
            trocas++;
        }
    }
    std::swap(arr[i + 1], arr[alto]);
    trocas++;
    return (i + 1);
}

void quickSortAux(std::vector<int>& arr, int baixo, int alto, unsigned long long& trocas) {
    if (baixo < alto) {
        // CORRIGIDO: de 'bajo' para 'baixo'
        int pi = partition(arr, baixo, alto, trocas);
        quickSortAux(arr, baixo, pi - 1, trocas);
        quickSortAux(arr, pi + 1, alto, trocas);
    }
}

unsigned long long quickSort(std::vector<int>& arr) {
    unsigned long long trocas = 0;
    quickSortAux(arr, 0, arr.size() - 1, trocas);
    return trocas;
}

// ==========================================
// FUNÇÕES AUXILIARES DE CÁLCULO E ESTATÍSTICA
// ==========================================
void calcularEstatisticas(Metricas& m) {
    double soma = 0.0;
    for (int i = 0; i < 3; ++i) soma += m.tempos[i];
    m.media = soma / 3.0;

    double soma_var = 0.0;
    for (int i = 0; i < 3; ++i) soma_var += pow(m.tempos[i] - m.media, 2);
    m.desvio_padrao = sqrt(soma_var / 3.0);
}

void exibirResultados(const std::string& algoritmo, int tamanho, const Metricas& m) {
    std::cout << algoritmo << " (" << tamanho << " elementos):\n";
    std::cout << "  Exec 1: " << m.tempos[0] << " s | Exec 2: " << m.tempos[1] << " s | Exec 3: " << m.tempos[2] << " s\n";
    std::cout << "  Media : " << m.media << " s | Desvio Padrao: " << m.desvio_padrao << " s\n";
    std::cout << "  Operacoes (Trocas/Mov): " << m.operacoes << "\n\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << std::fixed << std::setprecision(6);

    std::vector<int> tamanhos = {1000, 10000, 100000};

    // Gerador de números aleatórios estável
    std::mt19937 gerador(2026);
    std::uniform_int_distribution<int> dist(1, 1000000);

    for (int tam : tamanhos) {
        std::cout << "==================================================\n";
        std::cout << "INICIANDO TESTES PARA TAMANHO: " << tam << "\n";
        std::cout << "==================================================\n\n";

        Metricas mInsertion, mMerge, mQuick;

        // Executar 3 rodadas usando exatamente o MESMO vetor para os 3 algoritmos
        for (int rodada = 0; rodada < 3; ++rodada) {
            std::vector<int> vetor_original(tam);
            for (int i = 0; i < tam; ++i) vetor_original[i] = dist(gerador);

            // Cópia para cada algoritmo
            std::vector<int> vetIns = vetor_original;
            std::vector<int> vetMrg = vetor_original;
            std::vector<int> vetQck = vetor_original;

            // Teste Insertion Sort
            auto start = std::chrono::high_resolution_clock::now();
            mInsertion.operacoes = insertionSort(vetIns);
            auto end = std::chrono::high_resolution_clock::now();
            mInsertion.tempos[rodada] = std::chrono::duration<double>(end - start).count();

            // Teste Merge Sort
            start = std::chrono::high_resolution_clock::now();
            mMerge.operacoes = mergeSort(vetMrg);
            end = std::chrono::high_resolution_clock::now();
            mMerge.tempos[rodada] = std::chrono::duration<double>(end - start).count();

            // Teste Quick Sort
            start = std::chrono::high_resolution_clock::now();
            mQuick.operacoes = quickSort(vetQck);
            end = std::chrono::high_resolution_clock::now();
            mQuick.tempos[rodada] = std::chrono::duration<double>(end - start).count();
        }

        calcularEstatisticas(mInsertion);
        calcularEstatisticas(mMerge);
        calcularEstatisticas(mQuick);

        exibirResultados("Insertion Sort", tam, mInsertion);
        exibirResultados("Merge Sort", tam, mMerge);
        exibirResultados("Quick Sort", tam, mQuick);
    }
    return 0;
}
