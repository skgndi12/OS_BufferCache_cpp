#ifndef __BUFFER_CACHE_HPP__
#define __BUFFER_CACHE_HPP__

#include "PointerList.hpp"

#include <vector>

class BufferCache
{
public:
    BufferCache(uint32_t hash_queue_size);

public:
    void Insert(BlockNum block_num, BufferState state);
    BufferHeader* Insert_Hash(uint32_t mod, BlockNum blocknum, BufferState state);
    BufferHeader* Insert_Free(BlockNum blocknum, BufferState state);
    void PrintData();
    BufferHeader* Find_HashQueue(uint32_t mod, BlockNum blocknum);
    BufferHeader* Find_FreeList(BlockNum blocknum);
    BufferHeader* Remove_Hash(uint32_t mod,BlockNum blocknum);
    BufferHeader* Remove_Free(BlockNum blocknum);
    BufferHeader* PopFront_Free();
    bool IsEmpty_Free();

private:
    uint32_t Hash(BlockNum blocknum);
    bool TenPercent();
    bool SeventyPercent();

private:
    const uint32_t HASH_QUEUE_SIZE;
    std::vector<BufferQueue> m_hash_queue;
    FreeList m_free_list;
};

#endif // __BUFFER_CACHE_HPP__