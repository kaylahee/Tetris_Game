#include "Block.h"

// 블럭들
std::vector<std::vector<int>> Block::Blocks(int num)
{
    std::vector<std::vector<int>> I = { {0, 0, 0, 0}, {0, 0, 0, 0}, {2, 2, 2, 2}, {0, 0, 0, 0} };
    std::vector<std::vector<int>> T = { {0, 0, 0, 0}, {0, 0, 2, 0}, {0, 2, 2, 2}, {0, 0, 0, 0} };
    std::vector<std::vector<int>> L = { {0, 2, 0, 0}, {0, 2, 0, 0}, {0, 2, 2, 0}, {0, 0, 0, 0} };
    std::vector<std::vector<int>> J = { {0, 0, 2, 0}, {0, 0, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0} };
    std::vector<std::vector<int>> Z = { {0, 0, 0, 0}, {0, 2, 2, 0}, {0, 0, 2, 2}, {0, 0, 0, 0} };
    std::vector<std::vector<int>> S = { {0, 0, 0, 0}, {0, 0, 2, 2}, {0, 2, 2, 0}, {0, 0, 0, 0} };
    std::vector<std::vector<int>> O = { {0, 0, 0, 0}, {0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0} };

    switch (num)
    {
    case 1:
        return I;
    case 2:
        return T;
    case 3:
        return L;
    case 4:
        return J;
    case 5:
        return Z;
    case 6:
        return S;
    case 7:
        return O;
    default:
        return { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }; // 기본 빈 블럭
    }
}

// 블럭들 회전
std::vector<std::vector<int>> Block::rotate_Block(std::vector<std::vector<int>> block)
{
    int n = block.size();
    std::vector<std::vector<int>> rotated(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rotated[j][n - 1 - i] = block[i][j];
        }
    }
    return rotated;
}