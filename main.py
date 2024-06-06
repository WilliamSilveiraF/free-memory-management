class MemoryManager:
    def __init__(self, total_memory, block_size):
        self.total_memory = total_memory
        self.block_size = block_size
        self.num_blocks = (total_memory + block_size - 1) // block_size  # Arredonda para cima
        self.bitmap = [0] * self.num_blocks  # Inicializa todos os blocos como livres

    def allocate(self, size):
        num_blocks_needed = (size + self.block_size - 1) // self.block_size
        for i in range(self.num_blocks - num_blocks_needed + 1):  # Verifica espaço para alocação
            if all(self.bitmap[j] == 0 for j in range(i, i + num_blocks_needed)):
                for j in range(i, i + num_blocks_needed):
                    self.bitmap[j] = 1
                print(f"Allocated {size} bytes starting at block {i}")
                return i * self.block_size
        print("Not enough memory to allocate.")
        return None

    def free(self, start_address):
        block_index = start_address // self.block_size
        # Considerando que sabemos quantos blocos foram alocados ou mantendo um registro separado
        # Aqui precisamos saber quantos blocos liberar, que poderia ser passado como parâmetro adicional
        # Por simplificação, vamos assumir que liberamos um único bloco:
        if block_index < self.num_blocks and self.bitmap[block_index] == 1:
            self.bitmap[block_index] = 0
            print(f"Freed memory at block {block_index}")
        else:
            print("Invalid free operation or block already free.")

    def display_memory(self):
        print("".join(map(str, self.bitmap)))

def main():
    mm = MemoryManager(1024, 4)  # Gerencia 1024 bytes com blocos de 4 bytes
    mm.allocate(16)  # Aloca 16 bytes
    mm.display_memory()
    mm.free(3)  # Libera memória do início
    mm.free(9)  # Libera memória do início
    mm.display_memory()

if __name__ == "__main__":
    main()
