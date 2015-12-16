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
	KUOLONKORINA,
	JUMP,
	SELECT,
	TITLE_SCREEN,
	BOSS_DAMAGE,
	LEVEL_UNLOCK,
	PORA_1,
	PORA_2,
	LONKERO, // all looping sounds under this one
	CASTLE_THEME,
	BOSS_THEME
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