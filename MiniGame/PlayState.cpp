#include "PlayState.h"
#include "AnimatedGraphic.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
	if (m_gameObjects.size() >= 3)
	{
		if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[1]),
			dynamic_cast<SDLGameObject*>(m_gameObjects[2])))
		{
			TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
		}
	}
	else if (m_gameObjects.size() == 2)
	{
		TheGame::Instance()->getStateMachine()->changeState(WinState::Instance());
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->changeState(PauseState::Instance());
	}
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if (!TheTextureManager::Instance()->load("Assets/BG.png", "BG", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/Boy.png", "helicopter"
		, TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/Dog.png", "helicopter2"
		, TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* BG = new SDLGameObject(new LoaderParams(0, 0, 1000, 700, "BG"));
	GameObject* player = new Player(new LoaderParams(500, 100, 40, 55, "helicopter"));
	SDLGameObject* enemy = new Enemy(new LoaderParams(10, 10, 85, 55, "helicopter2"));

	m_gameObjects.push_back(BG);
	m_gameObjects.push_back(player);
	m_gameObjects.push_back(enemy);
	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("BG");
	TheTextureManager::Instance()->clearFromTextureMap("helicopter");
	TheTextureManager::Instance()->clearFromTextureMap("helicopter2");

	std::cout << "exiting PlayState\n";
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }
	return true;
}