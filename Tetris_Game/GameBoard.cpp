#include "GameBoard.h"
#include <iostream>
#include <vector>

//게임 보드 출력
void GameBoard::draw_GameBoard()
{
    for (int i = 0; i < Board_H; i++)
    {
        for (int j = 0; j < Board_W; j++)
        {
            if (i == Board_H - 1 || j == 0 || j == Board_W - 1)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
}
//블록을 보드에 표시할 때 현재 위치와 미리 계산된 위치를 다르게 표시하는 함수
void GameBoard::draw_BlockOnBoardWithShadow(std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY, int shadowPosY)
{
    for (int i = 0; i < block.size(); i++)
    {
        for (int j = 0; j < block[i].size(); j++)
        {
            if (block[i][j] == 2)
            {
                //현재 위치에 블록을 표시
                board[posY + i][posX + j] = 2;

                //미리 계산된 위치에 다른 모양의 블록을 표시
                if (shadowPosY + i < Board_H - 1)
                {
                    board[shadowPosY + i][posX + j] = 3;
                }
            }
        }
    }
}
void GameBoard::print_Board(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& nextBlock)
{
    //현재 보드의 너비와 높이
    int boardWidth = Board_W;
    int boardHeight = Board_H;

    //다음 블럭의 너비와 높이
    int nextBlockWidth = 4;
    int nextBlockHeight = 4;

    for (int i = 0; i < boardHeight; i++)
    {
        //현재 보드 출력
        for (int j = 0; j < boardWidth; j++)
        {
            if (board[i][j] == 1)
            {
                std::cout << "▣ ";
            }
            else if (board[i][j] == 2)
            {
                std::cout << "▩ ";
            }
            else if (board[i][j] == 3)
            {
                std::cout << "□ ";
            }
            else
            {
                std::cout << "  ";
            }
        }

        //다음 블럭 출력 (보드 옆에)
        if (i == 0 || i == nextBlockHeight + 1)
        {
            std::cout << " ▣ ▣ ▣ ▣ ▣ ▣ ";
        }
        else if (i <= nextBlockHeight)
        {
            std::cout << " ▣ ";
            for (int j = 0; j < nextBlockWidth; j++)
            {
                if (nextBlock[i - 1][j] == 2)
                {
                    std::cout << "▩ ";
                }
                else
                {
                    std::cout << "  ";
                }
            }
            std::cout << "▣ ";
        }

        std::cout << "\n";
    }
}

