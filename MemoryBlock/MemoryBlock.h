#ifndef __MEMORY_BLOCK__
#define __MEMORY_BLOCK__

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
