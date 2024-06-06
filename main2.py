class MemoryManager:
    def __init__(self, total_memory, block_size, alloc_algorithm):
        self.total_memory = total_memory
        self.block_size = block_size
        self.num_blocks = (total_memory + block_size - 1) // block_size
        self.bitmap = [0] * self.num_blocks
        self.alloc_algorithm = alloc_algorithm  # "first_fit" ou "best_fit"

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
        for i in range(self.num_blocks - num_blocks_needed + 1):
            if all(self.bitmap[j] == 0 for j in range(i, i + num_blocks_needed)):
                for j in range(i, i + num_blocks_needed):
                    self.bitmap[j] = 1
                print(f"First Fit: Allocated at block {i}")
                return i * self.block_size
        print("Not enough memory to allocate.")
        return None

    def best_fit(self, num_blocks_needed):
        best_start = None
        best_size = float('inf')

        current_start = None
        current_length = 0

        for i in range(self.num_blocks):
            if self.bitmap[i] == 0:
                if current_start is None:
                    current_start = i
                current_length += 1
            else:
                if current_start is not None and current_length >= num_blocks_needed:
                    if current_length < best_size:
                        best_size = current_length
                        best_start = current_start
                current_start = None
                current_length = 0

        # Check the last sequence
        if current_start is not None and current_length >= num_blocks_needed:
            if current_length < best_size:
                best_start = current_start
                best_size = current_length

        if best_start is not None:
            for j in range(best_start, best_start + num_blocks_needed):
                self.bitmap[j] = 1
            print(f"Best Fit: Allocated at block {best_start}")
            return best_start * self.block_size

        print("Not enough memory to allocate.")
        return None

    def free(self, start_address):
        block_index = start_address // self.block_size
        if block_index < self.num_blocks and self.bitmap[block_index] == 1:
            self.bitmap[block_index] = 0
            print(f"Freed memory at block {block_index}")
        else:
            print("Invalid free operation or block already free.")

    def display_memory(self):
        print("Memory Bitmap: " + "".join(map(str, self.bitmap)))

def main():
    mm = MemoryManager(1024, 4, "first_fit")
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


