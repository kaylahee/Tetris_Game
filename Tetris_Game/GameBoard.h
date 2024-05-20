#pragma once
#include <vector>

class GameBoard 
{
public:
    int Board_W = 12;
    int Board_H = 25;
    std::vector<std::vector<int>> matrix;

    GameBoard() 
    {
        matrix.resize(Board_H, std::vector<int>(Board_W, 0));
        draw_GameBoard();
    }

    //���� ���� ���
    void draw_GameBoard();
    //����� ���忡 ǥ���� �� ���� ��ġ�� �̸� ���� ��ġ�� �ٸ��� ǥ���ϴ� �Լ�
    void draw_BlockOnBoardWithShadow(std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY, int shadowPosY);
    void print_Board(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& nextBlock);
};
