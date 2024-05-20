#include "GameBoard.h"
#include <iostream>
#include <vector>

//���� ���� ���
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
//����� ���忡 ǥ���� �� ���� ��ġ�� �̸� ���� ��ġ�� �ٸ��� ǥ���ϴ� �Լ�
void GameBoard::draw_BlockOnBoardWithShadow(std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY, int shadowPosY)
{
    for (int i = 0; i < block.size(); i++)
    {
        for (int j = 0; j < block[i].size(); j++)
        {
            if (block[i][j] == 2)
            {
                //���� ��ġ�� ����� ǥ��
                board[posY + i][posX + j] = 2;

                //�̸� ���� ��ġ�� �ٸ� ����� ����� ǥ��
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
    //���� ������ �ʺ�� ����
    int boardWidth = Board_W;
    int boardHeight = Board_H;

    //���� ���� �ʺ�� ����
    int nextBlockWidth = 4;
    int nextBlockHeight = 4;

    for (int i = 0; i < boardHeight; i++)
    {
        //���� ���� ���
        for (int j = 0; j < boardWidth; j++)
        {
            if (board[i][j] == 1)
            {
                std::cout << "�� ";
            }
            else if (board[i][j] == 2)
            {
                std::cout << "�� ";
            }
            else if (board[i][j] == 3)
            {
                std::cout << "�� ";
            }
            else
            {
                std::cout << "  ";
            }
        }

        //���� �� ��� (���� ����)
        if (i == 0 || i == nextBlockHeight + 1)
        {
            std::cout << " �� �� �� �� �� �� ";
        }
        else if (i <= nextBlockHeight)
        {
            std::cout << " �� ";
            for (int j = 0; j < nextBlockWidth; j++)
            {
                if (nextBlock[i - 1][j] == 2)
                {
                    std::cout << "�� ";
                }
                else
                {
                    std::cout << "  ";
                }
            }
            std::cout << "�� ";
        }

        std::cout << "\n";
    }
}

