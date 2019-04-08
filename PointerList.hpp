#ifndef __POINTER_LIST_HPP__
#define __POINTER_LIST_HPP__

#include <functional>

#include "BufferHeader.hpp"

class DoublyLinkedList
{
public:
    DoublyLinkedList();
    virtual ~DoublyLinkedList();

public:
    void PushFront(BufferHeader* node);
    void PushBack(BufferHeader* node);
    BufferHeader* Find(BlockNum num);
    virtual BufferHeader* Remove(BlockNum num) = 0;
    bool IsEmpty();
    void ForEach(std::function<void(BufferHeader*)>&& callback);
    int GetSize() { return m_size;}

private:
    virtual BufferHeader* NextNode(BufferHeader* node) = 0;
    virtual BufferHeader* PrevNode(BufferHeader* node) = 0;

    virtual void Insert(BufferHeader* source, BufferHeader* target) = 0;

protected:
    int m_size;
    BufferHeader* m_head;
    BufferHeader* m_tail;

private:
    static const BlockNum INVALID_BLOCK_NUM = -1;
};

class FreeList : public DoublyLinkedList
{
public:
    FreeList();

public:
    BufferHeader* Remove(BlockNum num) override;
    BufferHeader* PopFront();

private:
    BufferHeader* NextNode(BufferHeader* node) override;
    BufferHeader* PrevNode(BufferHeader* node) override;

    void Insert(BufferHeader* source, BufferHeader* target) override;
};

class BufferQueue : public DoublyLinkedList
{
public:
    BufferQueue();

public:
    BufferHeader* Remove(BlockNum num) override;

private:
    BufferHeader* NextNode(BufferHeader* node) override;
    BufferHeader* PrevNode(BufferHeader* node) override;

    void Insert(BufferHeader* source, BufferHeader* target) override;
};

#endif // __POINTER_LIST_HPP__
