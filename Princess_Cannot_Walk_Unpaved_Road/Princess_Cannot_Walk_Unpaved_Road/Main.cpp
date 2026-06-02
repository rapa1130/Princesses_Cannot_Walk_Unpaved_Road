#include <iostream>
#include "GameApp.h"
#include "Debug.h"

int main()
{
	Bisang::GameApp game;

	if (false == game.Initialize())
	{
		std::cout << "게임 초기화 실패" << std::endl;
		return -1;

	}

	game.Run();

	game.Finalize();

	return 0;
}