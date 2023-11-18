// ====================================================================================================================
// Created by Retro & Chill on 11/18/2023.
// ------------------------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
// documentation files (the “Software”), to deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so.
// ====================================================================================================================
#include "sound.h"

#include <SDL_sound.h>

namespace SDL2 {
    Sound::Sound() {
        if (Sound_Init() != 0)
            startupSucceeded();
        else
            startupFailed(std::string("Error initializing SDL_sound: ") + Sound_GetError());
    }

    Sound::~Sound() {
        if (startedSuccessfully())
            Sound_Quit();
    }
} // SDL2