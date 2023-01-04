#include "GameManager.h"
#include "OptionMenu.h"
#include <string>
#include "AudioManager.h"
#include "WindowsManager.h"

using namespace std;

void OptionMenu::init(GameManager* gameManager)
{
	uiPanel = new Panel(new D3DXVECTOR2(WindowsManager::windowsWidth / 2, WindowsManager::windowsHeight / 2));
	textures.push_back(new Texture("Assets/Button2.png", 24, 62));
	textures.push_back(new Texture("Assets/VolumeUp.png", 50, 52));
	textures.push_back(new Texture("Assets/VolumeDown.png", 50, 52));

	//Option Text
	Text* optionText = new Text("Options\0", 100, 100, 500, 200, 255, 255, 255, new D3DXVECTOR2(-83, -150), true);

	//Audio Volume Text
	Text* volumeText = new Text("Volume\0", 100, 100, 500, 200, 255, 255, 255, new D3DXVECTOR2(-60, -100), false);

	//Volume UP Button
	Button* upVolumeButton = new Button(textures.at(1),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.7f, 0.7f), 0.0f),
		new Text(".\0", 0, 0, 0),
		new D3DXVECTOR2(25, -50));

	AudioManager::currentChannel->getVolume(&AudioManager::volume);
	volumeInt = AudioManager::volume * 100;
	volumeString = to_string(volumeInt);
	

	//Audio Volume Value
	Text* volumeNumber = new Text(volumeString, 100, 100, 500, 200, 255, 255, 255,
		new D3DXVECTOR2(-35, -50), false);

	//Volume DOWN Button
	Button* downVolumeButton = new Button(textures.at(2),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.7f, 0.7f), 0.0f),
		new Text("..\0", 0, 0, 0),
		new D3DXVECTOR2(-95, -50));

	//Resume Button
	Button* resumeButton = new Button(textures.at(0),
		new TransformationMatrix(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(3.0f, 2.15f), 0.0f),
		new Text("Resume\0", 0, 0, 0),
		new D3DXVECTOR2(-105, 35));

	uiPanel->vecLbls.push_back(optionText);
	uiPanel->vecLbls.push_back(volumeText);
	uiPanel->vecLbls.push_back(volumeNumber);

	uiPanel->vecBtns.push_back(upVolumeButton);
	uiPanel->vecBtns.push_back(downVolumeButton);
	uiPanel->vecBtns.push_back(resumeButton);

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

void OptionMenu::updateVolumeString()
{
	volumeInt = AudioManager::volume * 100;
	volumeString = to_string(volumeInt);
	uiPanel->vecLbls.back()->setText(volumeString);
}

void OptionMenu::update(GameManager* gameManager, int framesToUpdate, AudioManager* audioManager)
{
	mouseCursor->updateBoxCollider();
	mouseCheckBoundary();

	//-----------------------------------------------Cursor & UI Collision Check-----------------------------------------------
	btnString = checkButtonCollision(gameManager, audioManager);

	if (btnString == ".H")
	{
		if (AudioManager::volume < 1)
		{
			AudioManager::volume += 0.01f;
			audioManager->updateVolume();
			updateVolumeString();
		}
		
		if (volumeInt == 0)
		{
			AudioManager::currentChannel->setMute(false);
		}
		
	}
	else if (btnString == "..H")
	{
		if (AudioManager::volume >= 0)
		{
			AudioManager::volume -= 0.01f;
			AudioManager::currentChannel->setVolume(AudioManager::volume);
			updateVolumeString();
		}

		if (volumeInt == 0)
		{
			AudioManager::currentChannel->setMute(true);
		}
	}
	else if (btnString == "Resume")
	{
		gameManager->gameScene->back()->cleanup();
		delete gameManager->gameScene->back();
		gameManager->gameScene->pop_back();
	}

	//-----------------------------------------------Cursor & UI Collision Check-----------------------------------------------
}
