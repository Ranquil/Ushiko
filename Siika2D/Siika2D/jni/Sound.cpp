#include "Sound.hpp"

Sound sound;

Sound::Sound()
{
	currentlyPlaying.clear();
}

Sound::~Sound()
{

}

void Sound::pause()
{
	for (soundName snd : currentlyPlaying)
		sounds[snd]->pause();
}

void Sound::resume()
{
	for (soundName snd : currentlyPlaying)
		sounds[snd]->play();
}

void Sound::loadSounds(core::Siika2D* siika)
{
	// Load sounds
	sounds[COIN] = siika->_audioManager->createAudio("coin.ogg");
	sounds[ENEMY_DEAD] = siika->_audioManager->createAudio("enemy_dead.ogg");
	sounds[LONKERO] = siika->_audioManager->createAudio("lonkero.ogg");
	sounds[KUOLONKORINA] = siika->_audioManager->createAudio("kuolonkorina.ogg");
	sounds[JUMP] = siika->_audioManager->createAudio("jump.ogg");
	sounds[SELECT] = siika->_audioManager->createAudio("select.ogg");
	sounds[TITLE_SCREEN] = siika->_audioManager->createAudio("title_screen.ogg");
	sounds[BOSS_DAMAGE] = siika->_audioManager->createAudio("boss_damage.ogg");
	sounds[LEVEL_UNLOCK] = siika->_audioManager->createAudio("level_unlock.ogg");
	sounds[PORA_1] = siika->_audioManager->createAudio("pora_1.ogg");
	sounds[PORA_2] = siika->_audioManager->createAudio("pora_2.ogg");
	sounds[CASTLE_THEME] = siika->_audioManager->createAudio("castle_theme.ogg");
	sounds[BOSS_THEME] = siika->_audioManager->createAudio("boss_theme.ogg");
	sounds[MENU_THEME] = siika->_audioManager->createAudio("menu_theme.ogg");

	// Adjust special properties/volumes
	sounds[COIN]->setVolume(0.5f);
	sounds[JUMP]->setVolume(0.6f);
	sounds[LONKERO]->setLooping(true);
	sounds[CASTLE_THEME]->setLooping(true);
	sounds[BOSS_THEME]->setLooping(true);
	sounds[MENU_THEME]->setLooping(true);

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

	if (snd >= LONKERO) // add any looping sounds to this vector
		currentlyPlaying.push_back(snd);
}

void Sound::stopSound(soundName snd)
{
	if (snd >= LONKERO) // only looping sounds should be stopped
	{
		sounds[snd]->stop();

		for (int i = 0; i < currentlyPlaying.size(); i++)
		{
			if (currentlyPlaying[i] == snd)
			{
				currentlyPlaying.erase(currentlyPlaying.begin() + i);
				break;
			}
		}
	}
}