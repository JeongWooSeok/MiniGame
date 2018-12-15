#include "Player.h"
#include "Game.h"

Player::Player(const LoaderParams* pParams)
	: SDLGameObject(pParams)
{

}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);
	handleInput();
	isRight();
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
	m_acceleration.setX(1);
	SDLGameObject::update();
}

void Player::clean()
{
	SDLGameObject::clean();
}

void Player::handleInput()
{
	Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	m_velocity = *target - m_position;
	m_velocity /= 50;

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && PlayState::Instance()->m_gameObjects.size() == 3)
	{
		createBullet();
	}
}

bool Player::createBullet()
{
	if (!TheTextureManager::Instance()->load("Assets/Bullet.png", "bullet"
		, TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (isRight() == true)
	{
		Bullet* bullet = new Bullet(new LoaderParams(m_position.getX() + 50, m_position.getY(), 54, 20, "bullet"));
		bullet->velocity = 6;
		PlayState::Instance()->m_gameObjects.push_back(bullet);
	}
	else if (isRight() == false)
	{
		Bullet* bullet = new Bullet(new LoaderParams(m_position.getX() - 50, m_position.getY(), 54, 20, "bullet"));
		bullet->velocity = -6;
		PlayState::Instance()->m_gameObjects.push_back(bullet);
	}

	return true;
}

bool Player::isRight()
{
	if (InputHandler::Instance()->getMousePosition()->getX() > m_position.getX())
	{
		return true;
	}
	else
	{
		return false;
	}
}