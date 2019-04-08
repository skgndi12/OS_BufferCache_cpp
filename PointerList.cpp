#include "PointerList.hpp"

DoublyLinkedList::DoublyLinkedList()
    : m_size(0)
{
    m_tail = new BufferHeader(INVALID_BLOCK_NUM);
    m_head = new BufferHeader(INVALID_BLOCK_NUM);
}

DoublyLinkedList::~DoublyLinkedList()
{
    for (BufferHeader* iter = PrevNode(m_tail); iter != m_head; iter = PrevNode(iter))
    {
        delete iter;
    }
    if (m_tail != nullptr)
    {
        delete m_tail;
    }

    if (m_head != nullptr)
    {
        delete m_head;
    }

    m_tail = m_head = nullptr;
}

void DoublyLinkedList::PushFront(BufferHeader* node)
{
    if(m_size != 10)
    {
        Insert(m_head, node);
        m_size += 1;
    }
}

void DoublyLinkedList::PushBack(BufferHeader* node)
{
    if(m_size != 10)
    {
        Insert(PrevNode(m_tail), node);
        m_size += 1;
    }
}

BufferHeader* DoublyLinkedList::Find(BlockNum num)
{
    for (BufferHeader* iter = NextNode(m_head); iter != m_tail; iter = NextNode(iter))
    {
        if (iter->GetBlockNum() == num)
        {
            return iter;
        }
    }

    return nullptr;
}

bool DoublyLinkedList::IsEmpty()
{
    return (bool)(m_size == 0);
}

void DoublyLinkedList::ForEach(std::function<void(BufferHeader*)>&& callback)
{
    for (BufferHeader* iter = NextNode(m_head); iter != m_tail; iter = NextNode(iter))
    {
        callback(iter);
    }
}

FreeList::FreeList()
    : DoublyLinkedList()
{
    m_head->SetNextFreeNode(m_tail);
    m_tail->SetPrevFreeNode(m_head);
}

BufferHeader* FreeList::Remove(BlockNum num)
{
    BufferHeader* found = Find(num);
    if (found == nullptr)
    {
        return nullptr;
    }

    BufferHeader* before = found->PrevFreeNode();
    BufferHeader* after = found->NextFreeNode();

    before->SetNextFreeNode(after);
    after->SetPrevFreeNode(before);

    found->SetNextFreeNode(nullptr);
    found->SetPrevFreeNode(nullptr);

    m_size -= 1;

    return found;
}

BufferHeader* FreeList::NextNode(BufferHeader* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    return node->NextFreeNode();
}

BufferHeader* FreeList::PrevNode(BufferHeader* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    return node->PrevFreeNode();
}

BufferHeader* FreeList::PopFront()
{
    BufferHeader* front = m_head->NextFreeNode();
    BufferHeader* after = front->NextFreeNode();

    m_head->SetNextFreeNode(after);
    after->SetPrevFreeNode(m_head);

    front->SetNextFreeNode(nullptr);
    front->SetPrevFreeNode(nullptr);
    
    m_size -= 1;

    return front;
    
}
void FreeList::Insert(BufferHeader* source, BufferHeader* target)
{
    if (source == nullptr || target == nullptr)
    {
        return;
    }

    /***********************************************************
     * source <-> target <-> after
     ***********************************************************
     */

    BufferHeader* after = source->NextFreeNode();

    source->SetNextFreeNode(target);
    target->SetPrevFreeNode(source);
    target->SetNextFreeNode(after);
    after->SetPrevFreeNode(target);
}

BufferQueue::BufferQueue()
    : DoublyLinkedList()
{
    m_head->SetNextHashNode(m_tail);
    m_tail->SetPrevHashNode(m_head);
}

BufferHeader* BufferQueue::Remove(BlockNum num)
{
    BufferHeader* found = Find(num);
    if (found == nullptr)
    {
        return nullptr;
    }

    BufferHeader* before = found->PrevHashNode();
    BufferHeader* after = found->NextFreeNode();

    before->SetNextFreeNode(after);
    after->SetPrevFreeNode(before);

    found->SetNextFreeNode(nullptr);
    found->SetPrevFreeNode(nullptr);

    m_size -= 1;

    return found;
}

BufferHeader* BufferQueue::NextNode(BufferHeader* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    return node->NextHashNode();
}

BufferHeader* BufferQueue::PrevNode(BufferHeader* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    return node->PrevHashNode();
}

void BufferQueue::Insert(BufferHeader* source, BufferHeader* target)
{
    if (source == nullptr || target == nullptr)
    {
        return;
    }

    /***********************************************************
     * source <-> target <-> after
     ***********************************************************
     */

    BufferHeader* after = source->NextHashNode();

    source->SetNextHashNode(target);
    target->SetPrevHashNode(source);
    target->SetNextHashNode(after);
    after->SetPrevHashNode(target);
}
