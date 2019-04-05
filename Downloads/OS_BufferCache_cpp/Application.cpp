#include <iostream>
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
    std::cout << "Number of Buffer to GetBlk: ";
    getline(std::cin, bl_num);
    mod_num = stoi(bl_num) % size;//save mod number to find buffer

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
                if(blockList[i].IsDuplicate(item))
                {
                    std::srand(5323);//현재 중복된 원소가 생겼을 경우 다른 원소를 생성해서 추가해주는 연산 필요
                }
                blockList[i].Insert(item);
            }
        }
    }
}

void Application::Print()
{
    for(int i = 0; i < size; i++)
    for(const DDL& bl : blockList)
    {
        std::cout << "mod " << i << '\n';
        bl.Print();
    }
    std::cout << "FreeList\n";
    freeList.Print();
}

void Application::FreeListInitialize()
{
    //생각을 해보자
    //DLL array에서 size
}
