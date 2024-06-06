#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "Bitmap.cpp"

class BitmapMemoryManager {
private:
    Bitmap bitmap;
    int blockSize;

public:
    BitmapMemoryManager(int totalMemory, int blockSize)
        : bitmap((totalMemory + blockSize - 1) / blockSize), blockSize(blockSize) {}

    int allocate(int size) {
        int numBlocksNeeded = (size + blockSize - 1) / blockSize;
        auto freeBlocks = bitmap.findFreeBlocks(numBlocksNeeded);
        for (const auto& block : freeBlocks) {
            if (block.second >= numBlocksNeeded) {
                bitmap.setBits(block.first, numBlocksNeeded);
                std::cout << "Allocated " << size << " bytes at block " << block.first << std::endl;
                return block.first * blockSize;
            }
        }
        std::cout << "Not enough memory to allocate." << std::endl;
        return -1;
    }

    void free(int startAddress, int size) {
        int numBlocks = (size + blockSize - 1) / blockSize;
        bitmap.clearBits(startAddress / blockSize, numBlocks);
        std::cout << "Freed " << numBlocks << " blocks starting from block " << startAddress / blockSize << std::endl;
    }

    void displayMemory() {
        const auto& bits = bitmap.getBitmap();
        std::cout << "Memory Bitmap: ";
        for (bool bit : bits) {
            std::cout << (bit ? '1' : '0');
        }
        std::cout << std::endl;
    }
};
