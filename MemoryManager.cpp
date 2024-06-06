#include <iostream>
#include <memory>
#include <map>
#include <string>
#include "BitmapMemoryManager.cpp"
#include "LinkedListMemoryManager.cpp"

class MemoryManager {
private:
    int totalMemory;
    int blockSize;
    std::string allocAlgorithm;
    std::unique_ptr<BitmapMemoryManager> bitmapManager;
    std::unique_ptr<LinkedListMemoryManager> linkedListManager;
    std::map<int, std::pair<int, int>> idToAddressSize;  // Mapeia IDs para endereços e tamanhos

public:
    MemoryManager(int totalMemory, int blockSize, const std::string& managementType, const std::string& allocAlgorithm)
        : totalMemory(totalMemory), blockSize(blockSize), allocAlgorithm(allocAlgorithm) {
        if (managementType == "bitmap") {
            bitmapManager.reset(new BitmapMemoryManager(totalMemory, blockSize));  // Replace make_unique
        } else if (managementType == "linked_list") {
            linkedListManager.reset(new LinkedListMemoryManager(totalMemory, blockSize, allocAlgorithm));  // Replace make_unique
        } else {
            throw std::invalid_argument("Unsupported management type");
        }
    }

    int allocate(int size, int id) {
        int address = (bitmapManager ? bitmapManager->allocate(size) : linkedListManager->allocate(size));
        if (address != -1) {
            idToAddressSize[id] = std::make_pair(address, size);
        }
        return address;
    }

    void free(int id) {
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

    void displayMemory() {
        if (bitmapManager) {
            bitmapManager->displayMemory();
        } else {
            linkedListManager->displayMemory();
        }
    }
};
