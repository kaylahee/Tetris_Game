#include "GameFunc.h"

// ����� ������ �̵��� �� �ִ����� ��ȯ�ϴ� �Լ�
int GameFunc::calculate_FallDistance(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY)
{
    int distance = 0;
    while (!check_Collision(board, block, posX, posY + distance + 1)) // �Ʒ��� �̵��� �� �ִ� �Ÿ��� ���
    {
        distance++;
    }
    return distance;
}

//�浹 ���� -> �� ����
//�� �浹 �˻�
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

                // ���� ��踦 �Ѵ��� Ȯ��
                if (newX < 0 || newX >= Board_W || newY < 0 || newY >= Board_H)
                {
                    return true;
                }

                // �ٸ� ���� �浹�ϴ��� Ȯ��
                if (board[newY][newX] == 2 || board[newY][newX] == 1)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

//�� ���� �� ���� ���� �� ���� ȹ��
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
    //������ ���� ���� ���� ���� ȹ��
    int linesCleared = clear_FullLines(board);
    score += linesCleared * 100;
}
int GameFunc::clear_FullLines(std::vector<std::vector<int>>& board)
{
    int linesCleared = 0;
    //�� �Ʒ����� �˻� (�� �Ʒ����� üũ���� ����)
    for (int i = Board_H - 2; i > 0; --i)
    {
        bool fullLine = true;
        //���� ���� üũ���� ����
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
            //���� �� ���� �����ϰ� �� �پ� �Ʒ��� ������
            for (int k = i; k > 0; --k)
            {
                for (int j = 1; j < Board_W - 1; ++j)
                {
                    board[k][j] = board[k - 1][j];
                }
            }
            //�� �� ���� �� �ٷ� ä���
            for (int j = 1; j < Board_W - 1; ++j)
            {
                board[0][j] = 0;
            }
            linesCleared++;
            //�ٽ� ���� ��ġ���� �˻��ϱ� ���� i�� �� ĭ �ø�
            i++;
        }
    }
    return linesCleared;
}

//���ӿ��� Ȯ��
bool GameFunc::check_GameOver(const std::vector<std::vector<int>>& board)
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