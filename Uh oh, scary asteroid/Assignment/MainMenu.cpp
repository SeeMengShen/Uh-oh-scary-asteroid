#include "GameManager.h"
#include "MainMenu.h"
#include "Level1.h"
#include "OptionMenu.h"
#include <array>
#include "WindowsManager.h"

using namespace std;

void MainMenu::init(GameManager* gameManager, AudioManager* audioManager)
{
	uiPanel = new Panel(new D3DXVECTOR2(WindowsManager::windowsWidth / 2, WindowsManager::windowsHeight / 2));
	textures.push_back(new Texture("Assets/bg.png", 612, 612));
	textures.push_back(new Texture("Assets/Button2.png", 24, 62));
	textures.push_back(new Texture("Assets/Logo.png", 384, 648));

	background = textures.at(0);

	//"Game Title" Text
	Text* gameTitle = new Text("Uh Oh, Scary Asteroid\0", 100, 100, 500, 200, 255, 255, 255, new D3DXVECTOR2(-190, -160), true);

	//Start Button
	Button* startButton = new Button(textures.at(1),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(3.0f, 2.15f), 0.0f),
		new Text("Start Game\0", 0, 0, 0),
		new D3DXVECTOR2(-105, -100));

	//Option Button
	Button* optionButton = new Button(textures.at(1),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(3.0f, 2.15f), 0.0f),
		new Text("Options\0", 0, 0, 0),
		new D3DXVECTOR2(-105,-20));

	//End Game Button
	Button* endButton = new Button(textures.at(1),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(3.0f, 2.15f), 0.0f),
		new Text("End Game\0", 0, 0, 0),
		new D3DXVECTOR2(-105, 150));

	Button* logo = new Button(textures.at(2),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.3f, 0.3f), 0.0f),
		new Text(".\0", 0, 0, 0),
		new D3DXVECTOR2(-400.0f, 200.0f));

	uiPanel->vecLbls.push_back(gameTitle);
	uiPanel->vecBtns.push_back(startButton);
	uiPanel->vecBtns.push_back(optionButton);
	uiPanel->vecBtns.push_back(endButton);
	uiPanel->vecBtns.push_back(logo);

	for (auto btn : uiPanel->vecBtns)
	{
		btn->setButtonBoxCollider(uiPanel->getPositionRelativeToWindow()->x,
			uiPanel->getPositionRelativeToWindow()->y);
	}

	lineArr.push_back(D3DXVECTOR2(210.0f, 180.0f));
	lineArr.push_back(D3DXVECTOR2(600.0f, 180.0f));
	lines.push_back(lineArr);
	lineArr.clear();

	mouseCursor = new GameObject("Mouse",
		new SpriteSheet("Assets/starCursor.png", 26, 26, 1, 1, 1),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2(1.0f, 1.0f), 0.0f), 255, 255, 255,
		new D3DXVECTOR2(WindowsManager::windowsWidth / 2, WindowsManager::windowsHeight / 2), 0.0f, 0.0f);

	AudioManager::currentChannel = audioManager->playMenuSoundTrack(AudioManager::volume);
}

void MainMenu::update(GameManager* gameManager, int framesToUpdate, AudioManager* audioManager)
{
	mouseCursor->updateBoxCollider();
	mouseCheckBoundary();

	//-----------------------------------------------Cursor & UI Collision Check-----------------------------------------------
	btnString = checkButtonCollision(gameManager, audioManager);

	if (btnString == "Start Game")
	{
		AudioManager::currentChannel->stop();

		//Level 1
		Level1* level1 = new Level1();
		level1->init(gameManager, audioManager);
		gameManager->gameScene->push_back(level1);
	}
	else if (btnString == "Options")
	{
		//Option Menu
		OptionMenu* om = new OptionMenu();
		om->init(gameManager);
		gameManager->gameScene->push_back(om);
	}
	else if(btnString == "End Game")
	{
		PostQuitMessage(0);
	}
	//-----------------------------------------------Cursor & UI Collision Check-----------------------------------------------
}