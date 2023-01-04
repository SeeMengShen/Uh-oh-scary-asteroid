#ifndef AUDIOMANAGER_H

#define AUDIOMANAGER_H

#pragma once
#include "fmod.hpp"
#include <d3dx9.h>

class AudioManager
{
public:
	FMOD::System* system;
	FMOD::Sound* jumpSound, * hurtSound, * fallingSound, * pointingSound, * menuSoundTrack, * inGameSoundTrack;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extraDriverData = 0;

	static FMOD::Channel* currentChannel;
	static float volume;

	void initializeAudio();
	FMOD::Channel* playJumpSound(D3DXVECTOR2* position);
	FMOD::Channel* playHurtSound(D3DXVECTOR2* position);
	FMOD::Channel* playFallingSound(D3DXVECTOR2* position);
	FMOD::Channel* playPointingSound();
	FMOD::Channel* playMenuSoundTrack(float volume);
	FMOD::Channel* playInGameSoundTrack(float volume);
	void loadSounds();
	void updateSound();
	void updateVolume();
	void cleanupAudio();

	AudioManager();
	~AudioManager();
};
#endif

