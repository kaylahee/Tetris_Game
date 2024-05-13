#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <ctime>

const int TABLE_W = 20;
const int TABLE_H = 20;
const int DELAY_MS = 500; // Time delay in milliseconds for block auto-movement

void CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void gotoxy(int x, int y)
{
    COORD pos = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

enum keyCode
{
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    SPACE = 32,
    R = 114,
    C = 99
};

const int BLOCKS[][4 * 4] =
{
    //I
    {
        0, 0, 0, 0,
        2, 2, 2, 2,
        0, 0, 0, 0,
        0, 0, 0, 0
    },
    //J
    {
        0, 0, 0, 0,
        0, 0, 2, 0,
        0, 0, 2, 0,
        0, 2, 2, 0
    },
    //L
    {
        0, 0, 0, 0,
        0, 2, 0, 0,
        0, 2, 0, 0,
        0, 2, 2, 0
    },
    //O
    {
        0, 0, 0, 0,
        0, 2, 2, 0,
        0, 2, 2, 0,
        0, 0, 0, 0
    },
    //S
    {
        0, 0, 0, 0,
        0, 2, 2, 0,
        2, 2, 0, 0,
        0, 0, 0, 0
    },
    //T
    {
        0, 0, 0, 0,
        0, 2, 2, 2,
        0, 0, 2, 0,
        0, 0, 0, 0
    },
    //Z
    {
        0, 0, 0, 0,
        0, 2, 2, 0,
        0, 0, 2, 2,
        0, 0, 0, 0
    },
};

const char BLOCK_TYPES[][4] =
{
    " ",
    "бс",
    "бр" };

class GameTable
{
private:
    int x;
    int y;
    std::vector<std::vector<int>> table;

public:
    GameTable(int x, int y)
    {
        this->x = x;
        this->y = y;

        for (int i = 0; i < y; i++)
        {
            std::vector<int> tmp;
            for (int j = 0; j < x; j++)
            {
                tmp.push_back(0);
            }
            table.push_back(tmp);
        }

        for (int i = 0; i < x; i++)
        {
            table[0][i] = 1;
            table[y - 1][i] = 1;
        }
        for (int i = 0; i < y; i++)
        {
            table[i][0] = 1;
            table[i][x - 1] = 1;
        }
    }

    void drawGameTable()
    {
        for (int i = 0; i < y; i++)
        {
            for (int j = 0; j < x; j++)
            {
                if (table[i][j] == 1)
                {
                    std::cout << "бс";
                }
                else
                {
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }

    bool isCollision(int x, int y) const
    {
        return table[y][x] != 0;
    }
};

class Block
{
private:
    int x, y;
    int shape[4][4];

public:
    Block()
    {
        x = TABLE_W / 2;
        y = 0;
        generateRandomShape();
    }

    void generateRandomShape()
    {
        int shapeIndex = rand() % 7;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                shape[i][j] = BLOCKS[shapeIndex][i * 4 + j];
            }
        }
    }

    void drawBlock(int x, int y, const Block& block)
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (block.getShape(i, j) != 0)
                {
                    gotoxy(x + j * 2, y + i);
                    std::cout << BLOCK_TYPES[block.getShape(i, j)];
                }
            }
        }
    }

    void rotate(const GameTable& gameTable)
    {
        int temp[4][4];
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                temp[i][j] = shape[i][j];
            }
        }

        // Rotate the block
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                shape[i][j] = temp[3 - j][i];
            }
        }

        // Check if rotation causes collision
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (shape[i][j] != 0 && (getX() + j < 1 || getX() + j >= TABLE_W - 1 || gameTable.isCollision(getX() + j, getY() + i)))
                {
                    for (int k = 0; k < 4; ++k)
                    {
                        for (int l = 0; l < 4; ++l)
                        {
                            shape[k][l] = temp[k][l];
                        }
                    }
                    return;
                }
            }
        }
    }

    void moveDown(const GameTable& gameTable)
    {
        // Check if the block can move down without colliding
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (shape[i][j] != 0 && (getY() + i + 1 >= TABLE_H - 1 || gameTable.isCollision(getX() + j, getY() + i + 1)))
                    return;
            }
        }
        ++y;
    }

    void moveLeft(const GameTable& gameTable)
    {
        // Check if the block can move left without colliding
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (shape[i][j] != 0 && (getX() + j - 1 <= 0 || gameTable.isCollision(getX() + j - 1, getY() + i)))
                    return;
            }
        }
        --x;
    }

    void moveRight(const GameTable& gameTable)
    {
        // Check if the block can move right without colliding
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (shape[i][j] != 0 && (getX() + j + 1 >= TABLE_W - 1 || gameTable.isCollision(getX() + j + 1, getY() + i)))
                    return;
            }
        }
        ++x;
    }

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    int getShape(int i, int j) const
    {
        return shape[i][j];
    }
};

void InputKey(Block& block, GameTable& gameTable)
{
    int k = 0;

    if (_kbhit() > 0)
    {
        k = _getch();

        switch (k)
        {
            case keyCode::UP:
            {
                GameTable gt(TABLE_W, TABLE_H);
                block.rotate(gt);
                break;
            }
            case keyCode::DOWN:
            {
                GameTable gt(TABLE_W, TABLE_H);
                block.moveDown(gt);
                break;
            }
            case keyCode::RIGHT:
            {
                GameTable gt(TABLE_W, TABLE_H);
                block.moveRight(gt);
                break;
            }
            case keyCode::LEFT:
            {
                GameTable gt(TABLE_W, TABLE_H);
                block.moveLeft(gt);
                break;
            }
            // Drop block instantly
            case keyCode::SPACE:
            {
                break;
            }
            //Hold
            case keyCode::C:
            {
                break;
            }
        }
    }

}

int main()
{
    srand(time(NULL));

    GameTable gt(TABLE_W, TABLE_H);
    Block block;

    CursorView(false);

    while (true)
    {
        InputKey(block, gt);

        // Move the block down automatically
        //block.moveDown(gt);

        system("cls");

        gt.drawGameTable();

        block.drawBlock(block.getX(), block.getY(), block);
    }

    return 0;
}