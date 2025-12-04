#include "SoundManager.h"
#include <string>
#include <iostream>
#include "SDLError.h"

constexpr const char* const soundBase = "../assets/sounds/";

constexpr std::array<const char*, SoundManager::NUM_SOUNDS> audiosList{
    "jump.wav",
    /*"game-start.wav",
    "pause.wav",
    "hover.wav",
    "victory.wav",
    "game-over.wav",
    "win.wav"*/
};

void SoundManager::load()
{
    // Load sounds
    AudioData data;
    for (int i = 0; i < audiosList.size(); ++i)
    {
        std::string path = (std::string(soundBase) + (audiosList[i]));
        if (!SDL_LoadWAV(path.c_str(), &data.spec, &data.buffer, &data.length))
            throw SDLError();
        audios[i] = data;
    }

    // Get audio device
    int nDevices;
    SDL_AudioDeviceID* devices = SDL_GetAudioPlaybackDevices(&nDevices);
    for (int i = 0; i < nDevices; ++i)
    {
        std::cout << "Device: " << "ID - " << devices[i] << " - " << SDL_GetAudioDeviceName(devices[i]) << '\n';
    }
    audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    std::cout << "\nOpened device: " << "ID - " << audioDevice << '\n';// << " - " << SDL_GetAudioDeviceName(devices[openedDeviceID]) << '\n';

    nextAudioStream = 0;
    for (int i = 0; i < audioStreams.size(); ++i)
    {
        audioStreams[i] = SDL_CreateAudioStream(nullptr, nullptr);
        SDL_BindAudioStream(audioDevice, audioStreams[i]);
    }

    /*SDL_LoadWAV("game-over.wav", &data.spec, &data.buffer, &data.length);
    audios[SoundName::GAMEOVER] = data;*/
}

void SoundManager::unload()
{
    for(SDL_AudioStream* stream : audioStreams) SDL_DestroyAudioStream(stream);
    for (AudioData data : audios)
        SDL_free(data.buffer);
}

SoundManager::~SoundManager()
{
}

SoundManager::SoundManager() : audioDevice(0)
{
}

void SoundManager::play(SoundName soundName)
{
    SDL_ClearAudioStream(audioStreams[nextAudioStream]);
    SDL_SetAudioStreamFormat(audioStreams[nextAudioStream], &audios[soundName].spec, nullptr);
    SDL_PutAudioStreamData(audioStreams[nextAudioStream], audios[soundName].buffer, audios[soundName].length);
    SDL_ResumeAudioStreamDevice(audioStreams[nextAudioStream]);
    nextAudioStream = (nextAudioStream+1) % audioStreams.size();
}
