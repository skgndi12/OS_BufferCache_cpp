#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

enum BufferState
{
    UNLOCK,
    LOCK,
    DELAY,
    WRITE,
    BS_MAX
};

class Block
{
    private:
        BufferState state;
        int hash_value;
    public:
        Block();
        Block(int hash, BufferState state);
        void UpdateState(BufferState new_state);
        void UpdateHash(int value);
        BufferState GetState() const;
        int GetHash() const;
        void operator=(const Block& rhs);
        bool operator==(const Block& rhs);
};
#endif //BLOCK_H