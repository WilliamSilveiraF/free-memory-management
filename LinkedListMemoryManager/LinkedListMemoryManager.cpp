#include "LinkedListMemoryManager.h"

LinkedListMemoryManager::LinkedListMemoryManager(int totalMemory, int blockSize, const std::string& allocAlgorithm)
    : blockSize(blockSize), allocAlgorithm(allocAlgorithm) {
    head = new MemoryBlock(0, totalMemory, true);
}

LinkedListMemoryManager::~LinkedListMemoryManager() {
    MemoryBlock* current = head;
    while (current != nullptr) {
        MemoryBlock* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

int LinkedListMemoryManager::allocate(int size) {
    MemoryBlock* method = (allocAlgorithm == "first_fit") ? firstFit(size) : bestFit(size);
    if (method != nullptr) {
        return allocateBlock(method, size);
    }
    std::cout << "Not enough memory to allocate." << std::endl;
    return -1;
}

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

void LinkedListMemoryManager::displayMemory() {
    MemoryBlock* current = head;
    while (current != nullptr) {
        std::cout << "Block at " << current->start << ", size " << current->size
                  << ", " << (current->free ? "free" : "occupied") << std::endl;
        current = current->next;
    }
}
