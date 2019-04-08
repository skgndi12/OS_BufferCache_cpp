#ifndef APPLICATION_H
#define APPLICATION_H
#include <iostream>
#include <vector>
#include <unistd.h>
#include <string>
#include "BufferCache.hpp"
/*class Application
{
    private:
        DDL freeList;
        std::vector<DDL> blockList; 
        std::ifstream inFile;
        std::ofstream outFile;
        const int size;
    public:
        Application(int max = MAX_SIZE); 
        ~Application()
        {
            outFile.close();
            inFile.close();
        }
        void Run();
        void Initialize(std::vector<int>& value);
        void Print();
        void FreeListInitialize();
        void ReadFromFile();
        void WriteToFile();


};*/

class Application
{
public:
    Application(uint32_t queue_size);
    void Run();
    void Insert(BlockNum block_num, BufferState state);
    void Print();
private:
    BufferCache bufferCache;
    uint32_t queue_size;

};
#endif //APPLICATION_H
