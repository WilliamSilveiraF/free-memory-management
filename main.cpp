#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "MemoryManager.h"

void processCommands(const std::string& inputFileName) {
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file: " << inputFileName << std::endl;
        return;
    }

    std::string line;
    getline(inputFile, line);
    std::string managementType = (line == "1") ? "bitmap" : "linked_list";

    getline(inputFile, line);
    int totalMemory = std::stoi(line);

    getline(inputFile, line);
    int blockSize = std::stoi(line);

    getline(inputFile, line);
    std::string allocAlgorithm = (line == "1") ? "first_fit" : "best_fit";

    MemoryManager memoryManager(totalMemory, blockSize, managementType, allocAlgorithm);

    while (getline(inputFile, line)) {
        std::istringstream iss(line);
        char commandType;
        int sizeOrId, id;

        iss >> commandType;
        if (commandType == 'A') {
            iss >> sizeOrId >> id;
            std::cout << "Allocating " << sizeOrId << " bytes with ID " << id << std::endl;
            memoryManager.allocate(sizeOrId, id);
        } else if (commandType == 'D') {
            iss >> id;
            std::cout << "Deallocating memory with ID " << id << std::endl;
            memoryManager.free(id);
        }
    }

    memoryManager.displayMemory();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string inputFileName(argv[1]);
    processCommands(inputFileName);

    return 0;
}
