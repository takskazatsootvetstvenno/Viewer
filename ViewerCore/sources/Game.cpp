#include "Game.h"
#include "ResourceManager.h"
namespace TestEngine {
	void Game::setField(unsigned int x, unsigned int y)
	{
		//if(map[x][5 - y] == 0) map[x][5 - y] = 1;
		map[x][5 - y] = (map[x][5 - y] == 0)? 1:0;
		m_needUpdate = true;
	}
	void Game::drawCross()
	{
		for (int i = 0; i < map.size(); i++) {
			map[i][5 - i] = 1;
			map[i][i] = 1;
		}
		m_needUpdate = true;
	}
	void Game::updateField()
	{
		if (false == m_needUpdate) return;
		for(int i = 0;i < 6; i++)
			for (int j = 0; j < 6; j++)
			{
				switch (map[i][j])
				{
				case 0:
					ResourceManager::Instance().getMeshes()[i * 6 + j + 1].setShaderByName("General");
					break;
				case 1:
					ResourceManager::Instance().getMeshes()[i * 6 + j + 1].setShaderByName("Red");
					break;
				}
			}
		m_needUpdate = false;
	}
	void Game::clearFields()
	{
		for (auto& line : map)
			for (auto& value : line)
				value = 0;
		m_needUpdate = true;
	}
}