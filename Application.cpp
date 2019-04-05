#include "Application.h"

Application::Application(int max)
    : size(max)
{
    blockList.resize(size);
    inFile.open("input.txt");
    outFile.open("output.txt");
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
