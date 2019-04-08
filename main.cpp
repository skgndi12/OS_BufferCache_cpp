#include <iostream>
#include <string>

#include "BufferHeader.hpp"
#include "Application.h"

BufferState GenerateState();

void Print(std::vector<BlockNum> &blocks);

int main()
{
    /*
    srand((unsigned int)time(0));
    std::string size;
    std::string max;
    std::vector<int> value;
    int bl_num;
    std::cout << "Mod Number: ";
    std::getline(std::cin, size);
    Application app(stoi(size));
    std::cout << "Numbers of Buffer: ";
    std::getline(std::cin, max);
    bl_num = stoi(max);
    for(int i = 0; i < bl_num; i++)
    {
        value.push_back(i);
    }
    std::random_shuffle(value.begin(), value.end());
    app.Initialize(value);
    app.Print();
    app.Run();
    return 0;
    */

    std::srand(std::time(nullptr));

    std::string size;
    std::string max;

    std::cout << "Mod Number: ";
    std::getline(std::cin, size);

    std::cout << "Numbers of Buffer: ";
    std::getline(std::cin, max);

    uint32_t queue_size = (uint32_t)stoi(size);
    Application app(queue_size);

    int data_size = stoi(max);
    std::vector<BlockNum> blocks;
    for(int i = 0; i < data_size; ++i)
    {
        blocks.push_back(i);
    }
    std::random_shuffle(blocks.begin(), blocks.end());

    for (BlockNum num : blocks)
    {
        app.Insert(num, GenerateState());
    }
    Print(blocks);
    app.Print();
    app.Run();

    return 0;
}

BufferState GenerateState()
{
    return (BufferState)(std::rand() % 4);
}

void Print(std::vector<BlockNum> &blocks)
{
    std::cout << "List of all blocks\n";
    for(std::vector<BlockNum>::iterator it = blocks.begin(); it != blocks.end(); it++)
    {
        std::cout << '(' << *it << ") "; 
    }
    std::cout << std::endl;
}
