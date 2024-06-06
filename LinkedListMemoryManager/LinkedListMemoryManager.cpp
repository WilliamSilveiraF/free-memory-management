#include "LinkedListMemoryManager.h"

/**
 * Construtor que inicializa o gerenciador com um bloco inicial que representa toda a memória disponível.
 * totalMemory: quantidade total de memória a ser gerenciada.
 * blockSize: tamanho do bloco em bytes, utilizado para ajustes de alocação.
 * allocAlgorithm: algoritmo de alocação a ser usado ("first_fit" ou "best_fit").
*/
LinkedListMemoryManager::LinkedListMemoryManager(int totalMemory, int blockSize, const std::string& allocAlgorithm)
    : blockSize(blockSize), allocAlgorithm(allocAlgorithm) {
    head = new MemoryBlock(0, totalMemory, true);
}

/**
 * Destruidor que libera todos os blocos de memória da lista para evitar vazamentos de memória.
*/
LinkedListMemoryManager::~LinkedListMemoryManager() {
    MemoryBlock* current = head;
    while (current != nullptr) {
        MemoryBlock* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

/**
 * Tenta alocar memória de acordo com o tamanho solicitado usando o algoritmo de alocação configurado.
 * size: tamanho da memória a ser alocada em bytes.
 * Retorna o endereço inicial do bloco alocado ou -1 se a alocação falhar.
*/
int LinkedListMemoryManager::allocate(int size) {
    MemoryBlock* method = (allocAlgorithm == "first_fit") ? firstFit(size) : bestFit(size);
    if (method != nullptr) {
        return allocateBlock(method, size);
    }
    std::cout << "Not enough memory to allocate." << std::endl;
    return -1;
}

/**
 * Implementação do algoritmo First Fit para encontrar o primeiro bloco suficientemente grande que está livre.
 * size: tamanho do bloco requerido em bytes.
 * Retorna um ponteiro para o bloco se um adequado for encontrado, ou nullptr caso contrário.
*/
MemoryBlock* LinkedListMemoryManager::firstFit(int size) {
    MemoryBlock* current = head;
    while (current != nullptr) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

/**
 * Implementação do algoritmo Best Fit para encontrar o menor bloco livre que se ajuste ao tamanho requerido.
 * size: tamanho do bloco requerido em bytes.
 * Retorna um ponteiro para o bloco se um adequado for encontrado, ou nullptr caso contrário.
*/
MemoryBlock* LinkedListMemoryManager::bestFit(int size) {
    MemoryBlock* bestFit = nullptr;
    int bestFitSize = INT_MAX;
    MemoryBlock* current = head;
    while (current != nullptr) {
        if (current->free && current->size >= size && current->size < bestFitSize) {
            bestFit = current;
            bestFitSize = current->size;
        }
        current = current->next;
    }
    return bestFit;
}

/**
 * Aloca um bloco de memória, atualizando a lista de blocos conforme necessário.
 * block: bloco a ser alocado.
 * size: tamanho da alocação em bytes.
 * Retorna o endereço inicial do bloco alocado.
*/
int LinkedListMemoryManager::allocateBlock(MemoryBlock* block, int size) {
    if (block->size == size) {
        block->free = false;
    } else {
        MemoryBlock* newBlock = new MemoryBlock(block->start + size, block->size - size, true);
        newBlock->next = block->next;
        newBlock->prev = block;
        if (newBlock->next) {
            newBlock->next->prev = newBlock;
        }
        block->next = newBlock;
        block->size = size;
        block->free = false;
    }
    std::cout << "Allocated " << size << " bytes at address " << block->start << std::endl;
    return block->start;
}

/**
 * Libera um bloco de memória e tenta mesclar blocos adjacentes livres para otimizar o uso de espaço.
 * address: endereço do bloco a ser liberado.
 * size: tamanho do bloco a ser liberado em bytes.
*/
void LinkedListMemoryManager::free(int address, int size) {
    MemoryBlock* current = head;
    while (current != nullptr) {
        if (current->start == address && current->size == size && !current->free) {
            current->free = true;
            mergeBlocks(current);
            std::cout << "Freed " << size << " bytes starting at address " << address << std::endl;
            return;
        }
        current = current->next;
    }
    std::cout << "Invalid free operation. No matching block found." << std::endl;
}

/**
 * Mescla blocos adjacentes livres para formar um bloco maior, reduzindo a fragmentação.
 * block: bloco para começar a tentativa de mesclagem.
*/
void LinkedListMemoryManager::mergeBlocks(MemoryBlock* block) {
    if (block->prev && block->prev->free) {
        block->prev->size += block->size;
        block->prev->next = block->next;
        if (block->next) {
            block->next->prev = block->prev;
        }
        block = block->prev;
    }
    if (block->next && block->next->free) {
        block->size += block->next->size;
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
        }
    }
}

/**
 * Exibe o estado atual da memória, mostrando todos os blocos e seu status (livre ou ocupado).
*/
void LinkedListMemoryManager::displayMemory() {
    MemoryBlock* current = head;
    while (current != nullptr) {
        std::cout << "Block at " << current->start << ", size " << current->size
                  << ", " << (current->free ? "free" : "occupied") << std::endl;
        current = current->next;
    }
}
