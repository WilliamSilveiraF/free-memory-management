#include <iostream>
#include "Bitmap.h"

/**
 * Construtor que inicializa o bitmap com o tamanho especificado, marcando todos os blocos inicialmente como livres (false).
*/
Bitmap::Bitmap(int size) : bitmap(size, false) {}

/**
 * Método para definir (setar) os bits no bitmap, marcando blocos como alocados.
 * start: índice inicial do bloco a ser marcado.
 * umBlocks: número de blocos consecutivos a serem marcados como alocados.
*/
void Bitmap::setBits(int start, int numBlocks) {
    for (int i = start; i < start + numBlocks; ++i) {
        bitmap[i] = true;
    }
}

/**
 * Método para limpar (resetar) os bits no bitmap, marcando blocos como livres.
 * start: índice inicial do bloco a ser desmarcado.
 * numBlocks: número de blocos consecutivos a serem marcados como livres.
*/
void Bitmap::clearBits(int start, int numBlocks) {
    for (int i = start; i < start + numBlocks; ++i) {
        bitmap[i] = false;
    }
}

/**
 * Método para encontrar blocos livres suficientes para acomodar uma quantidade de blocos necessária.
 * numBlocksNeeded: número de blocos consecutivos necessários.
 * Retorna um vetor de pares (início do bloco livre, tamanho do bloco livre) onde alocação é possível.
*/
std::vector<std::pair<int, int>> Bitmap::findFreeBlocks(int numBlocksNeeded) const {
    std::vector<std::pair<int, int>> freeBlocks;
    int currentStart = -1;
    int currentLength = 0;

    for (size_t i = 0; i <= bitmap.size(); ++i) {
        if (i < bitmap.size() && !bitmap[i]) {
            if (currentStart == -1) {
                currentStart = static_cast<int>(i);
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

/**
 * Getter para obter uma referência constante ao bitmap, permitindo leitura sem modificação.
*/
const std::vector<bool>& Bitmap::getBitmap() const {
    return bitmap;
}
