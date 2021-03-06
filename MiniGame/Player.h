#pragma once
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "Bullet.h"

class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	bool isRight();
private:
	void handleInput();
	bool createBullet();
};