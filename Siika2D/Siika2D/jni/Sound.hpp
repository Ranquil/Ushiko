#ifndef SOUND_H
#define SOUND_H

#include "../engine/core/Siika2D.h"
#include "../engine/audio/Audio.h"

#include <map>

enum soundName
{
	COIN,
	ENEMY_DEAD,
	USHIKO_HURT,
	LONKERO,
	KUOLONKORINA
};

class Sound
{
public:
	Sound();
	~Sound();

	void pause();
	void resume();

	void loadSounds(core::Siika2D *siika);

	void playSound(soundName snd);
	void stopSound(soundName snd);

private:
	std::map<soundName, audio::Audio*> sounds;
	std::vector<audio::Audio*> ushikoHurts;
	std::vector<soundName> currentlyPlaying;
};

extern Sound sound;

#endif // SOUND_H