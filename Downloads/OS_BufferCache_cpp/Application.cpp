#include <iostream>
#include "Application.h"

Application::Application(int max)
{
    BlockList = new DDL[max];
    size = max;
    inFile.open("input.txt");
    outFile.open("output.txt");
}

void Application::Initialize(int *value, int num)
{
    int temp;
    for(int i = 0; i <= size; i++)
    {
        for(int j = 0; j < num; j++)
        {
            if(value[j] % size == i)
            {
                temp = value[j] % size;
                Block item;
                item.UpdateHash(value[j]);
                if(BlockList[i].IsDuplicate(item))
                {
                    std::srand(5323);//현재 중복된 원소가 생겼을 경우 다른 원소를 생성해서 추가해주는 연산 필요
                }
                BlockList[i].Insert(item);
            }
        }
    }
}

void Application::Print()
{
    for(int i = 0; i < size; i++)
    {
        std::cout << "mod " << i << '\n';
        BlockList[i].Print();
    }
}
