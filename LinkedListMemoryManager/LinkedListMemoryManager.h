#ifndef __LINKED_LIST_MEMORY_MANAGER__
#define __LINKED_LIST_MEMORY_MANAGER__

#include <iostream>
#include <string>
#include <climits>
#include "../MemoryBlock/MemoryBlock.h"

/**
 * LinkedListMemoryManager
 * Gerenciador de memória que usa uma lista duplamente encadeada para controlar blocos de memória.
 * - Mantém um ponteiro para o primeiro bloco de memória, gerenciando blocos como uma lista encadeada.
 * - Suporta dois algoritmos de alocação: first_fit e best_fit, para encontrar o melhor bloco disponível para alocação.
 * - Implementa funcionalidades para alocar, liberar e exibir o estado da memória, além de mesclar blocos adjacentes quando são liberados.
 */

class LinkedListMemoryManager {
private:
    MemoryBlock* head;
    int blockSize;
    std::string allocAlgorithm;

public:
    /**
     * Construtor que inicializa o gerenciador com um bloco inicial que representa toda a memória disponível.
     * totalMemory: quantidade total de memória a ser gerenciada.
     * blockSize: tamanho do bloco em bytes, utilizado para ajustes de alocação.
     * allocAlgorithm: algoritmo de alocação a ser usado ("first_fit" ou "best_fit").
    */
    LinkedListMemoryManager(int totalMemory, int blockSize, const std::string& allocAlgorithm);
    
    /**
     * Destruidor que libera todos os blocos de memória da lista para evitar vazamentos de memória.
    */
    ~LinkedListMemoryManager();

    /**
     * Tenta alocar memória de acordo com o tamanho solicitado usando o algoritmo de alocação configurado.
     * size: tamanho da memória a ser alocada em bytes.
     * Retorna o endereço inicial do bloco alocado ou -1 se a alocação falhar.
    */
    int allocate(int size);

    /**
     * Libera um bloco de memória e tenta mesclar blocos adjacentes livres para otimizar o uso de espaço.
     * address: endereço do bloco a ser liberado.
     * size: tamanho do bloco a ser liberado em bytes.
    */
    void free(int address, int size);

    /**
     * Exibe o estado atual da memória, mostrando todos os blocos e seu status (livre ou ocupado).
    */
    void displayMemory();

private:
    /**
     * Implementação do algoritmo First Fit para encontrar o primeiro bloco suficientemente grande que está livre.
     * size: tamanho do bloco requerido em bytes.
     * Retorna um ponteiro para o bloco se um adequado for encontrado, ou nullptr caso contrário.
    */
    MemoryBlock* firstFit(int size);

    /**
     * Implementação do algoritmo Best Fit para encontrar o menor bloco livre que se ajuste ao tamanho requerido.
     * size: tamanho do bloco requerido em bytes.
     * Retorna um ponteiro para o bloco se um adequado for encontrado, ou nullptr caso contrário.
    */
    MemoryBlock* bestFit(int size);

    /**
     * Aloca um bloco de memória, atualizando a lista de blocos conforme necessário.
     * block: bloco a ser alocado.
     * size: tamanho da alocação em bytes.
     * Retorna o endereço inicial do bloco alocado.
    */
    int allocateBlock(MemoryBlock* block, int size);

    /**
     * Mescla blocos adjacentes livres para formar um bloco maior, reduzindo a fragmentação.
     * block: bloco para começar a tentativa de mesclagem.
    */
    void mergeBlocks(MemoryBlock* block);
};

#endif
