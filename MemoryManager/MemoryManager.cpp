#include "MemoryManager.h"

MemoryManager::MemoryManager(int totalMemory, int blockSize, const std::string& managementType, const std::string& allocAlgorithm)
    : totalMemory(totalMemory), blockSize(blockSize), allocAlgorithm(allocAlgorithm) {
    if (managementType == "bitmap") {
        bitmapManager.reset(new BitmapMemoryManager(totalMemory, blockSize));
    } else if (managementType == "linked_list") {
        linkedListManager.reset(new LinkedListMemoryManager(totalMemory, blockSize, allocAlgorithm));
    } else {
        throw std::invalid_argument("Unsupported management type");
    }
}

int MemoryManager::allocate(int size, int id) {
    int address = (bitmapManager ? bitmapManager->allocate(size) : linkedListManager->allocate(size));
    if (address != -1) {
        idToAddressSize[id] = std::make_pair(address, size);
    }
    return address;
}

void MemoryManager::free(int id) {
    auto it = idToAddressSize.find(id);
    if (it != idToAddressSize.end()) {
        int address = it->second.first;
        int size = it->second.second;
        if (bitmapManager) {
            bitmapManager->free(address, size);
        } else {
            linkedListManager->free(address, size);
        }
        idToAddressSize.erase(it);
        std::cout << "Successfully freed memory for ID " << id << " at address " << address << std::endl;
    } else {
        std::cout << "ID " << id << " not found" << std::endl;
    }
}

void MemoryManager::displayMemory() {
    if (bitmapManager) {
        bitmapManager->displayMemory();
    } else {
        linkedListManager->displayMemory();
    }
}
