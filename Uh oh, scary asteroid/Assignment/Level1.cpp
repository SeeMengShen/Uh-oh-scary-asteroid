#include "Timer.h"
#include "Level1.h"
#include "GameManager.h"
#include "GameObject.h"
#include "AnimatedObject.h"
#include "TransformationMatrix.h"
#include "PauseMenu.h"
#include "GameOverMenu.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "WindowsManager.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80)

void Level1::init(GameManager* gameManager, AudioManager* audioManager)
{
	srand(time(0));
	timer = new Timer();
	timeLeft = 100;
	highScore = 0;
	gravity.y = 0.3f;
	friction = 0.1f;
	fps = gameManager->timer->getFPS();

	textures.push_back(new Texture("Assets/bg2.png", 600, 800));
	textures.push_back(new Texture("Assets/Pause.png", 50, 54));
	textures.push_back(new SpriteSheet("Assets/Astronaut.png", 224, 32, 2, 14, 14));
	textures.push_back(new SpriteSheet("Assets/Rock.png", 20, 20, 1, 1, 1));

	uiPanel = new Panel(new D3DXVECTOR2(0.0f, 0.0f));

	background = textures.at(0);

	Button* pauseBtn = new Button(textures.at(1),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), 0.0f),
		new Text(".\0", 0, 0, 0),
		new D3DXVECTOR2(746.0f, 0.0f));

	highScoreString = to_string(highScore);
	timeString = to_string(timeLeft);

	Text* highScoreLbl = new Text("High Score: \0", 0, 0, 300, 100, 255, 255, 255, new D3DXVECTOR2(0.0f, 0.0f), false);
	Text* highScore = new Text(highScoreString, 0, 0, 300, 100, 255, 255, 255, new D3DXVECTOR2(170.0f, 0.0f), false);
	Text* timeLbl = new Text("Time left: \0", 0, 0, 300, 100, 255, 255, 255, new D3DXVECTOR2(WindowsManager::windowsWidth * 0.3, 0.0f), false);
	Text* time = new Text(timeString, 0, 0, 300, 100, 255, 255, 255, new D3DXVECTOR2(timeLbl->getPositionRelativeToPanel()->x + 130.0f, 0.0f), false);

	uiPanel->vecBtns.push_back(pauseBtn);
	uiPanel->vecLbls.push_back(highScoreLbl);
	uiPanel->vecLbls.push_back(highScore);
	uiPanel->vecLbls.push_back(timeLbl);
	uiPanel->vecLbls.push_back(time);

	//Update the buttons box collider
	for (auto btn : uiPanel->vecBtns)
	{
		btn->setButtonBoxCollider(uiPanel->getPositionRelativeToWindow()->x,
			uiPanel->getPositionRelativeToWindow()->y);
	}

	mouseCursor = new GameObject("Mouse",
		new SpriteSheet("Assets/starCursor.png", 26, 26, 1, 1, 1),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2(1.0f, 1.0f), 0.0f), 255, 255, 255,
		new D3DXVECTOR2(WindowsManager::windowsWidth / 2, WindowsManager::windowsHeight / 2), 0.0f, 0.0f);

	GameObject* asteroid = new GameObject("Asteroid",
		(SpriteSheet*)textures.at(3),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f), 0.0f),
		131, 98, 74,
		new D3DXVECTOR2(rand() % WindowsManager::windowsWidth, 0.0f),
		10.0f, 20.0f);

	asteroid->addAcceleration(D3DXVECTOR2(rand() % 10 - 5, rand() % 5 + 4));

	gameObjects.push_back(asteroid);

	audioManager->playFallingSound(asteroid->getPosition());

	AnimatedObject* astronaut = new AnimatedObject("Astronaut",
		(SpriteSheet*)textures.at(2),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(3.0f, 3.0f), 0.0f),
		255, 255, 255,
		new D3DXVECTOR2(10.0f, 580.0f),
		30.0f, 55.0f, 30);

	astronaut->setCharacterAnimation(gameManager->right);

	animatedObjects.push_back(astronaut);

	AudioManager::currentChannel = audioManager->playInGameSoundTrack(AudioManager::volume);
}

