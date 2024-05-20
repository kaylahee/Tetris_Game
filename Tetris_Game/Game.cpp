#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

#include "ConsoleUtils.h"
#include "GameBoard.h"
#include "GameFunc.h"
#include "Block.h"
#include "InputHandler.h"
#include "Game.h"

ConsoleUtils  cu;
GameBoard gb;
GameFunc gf;
Block b;
InputHandler ih;

void Game::run()
{
    cu.CursorView();
    gb.draw_GameBoard();

    std::vector<std::vector<int>> currentBlock = b.Blocks(1);
    std::vector<std::vector<int>> nextBlock = b.Blocks(rand() % 7 + 1);
    std::vector<std::vector<int>> heldBlock;

    int blockPosX = 5;
    int blockPosY = 0;

    clock_t lastUpdateTime = clock();

    double delay = 1.0;
    int score = 0;

    while (true)
    {
        clock_t currentTime = clock();
        double elapsedTime = double(currentTime - lastUpdateTime) / CLOCKS_PER_SEC;

        if (elapsedTime >= delay)
        {
            if (!gf.check_Collision(gb.matrix, currentBlock, blockPosX, blockPosY + 1))
            {
                blockPosY++;
            }
            else
            {
                gf.fix_Block_And_ClearLines(gb.matrix, currentBlock, blockPosX, blockPosY, score);
                currentBlock = nextBlock;
                nextBlock = b.Blocks(rand() % 7 + 1);
                blockPosX = 5;
                blockPosY = 0;
            }
            lastUpdateTime = currentTime;
        }

        int tempPosX = blockPosX;
        int tempPosY = blockPosY;
        bool rotate = false;
        bool drop = false;
        ih.input_User(tempPosX, tempPosY, rotate, drop);

        if (rotate)
        {
            std::vector<std::vector<int>> rotatedBlock = b.rotate_Block(currentBlock);
            if (!gf.check_Collision(gb.matrix, rotatedBlock, blockPosX, blockPosY))
            {
                currentBlock = rotatedBlock;
            }
        }

        if (drop)
        {
            while (!gf.check_Collision(gb.matrix, currentBlock, blockPosX, blockPosY + 1))
            {
                blockPosY++;
            }
            gf.fix_Block_And_ClearLines(gb.matrix, currentBlock, blockPosX, blockPosY, score);
            currentBlock = nextBlock;
            nextBlock = b.Blocks(rand() % 7 + 1);
            tempPosX = 5;
            tempPosY = 0;
        }

        if (!gf.check_Collision(gb.matrix, currentBlock, tempPosX, tempPosY))
        {
            blockPosX = tempPosX;
            blockPosY = tempPosY;
        }

        int fallDistance = gf.calculate_FallDistance(gb.matrix, currentBlock, blockPosX, blockPosY);
        std::vector<std::vector<int>> tempBoard = gb.matrix;
        gb.draw_BlockOnBoardWithShadow(tempBoard, currentBlock, blockPosX, blockPosY, blockPosY + fallDistance);
        cu.clear_Screen();
        gb.print_Board(tempBoard, nextBlock);
        std::cout << "Score: " << score << std::endl;

        if (gf.check_GameOver(gb.matrix))
        {
            system("cls");
            std::cout << "Game Over!" << std::endl;
            std::cout << "Your Score: " << score << std::endl;
            break;
        }
    }
}