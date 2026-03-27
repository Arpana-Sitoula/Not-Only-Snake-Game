#pragma once
#include <string>
#include <SDL3/SDL.h>

struct Audio {
    void init(const std::string& path) {
        SDL_LoadWAV(path.c_str(), &spec, &buffer, &buffer_size);
    }
    void destroy() {
        if (buffer) {
            SDL_free(buffer);
            buffer = nullptr;
        }
    }
    void play(SDL_AudioStream* stream) const {
        if (stream && buffer) {
            SDL_PutAudioStreamData(stream, buffer, buffer_size);
        }
    }

    SDL_AudioStream* open_stream() const {
        SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr, nullptr, nullptr);
        if (stream) {
            SDL_AudioSpec device_format;
            SDL_GetAudioDeviceFormat(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &device_format, nullptr);
            SDL_SetAudioStreamFormat(stream, &spec, &device_format);
            SDL_ResumeAudioStreamDevice(stream);
        }
        return stream;
    }

    SDL_AudioSpec spec;
    Uint8* buffer = nullptr;
    Uint32 buffer_size = 0;
};