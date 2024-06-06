#include "MemoryManager.h"

/**
 * Construtor do MemoryManager.
 * Inicializa o gerenciador de memória com o tipo de gerenciamento desejado e o algoritmo de alocação.
 * 
 * totalMemory: Total de memória a ser gerenciada.
 * blockSize: Tamanho de cada bloco de memória.
 * managementType: Tipo de gerenciamento de memória ("bitmap" ou "linked_list").
 * allocAlgorithm: Algoritmo de alocação a ser utilizado.
 */
MemoryManager::MemoryManager(int totalMemory, int blockSize, const std::string& managementType, const std::string& allocAlgorithm)
    : totalMemory(totalMemory), blockSize(blockSize), allocAlgorithm(allocAlgorithm) {
    if (managementType == "bitmap") {
        bitmapManager.reset(new BitmapMemoryManager(totalMemory, blockSize));
    } else if (managementType == "linked_list") {
        linkedListManager.reset(new LinkedListMemoryManager(totalMemory, blockSize, allocAlgorithm));
    } else {
        throw std::invalid_argument("Unsupported management type");
    }
}

/**
 * Aloca memória com um determinado ID.
 * 
 * size: Tamanho da memória a ser alocada em bytes.
 * id: Identificador único da alocação.
 * Retorna o Endereço do bloco de memória alocado ou -1 em caso de falha.
 */
int MemoryManager::allocate(int size, int id) {
    int address = (bitmapManager ? bitmapManager->allocate(size) : linkedListManager->allocate(size));
    if (address != -1) {
        idToAddressSize[id] = std::make_pair(address, size);
    }
    return address;
}

/**
 * Libera a memória associada a um ID específico.
 * 
 * id: Identificador único da alocação a ser liberada.
 */
void MemoryManager::free(int id) {
    auto it = idToAddressSize.find(id);
    if (it != idToAddressSize.end()) {
        int address = it->second.first;
        int size = it->second.second;
        if (bitmapManager) {
            bitmapManager->free(address, size);
        } else {
            linkedListManager->free(address, size);
        }
        idToAddressSize.erase(it);
        std::cout << "Successfully freed memory for ID " << id << " at address " << address << std::endl;
    } else {
        std::cout << "ID " << id << " not found" << std::endl;
    }
}

/**
 * Exibe o estado atual da memória, mostrando quais blocos estão alocados ou livres.
 */
void MemoryManager::displayMemory() {
    if (bitmapManager) {
        bitmapManager->displayMemory();
    } else {
        linkedListManager->displayMemory();
    }
}
