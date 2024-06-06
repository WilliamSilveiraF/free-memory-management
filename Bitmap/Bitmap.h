#ifndef __BITMAP__
#define __BITMAP__

#include <vector>
#include <utility> 

/**
 * Bitmap
 * Classe que gerencia um vetor de bits para representar blocos de memória alocados ou livres.
 * - O vetor `bitmap` armazena cada bit que indica se um bloco está alocado (true) ou livre (false).
 * - Oferece funcionalidades para definir bits (alocar blocos) e limpar bits (liberar blocos).
 * - Capaz de encontrar sequências de blocos livres de tamanho necessário para a alocação de memória.
 * - Permite acessar o estado atual do bitmap para propósitos de exibição ou verificação.
 */
class Bitmap {
private:
    std::vector<bool> bitmap;

public:
    Bitmap(int size);

    /**
     * Método para definir (setar) os bits no bitmap, marcando blocos como alocados.
     * start: índice inicial do bloco a ser marcado.
     * umBlocks: número de blocos consecutivos a serem marcados como alocados.
    */
    void setBits(int start, int numBlocks);

    /**
     * Método para limpar (resetar) os bits no bitmap, marcando blocos como livres.
     * start: índice inicial do bloco a ser desmarcado.
     * numBlocks: número de blocos consecutivos a serem marcados como livres.
    */
    void clearBits(int start, int numBlocks);

    /**
     * Método para encontrar blocos livres suficientes para acomodar uma quantidade de blocos necessária.
     * numBlocksNeeded: número de blocos consecutivos necessários.
     * Retorna um vetor de pares (início do bloco livre, tamanho do bloco livre) onde alocação é possível.
    */
    std::vector<std::pair<int, int>> findFreeBlocks(int numBlocksNeeded) const;

    /**
     * Getter para obter uma referência constante ao bitmap, permitindo leitura sem modificação.
    */
    const std::vector<bool>& getBitmap() const;
};

#endif 
