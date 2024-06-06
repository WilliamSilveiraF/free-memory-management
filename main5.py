
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
    
class BitmapMemoryManager:
    def __init__(self, total_memory, block_size, alloc_algorithm):
        num_blocks = (total_memory + block_size - 1) // block_size
        self.bitmap = Bitmap(num_blocks)
        self.alloc_algorithm = alloc_algorithm
        self.block_size = block_size

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
        size = num_blocks_needed * self.block_size  # Calculate the size based on the number of blocks and block size
        for start, length in self.bitmap.find_free_blocks(num_blocks_needed):
            if length >= num_blocks_needed:
                self.bitmap.set_bits(start, num_blocks_needed)
                print(f"First Fit: Allocated {size} bytes at block {start}")
                return start * self.block_size
        print("Not enough memory to allocate.")
        return None

    def best_fit(self, num_blocks_needed):
        size = num_blocks_needed * self.block_size  # Calculate the size based on the number of blocks and block size
        best_fit = None
        best_start = None
        for start, length in self.bitmap.find_free_blocks(num_blocks_needed):
            if length >= num_blocks_needed and (best_fit is None or length < best_fit):
                best_fit = length
                best_start = start
        if best_fit is not None:
            self.bitmap.set_bits(best_start, num_blocks_needed)
            print(f"Best Fit: Allocated {size} bytes at block {best_start}")
            return best_start * self.block_size
        print("Not enough memory to allocate.")
        return None

    def free(self, start_address):
        block_index = start_address // self.block_size
        # Assuming we know the exact number of blocks that need to be freed, which could be an improvement point
        self.bitmap.clear_bits(block_index, 1)  # Simplified: only one block freed
        print(f"Freed memory at block {block_index}")

    def display_memory(self):
        print("Memory Bitmap: " + str(self.bitmap))

class MemoryBlock:
    def __init__(self, start, size, free=True):
        self.start = start
        self.size = size
        self.free = free
        self.next = None
        self.prev = None

class LinkedListMemoryManager:
    def __init__(self, total_memory, block_size, alloc_algorithm):
        self.head = MemoryBlock(0, total_memory, free=True)
        self.alloc_algorithm = alloc_algorithm  # "first_fit" ou "best_fit"
        self.block_size = block_size

    def allocate(self, size):
        method = self.first_fit if self.alloc_algorithm == "first_fit" else self.best_fit
        return method(size)

    def first_fit(self, size):
        current = self.head
        while current:
            if current.free and current.size >= size:
                return self.allocate_block(current, size)
            current = current.next
        print("Not enough memory to allocate.")
        return None
    
    def best_fit(self, size):
        best_fit = None
        best_fit_size = float('inf')

        current = self.head
        while current:
            if current.free and current.size >= size and current.size < best_fit_size:
                best_fit = current
                best_fit_size = current.size
            current = current.next

        if best_fit:
            return self.allocate_block(best_fit, size)
        print("Not enough memory to allocate.")
        return None

    def allocate_block(self, block, size):
        if block.size == size:
            block.free = False
        else:
            new_block = MemoryBlock(block.start + size, block.size - size, True)
            new_block.next = block.next
            new_block.prev = block
            if new_block.next:
                new_block.next.prev = new_block
            block.next = new_block
            block.size = size
            block.free = False
        print(f"Allocated {size} bytes at address {block.start}")
        return block.start

    def free(self, address):
        current = self.head
        while current:
            if current.start == address:
                current.free = True
                self.merge_blocks(current)
                print(f"Freed memory at address {address}")
                return
            current = current.next
        print("Invalid free operation.")

    def merge_blocks(self, block):
        if block.prev and block.prev.free:
            block.prev.size += block.size
            block.prev.next = block.next
            if block.next:
                block.next.prev = block.prev
            block = block.prev
        if block.next and block.next.free:
            block.size += block.next.size
            block.next = block.next.next
            if block.next:
                block.next.prev = block

    def display_memory(self):
        current = self.head
        while current:
            print(f"Block at {current.start}, size {current.size}, {'free' if current.free else 'occupied'}")
            current = current.next



class MemoryManager:
    def __init__(self, total_memory, block_size, management_type, alloc_algorithm):
        self.total_memory = total_memory
        self.block_size = block_size
        self.alloc_algorithm = alloc_algorithm
        if management_type == "bitmap":
            self.manager = BitmapMemoryManager(total_memory, block_size, alloc_algorithm)
        elif management_type == "linked_list":
            self.manager = LinkedListMemoryManager(total_memory, block_size, alloc_algorithm)
        else:
            raise ValueError("Unsupported management type")

    def allocate(self, size):
        return self.manager.allocate(size)

    def free(self, address):
        return self.manager.free(address)

    def display_memory(self):
        return self.manager.display_memory()

def main():
    mm = MemoryManager(1024, 4, "linked_list", "best_fit")
    mm.allocate(512)
    mm.display_memory()
    mm.allocate(256)
    mm.display_memory()
    mm.free(0)
    mm.display_memory()
    mm.allocate(128)
    mm.display_memory()
    mm.allocate(64)
    mm.display_memory()

if __name__ == "__main__":
    main()