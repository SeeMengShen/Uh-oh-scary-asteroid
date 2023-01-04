#include "Game.h"
#include "GameManager.h"
#include "GameObject.h"
#include "AnimatedObject.h"
#include "Text.h"
#include "TransformationMatrix.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "DirectInputManager.h"
#include "Direct3DManager.h"
#include "WindowsManager.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80)

void Game::init(GameManager* gameManager)
{
}

void Game::getInput(GameManager* gameManager)
{
	DirectInputManager::dInputKeyboardDevice->Acquire();
	DirectInputManager::dInputMouseDevice->Acquire();

	//	Get immediate Keyboard Data.
	DirectInputManager::dInputKeyboardDevice->GetDeviceState(256, DirectInputManager::diKeys);
	DirectInputManager::dInputMouseDevice->GetDeviceState(sizeof(DirectInputManager::mouseState), &DirectInputManager::mouseState);

	if (DirectInputManager::diKeys[DIK_UP] & 0x80)
	{
		gameManager->upKeyPressed = true;
	}
	if (DirectInputManager::diKeys[DIK_DOWN] & 0x80)
	{
		gameManager->downKeyPressed = true;
	}
	if (DirectInputManager::diKeys[DIK_LEFT] & 0x80)
	{
		gameManager->leftKeyPressed = true;
	}
	if (DirectInputManager::diKeys[DIK_RIGHT] & 0x80)
	{
		gameManager->rightKeyPressed = true;
	}
	if (DirectInputManager::diKeys[DIK_SPACE] & 0x80)
	{
		gameManager->spaceKeyPressed = true;
	}

	if (BUTTONDOWN(DirectInputManager::mouseState, 0))
	{
		//Use prevMouse0Clicked to prevent multiple click event
		//If prevMouse0Clicked is false, then set mouse0Clicked and prevMouse0Clicked to true
		//Else the mouse0 is in holding mode, then set mouse0Clicked as false and mouse0Holding as true
		if (!gameManager->prevMouse0Clicked)
		{
			gameManager->mouse0Clicked = true;
			gameManager->prevMouse0Clicked = true;
		}
		else
		{
			gameManager->mouse0Clicked = false;
			gameManager->mouse0Holding = true;
		}
	}
	else
	{
		gameManager->mouse0Clicked = false;
		gameManager->prevMouse0Clicked = false;
		gameManager->mouse0Holding = false;
	}

	mouseCursor->getPosition()->x += DirectInputManager::mouseState.lX;
	mouseCursor->getPosition()->y += DirectInputManager::mouseState.lY;
}

void Game::update(GameManager* gameManager, int framesToUpdate, AudioManager* audioManager)
{
}

