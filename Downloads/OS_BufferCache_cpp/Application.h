#ifndef APPLICATION_H
#define APPLICATION_H
#include "DoublyLinkedList.h"
#include <fstream>
class Application
{
    private:
        DDL FreeList;
        DDL mod0;
        DDL mod1;
        DDL mod2;
        DDL mod3;
        DDL mod4;
        std::ifstream inFile;
        std::ofstream outFile;
    public:
        void Scenario1();
        void Scenario2();
        void Scenario3();
        void Scenario4();
        void Scenario5();
        void ReadFromFile();

};
#endif //APPLICATION_H
