#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <conio.h>
#include <windows.h>

const int Board_W = 12;
const int Board_H = 25;
std::vector<std::vector<int>> matrix(Board_H, std::vector<int>(Board_W, 0));

void CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void clear_Screen()
{
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

// ���� ����
void draw_GameBoard()
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

enum eKeyCode
{
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,
    KEY_R = 114,
    KEY_SPACE = 32,
    KEY_H = 104,
};

// ����� �Է�
void input_User(int& blockPosX, int& blockPosY, bool& rotate, bool& drop)
{
    int nKey = 0;

    if (_kbhit() > 0)
    {
        nKey = _getch();

        switch (nKey)
        {
        case eKeyCode::KEY_UP:
            break;
        case eKeyCode::KEY_DOWN:
            blockPosY++;
            break;
        case eKeyCode::KEY_LEFT:
            blockPosX--;
            break;
        case eKeyCode::KEY_RIGHT:
            blockPosX++;
            break;
        case eKeyCode::KEY_R:
            rotate = true;
            break;
        case eKeyCode::KEY_SPACE:
            drop = true;
            break;
        case eKeyCode::KEY_H:
            //hold = true;
            break;
        }
    }
}

// ����
std::vector<std::vector<int>> Blocks(int num)
{
    std::vector<std::vector<int>> I;
    I = { {0, 0, 0, 0}, {0, 0, 0, 0}, {2, 2, 2, 2}, {0, 0, 0, 0} };

    std::vector<std::vector<int>> T;
    T = { {0, 0, 0, 0}, {0, 0, 2, 0}, {0, 2, 2, 2}, {0, 0, 0, 0} };

    std::vector<std::vector<int>> L;
    L = { {0, 2, 0, 0}, {0, 2, 0, 0}, {0, 2, 2, 0}, {0, 0, 0, 0} };

    std::vector<std::vector<int>> J;
    J = { {0, 0, 2, 0}, {0, 0, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0} };

    std::vector<std::vector<int>> Z;
    Z = { {0, 0, 0, 0}, {0, 2, 2, 0}, {0, 0, 2, 2}, {0, 0, 0, 0} };

    std::vector<std::vector<int>> S;
    S = { {0, 0, 0, 0}, {0, 0, 2, 2}, {0, 2, 2, 0}, {0, 0, 0, 0} };

    std::vector<std::vector<int>> O;
    O = { {0, 0, 0, 0}, {0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0} };

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
    }
}

// ���� ȸ��
std::vector<std::vector<int>> rotate_Block(std::vector<std::vector<int>> block)
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

