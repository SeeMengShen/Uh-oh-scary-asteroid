#define WIN32_LEAN_AND_MEAN
#include "WindowsManager.h"
#include "Direct3DManager.h"
#include "DirectInputManager.h"
#include "GameManager.h"
#include "Game.h"
#include "AudioManager.h"
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "fmod_vc.lib")

using namespace std;

//---------------------------MANAGERS----------------------------------

WindowsManager* windowsManager;
Direct3DManager* d3dManager;
DirectInputManager* diManager;
GameManager* gameManager;
AudioManager* audioManager;

//--------------------------------------------------------------------

void createManagers()
{
	windowsManager = new WindowsManager();
	d3dManager = new Direct3DManager();
	diManager = new DirectInputManager();
	audioManager = new AudioManager();
	gameManager = new GameManager();
}

void initialize()
{
	windowsManager->createWindow();
	d3dManager->createD3D(windowsManager->g_hWnd);
	diManager->createDInput(windowsManager->g_hWnd);

	audioManager->initializeAudio();
	audioManager->loadSounds();
	AudioManager::volume = 0.5f;

	gameManager->init(audioManager);	
}

void cleanup()
{	
	gameManager->cleanupGames();
	audioManager->cleanupAudio();
	diManager->cleanupDInput();
	d3dManager->cleanupD3D();
	windowsManager->cleanupWindow();

	delete gameManager;
	gameManager = NULL;
	
	delete audioManager;
	audioManager = NULL;

	delete diManager;
	diManager = NULL;

	delete d3dManager;
	d3dManager = NULL;

	delete windowsManager;
	windowsManager = NULL;
}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	createManagers();
	initialize();

	while (windowsManager->windowIsRunning())
	{
		gameManager->gameScene->back()->getInput(gameManager);
		gameManager->gameScene->back()->update(gameManager, gameManager->timer->framesToUpdate(), audioManager);
		gameManager->gameScene->back()->render();
		audioManager->updateSound();
	}

	cleanup();
	return 0;
}