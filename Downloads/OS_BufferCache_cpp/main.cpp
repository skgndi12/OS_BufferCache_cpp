#include "Application.h"
#include <string>


int main()
{
    srand((unsigned int)time(0));
    std::string size;
    std::string max;
    std::cout << "Input size: ";
    std::getline(std::cin, size);
    Application app(stoi(size));
    std::cout << "How many element: ";
    std::getline(std::cin, max);
    int *value = new int[stoi(max)];
    for(int i = 0; i < stoi(max); i++)
    {
        value[i] = std::rand() % 100;
    }
    app.Initialize(value, stoi(max));
    app.Print();
    delete [] value;
    return 0;

}