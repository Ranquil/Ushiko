#include "Sound.hpp"

Sound sound;

Sound::Sound()
{

}

Sound::~Sound()
{

}

void Sound::loadSounds(core::Siika2D* siika)
{
	sounds[COIN] = siika->_audioManager->createAudio("coin.ogg");
}

void Sound::playSound(soundName snd)
{
	sounds[snd]->play();
}