#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"

extern Sound monch;

void audio_Init();
void audio_DeInit();

void audio_playSoundPitchVariation(Sound sound);

#endif