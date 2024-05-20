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

    //게임 보드 출력
    void draw_GameBoard();
    //블록을 보드에 표시할 때 현재 위치와 미리 계산된 위치를 다르게 표시하는 함수
    void draw_BlockOnBoardWithShadow(std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY, int shadowPosY);
    void print_Board(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& nextBlock);
};
