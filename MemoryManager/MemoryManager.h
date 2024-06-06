#ifndef __MEMORY_MANAGER__
#define __MEMORY_MANAGER__

#include <iostream>
#include <memory>
#include <map>
#include <string>
#include "BitmapMemoryManager.h"
#include "LinkedListMemoryManager.h"

/**
 * MemoryManager
 * Classe central para gerenciamento de memória que abstrai e coordena diferentes estratégias de gerenciamento de memória.
 * 
 * Esta classe permite a seleção dinâmica entre diferentes técnicas de gerenciamento de memória, como bitmap e lista duplamente encadeada,
 * e oferece uma interface unificada para alocação e desalocação de memória. A classe é projetada para ser flexível e extensível,
 * facilitando a adição de novos métodos de gerenciamento de memória.
 * 
 * - `totalMemory`: Total de memória gerenciada pelo sistema.
 * - `blockSize`: Tamanho dos blocos de memória para alocação.
 * - `allocAlgorithm`: Algoritmo de alocação utilizado (ex.: first_fit, best_fit).
 * - `bitmapManager`: Gerenciador de memória que utiliza bitmap para gerenciamento de blocos.
 * - `linkedListManager`: Gerenciador de memória que utiliza uma lista duplamente encadeada.
 * - `idToAddressSize`: Dicionário que mapeia IDs de alocação para seus endereços e tamanhos correspondentes, facilitando a gestão e desalocação por ID.
 */

class MemoryManager {
private:
    int totalMemory;
    int blockSize;
    std::string allocAlgorithm;
    std::unique_ptr<BitmapMemoryManager> bitmapManager;
    std::unique_ptr<LinkedListMemoryManager> linkedListManager;
    std::map<int, std::pair<int, int>> idToAddressSize; 

public:
    /**
     * Construtor do MemoryManager.
     * Inicializa o gerenciador de memória com o tipo de gerenciamento desejado e o algoritmo de alocação.
     * 
     * totalMemory: Total de memória a ser gerenciada.
     * blockSize: Tamanho de cada bloco de memória.
     * managementType: Tipo de gerenciamento de memória ("bitmap" ou "linked_list").
     * allocAlgorithm: Algoritmo de alocação a ser utilizado.
     */
    MemoryManager(int totalMemory, int blockSize, const std::string& managementType, const std::string& allocAlgorithm);
    
    /**
     * Aloca memória com um determinado ID.
     * 
     * size: Tamanho da memória a ser alocada em bytes.
     * id: Identificador único da alocação.
     * Retorna o Endereço do bloco de memória alocado ou -1 em caso de falha.
     */
    int allocate(int size, int id);

    /**
     * Libera a memória associada a um ID específico.
     * 
     * id: Identificador único da alocação a ser liberada.
     */
    void free(int id);

    /**
     * Exibe o estado atual da memória, mostrando quais blocos estão alocados ou livres.
     */
    void displayMemory();
};

#endif