void Game::render()
{
	//	Clear and begin scene
	//	Clear the back buffer.
	Direct3DManager::d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	//	Begin the scene
	Direct3DManager::d3dDevice->BeginScene();

	//	Specify alpha blend will ensure that the spriteSheet will render the background with alpha.
	Direct3DManager::spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTransformation2D(&mat, NULL, 0.0f, NULL, NULL, NULL, NULL);
	Direct3DManager::spriteBrush->SetTransform(&mat);


	//Only executes when the background is not null
	if (background != NULL)
	{
		Direct3DManager::spriteBrush->Draw(background->getTexturePointer(),
			NULL, NULL, NULL,
			D3DCOLOR_XRGB(255, 255, 255));
	}

	for (auto gameObj : gameObjects)
	{
		//Get information for each gameObj to set transformation
		spriteCentre = gameObj->getSpriteCentre();
		scalingCentre = gameObj->getTransformMatrix()->getScalingCentre();
		scaling = gameObj->getTransformMatrix()->getScaling();
		rotation = gameObj->getTransformMatrix()->getRotation();
		trans = gameObj->getPosition();

		D3DXMatrixTransformation2D(&mat, &scalingCentre, 0.0f, &scaling, NULL, rotation, trans);
		Direct3DManager::spriteBrush->SetTransform(&mat);

		Direct3DManager::spriteBrush->Draw(gameObj->getSpriteSheet()->getTexturePointer(),
			NULL, NULL, NULL,
			D3DCOLOR_XRGB(gameObj->getRed(),
				gameObj->getGreen(),
				gameObj->getBlue()));
	}

	for (auto aniObj : animatedObjects)
	{
		//Get information for each aniObj to set transformation
		spriteCentre = aniObj->getSpriteCentre();
		scalingCentre = aniObj->getTransformMatrix()->getScalingCentre();
		scaling = aniObj->getTransformMatrix()->getScaling();
		trans = aniObj->getPosition();

		D3DXMatrixTransformation2D(&mat, &scalingCentre, 0.0f, &scaling, &spriteCentre, 0.0f, trans);
		Direct3DManager::spriteBrush->SetTransform(&mat);

		Direct3DManager::spriteBrush->Draw(aniObj->getSpriteSheet()->getTexturePointer(),
			aniObj->getSpriteRect(), NULL, NULL,
			D3DCOLOR_XRGB(aniObj->getRed(),
				aniObj->getGreen(),
				aniObj->getBlue()));
	}

	//Only executes when uiPanel is not null
	if (uiPanel != NULL)
	{
		for (auto button : uiPanel->vecBtns)
		{
			//Assign the precise position to draw this button into a temp variable, assign its pointer to trans
			D3DXVECTOR2 temp = *uiPanel->getPositionRelativeToWindow() + *button->getPositionRelativeToPanel();
			trans = &temp;
			scalingCentre = button->getTransformationMatrix()->getScalingCentre();
			scaling = button->getTransformationMatrix()->getScaling();

			D3DXMatrixTransformation2D(&mat, &scalingCentre, 0.0f, &scaling, NULL, 0.0f, trans);
			Direct3DManager::spriteBrush->SetTransform(&mat);

			//If the mouse is on top of it, then apply some colour filter, else draw original colour
			if (button->isMouseOn())
			{
				Direct3DManager::spriteBrush->Draw(button->getTexture()->getTexturePointer(),
					button->getButtonRect(), NULL, NULL,
					D3DCOLOR_XRGB(200, 200, 200));
			}
			else
			{
				Direct3DManager::spriteBrush->Draw(button->getTexture()->getTexturePointer(),
					button->getButtonRect(), NULL, NULL,
					D3DCOLOR_XRGB(255, 255, 255));
			}


			//Set the Z-Order for drawing label
			D3DXMATRIX mat(1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 1.0f);
			Direct3DManager::spriteBrush->SetTransform(&mat);

			button->getLabel()->setRect(temp.x * 1.025f,
				temp.x + button->getTexture()->getTextureWidth() * button->getTransformationMatrix()->getScaling().x,
				temp.y * 1.025f,
				temp.y + button->getTexture()->getTextureHeight() * button->getTransformationMatrix()->getScaling().y);

			Direct3DManager::font->DrawText(Direct3DManager::spriteBrush,
				button->getLabel()->getStr().c_str(),
				-1, button->getLabel()->getTextRect(), 0,
				D3DCOLOR_XRGB(button->getLabel()->getRed(),
					button->getLabel()->getGreen(),
					button->getLabel()->getBlue()));
		}

		for (auto label : uiPanel->vecLbls)
		{
			//Assign the precise position to draw this label into a temp variable, use it to set the textRect for drawing
			D3DXVECTOR2 temp = *uiPanel->getPositionRelativeToWindow() + *label->getPositionRelativeToPanel();

			D3DXMATRIX mat(1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 1.0f);
			Direct3DManager::spriteBrush->SetTransform(&mat);

			label->setRect(temp.x,
				temp.x + label->getRectRight(),
				temp.y,
				temp.y + label->getRectBottom());

			//Check whether it is a title, if true then use title font to draw, else use normal font
			if (label->isTitleFont())
			{
				Direct3DManager::titleFont->DrawText(Direct3DManager::spriteBrush,
					label->getStr().c_str(),
					-1, label->getTextRect(), 0,
					D3DCOLOR_XRGB(label->getRed(),
						label->getGreen(),
						label->getBlue()));
			}
			else
			{
				Direct3DManager::font->DrawText(Direct3DManager::spriteBrush,
					label->getStr().c_str(),
					-1, label->getTextRect(), 0,
					D3DCOLOR_XRGB(label->getRed(),
						label->getGreen(),
						label->getBlue()));
			}
		}

		//Mouse Cursor render
		scaling = mouseCursor->getTransformMatrix()->getScaling();
		rotation = mouseCursor->getTransformMatrix()->getRotation();
		trans = mouseCursor->getPosition();

		D3DXMatrixTransformation2D(&mat, NULL, 0.0f, &scaling, NULL, rotation, trans);
		Direct3DManager::spriteBrush->SetTransform(&mat);

		Direct3DManager::spriteBrush->Draw(mouseCursor->getSpriteSheet()->getTexturePointer(),
			NULL, NULL, NULL,
			D3DCOLOR_XRGB(mouseCursor->getRed(),
				mouseCursor->getGreen(),
				mouseCursor->getBlue()));

	}

	//	End spriteSheet drawing
	Direct3DManager::spriteBrush->End();

	//Line rendering
	for (auto line : lines)
	{
		tempLine[0] = line.back();
		line.pop_back();
		tempLine[1] = line.back();
		line.pop_back();

		Direct3DManager::lineBrush->Begin();
		Direct3DManager::lineBrush->Draw(tempLine, 2, D3DCOLOR_XRGB(255, 255, 255));
		Direct3DManager::lineBrush->End();
	}


	//	End and present scene
	//	End the scene
	Direct3DManager::d3dDevice->EndScene();

	//	Present the back buffer to screen
	Direct3DManager::d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Game::cleanup()
{
	//Cleanup each texture in the textures vector
	while (!textures.empty())
	{
		cout << "\nCleanup texture : " + textures.back()->getTexturePath() << endl;
		textures.back()->getTexturePointer()->Release();
		textures.back()->nullTexturePointer();
		delete textures.back();
		textures.back() = NULL;
		textures.pop_back();
		cout << "SUCCESSFUL\n\n" << endl;
	}

	//Cleanup each gameObject in the gameObjects vector
	while (!gameObjects.empty())
	{
		cout << "\nCleanup gObj : " + gameObjects.back()->getName() << endl;
		gameObjects.back()->cleanup();
		delete gameObjects.back();
		gameObjects.back() = NULL;
		gameObjects.pop_back();
		cout << "SUCCESSFUL\n\n" << endl;
	}

	//Cleanup each animatedObject in the animatedObjects vector
	while (!animatedObjects.empty())
	{
		cout << "\nCleanup gObj : " + animatedObjects.back()->getName() << endl;
		animatedObjects.back()->cleanup();
		delete animatedObjects.back();
		animatedObjects.back() = NULL;
		animatedObjects.pop_back();
		cout << "SUCCESSFUL\n\n" << endl;
	}

	//Invoke uiPanel cleanup when it is not null
	if (uiPanel != NULL)
	{
		cout << "\nCleanup uiPanel : " << endl;

		uiPanel->cleanup();
		delete uiPanel;
		uiPanel = NULL;

		cout << "SUCCESSFUL\n\n" << endl;
	}

	mouseCursor->getSpriteSheet()->getTexturePointer()->Release();
	mouseCursor->getSpriteSheet()->nullTexturePointer();
	mouseCursor->cleanup();

	trans = NULL;
}

//Rectangle collision detection for two object
bool Game::collisionDetection(RECT a, RECT b)
{
	if (a.top > b.bottom)
	{
		return false;
	}
	if (a.bottom < b.top)
	{
		return false;
	}
	if (a.left > b.right)
	{
		return false;
	}
	if (a.right < b.left)
	{
		return false;
	}
	return true;
}

//Check collision between ui Buttons and mouse cursor, if collision detected then return the buttton's label string
//else return empty string
string Game::checkButtonCollision(GameManager* gameManager, AudioManager* audioManager)
{
	if (uiPanel != NULL)
	{
		for (auto btn : uiPanel->vecBtns)
		{
			if (collisionDetection(mouseCursor->getBoxCollider(), btn->getButtonBoxCollider()))
			{
				if (!btn->isMouseOn())
				{
					audioManager->playPointingSound();
					btn->setMouseOn(true);
				}
				else
				{
					if (gameManager->mouse0Clicked)
					{
						return btn->getLabel()->getStr();
					}
					else if (gameManager->mouse0Holding)
					{
						return btn->getLabel()->getStr() + 'H';
					}
				}
			}
			else
			{
				btn->setMouseOn(false);
			}
		}
	}
	gameManager->mouse0Clicked = false;
	return "";
}

void Game::mouseCheckBoundary()
{
	if (mouseCursor->getPosition()->x >= WindowsManager::windowsWidth - mouseCursor->getSpriteSheet()->getTextureWidth())
	{
		mouseCursor->getPosition()->x = WindowsManager::windowsWidth - mouseCursor->getSpriteSheet()->getTextureWidth();
	}
	else if (mouseCursor->getPosition()->x <= 0)
	{
		mouseCursor->getPosition()->x = 0;
	}

	if (mouseCursor->getPosition()->y >= WindowsManager::windowsHeight - mouseCursor->getSpriteSheet()->getTextureHeight())
	{
		mouseCursor->getPosition()->y = WindowsManager::windowsHeight - mouseCursor->getSpriteSheet()->getTextureHeight();
	}
	else if (mouseCursor->getPosition()->y <= 0)
	{
		mouseCursor->getPosition()->y = 0;
	}
}
