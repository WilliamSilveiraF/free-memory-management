#include <vector>
#include <iostream>

class Bitmap {
private:
    std::vector<bool> bitmap;

public:
    Bitmap(int size) : bitmap(size, false) {}

    void setBits(int start, int numBlocks) {
        for (int i = start; i < start + numBlocks; ++i) {
            bitmap[i] = true;
        }
    }

    void clearBits(int start, int numBlocks) {
        for (int i = start; i < start + numBlocks; ++i) {
            bitmap[i] = false;
        }
    }

    std::vector<std::pair<int, int>> findFreeBlocks(int numBlocksNeeded) {
        std::vector<std::pair<int, int>> freeBlocks;
        int currentStart = -1;
        int currentLength = 0;

        for (size_t i = 0; i <= bitmap.size(); ++i) {
            if (i < bitmap.size() && !bitmap[i]) {
                if (currentStart == -1) {
                    currentStart = i;
                }
                currentLength++;
            } else {
                if (currentStart != -1 && currentLength >= numBlocksNeeded) {
                    freeBlocks.push_back({currentStart, currentLength});
                }
                currentStart = -1;
                currentLength = 0;
            }
        }
        return freeBlocks;
    }

    const std::vector<bool>& getBitmap() const {
        return bitmap;
    }
};
