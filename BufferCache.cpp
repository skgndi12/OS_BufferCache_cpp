#include <cstdlib>
#include <ctime>

#include <iostream>

#include "BufferCache.hpp"

BufferCache::BufferCache(uint32_t hash_queue_size)
    : HASH_QUEUE_SIZE(hash_queue_size)
{
    m_hash_queue.resize(HASH_QUEUE_SIZE);

    std::srand(std::time(nullptr));
}


void BufferCache::Insert(BlockNum block_num, BufferState state)
{
    BufferHeader* noob = new BufferHeader(block_num);
    noob->SetState(state);
    if(SeventyPercent())
   {
    uint32_t mod = Hash(block_num);
    m_hash_queue[mod].PushBack(noob);
   }
    if (state == DELAY || TenPercent())
    {
        m_free_list.PushBack(noob);
    }
}

BufferHeader* BufferCache::Insert_Hash(uint32_t mod, BlockNum blocknum, BufferState state)
{
    BufferHeader* noob = new BufferHeader(blocknum);
    noob->SetState(state);
    m_hash_queue[mod].PushBack(noob);
    return noob;
}

BufferHeader* BufferCache::Insert_Free(BlockNum blocknum, BufferState state)
{
    BufferHeader* noob = new BufferHeader(blocknum);
    noob->SetState(state);
    m_free_list.PushBack(noob);
    return noob;
}

void BufferCache::PrintData()
{
    int mod = 0;
    for (BufferQueue& bqueue : m_hash_queue)
    {
        std::vector<BufferHeader*> collector;

        bqueue.ForEach(
            [&collector](BufferHeader* block)
            {
                collector.push_back(block);
            }
        );

        std::cout << "Mod " << mod << '\n';
        std::cout << "Size: " << bqueue.GetSize() << '\n';
        for (BufferHeader* block : collector)
        {
            std::cout << '(' << block->GetBlockNum() << ", " << block->GetStateStr() << ") ";
        }
        std::cout << std::endl;

        mod += 1;
    }

    std::vector<BufferHeader*> collector;

    m_free_list.ForEach(
        [&collector](BufferHeader* block)
        {
            collector.push_back(block);
        }
    );

    std::cout << "FreeList\n";
    std::cout << "Size: " << m_free_list.GetSize() << '\n';
    for (BufferHeader* block : collector)
    {
        std::cout << '(' << block->GetBlockNum() << ", " << block->GetStateStr() << ") ";
    }
    std::cout << std::endl;
}

BufferHeader* BufferCache::Find_HashQueue(uint32_t mod, BlockNum blocknum)
{
    return m_hash_queue[mod].Find(blocknum);
}

BufferHeader* BufferCache::Find_FreeList(BlockNum blocknum)
{
    return m_free_list.Find(blocknum);
}

BufferHeader* BufferCache::Remove_Hash(uint32_t mod, BlockNum blocknum)
{
    return m_hash_queue[mod].Remove(blocknum);
}

BufferHeader* BufferCache::Remove_Free(BlockNum blocknum)
{
    return m_free_list.Remove(blocknum);
}

BufferHeader* BufferCache::PopFront_Free()
{
    return m_free_list.PopFront();
}

bool BufferCache::IsEmpty_Free()
{
    return m_free_list.IsEmpty();
}

uint32_t BufferCache::Hash(BlockNum blocknum)
{
    return blocknum % HASH_QUEUE_SIZE;
}

bool BufferCache::TenPercent()
{
    int result = std::rand() % 100;
    return (bool)(result < 10);
}


bool BufferCache::SeventyPercent()
{
    int result = std::rand() % 100;
    return (bool)(result < 70);
}