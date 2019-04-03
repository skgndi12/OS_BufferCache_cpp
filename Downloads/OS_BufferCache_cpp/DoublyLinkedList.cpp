#include "DoublyLinkedList.h"

DDL::DDL(Block item)
{
  blocks.push_back(item);
}

bool DDL::Search(Block& item)//Block의 private 변수를 활용하여 해당하는 Block을 찾는다.
{
  for(std::list<Block>::iterator it = blocks.begin(); it != blocks.end(); it++)
  {
    if(item.GetHash() == it->GetHash())
    {
      item.UpdateState(it->GetState());
      return true;//찾았을 경우 item을 업데이트하고 true를 리턴
    }
  }
  return false;
}

bool DDL::IsDuplicate(Block item)//Block이 해당 리스트에서 중복인 원소인지 검사한다.
{
  for(std::list<Block>::iterator it = blocks.begin(); it != blocks.end(); it++)
  {
    if(item.GetHash() == it->GetHash())
    {
      item.UpdateState(it->GetState());
      return true;
    }
  }
  return false;
}

void DDL::Insert(Block item)
{
  if(!IsDuplicate(item))
  {
    blocks.push_back(item);
    return;
  }
  std::cout << "This Block " << item.GetHash() << " is Duplicated\n";
}

void DDL::Delete(Block item)
{
  for(std::list<Block>::iterator it = blocks.begin(); it != blocks.end(); it++)
  {
    if(*it == item)
    {
      blocks.erase(it);
      return;
    }
  }
  std::cout << "There is no matched Block\n";
}

void DDL::Print()
{
  int i = 0;
  for(std::list<Block>::iterator it = blocks.begin(); it != blocks.end(); it++) 
  {
    std::cout << "*----------------*" << '\n';
        std::cout << "|                |" << '\n';
        std::cout << "|       " << it->GetHash() << "       |" << '\n';
        std::cout << "       " << it->GetState()   << '\n';
        std::cout << "|                |" << '\n';
        std::cout << "*----------------*" << '\n';
    i++;
  }
}

int DDL::GetSize()
{
  return blocks.size();
}
