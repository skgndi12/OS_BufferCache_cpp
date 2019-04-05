#ifndef APPLICATION_H
#define APPLICATION_H
#include "DoublyLinkedList.h"
#include <fstream>
#include <vector>
const int MAX_SIZE = 5;
class Application
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
        void Initialize(int *value, int num);
        void Print();
        void FreeListInitialize();
        void ReadFromFile();
        void WriteToFile();


};
#endif //APPLICATION_H
