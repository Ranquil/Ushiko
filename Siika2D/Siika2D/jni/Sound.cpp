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
	sounds[ENEMY_DEAD] = siika->_audioManager->createAudio("enemy_dead.ogg");

	// Too lazy to do this any other way
	ushikoHurts.push_back(siika->_audioManager->createAudio("voih_1.ogg"));
	ushikoHurts.push_back(siika->_audioManager->createAudio("voih_2.ogg"));
	ushikoHurts.push_back(siika->_audioManager->createAudio("voih_3.ogg"));
	ushikoHurts.push_back(siika->_audioManager->createAudio("voih_4.ogg"));
	ushikoHurts.push_back(siika->_audioManager->createAudio("voih_5.ogg"));
	ushikoHurts.push_back(siika->_audioManager->createAudio("voih_6.ogg"));
	ushikoHurts.push_back(siika->_audioManager->createAudio("voih_7.ogg"));
	ushikoHurts.push_back(siika->_audioManager->createAudio("voih_8.ogg"));
	ushikoHurts.push_back(siika->_audioManager->createAudio("voih_9.ogg"));
	ushikoHurts.push_back(siika->_audioManager->createAudio("voih_10.ogg"));
	ushikoHurts.push_back(siika->_audioManager->createAudio("voih_11.ogg"));
}

void Sound::playSound(soundName snd)
{
	if (snd == USHIKO_HURT)
		ushikoHurts[lrand48() % 11]->play();
	else sounds[snd]->play();
}