#ifndef __MEMORY_MANAGER__
#define __MEMORY_MANAGER__

#include <iostream>
#include <memory>
#include <map>
#include <string>
#include "BitmapMemoryManager.h"
#include "LinkedListMemoryManager.h"

class MemoryManager {
private:
    int totalMemory;
    int blockSize;
    std::string allocAlgorithm;
    std::unique_ptr<BitmapMemoryManager> bitmapManager;
    std::unique_ptr<LinkedListMemoryManager> linkedListManager;
    std::map<int, std::pair<int, int>> idToAddressSize; 

public:
    MemoryManager(int totalMemory, int blockSize, const std::string& managementType, const std::string& allocAlgorithm);
    int allocate(int size, int id);
    void free(int id);
    void displayMemory();
};

#endif
