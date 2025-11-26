#include "SoundManager.h"
#include <string>
#include <iostream>
#include "SDLError.h"

constexpr const char* const soundBase = "../assets/sounds/";

void SoundManager::load()
{
    AudioData data;
    std::string path = (std::string(soundBase) + ("jump.wav"));
    SDL_LoadWAV(path.c_str(), &data.spec, &data.buffer, &data.length);
    audios[JUMP] = data;

    /*SDL_LoadWAV("game-over.wav", &data.spec, &data.buffer, &data.length);
    audios[SoundName::GAMEOVER] = data;*/

    playDevice = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr, nullptr, nullptr);
    if (!playDevice) throw SDLError();
    int nDevices;
    SDL_AudioDeviceID * devices = SDL_GetAudioPlaybackDevices(&nDevices);
    for (int i = 0; i < nDevices; ++i)
    {
        std::cout << "Device: " << "ID - " << devices[i] << " - " << SDL_GetAudioDeviceName(devices[i]) << '\n';
    }
    
}

void SoundManager::unload()
{
    SDL_DestroyAudioStream(playDevice);
    for (AudioData data : audios) SDL_free(data.buffer);
}

SoundManager::~SoundManager()
{
}

SoundManager::SoundManager() : audios(2), playDevice(nullptr)
{
}

void SoundManager::play(SoundName soundName) const
{
    SDL_PutAudioStreamData(playDevice, audios[soundName].buffer, audios[soundName].length);
    SDL_ResumeAudioStreamDevice(playDevice);
}
