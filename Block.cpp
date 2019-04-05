#include "Block.h"

Block::Block()
{
    int random = rand() % BS_MAX;
    state = static_cast<BufferState>(random);
}

Block::Block(int hash, BufferState state)
    : hash_value(hash),
    state(state)
{
}

void Block::UpdateState(BufferState new_state)
{
    state = new_state;
}

// testing..

void Block::UpdateHash(int value)
{
    hash_value = value;
}

BufferState Block::GetState() const
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