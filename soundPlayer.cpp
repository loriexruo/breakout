#include "soundPlayer.h"
irrklang::ISoundEngine* SoundMng::soundEngine;
void SoundMng::Init() {
	SoundMng::soundEngine = irrklang::createIrrKlangDevice();
}
void SoundMng::Play(const char *path, bool isloop) {
	SoundMng::soundEngine->play2D(path, isloop);
}
void SoundMng::RemoveAll() {
	SoundMng::soundEngine->removeAllSoundSources();
}