#include "Bullet.h"
#include "Game.h"

Bullet::Bullet(const LoaderParams* pParams)
	: SDLGameObject(pParams)
{
}

void Bullet::draw()
{
	SDLGameObject::draw();
}
void Bullet::update()
{
	m_velocity.setX(velocity);

	if (PlayState::Instance()->checkCollision(
		dynamic_cast<SDLGameObject*>(PlayState::Instance()->m_gameObjects[2]),
		dynamic_cast<SDLGameObject*>(PlayState::Instance()->m_gameObjects[3])))
	{
		clean();
		PlayState::Instance()->m_gameObjects.pop_back();
		PlayState::Instance()->m_gameObjects.pop_back();
	}
	if (m_position.getX() <= 0 || m_position.getX() >= 1000)
	{
		clean();
		PlayState::Instance()->m_gameObjects.pop_back();
	}

	SDLGameObject::update();
}
void Bullet::clean()
{
	SDLGameObject::clean();
}
