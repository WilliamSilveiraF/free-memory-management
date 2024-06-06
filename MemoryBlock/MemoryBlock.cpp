#include "MemoryBlock.h"

MemoryBlock::MemoryBlock(int start, int size, bool free)
    : start(start), size(size), free(free), next(nullptr), prev(nullptr) {}
