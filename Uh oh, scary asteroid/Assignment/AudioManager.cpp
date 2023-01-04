#include "AudioManager.h"
#include "WindowsManager.h"

FMOD::Channel* AudioManager::currentChannel = NULL;
float AudioManager::volume = 0.0f;

void AudioManager::initializeAudio()
{
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extraDriverData);
}

FMOD::Channel* AudioManager::playJumpSound(D3DXVECTOR2* position)
{
	result = system->playSound(jumpSound, 0, false, &channel);
	float ratio = position->x / (float)WindowsManager::windowsWidth;
	channel->setPan(ratio * 2 - 1);
	return channel;
}

FMOD::Channel* AudioManager::playHurtSound(D3DXVECTOR2* position)
{
	result = system->playSound(hurtSound, 0, false, &channel);
	float ratio = position->x / (float)WindowsManager::windowsWidth;
	channel->setPan(ratio * 2 - 1);
	return channel;
}

FMOD::Channel* AudioManager::playFallingSound(D3DXVECTOR2* position)
{
	result = system->playSound(fallingSound, 0, false, &channel);
	channel->setVolume(0.1);
	float ratio = position->x / (float)WindowsManager::windowsWidth;
	channel->setPan(ratio * 2 - 1);
	return channel;
}

FMOD::Channel* AudioManager::playPointingSound()
{
	result = system->playSound(pointingSound, 0, false, &channel);
	return channel;
}

FMOD::Channel* AudioManager::playMenuSoundTrack(float volume)
{
	result = system->playSound(menuSoundTrack, 0, false, &channel);
	channel->setVolume(volume);
	return channel;
}

FMOD::Channel* AudioManager::playInGameSoundTrack(float volume)
{
	result = system->playSound(inGameSoundTrack, 0, false, &channel);
	channel->setVolume(volume);
	return channel;
}

void AudioManager::loadSounds()
{
	result = system->createSound("Assets/Audio/jump.flac", FMOD_DEFAULT, 0, &jumpSound);
	result = jumpSound->setMode(FMOD_LOOP_OFF);

	result = system->createSound("Assets/Audio/hurt.wav", FMOD_DEFAULT, 0, &hurtSound);
	result = hurtSound->setMode(FMOD_LOOP_OFF);

	result = system->createSound("Assets/Audio/falling.flac", FMOD_DEFAULT, 0, &fallingSound);
	result = fallingSound->setMode(FMOD_LOOP_OFF);

	result = system->createSound("Assets/Audio/point.flac", FMOD_DEFAULT, 0, &pointingSound);
	result = pointingSound->setMode(FMOD_LOOP_OFF);

	result = system->createStream("Assets/Audio/47 Town Night.flac", FMOD_DEFAULT, 0, &menuSoundTrack);
	result = menuSoundTrack->setMode(FMOD_LOOP_NORMAL);

	result = system->createStream("Assets/Audio/15 Space Night.flac", FMOD_DEFAULT, 0, &inGameSoundTrack);
	result = inGameSoundTrack->setMode(FMOD_LOOP_NORMAL);
}

void AudioManager::updateSound()
{
	result = system->update();
}

void AudioManager::updateVolume()
{
	currentChannel->setVolume(volume);
}

void AudioManager::cleanupAudio()
{
	system->release();
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}
