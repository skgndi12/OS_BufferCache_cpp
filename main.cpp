#include "Application.h"
#include <string>



int main()
{
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

}