// �� �浹 �˻�
bool check_Collision(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY)
{
    for (int i = 0; i < block.size(); i++)
    {
        for (int j = 0; j < block[i].size(); j++)
        {
            if (block[i][j] == 2)
            {
                int newX = posX + j;
                int newY = posY + i;

                // ���� ��踦 �Ѱų� �ٸ� ���� �浹�ϴ��� Ȯ��
                if (newX < 0 || newX >= Board_W || newY < 0 || newY >= Board_H || board[newY][newX] == 2 || board[newY][newX] == 1)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// ���� ����
int clear_FullLines(std::vector<std::vector<int>>& board)
{
    int linesCleared = 0;
    for (int i = Board_H - 2; i > 0; --i) // �� �Ʒ����� �˻� (�� �Ʒ����� üũ���� ����)
    {
        bool fullLine = true;
        for (int j = 1; j < Board_W - 1; ++j) // ���� ���� üũ���� ����
        {
            if (board[i][j] == 0)
            {
                fullLine = false;
                break;
            }
        }
        if (fullLine)
        {
            // ���� �� ���� �����ϰ� �� �پ� �Ʒ��� ������
            for (int k = i; k > 0; --k)
            {
                for (int j = 1; j < Board_W - 1; ++j)
                {
                    board[k][j] = board[k - 1][j];
                }
            }
            // �� �� ���� �� �ٷ� ä���
            for (int j = 1; j < Board_W - 1; ++j)
            {
                board[0][j] = 0;
            }
            linesCleared++;
            // �ٽ� ���� ��ġ���� �˻��ϱ� ���� i�� �� ĭ �ø�
            i++;
        }
    }

    return linesCleared;
}

// ���� ���� �� ���� ȹ��
void fix_Block_And_ClearLines(std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY, int& score)
{
    for (int i = 0; i < block.size(); ++i)
    {
        for (int j = 0; j < block[i].size(); ++j)
        {
            if (block[i][j] == 2)
            {
                board[posY + i][posX + j] = 2;
            }
        }
    }
    // ������ ���� ���� ���� ���� ȹ��
    int linesCleared = clear_FullLines(board);
    score += linesCleared * 100;
}

// ����� ���忡 ǥ���� �� ���� ��ġ�� �̸� ���� ��ġ�� �ٸ��� ǥ���ϴ� �Լ�
void draw_BlockOnBoardWithShadow(std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY, int shadowPosY)
{
    for (int i = 0; i < block.size(); i++)
    {
        for (int j = 0; j < block[i].size(); j++)
        {
            if (block[i][j] == 2)
            {
                // ���� ��ġ�� ����� ǥ��
                board[posY + i][posX + j] = 2;

                // �̸� ���� ��ġ�� �ٸ� ����� ����� ǥ��
                if (shadowPosY + i < Board_H - 1) // ������ �ϴ��� ���� �ʵ���
                {
                    board[shadowPosY + i][posX + j] = 3;
                }
            }
        }
    }
}

// ���� ���� ���
void print_Board(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& nextBlock)
{
    // ���� ������ �ʺ�� ����
    int boardWidth = Board_W;
    int boardHeight = Board_H;

    // ���� ���� �ʺ�� ����
    int nextBlockWidth = nextBlock[0].size();
    int nextBlockHeight = nextBlock.size();

    // ���� ����� ���� ���� ���
    for (int i = 0; i < boardHeight; i++)
    {
        // ���� ���� ���
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

        // ���� �� ��� (���� ����)
        if (i == 0)
        {
            std::cout << " �� �� �� �� �� �� ";
        }
        else if (i < nextBlockHeight + 1)
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
        else if (i == nextBlockHeight + 1)
        {
            std::cout << " �� �� �� �� �� �� ";
        }

        std::cout << "\n";
    }
}

// ���� ���� ���θ� Ȯ���ϴ� �Լ�
bool check_GameOver(const std::vector<std::vector<int>>& board)
{
    // ���� ��� ������ ���̸� ����Ͽ� ù ��° ���� Ȯ��
    for (int j = 1; j < Board_W - 1; ++j)
    {
        if (board[3][j] == 2) // ���� ��� ������ ù ��° ���� �������� ����
        {
            return true;
        }
    }
    return false;
}

// ����� ������ �̵��� �� �ִ����� ��ȯ�ϴ� �Լ�
int calculate_FallDistance(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY)
{
    int distance = 0;
    while (!check_Collision(board, block, posX, posY + distance + 1)) // �Ʒ��� �̵��� �� �ִ� �Ÿ��� ���
    {
        distance++;
    }
    return distance;
}

int main(void)
{
    CursorView();
    draw_GameBoard();
    std::vector<std::vector<int>> currentBlock = Blocks(1);
    //���� �� �̸� ����
    std::vector<std::vector<int>> nextBlock = Blocks(rand() % 7 + 1);
    int blockPosX = 5;
    int blockPosY = 0;

    clock_t lastUpdateTime = clock();

    // ���� �ϰ��ϴ� ���� (�� ����)
    double delay = 1.0;
    int score = 0;

    while (true)
    {
        // ���� �ð� ��������
        clock_t currentTime = clock();
        double elapsedTime = double(currentTime - lastUpdateTime) / CLOCKS_PER_SEC;

        // ���� �ð� �������� �� �ϰ�
        if (elapsedTime >= delay)
        {
            if (!check_Collision(matrix, currentBlock, blockPosX, blockPosY + 1))
            {
                blockPosY++;
            }
            else
            {
                // ���� �� �̻� �Ʒ��� �̵��� �� ���� �� ������Ű�� ���ο� �� ����
                fix_Block_And_ClearLines(matrix, currentBlock, blockPosX, blockPosY, score);
                currentBlock = nextBlock;
                nextBlock = Blocks(rand() % 7 + 1);
                blockPosX = 5;
                blockPosY = 0;
            }
            lastUpdateTime = currentTime;
        }

        // ����� �Է� ó��
        int tempPosX = blockPosX;
        int tempPosY = blockPosY;
        bool rotate = false;
        bool drop = false;
        input_User(tempPosX, tempPosY, rotate, drop);

        // ȸ�� ó��
        if (rotate)
        {
            std::vector<std::vector<int>> rotatedBlock = rotate_Block(currentBlock);
            if (!check_Collision(matrix, rotatedBlock, blockPosX, blockPosY))
            {
                currentBlock = rotatedBlock;
            }
        }

        // ��� ó��
        if (drop)
        {
            while (!check_Collision(matrix, currentBlock, blockPosX, blockPosY + 1))
            {
                blockPosY++;
            }
            fix_Block_And_ClearLines(matrix, currentBlock, blockPosX, blockPosY, score);
            currentBlock = nextBlock;
            nextBlock = Blocks(rand() % 7 + 1);
            tempPosX = 5;
            tempPosY = 0;
        }

        // �浹 �˻�
        if (!check_Collision(matrix, currentBlock, tempPosX, tempPosY))
        {
            blockPosX = tempPosX;
            blockPosY = tempPosY;
        }

        // ����� ������ �̵��� �� �ִ����� ����Ͽ� ǥ��
        int fallDistance = calculate_FallDistance(matrix, currentBlock, blockPosX, blockPosY);

        // ���带 �ʱ�ȭ�ϰ� ���� ���忡 �׸���
        std::vector<std::vector<int>> tempBoard = matrix;
        draw_BlockOnBoardWithShadow(tempBoard, currentBlock, blockPosX, blockPosY, blockPosY + fallDistance);

        // ���� ���
        clear_Screen();
        print_Board(tempBoard, nextBlock);

        // ���� ��� (���� �ڵ�� ����)
        std::cout << "Score: " << score << std::endl;

        // ���� ���� ���� Ȯ��
        if (check_GameOver(matrix))
        {
            system("cls");
            std::cout << "Game Over!" << std::endl;
            std::cout << "Your Score: " << score << std::endl;
            break; // ���� ����
        }
    }

    return 0;
}