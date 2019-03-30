#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

enum
{
    UNLOCK,
    LOCK,
    DELAY,
    WRITE
};


class Block
{
    private:
        std::string state;
        int hash_value;
    public:
        Block();
        Block(int m_hash, std::string m_state);
        void UpdateState(std::string new_state);
        void UpdateHash(int value);
        std::string GetState() const;
        int GetHash() const;
        void operator=(const Block& rhs);
        bool operator==(const Block& rhs);
};
#endif //BLOCK_H