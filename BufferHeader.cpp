#include "BufferHeader.hpp"

NodeHelper::NodeHelper(BufferHeader* body)
    : m_body(body),
    m_next(nullptr),
    m_prev(nullptr)
{
}

NodeHelper* NodeHelper::Next()
{
    return m_next;
}

NodeHelper* NodeHelper::Prev()
{
    return m_prev;
}

BufferHeader* NodeHelper::Get()
{

    return m_body;
}

void NodeHelper::SetNext(NodeHelper* node)
{
    m_next = node;
}

void NodeHelper::SetPrev(NodeHelper* node)
{
    m_prev = node;
}

BufferHeader::BufferHeader(BlockNum blocknum)
    : m_block_num(blocknum),
    m_state(UNLOCK),
    m_freelist_helper(this),
    m_hashqueue_helper(this)
{
}

bool BufferHeader::operator == (const BufferHeader& rhs)
{
    return m_block_num == rhs.m_block_num;
}

void BufferHeader::SetState(BufferState state)
{
    m_state = state;
}

BufferState BufferHeader::GetState()
{
    return m_state;
}

const char* BufferHeader::GetStateStr()
{
    static const char* UNLOCK_STR = "UNLOCK";
    static const char* LOCK_STR = "LOCK";
    static const char* DELAY_STR = "DELAY";
    static const char* WRITE_STR = "WRITE";
    static const char* ERROR_STR = "ERROR";

    switch (m_state)
    {
        case UNLOCK:
            return UNLOCK_STR;
            break;
        case LOCK:
            return LOCK_STR;
            break;
        case DELAY:
            return DELAY_STR;
            break;
        case WRITE:
            return WRITE_STR;
            break;
        default:
            return ERROR_STR;
            break;
    }
}

BlockNum BufferHeader::GetBlockNum()
{
    return m_block_num;
}

BufferHeader* BufferHeader::NextFreeNode()
{
    NodeHelper* next_node = m_freelist_helper.Next();
    if (next_node == nullptr)
    {
        return nullptr;
    }

    return next_node->Get();
}

BufferHeader* BufferHeader::PrevFreeNode()
{
    NodeHelper* prev_node = m_freelist_helper.Prev();
    if (prev_node == nullptr)
    {
        return nullptr;
    }

    return prev_node->Get();
}

BufferHeader* BufferHeader::NextHashNode()
{
    NodeHelper* next_node = m_hashqueue_helper.Next();
    if (next_node == nullptr)
    {
        return nullptr;
    }

    return next_node->Get();
}

BufferHeader* BufferHeader::PrevHashNode()
{
    NodeHelper* prev_node = m_hashqueue_helper.Prev();
    if (prev_node == nullptr)
    {
        return nullptr;
    }

    return prev_node->Get();
}

void BufferHeader::SetNextFreeNode(BufferHeader* node)
{
    if (node == nullptr)
    {
        m_freelist_helper.SetNext(nullptr);
    }

    m_freelist_helper.SetNext(&node->m_freelist_helper);
}

void BufferHeader::SetPrevFreeNode(BufferHeader* node)
{
    if (node == nullptr)
    {
        m_freelist_helper.SetPrev(nullptr);
    }

    m_freelist_helper.SetPrev(&node->m_freelist_helper);
}

void BufferHeader::SetNextHashNode(BufferHeader* node)
{
    if (node == nullptr)
    {
        m_hashqueue_helper.SetNext(nullptr);
    }

    m_hashqueue_helper.SetNext(&node->m_hashqueue_helper);
}

void BufferHeader::SetPrevHashNode(BufferHeader* node)
{
    if (node == nullptr)
    {
        m_hashqueue_helper.SetPrev(nullptr);
    }

    m_hashqueue_helper.SetPrev(&node->m_hashqueue_helper);
}
