#ifndef __BITMAP_MEMORY_MANAGER__
#define __BITMAP_MEMORY_MANAGER__

#include <iostream>
#include <vector>
#include "Bitmap.h"

/**
 * BitmapMemoryManager
 * Gerenciador de memória que usa um bitmap para gerenciar a alocação de blocos de memória.
 * - Usa uma instância da classe Bitmap para manter um registro de blocos de memória livres ou alocados.
 * - Oferece métodos para alocar e liberar memória com base no número de blocos necessários.
 * - Pode exibir o estado atual da memória (bitmap), mostrando visualmente os blocos alocados e livres.
 */
class BitmapMemoryManager {
private:
    Bitmap bitmap;
    int blockSize;

public:
    /**
     * Construtor que inicializa o bitmap com base no tamanho total da memória e no tamanho de bloco.
     * totalMemory: quantidade total de memória a ser gerenciada.
     * blockSize: tamanho de cada bloco de memória em bytes.
    */
    BitmapMemoryManager(int totalMemory, int blockSize);

    /**
     * Método para alocar memória. Tenta encontrar blocos livres suficientes para satisfazer o pedido de alocação.
     * size: tamanho da memória solicitada em bytes.
     * Retorna o endereço inicial do bloco alocado ou -1 se não houver espaço suficiente disponível.
    */
    int allocate(int size);

    /**
     * Método para liberar memória previamente alocada.
     * startAddress: endereço inicial do bloco de memória a ser liberado.
     * size: tamanho do bloco de memória a ser liberado em bytes.
    */
    void free(int startAddress, int size);

    /**
     * Método para exibir o estado atual da memória, mostrando o bitmap de alocação.
     * Exibe '1' para blocos alocados e '0' para blocos livres.
    */
    void displayMemory();
};

#endif 
