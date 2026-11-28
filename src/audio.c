#include "audio.h"

Sound monch;

void audio_Init(){

    InitAudioDevice();

    monch = LoadSound("C:/Users/Admin/Projects/Prototype_C99/assets/monch.wav");
}
void audio_DeInit() {

    UnloadSound(monch);
    CloseAudioDevice();
}
void audio_playSoundPitchVariation(Sound sound) {
    //Between 90% to 110% pitch difference
    float pitch = GetRandomValue(0.80f, 1.20f);
    
    SetSoundPitch(sound, pitch);
    PlaySound(sound);
}