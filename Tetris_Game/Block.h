#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

class Block 
{
public:
    // ����
    std::vector<std::vector<int>> Blocks(int num);
    // ���� ȸ��
    std::vector<std::vector<int>> rotate_Block(std::vector<std::vector<int>> block);
};

#endif // BLOCK_H
