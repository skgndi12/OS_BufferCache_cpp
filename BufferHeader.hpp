#ifndef __BUFFER_HEADER_HPP__
#define __BUFFER_HEADER_HPP__

using BlockNum = int;

enum BufferState
{
    UNLOCK,
    LOCK,
    DELAY,
    WRITE,
    BS_MAX
};

class BufferHeader;

class NodeHelper
{
public:
    NodeHelper(BufferHeader* body);

public:
    NodeHelper* Next();
    NodeHelper* Prev();
    BufferHeader* Get();

    void SetNext(NodeHelper* node);
    void SetPrev(NodeHelper* node);

private:
    BufferHeader* m_body;
    NodeHelper* m_next;
    NodeHelper* m_prev;
};

class BufferHeader
{
public:
    BufferHeader(BlockNum num);
    BufferHeader(const BufferHeader& rhs) = delete;

    bool operator == (const BufferHeader& rhs);
    BufferHeader& operator = (const BufferHeader& rhs) = delete;

public:
    void SetState(BufferState state);
    BufferState GetState();
    const char* GetStateStr();
    BlockNum GetBlockNum();

    BufferHeader* NextFreeNode();
    BufferHeader* PrevFreeNode();
    BufferHeader* NextHashNode();
    BufferHeader* PrevHashNode();

    void SetNextFreeNode(BufferHeader* node);
    void SetPrevFreeNode(BufferHeader* node);
    void SetNextHashNode(BufferHeader* node);
    void SetPrevHashNode(BufferHeader* node);

private:
    BlockNum m_block_num;
    BufferState m_state;
    NodeHelper m_freelist_helper;
    NodeHelper m_hashqueue_helper;
};

#endif // __BUFFER_HEADER_HPP__