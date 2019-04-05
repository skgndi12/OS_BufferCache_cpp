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

std::list<Block> DDL::SearchState(BufferState state)
{
  std::list<Block> temp;
  for(std::list<Block>::iterator it = blocks.begin(); it != blocks.end(); it++)
  {
    if(it->GetState() == state)
    {
      Block item;
      item.UpdateState(it->GetState());
      item.UpdateHash(it->GetHash());
      temp.push_back(item);
    }
  }
  return temp;
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

void DDL::Update(Block item, int value, BufferState state)
{
  for(std::list<Block>::iterator it = blocks.begin(); it != blocks.end(); it++)
  {
    if(*it == item)
    {
      it->UpdateHash(value);
      it->UpdateState(state);
      return;
    }
  }
}

void DDL::Print()
{
  for(std::list<Block>::iterator it = blocks.begin(); it != blocks.end(); it++) 
  {
      if(it->GetState() == UNLOCK)
      { 
        std::cout << "*----------------*" << '\n';
        std::cout << "|                |" << '\n';
        std::cout << "|       " << it->GetHash() << "        |" << '\n';
        std::cout << "       " << "UNLOCK"   << '\n';
        std::cout << "|                |" << '\n';
        std::cout << "*----------------*" << '\n';
      }
      else if(it->GetState() == LOCK)
      { 
        std::cout << "*----------------*" << '\n';
        std::cout << "|                |" << '\n';
        std::cout << "|       " << it->GetHash() << "        |" << '\n';
        std::cout << "       " << "LOCK"   << '\n';
        std::cout << "|                |" << '\n';
        std::cout << "*----------------*" << '\n';
       }
      else if(it->GetState() == DELAY)
      { 
        std::cout << "*----------------*" << '\n';
        std::cout << "|                |" << '\n';
        std::cout << "|       " << it->GetHash() << "        |" << '\n';
        std::cout << "       " << "DELAY"   << '\n';
        std::cout << "|                |" << '\n';
        std::cout << "*----------------*" << '\n';
       }
      else
      { 
        std::cout << "*----------------*" << '\n';
        std::cout << "|                |" << '\n';
        std::cout << "|       " << it->GetHash() << "        |" << '\n';
        std::cout << "       " << "WRITE"   << '\n';
        std::cout << "|                |" << '\n';
        std::cout << "*----------------*" << '\n';
       }
  }
}

int DDL::GetSize()
{
  return blocks.size();
}

void DDL::operator=(const DDL& rhs)
{
  for(std::list<Block>::iterator it = blocks.begin(); it != blocks.end(); it++)
  {
    
  }
}