bool circleCollisionDetection(float radiusA, float radiusB, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB)
{
	//Get distance between tow object
	D3DXVECTOR2 distance = positionA - positionB;

	//If sum of both radius is smaller than their distance, collision is detected
	if (pow((radiusA + radiusB), 2) > D3DXVec2LengthSq(&distance))
	{
		return true;
	}
	else
	{
		return false;
	}
}

D3DXVECTOR2 turnLeft(D3DXVECTOR2 v) {
	//Turning a vector 90 degree
	return D3DXVECTOR2(-v.y, v.x);
}

D3DXVECTOR2 proj(D3DXVECTOR2 a, D3DXVECTOR2 b) {
	return ((D3DXVec2Dot(&a, &b) / D3DXVec2LengthSq(&b)) * b);

	//https://www.softschools.com/formulas/physics/vector_projection_formula/650/
	// a.b
	// ----  (b)
	// |b|^2
}

D3DXVECTOR2 computeVel(D3DXVECTOR2 v1, D3DXVECTOR2 v2, float m1, float m2, D3DXVECTOR2 x1, D3DXVECTOR2 x2)
{
	//Compute the final velocity of the elastic collision
	//https://en.wikipedia.org/wiki/Elastic_collision
	D3DXVECTOR2 v3 = v1 - v2;
	D3DXVECTOR2 x3 = x1 - x2;
	return v1 - (2 * m2 / (m1 + m2)) * D3DXVec2Dot(&v3, &x3) / (D3DXVec2LengthSq(&x3)) * (x1 - x2);
}

void bounce(AnimatedObject* aO1, AnimatedObject* aO2)
{
	//Method on : https://github.com/nipunramk/Reducible/blob/master/2021/Collision/collision.py
	//Line 339 - 353

	//Declaring variables to compute the final velocity for elastic collision
	D3DXVECTOR2 v1 = aO1->getVelocity();
	D3DXVECTOR2 v2 = aO2->getVelocity();
	float m1 = aO1->getMass();
	float m2 = aO2->getMass();
	D3DXVECTOR2 x1 = *aO1->getPosition() + aO1->getSpriteCentre();
	D3DXVECTOR2 x2 = *aO2->getPosition() + aO2->getSpriteCentre();


	//Compute final velocity for elastic collision
	D3DXVECTOR2 response1 = computeVel(v1, v2, m1, m2, x1, x2);
	D3DXVECTOR2 response2 = computeVel(v2, v1, m2, m1, x2, x1);

	//Add the elastic collision final velocity 1 time first to avoid frame miss collision detection
	aO1->addToPosition(response1);
	aO2->addToPosition(response2);

	//Set the elastic collision final velocity to both object
	aO1->setVelocity(response1);
	aO2->setVelocity(response2);
}

void bounce(AnimatedObject* aO, GameObject* gO)
{
	//Method on : https://github.com/nipunramk/Reducible/blob/master/2021/Collision/collision.py
	//Line 339 - 353

	//Declaring variables to compute the final velocity for elastic collision
	D3DXVECTOR2 v1 = aO->getVelocity();
	D3DXVECTOR2 v2 = gO->getVelocity();
	float m1 = aO->getMass();
	float m2 = gO->getMass();
	D3DXVECTOR2 x1 = *aO->getPosition() + aO->getSpriteCentre();
	D3DXVECTOR2 x2 = *gO->getPosition() + gO->getSpriteCentre();


	//Compute final velocity for elastic collision
	D3DXVECTOR2 response1 = computeVel(v1, v2, m1, m2, x1, x2);
	D3DXVECTOR2 response2 = computeVel(v2, v1, m2, m1, x2, x1);

	//Add the elastic collision final velocity 1 time first to avoid frame miss collision detection
	aO->addToPosition(response1);
	gO->addToPosition(response2);

	//Set the elastic collision final velocity to both object
	aO->setVelocity(response1);
	gO->setVelocity(response2);
}

