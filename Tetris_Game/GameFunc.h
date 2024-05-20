#include "GameBoard.h"
#include "Block.h"

#pragma once
class GameFunc
{
public:
	int Board_W = 12;
	int Board_H = 25;

	//����� ������ �̵��� �� �ִ����� ��ȯ�ϴ� �Լ�
	int calculate_FallDistance(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY);

	//�浹 ���� -> �� ����
	bool check_Collision(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY);
	void fix_Block_And_ClearLines(std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY, int& score);

	//���ӿ��� Ȯ��
	bool check_GameOver(const std::vector<std::vector<int>>& board);

private:
	int clear_FullLines(std::vector<std::vector<int>>& board);
};

