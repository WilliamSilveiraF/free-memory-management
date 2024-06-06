#ifndef __BITMAP_MEMORY_MANAGER__
#define __BITMAP_MEMORY_MANAGER__

#include <iostream>
#include <vector>
#include "Bitmap.h"

class BitmapMemoryManager {
private:
    Bitmap bitmap;
    int blockSize;

public:
    BitmapMemoryManager(int totalMemory, int blockSize);
    int allocate(int size);
    void free(int startAddress, int size);
    void displayMemory();
};

#endif 
