class MemoryPoolManager {
private:
    char *head;
    /*
        head: the position of the first free block
    */
    size_t block_size, block_cnt;
    /*
        block_size: the size of each block (in bytes, at least 8);
        block_cnt: the maximum number of blocks
    */
public:
    MemoryPoolManager(char *ptr, size_t block_size_, size_t block_cnt_) : head(ptr), block_size(block_size_),
                                                                          block_cnt(block_cnt_) {
        //to do: code whatever you want here to initialize

        for (size_t i = 0; i < block_cnt_-1; ++i)

            *reinterpret_cast<void **>(head + i * block_size_) = reinterpret_cast<void *>(head +(i + 1) * block_size_);

        *reinterpret_cast<void **>(head + (block_cnt_ - 1) * block_size_) = nullptr;
    }

    void *allocate() {
        //to do: return a pointer pointing at a free block (nullptr if no free block left)
        void *tmp = nullptr;

        if (head == nullptr) return tmp;

        tmp = reinterpret_cast<void *>(head);

        head = reinterpret_cast<char *>(*reinterpret_cast<void **>(head));

        return tmp;
    }

    void free(void *ptr) {
        //to do: make a block ready for reuse (we will guarantee that ptr is a block acquired by previous allocation)

        *reinterpret_cast<void **>(ptr) = reinterpret_cast<void *>(head);

        head = reinterpret_cast<char *>(ptr);
    }
};