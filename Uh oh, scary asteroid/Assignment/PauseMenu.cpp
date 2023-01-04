#include "GameManager.h"
#include "PauseMenu.h"
#include "OptionMenu.h"
#include "WindowsManager.h"

using namespace std;

void PauseMenu::init(GameManager* gameManager)
{
	uiPanel = new Panel(new D3DXVECTOR2(WindowsManager::windowsWidth / 2, WindowsManager::windowsHeight / 2));
	textures.push_back(new Texture("Assets/Button2.png", 24, 62));

	//Pause Text
	Text* pauseText = new Text("Game Paused\0", 100, 100, 500, 200, 255, 255, 255, new D3DXVECTOR2(-135, -150), true);

	//Resume Button
	Button* resumeButton = new Button(textures.at(0),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(3.0f, 2.15f), 0.0f),
		new Text("Resume\0", 0, 0, 0),
		new D3DXVECTOR2(-105, -90));

	//Option Button
	Button* optionButton = new Button(textures.at(0),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(3.0f, 2.15f), 0.0f),
		new Text("Options\0", 0, 0, 0),
		new D3DXVECTOR2(-105, -20));

	//Home Button
	Button* homeButton = new Button(textures.at(0),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(3.0f, 2.15f), 0.0f),
		new Text("Home\0", 0, 0, 0),
		new D3DXVECTOR2(-105, 80));

	uiPanel->vecLbls.push_back(pauseText);
	uiPanel->vecBtns.push_back(resumeButton);
	uiPanel->vecBtns.push_back(optionButton);
	uiPanel->vecBtns.push_back(homeButton);

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
}

void PauseMenu::update(GameManager* gameManager, int framesToUpdate, AudioManager* audioManager)
{
	mouseCursor->updateBoxCollider();
	mouseCheckBoundary();

	//-----------------------------------------------Cursor & UI Collision Check-----------------------------------------------
	btnString = checkButtonCollision(gameManager, audioManager);

	if (btnString == "Resume")
	{
		gameManager->gameScene->back()->cleanup();
		delete gameManager->gameScene->back();
		gameManager->gameScene->pop_back();
	}
	else if (btnString == "Options")
	{
		//Option Menu
		OptionMenu* om = new OptionMenu();
		om->init(gameManager);
		gameManager->gameScene->push_back(om);
	}
	else if (btnString == "Home")
	{
		AudioManager::currentChannel->stop();

		gameManager->gameScene->back()->cleanup();
		delete gameManager->gameScene->back();
		gameManager->gameScene->pop_back();

		gameManager->gameScene->back()->cleanup();
		delete gameManager->gameScene->back();
		gameManager->gameScene->pop_back();		

		AudioManager::currentChannel = audioManager->playMenuSoundTrack(AudioManager::volume);
	}
	//-----------------------------------------------Cursor & UI Collision Check-----------------------------------------------
}
