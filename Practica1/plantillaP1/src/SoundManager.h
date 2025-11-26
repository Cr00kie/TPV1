#pragma once
#include <SDL3/SDL.h>
#include <vector>

class SoundManager
{
public:
    enum SoundName { JUMP, GAMEOVER, NUM_SOUNDS };
    void load();
    void unload();
    ~SoundManager();
    SoundManager();
    // reproduce un sonido
    void play(SoundName soundName) const;
private:
    struct AudioData {
        SDL_AudioSpec spec;
        uint8_t* buffer;
        uint32_t length;
    };
    // audios cargados en memoria
    std::vector<AudioData> audios;

    // dispositivo de reproducción
    SDL_AudioStream* playDevice;
};

