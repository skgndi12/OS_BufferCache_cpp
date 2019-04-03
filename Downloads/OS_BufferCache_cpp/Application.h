#ifndef APPLICATION_H
#define APPLICATION_H
#include "DoublyLinkedList.h"
#include <fstream>
const int MAX_SIZE = 5;
class Application
{
    private:
        DDL FreeList;
        DDL * BlockList; 
        std::ifstream inFile;
        std::ofstream outFile;
        int size;
    public:
        Application(int max = MAX_SIZE); 
        ~Application()
        {
            delete []BlockList;
            outFile.close();
            inFile.close();
        }
        void Initialize(int *value, int num);
        void Print();
        void ReadFromFile();
        void WriteToFile();

};
#endif //APPLICATION_H