bool checkCollision(AnimatedObject* aO1, AnimatedObject* aO2, AudioManager* audioManager)
{
	//If there is a collision, apply collision response by elastic collision formula and play sound
	if (circleCollisionDetection(aO1->getScaledSpriteWidth() * 0.9f / 2.0f, aO2->getScaledSpriteWidth() * 0.9f / 2.0f, *aO1->getPosition() + aO1->getSpriteCentre(), *aO2->getPosition() + aO2->getSpriteCentre()))
	{
		bounce(aO1, aO2);
		cout << "Collision " + aO1->getName() + " to " + aO2->getName() + " detected!" << endl;
		audioManager->playHurtSound(aO1->getPosition());
		return true;
	}
}

bool checkCollision(AnimatedObject* aO, GameObject* gO, AudioManager* audioManager)
{
	//If there is a collision, apply collision response by elastic collision formula and play sound
	if (circleCollisionDetection(aO->getScaledSpriteWidth() * 0.9f / 2.0f, gO->getScaledSpriteWidth() * 0.9f / 2.0f, *aO->getPosition() + aO->getSpriteCentre(), *gO->getPosition() + gO->getSpriteCentre()))
	{
		bounce(aO, gO);
		cout << "Collision " + aO->getName() + " to " + gO->getName() + " detected!" << endl;
		audioManager->playHurtSound(aO->getPosition());
		return true;
	}
}

