#include "Block.h"

Block::Block()
{
    srand((unsigned int)time(0));
    int random = rand()%4;
    switch(random)
    {
        case UNLOCK:
            state = "UNLOCK";
            break;
        case LOCK: 
            state = "LOCK";
            break;
        case DELAY:
            state = "DELAY";
            break;
        case WRITE:
            state = "WRITE";
            random = 0;
            break;
    }
            
}

Block::Block(int m_hash, std::string m_state)
{
    hash_value = m_hash;
    state = m_state;
}

void Block::UpdateState(std::string new_state)
{
    state = new_state;
}

void Block::UpdateHash(int value)
{
    hash_value = value;
}

std::string Block::GetState() const
{
    return state;
}

int Block::GetHash() const
{
    return hash_value;
}

void Block::operator=(const Block& rhs)
{
  this->state = rhs.state;
  this->hash_value = rhs.hash_value;
}

bool Block::operator==(const Block& rhs)
{
  if((this->hash_value == rhs.hash_value) && (this->state == rhs.state))
  {
    return true;
  }
  return false;
}