#ifndef __MEMORY_BLOCK__
#define __MEMORY_BLOCK__

/**
 * MemoryBlock
 * Representação de um bloco de memória em uma lista duplamente encadeada.
 * 
 * Este componente serve como os nós na implementação da lista duplamente encadeada usada para
 * gerenciar a alocação dinâmica de memória em um sistema de gerenciamento de memória. Cada bloco
 * contém informações sobre seu tamanho, estado (livre ou ocupado) e ponteiros para blocos adjacentes.
 * 
 * - `start`: Endereço de início do bloco de memória.
 * - `size`: Tamanho do bloco de memória em bytes.
 * - `free`: Estado do bloco, indicando se está livre (true) ou ocupado (false).
 * - `next`: Ponteiro para o próximo bloco na lista.
 * - `prev`: Ponteiro para o bloco anterior na lista.
 * 
 * Essa estrutura é essencial para o gerenciamento eficiente de memória, permitindo a alocação,
 * desalocação e otimização do uso da memória através de algoritmos de fusão de blocos adjacentes.
 */

class MemoryBlock {
public:
    int start;
    int size;
    bool free;
    MemoryBlock* next;
    MemoryBlock* prev;

    MemoryBlock(int start, int size, bool free);
};

#endif
