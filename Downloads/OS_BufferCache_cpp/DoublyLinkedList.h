#ifndef DLL_H
#define DLL_H
#include <iostream>
#include <list>
#include "Block.h"
class DDL
{
  private:
    std::list<Block> blocks;
  public:
    DDL(){};
    DDL(Block item);
    bool Search(Block& item);
    void SearchState(BufferState state);
    bool IsDuplicate(Block item);
    void Insert(Block item);
    void Delete(Block item);
    void Print();
    int GetSize();
    void operator=(const DDL& rhs);
};

#endif //DDL_H
