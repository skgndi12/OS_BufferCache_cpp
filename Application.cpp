#include "Application.h"
/*
Application::Application(int max)
    : size(max)
{
    blockList.resize(size);
}

void Application::Run()
{
    std::string bl_num;
    int mod_num;
    int bl_hash;
    Block tg_bl;//target block
    std::cout << "Number of Buffer to GetBlk: ";
    getline(std::cin, bl_num);
    bl_hash = stoi(bl_num);
    mod_num = bl_hash % size;//save mod number to find buffer
    tg_bl.UpdateHash(bl_hash);
    for(std::vector<DDL>::iterator it = blockList.begin(); it != blockList.end(); it++) 
    {
        if(it->Search(tg_bl))
        {
            if(tg_bl.GetState() == LOCK)//scenario 5
            {
                usleep(3000000);//wait for 3 second
                it->Update(tg_bl, tg_bl.GetHash(), UNLOCK);//buffer state change to UNLOCK
                std::cout << "Scenario 5, Wait 3 seconds and return Buffer" << tg_bl.GetHash() << "success\n";
            }
            else if(freeList.Search(tg_bl))//scenario 1 
            {
                freeList.Delete(tg_bl);
                it->Update(tg_bl, tg_bl.GetHash(), LOCK);
                std::cout << "Scenario 1, return Buffer "<<tg_bl.GetHash() << " success\n";
            }
        }
        else
        {
            if(freeList.GetSize() == 0)//scenario 4
            {
                usleep(3000000);//wait for 3 second
                freeList.Insert(tg_bl);//return free buffer to freeList
                std::cout << "Scenario 4, wait for 3 seconds and return Buffer " << tg_bl.GetHash() << " to FreeList\n";
            }
            else if(freeList.Search(tg_bl)
            {
                if(tg_bl.GetState() == DELAY))//scenario 3
                {
                    freeList.Delete(tg_bl);

                }
                else//scenario 2
                {

                }
            }
        }
        
    }
    Print();

}

void Application::Initialize(std::vector<int>& value)
{
    int temp;
    for(int i = 0; i <= size; i++)
    {
        for(int j = 0; j < value.size(); j++)
        {
            int random_pct = rand() % 100;
            if(value[j] % size == i)
            {
                temp = value[j] % size;
                Block item;
                item.UpdateHash(value[j]);
                blockList[i].Insert(item);
                if(random_pct < 5)
                {
                    freeList.Insert(item);//Add an element to the free list with a 5 percent chance
                }
            }
        }
    }
    FreeListInitialize();//Add a DELAY Block to freeList
}

void Application::Print()
{
    int i = 0;
    for(DDL& bl : blockList)
    {
        std::cout << "mod " << i << '\n';
        bl.Print();
        i++;
    }
    std::cout << "FreeList\n";
    freeList.Print();
}

void Application::FreeListInitialize()
{
    for(std::vector<DDL>::iterator it = blockList.begin(); it != blockList.end(); it++)
    {
        std::list<Block> temp; 
        temp = it->SearchState(DELAY);
        for(std::list<Block>::iterator it = temp.begin(); it != temp.end(); it++)
        {
            Block item;
            item.UpdateHash(it->GetHash());
            item.UpdateState(it->GetState());
            freeList.Insert(item);
        }

    }
}
*/
Application::Application(uint32_t queue_size)
    : bufferCache(queue_size),
    queue_size(queue_size)
{
}

void Application::Run()
{
    BufferState state;
    BlockNum blocknum;
    uint32_t mod;
    std::string bl_num;
    while(1)
    {
    std::cout << "Number of Buffer to GetBlk: ";
    getline(std::cin, bl_num);
    blocknum = stoi(bl_num);
    mod = blocknum % queue_size;
    BufferHeader *buff_head_hash;
    BufferHeader *buff_head_free;
    buff_head_hash = bufferCache.Find_HashQueue(mod, blocknum);
    if(buff_head_hash != nullptr)
    {
        if(buff_head_hash->GetState() == LOCK)//scenario 5
        {
            usleep(3000000);//wait for 3 second
            buff_head_hash->SetState(UNLOCK);//buffer state change to UNLOCK
            std::cout << "Scenario 5, Wait 3 seconds and return Buffer " << buff_head_hash->GetBlockNum() << " success\n";
        }
        else//scenario 1
        {
            buff_head_free = bufferCache.Find_FreeList(blocknum);
            if(buff_head_free != nullptr)
            {
                bufferCache.Remove_Free(blocknum);
                buff_head_hash->SetState(LOCK);//Buffer state changed to Busy
                 std::cout << "Scenario 1, return Buffer "<< buff_head_hash->GetBlockNum() << " success\n";
            }
        }
    }
    else
    {
        if(bufferCache.IsEmpty_Free())//scenario 4
        {
            usleep(3000000);//wait for 3 second
            buff_head_free = bufferCache.Insert_Free(blocknum, UNLOCK);//return free buffer to freeList
            std::cout << "Scenario 4, wait for 3 seconds and return Buffer " << blocknum << " to FreeList\n";
        }
        else
        {
            buff_head_free = bufferCache.Find_FreeList(blocknum);
            if(buff_head_free->GetState() == DELAY)//scenario 3
            {
                buff_head_hash = bufferCache.Remove_Free(blocknum);//Add free list deleted buffer to state change to write to hash queue
                buff_head_hash->SetState(WRITE);
                bufferCache.Insert_Hash(mod, buff_head_hash->GetBlockNum(), buff_head_hash->GetState());
                std::cout << "Scenario 3, Remove DELAY Buffer " << buff_head_hash->GetBlockNum() << " in freelist and insert new WRITE buffer to hash queue\n";
            }
            else//Scenario 2
            {
                buff_head_hash = bufferCache.PopFront_Free();//Pop front the first element of the free list
                BlockNum temp = buff_head_hash->GetBlockNum();
                uint32_t mod_remove = temp % queue_size;
                buff_head_hash = bufferCache.Remove_Hash(mod_remove, temp);//Remove old queue in hash queue
                bufferCache.Insert_Hash(mod, blocknum, UNLOCK);//Insert new queue in hash queue
                std::cout << "Scenario 2, Removes the first element of the free list from the free list and hash queue, recycles, " << temp << " and assigns a new Buffer " << blocknum <<  " to the hash queue\n";
            }
        }

    }

    Print();
    }

}

void Application::Insert(BlockNum block_num, BufferState state)
{
    bufferCache.Insert(block_num, state);
}

void Application::Print()
{
    bufferCache.PrintData();
}
