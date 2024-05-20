#include "GameFunc.h"

// 블록이 어디까지 이동할 수 있는지를 반환하는 함수
int GameFunc::calculate_FallDistance(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY)
{
    int distance = 0;
    while (!check_Collision(board, block, posX, posY + distance + 1)) // 아래로 이동할 수 있는 거리를 계산
    {
        distance++;
    }
    return distance;
}

//충돌 감지 -> 블럭 고정
//블럭 충돌 검사
bool GameFunc::check_Collision(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY)
{
    for (int i = 0; i < block.size(); i++)
    {
        for (int j = 0; j < block[i].size(); j++)
        {
            if (block[i][j] == 2)
            {
                int newX = posX + j;
                int newY = posY + i;

                // 보드 경계를 넘는지 확인
                if (newX < 0 || newX >= Board_W || newY < 0 || newY >= Board_H)
                {
                    return true;
                }

                // 다른 블럭과 충돌하는지 확인
                if (board[newY][newX] == 2 || board[newY][newX] == 1)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

//블럭 고정 및 라인 삭제 후 점수 획득
void GameFunc::fix_Block_And_ClearLines(std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY, int& score)
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
    //삭제된 라인 수에 따라 점수 획득
    int linesCleared = clear_FullLines(board);
    score += linesCleared * 100;
}
int GameFunc::clear_FullLines(std::vector<std::vector<int>>& board)
{
    int linesCleared = 0;
    //맨 아래부터 검사 (맨 아랫줄은 체크하지 않음)
    for (int i = Board_H - 2; i > 0; --i)
    {
        bool fullLine = true;
        //양쪽 벽은 체크하지 않음
        for (int j = 1; j < Board_W - 1; ++j)
        {
            if (board[i][j] == 0)
            {
                fullLine = false;
                break;
            }
        }
        if (fullLine)
        {
            //가득 찬 행을 삭제하고 한 줄씩 아래로 내리기
            for (int k = i; k > 0; --k)
            {
                for (int j = 1; j < Board_W - 1; ++j)
                {
                    board[k][j] = board[k - 1][j];
                }
            }
            //맨 윗 줄은 빈 줄로 채우기
            for (int j = 1; j < Board_W - 1; ++j)
            {
                board[0][j] = 0;
            }
            linesCleared++;
            //다시 같은 위치부터 검사하기 위해 i를 한 칸 올림
            i++;
        }
    }
    return linesCleared;
}

//게임오버 확인
bool GameFunc::check_GameOver(const std::vector<std::vector<int>>& board)
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