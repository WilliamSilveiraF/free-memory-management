class MemoryBlock:
    def __init__(self, start, size, free=True):
        self.start = start
        self.size = size
        self.free = free
        self.next = None
        self.prev = None

class MemoryManager:
    def __init__(self, total_memory, block_size, alloc_algorithm):
        self.total_memory = total_memory
        self.block_size = block_size
        self.alloc_algorithm = alloc_algorithm
        self.head = MemoryBlock(0, total_memory, free=True)
    
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

def main():
    mm = MemoryManager(1024, 256, "best_fit")
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

