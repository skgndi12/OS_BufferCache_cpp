#include "Application.h"


int main()
{
    DDL mylist;
    Block test;
    Block random;
    Block random2;
    Block random3;
    std::cout << random.GetState() << '\n';
    std::cout << random2.GetState() << '\n';
    std::cout << random3.GetState() << '\n';
    test.UpdateHash(3);
    mylist.Insert(test);
    random.UpdateHash(4);
    mylist.Insert(random);
    mylist.Print();
    Block temp;
    temp.UpdateHash(3);
    temp.UpdateState(test.GetState());
    mylist.Delete(temp);
    mylist.Print();
    return 0;

}