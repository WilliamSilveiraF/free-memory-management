#ifndef __BITMAP__
#define __BITMAP__

#include <vector>
#include <utility> 

class Bitmap {
private:
    std::vector<bool> bitmap;

public:
    Bitmap(int size);
    void setBits(int start, int numBlocks);
    void clearBits(int start, int numBlocks);
    std::vector<std::pair<int, int>> findFreeBlocks(int numBlocksNeeded) const;
    const std::vector<bool>& getBitmap() const;
};

#endif 
