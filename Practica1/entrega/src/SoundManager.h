#pragma once
#include <SDL3/SDL.h>
#include <array>
#include <string>

class SoundManager
{
public:
    enum SoundName { JUMP, GAMESTART, PAUSE, HOVER, NEST, GAMEOVER, WIN, NUM_SOUNDS };
    void load();
    void unload();
    ~SoundManager();
    SoundManager();
    // reproduce un sonido
    void play(SoundName soundName);
private:
    struct AudioData {
        SDL_AudioSpec spec;
        uint8_t* buffer;
        uint32_t length;
    };
    // audios cargados en memoria
    std::array<AudioData, NUM_SOUNDS> audios;

    // dispositivo de reproducción
    SDL_AudioDeviceID audioDevice;
    // piscina de audiostreams
    std::array<SDL_AudioStream*, 16> audioStreams;
    int nextAudioStream;
};

