#include "GameBoard.h"
#include "Block.h"

#pragma once
class GameFunc
{
public:
	int Board_W = 12;
	int Board_H = 25;

	//블록이 어디까지 이동할 수 있는지를 반환하는 함수
	int calculate_FallDistance(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY);

	//충돌 감지 -> 블럭 고정
	bool check_Collision(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY);
	void fix_Block_And_ClearLines(std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& block, int posX, int posY, int& score);

	//게임오버 확인
	bool check_GameOver(const std::vector<std::vector<int>>& board);

private:
	int clear_FullLines(std::vector<std::vector<int>>& board);
};

