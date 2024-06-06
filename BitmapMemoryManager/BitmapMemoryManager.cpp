#include "BitmapMemoryManager.h"

/**
 * Construtor que inicializa o bitmap com base no tamanho total da memória e no tamanho de bloco.
 * totalMemory: quantidade total de memória a ser gerenciada.
 * blockSize: tamanho de cada bloco de memória em bytes.
*/
BitmapMemoryManager::BitmapMemoryManager(int totalMemory, int blockSize)
    : bitmap((totalMemory + blockSize - 1) / blockSize), blockSize(blockSize) {}

/**
 * Método para alocar memória. Tenta encontrar blocos livres suficientes para satisfazer o pedido de alocação.
 * size: tamanho da memória solicitada em bytes.
 * Retorna o endereço inicial do bloco alocado ou -1 se não houver espaço suficiente disponível.
*/
int BitmapMemoryManager::allocate(int size) {
    int numBlocksNeeded = (size + blockSize - 1) / blockSize;
    auto freeBlocks = bitmap.findFreeBlocks(numBlocksNeeded);
    for (const auto& block : freeBlocks) {
        if (block.second >= numBlocksNeeded) {
            bitmap.setBits(block.first, numBlocksNeeded);
            std::cout << "Allocated " << size << " bytes at block " << block.first << std::endl;
            return block.first * blockSize;
        }
    }
    std::cout << "Not enough memory to allocate." << std::endl;
    return -1;
}

/**
 * Método para liberar memória previamente alocada.
 * startAddress: endereço inicial do bloco de memória a ser liberado.
 * size: tamanho do bloco de memória a ser liberado em bytes.
*/
void BitmapMemoryManager::free(int startAddress, int size) {
    int numBlocks = (size + blockSize - 1) / blockSize;
    bitmap.clearBits(startAddress / blockSize, numBlocks);
    std::cout << "Freed " << numBlocks << " blocks starting from block " << startAddress / blockSize << std::endl;
}

/**
 * Método para exibir o estado atual da memória, mostrando o bitmap de alocação.
 * Exibe '1' para blocos alocados e '0' para blocos livres.
*/
void BitmapMemoryManager::displayMemory() {
    const auto& bits = bitmap.getBitmap();
    std::cout << "Memory Bitmap: ";
    for (bool bit : bits) {
        std::cout << (bit ? '1' : '0');
    }
    std::cout << std::endl;
}
