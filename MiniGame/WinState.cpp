#include "WinState.h"
#include "MenuButton.h"

const std::string WinState::s_winID = "WIN";

void WinState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}
void WinState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}
bool WinState::onEnter()
{
	if (!TheTextureManager::Instance()->load("Assets/Win.png", "win",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/main.png", "mainbutton",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/exit2.png", "exitbutton",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	GameObject* win = new SDLGameObject(new LoaderParams(318, 50, 315, 315, "win"));
	GameObject* button1 = new MenuButton(new LoaderParams(380, 400, 200, 80, "mainbutton"), s_winToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(380, 500, 200, 80, "exitbutton"), s_exitFromWin);

	m_gameObjects.push_back(win);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	return true;
}
bool WinState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("win");
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

	return true;
}

void WinState::s_winToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(MenuState::Instance());
	std::cout << "GoToMain button clicked\n";
}

void WinState::s_exitFromWin()
{
	TheGame::Instance()->quit();
}