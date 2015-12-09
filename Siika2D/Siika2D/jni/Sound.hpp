#ifndef SOUND_H
#define SOUND_H

#include "../engine/core/Siika2D.h"
#include "../engine/audio/Audio.h"

#include <map>

enum soundName
{
	COIN,
	ENEMY_HURT,
	USHIKO_HURT,
	LONKERO
};

class Sound
{
public:
	Sound();
	~Sound();

	void loadSounds(core::Siika2D *siika);
	void playSound(soundName snd);

private:
	std::map<soundName, audio::Audio*> sounds;
};

extern Sound sound;

#endif // SOUND_H