#pragma once
#include<array>
namespace TestEngine {
	class Game
	{
	public:
		static Game& Instance() {
			static Game manager;
			return manager;
		}

		Game(const Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(const Game&) = delete;
		Game& operator=(Game&&) = delete;
		void setField(unsigned int x, unsigned int y);
		void drawCross();
		void updateField();
		void clearFields();
	private:
		std::array<std::array<unsigned int, 6>, 6> map{};
		bool m_needUpdate = false;
		Game() {};
	};
}
