#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

class Block 
{
public:
    // 블럭들
    std::vector<std::vector<int>> Blocks(int num);
    // 블럭들 회전
    std::vector<std::vector<int>> rotate_Block(std::vector<std::vector<int>> block);
};

#endif // BLOCK_H
