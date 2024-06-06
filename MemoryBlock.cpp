#include <iostream>

class MemoryBlock {
public:
    int start;
    int size;
    bool free;
    MemoryBlock* next;
    MemoryBlock* prev;

    MemoryBlock(int start, int size, bool free)
        : start(start), size(size), free(free), next(nullptr), prev(nullptr) {}
};
