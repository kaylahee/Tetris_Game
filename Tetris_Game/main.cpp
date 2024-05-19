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

// 게임 보드
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

// 사용자 입력
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

// 블럭들
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

// 블럭들 회전
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

// 블럭 충돌 검사
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

                // 보드 경계를 넘거나 다른 블럭과 충돌하는지 확인
                if (newX < 0 || newX >= Board_W || newY < 0 || newY >= Board_H || board[newY][newX] == 2 || board[newY][newX] == 1)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// 라인 삭제
int clear_FullLines(std::vector<std::vector<int>>& board)
{
    int linesCleared = 0;
    for (int i = Board_H - 2; i > 0; --i) // 맨 아래부터 검사 (맨 아랫줄은 체크하지 않음)
    {
        bool fullLine = true;
        for (int j = 1; j < Board_W - 1; ++j) // 양쪽 벽은 체크하지 않음
        {
            if (board[i][j] == 0)
            {
                fullLine = false;
                break;
            }
        }
        if (fullLine)
        {
            // 가득 찬 행을 삭제하고 한 줄씩 아래로 내리기
            for (int k = i; k > 0; --k)
            {
                for (int j = 1; j < Board_W - 1; ++j)
                {
                    board[k][j] = board[k - 1][j];
                }
            }
            // 맨 윗 줄은 빈 줄로 채우기
            for (int j = 1; j < Board_W - 1; ++j)
            {
                board[0][j] = 0;
            }
            linesCleared++;
            // 다시 같은 위치부터 검사하기 위해 i를 한 칸 올림
            i++;
        }
    }

    return linesCleared;
}

// 라인 삭제 후 점수 획득
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
    // 삭제된 라인 수에 따라 점수 획득
    int linesCleared = clear_FullLines(board);
    score += linesCleared * 100;
}

// 블록을 보드에 표시할 때 현재 위치와 미리 계산된 위치를 다르게 표시하는 함수
void draw_BlockOnBoardWithShadow(std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY, int shadowPosY)
{
    for (int i = 0; i < block.size(); i++)
    {
        for (int j = 0; j < block[i].size(); j++)
        {
            if (block[i][j] == 2)
            {
                // 현재 위치에 블록을 표시
                board[posY + i][posX + j] = 2;

                // 미리 계산된 위치에 다른 모양의 블록을 표시
                if (shadowPosY + i < Board_H - 1) // 보드의 하단을 넘지 않도록
                {
                    board[shadowPosY + i][posX + j] = 3;
                }
            }
        }
    }
}

// 게임 보드 출력
void print_Board(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& nextBlock)
{
    // 현재 보드의 너비와 높이
    int boardWidth = Board_W;
    int boardHeight = Board_H;

    // 다음 블럭의 너비와 높이
    int nextBlockWidth = nextBlock[0].size();
    int nextBlockHeight = nextBlock.size();

    // 게임 보드와 다음 블럭을 출력
    for (int i = 0; i < boardHeight; i++)
    {
        // 현재 보드 출력
        for (int j = 0; j < boardWidth; j++)
        {
            if (board[i][j] == 1)
            {
                std::cout << "■ ";
            }
            else if (board[i][j] == 2)
            {
                std::cout << "□ ";
            }
            else if (board[i][j] == 3)
            {
                std::cout << "▩ ";
            }
            else
            {
                std::cout << "  ";
            }
        }

        // 다음 블럭 출력 (보드 옆에)
        if (i == 0)
        {
            std::cout << " ▣ ▣ ▣ ▣ ▣ ▣ ";
        }
        else if (i < nextBlockHeight + 1)
        {
            std::cout << " ▣ ";
            for (int j = 0; j < nextBlockWidth; j++)
            {
                if (nextBlock[i - 1][j] == 2)
                {
                    std::cout << "□ ";
                }
                else
                {
                    std::cout << "  ";
                }
            }
            std::cout << "▣ ";
        }
        else if (i == nextBlockHeight + 1)
        {
            std::cout << " ▣ ▣ ▣ ▣ ▣ ▣ ";
        }

        std::cout << "\n";
    }
}

// 게임 오버 여부를 확인하는 함수
bool check_GameOver(const std::vector<std::vector<int>>& board)
{
    // 보드 출력 영역의 높이를 고려하여 첫 번째 줄을 확인
    for (int j = 1; j < Board_W - 1; ++j)
    {
        if (board[3][j] == 2) // 보드 출력 영역의 첫 번째 줄을 기준으로 수정
        {
            return true;
        }
    }
    return false;
}

// 블록이 어디까지 이동할 수 있는지를 반환하는 함수
int calculate_FallDistance(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY)
{
    int distance = 0;
    while (!check_Collision(board, block, posX, posY + distance + 1)) // 아래로 이동할 수 있는 거리를 계산
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
    //다음 블럭 미리 설정
    std::vector<std::vector<int>> nextBlock = Blocks(rand() % 7 + 1);
    int blockPosX = 5;
    int blockPosY = 0;

    clock_t lastUpdateTime = clock();

    // 블럭이 하강하는 간격 (초 단위)
    double delay = 1.0;
    int score = 0;

    while (true)
    {
        // 현재 시간 가져오기
        clock_t currentTime = clock();
        double elapsedTime = double(currentTime - lastUpdateTime) / CLOCKS_PER_SEC;

        // 일정 시간 간격으로 블럭 하강
        if (elapsedTime >= delay)
        {
            if (!check_Collision(matrix, currentBlock, blockPosX, blockPosY + 1))
            {
                blockPosY++;
            }
            else
            {
                // 블럭이 더 이상 아래로 이동할 수 없을 때 고정시키고 새로운 블럭 생성
                fix_Block_And_ClearLines(matrix, currentBlock, blockPosX, blockPosY, score);
                currentBlock = nextBlock;
                nextBlock = Blocks(rand() % 7 + 1);
                blockPosX = 5;
                blockPosY = 0;
            }
            lastUpdateTime = currentTime;
        }

        // 사용자 입력 처리
        int tempPosX = blockPosX;
        int tempPosY = blockPosY;
        bool rotate = false;
        bool drop = false;
        input_User(tempPosX, tempPosY, rotate, drop);

        // 회전 처리
        if (rotate)
        {
            std::vector<std::vector<int>> rotatedBlock = rotate_Block(currentBlock);
            if (!check_Collision(matrix, rotatedBlock, blockPosX, blockPosY))
            {
                currentBlock = rotatedBlock;
            }
        }

        // 드롭 처리
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

        // 충돌 검사
        if (!check_Collision(matrix, currentBlock, tempPosX, tempPosY))
        {
            blockPosX = tempPosX;
            blockPosY = tempPosY;
        }

        // 블록이 어디까지 이동할 수 있는지를 계산하여 표시
        int fallDistance = calculate_FallDistance(matrix, currentBlock, blockPosX, blockPosY);

        // 보드를 초기화하고 블럭을 보드에 그리기
        std::vector<std::vector<int>> tempBoard = matrix;
        draw_BlockOnBoardWithShadow(tempBoard, currentBlock, blockPosX, blockPosY, blockPosY + fallDistance);

        // 보드 출력
        clear_Screen();
        print_Board(tempBoard, nextBlock);

        // 보드 출력 (이전 코드와 동일)
        std::cout << "Score: " << score << std::endl;

        // 게임 오버 여부 확인
        if (check_GameOver(matrix))
        {
            system("cls");
            std::cout << "Game Over!" << std::endl;
            std::cout << "Your Score: " << score << std::endl;
            break; // 게임 종료
        }
    }

    return 0;
}