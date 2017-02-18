#pragma once
#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <irrklang/irrKlang.h>

class SoundMng {
private:
	static irrklang::ISoundEngine *soundEngine;
	SoundMng() {}
	~SoundMng() {}
public:
	static void Init();
	static void Play(const char *path, bool isloop);
	static void RemoveAll();
};
#endif