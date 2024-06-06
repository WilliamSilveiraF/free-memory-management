#ifndef __LINKED_LIST_MEMORY_MANAGER__
#define __LINKED_LIST_MEMORY_MANAGER__

#include <iostream>
#include <string>
#include <climits>
#include "../MemoryBlock/MemoryBlock.h"

class LinkedListMemoryManager {
private:
    MemoryBlock* head;
    int blockSize;
    std::string allocAlgorithm;

public:
    LinkedListMemoryManager(int totalMemory, int blockSize, const std::string& allocAlgorithm);
    ~LinkedListMemoryManager();

    int allocate(int size);
    void free(int address, int size);
    void displayMemory();

private:
    MemoryBlock* firstFit(int size);
    MemoryBlock* bestFit(int size);
    int allocateBlock(MemoryBlock* block, int size);
    void mergeBlocks(MemoryBlock* block);
};

#endif