void Level1::update(GameManager* gameManager, int framesToUpdate, AudioManager* audioManager)
{
	mouseCursor->updateBoxCollider();
	mouseCheckBoundary();

	//Timer update
	for (int i = 0; i < timer->secondsToUpdate(); i++)
	{
		//If time is not over yet, then minus time and update the string
		if (timeLeft > 0)
		{
			timeLeft--;
			timeString = to_string(timeLeft);
			uiPanel->vecLbls.back()->setText(timeString);
		}
		else //if the time is over, go to game over scene
		{
			//Game Over Menu
			GameOverMenu* gom = new GameOverMenu(highScore);
			gom->init(gameManager);
			gameManager->gameScene->push_back(gom);
		}
	}

	for (int i = 0; i < framesToUpdate; i++)
	{
		gameManager->counter++;
		for (auto aniObj : animatedObjects)
		{
			//Animation fps controller
			if (gameManager->counter % (int)(fps / aniObj->getAnimationFPS()) == 0)
			{
				//If no movement, set animation frame to frame 0
				if (!gameManager->leftKeyPressed && !gameManager->rightKeyPressed)
				{
					aniObj->setCurrentFrame(0);
				}
				else //If there is movement, add animation frame
				{
					aniObj->addCurrentFrame();
				}
			}

			//If the animation max frame is reached, reset it to frame 0
			if (aniObj->getCurrentFrame() > animatedObjects.at(0)->getSprite()->getMaxFrame())
			{
				aniObj->resetCurrentFrame();
			}

			//Update the animation rect
			aniObj->updateSprite();
		}

		//Apply gravity to character
		animatedObjects.at(0)->addAcceleration(gravity);

		if (gameManager->leftKeyPressed)
		{
			animatedObjects.at(0)->setCharacterAnimation(gameManager->left);

			//If the position within the screen, move the character
			if (animatedObjects.at(0)->getPosition()->x >= 5)
			{
				animatedObjects.at(0)->addAcceleration(D3DXVECTOR2(-(animatedObjects.at(0)->getForce() / animatedObjects.at(0)->getMass()), 0));
			}
		}

		if (gameManager->rightKeyPressed)
		{
			animatedObjects.at(0)->setCharacterAnimation(gameManager->right);

			//If the position within the screen, move the character
			if (animatedObjects.at(0)->getPosition()->x <= WindowsManager::windowsWidth - animatedObjects.at(0)->getScaledSpriteWidth())
			{
				animatedObjects.at(0)->addAcceleration(D3DXVECTOR2((animatedObjects.at(0)->getForce() / animatedObjects.at(0)->getMass()), 0));
			}
		}

		//Reset the key press flags if it is last frame to update
		if (i == framesToUpdate - 1)
		{
			gameManager->upKeyPressed = false;
			gameManager->downKeyPressed = false;
			gameManager->leftKeyPressed = false;
			gameManager->rightKeyPressed = false;
			gameManager->spaceKeyPressed = false;
		}
	}

	//-----------------------------------------------Cursor & UI Collision Check-----------------------------------------------
	//Get what button is clicked
	btnString = checkButtonCollision(gameManager, audioManager);

	if (btnString == ".")
	{
		//Pause Menu
		PauseMenu* pm = new PauseMenu();
		pm->init(gameManager);
		gameManager->gameScene->push_back(pm);
	}

	//-----------------------------------------------Cursor & UI Collision Check-----------------------------------------------

	if (gameManager->spaceKeyPressed)
	{
		if (gameManager->landed)
		{
			//Only apply jumping acceleration when character is landed
			audioManager->playJumpSound(animatedObjects.at(0)->getPosition());
			animatedObjects.at(0)->addAcceleration(D3DXVECTOR2(0, -(animatedObjects.at(0)->getForce() * 10 / animatedObjects.at(0)->getMass())));
		}
	}

	//Check if it is out of screen boundary, if it is true then move it back to top of the screen
	if (!(gameObjects.back()->getPosition()->y < WindowsManager::windowsHeight) ||
		(gameObjects.back()->getPosition()->y < 0) ||
		!(gameObjects.back()->getPosition()->x < WindowsManager::windowsWidth) ||
		(gameObjects.back()->getPosition()->x < 0))
	{
		gameObjects.back()->setPositionY(0.0f);
		gameObjects.back()->setPositionX(rand() % WindowsManager::windowsWidth);
		gameObjects.back()->resetAcceleration();
		gameObjects.back()->setVelocity(D3DXVECTOR2(0.0f, 0.0f));
		gameObjects.back()->addAcceleration(D3DXVECTOR2(rand() % 10 - 5, rand() % 5 + 4));
		audioManager->playFallingSound(gameObjects.back()->getPosition());
	}

	//------------------------------------------------Boundary Check------------------------------------------------------------

	//If character is not touching the windows bottom boundary, is not landed
	if (animatedObjects.at(0)->getPosition()->y < WindowsManager::windowsHeight - (animatedObjects.at(0)->getScaledSpriteHeight()))
	{
		gameManager->landed = false;
	}
	else
	{
		//If it is landed, then set the position to avoid falling out of screen bound, reset the y velocity
		animatedObjects.at(0)->setPositionY(WindowsManager::windowsHeight - (animatedObjects.at(0)->getScaledSpriteHeight()));
		animatedObjects.at(0)->setVelocity(D3DXVECTOR2(animatedObjects.at(0)->getVelocity().x, 0));
		gameManager->landed = true;
	}

	//If character is exceeding the screen right boundary, set the position to right boundary
	if (animatedObjects.at(0)->getPosition()->x > WindowsManager::windowsWidth - animatedObjects.at(0)->getScaledSpriteWidth())
	{
		animatedObjects.at(0)->setPositionX(WindowsManager::windowsWidth - animatedObjects.at(0)->getScaledSpriteWidth());
	}
	else if (animatedObjects.at(0)->getPosition()->x < 0)
	{
		//If character is exceeding the screen left boundary, set the position to left boundary
		animatedObjects.at(0)->setPositionX(0);
	}
	//------------------------------------------------Boundary Check------------------------------------------------------------

	//-----------------------------------------------Collision Check------------------------------------------------------------
	for (auto gObj : gameObjects)
	{
		//For each animated object, check the collision with character
		//If there is collision, add the highScore and update the highScore string
		if (checkCollision(animatedObjects.at(0), gObj, audioManager))
		{
			highScore += 10;
			highScoreString = to_string(highScore);
			uiPanel->vecLbls.at(1)->setText(highScoreString);
		}
	}
	//-----------------------------------------------Collision Check------------------------------------------------------------

	//Update the position and reset the acceleration for both character and asteroids
	animatedObjects.back()->updatePosition(friction);
	animatedObjects.back()->resetAcceleration();

	gameObjects.back()->updatePosition(0.0f);
	gameObjects.back()->resetAcceleration();
}