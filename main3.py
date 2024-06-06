class Bitmap:
    def __init__(self, size):
        self.size = size
        self.bitmap = [0] * size

    def set_bits(self, start, num_blocks):
        for i in range(start, start + num_blocks):
            self.bitmap[i] = 1

    def clear_bits(self, start, num_blocks):
        for i in range(start, start + num_blocks):
            self.bitmap[i] = 0

    def find_free_blocks(self, num_blocks_needed):
        current_start = None
        current_length = 0
        free_blocks = []

        for i in range(self.size + 1):
            if i < self.size and self.bitmap[i] == 0:
                if current_start is None:
                    current_start = i
                current_length += 1
            else:
                if current_start is not None:
                    if current_length >= num_blocks_needed:
                        free_blocks.append((current_start, current_length))
                    current_start = None
                    current_length = 0
        return free_blocks

    def __str__(self):
        return "".join(map(str, self.bitmap))

class MemoryManager:
    def __init__(self, total_memory, block_size, alloc_algorithm):
        self.total_memory = total_memory
        self.block_size = block_size
        self.num_blocks = (total_memory + self.block_size - 1) // self.block_size
        self.bitmap = Bitmap(self.num_blocks)
        self.alloc_algorithm = alloc_algorithm

    def allocate(self, size):
        num_blocks_needed = (size + self.block_size - 1) // self.block_size
        if self.alloc_algorithm == "first_fit":
            return self.first_fit(num_blocks_needed)
        elif self.alloc_algorithm == "best_fit":
            return self.best_fit(num_blocks_needed)
        else:
            print("Allocation algorithm not supported.")
            return None

    def first_fit(self, num_blocks_needed):
        for start, length in self.bitmap.find_free_blocks(num_blocks_needed):
            if length >= num_blocks_needed:
                self.bitmap.set_bits(start, num_blocks_needed)
                print(f"First Fit: Allocated at block {start}")
                return start * self.block_size
        print("Not enough memory to allocate.")
        return None

    def best_fit(self, num_blocks_needed):
        best_fit = None
        for start, length in self.bitmap.find_free_blocks(num_blocks_needed):
            if length >= num_blocks_needed and (best_fit is None or length < best_fit[1]):
                best_fit = (start, length)
        if best_fit:
            self.bitmap.set_bits(best_fit[0], num_blocks_needed)
            print(f"Best Fit: Allocated at block {best_fit[0]}")
            return best_fit[0] * self.block_size
        print("Not enough memory to allocate.")
        return None

    def free(self, start_address):
        block_index = start_address // self.block_size
        # Assuming we know how many blocks to free (could be tracked or passed as an argument)
        # Here we simplify by freeing just one block:
        self.bitmap.clear_bits(block_index, 1)
        print(f"Freed memory at block {block_index}")

    def display_memory(self):
        print("Memory Bitmap: " + str(self.bitmap))

def main():
    mm = MemoryManager(1024, 4, "best_fit")
    mm.allocate(16)
    mm.allocate(20)
    mm.allocate(120)
    mm.allocate(24)
    mm.display_memory()
    mm.free(12)
    mm.free(16)
    mm.free(20)
    mm.free(24)
    mm.free(28)
    mm.free(32)
    mm.free(52)
    mm.display_memory()
    mm.allocate(4)
    mm.display_memory()

if __name__ == "__main__":
    main()
