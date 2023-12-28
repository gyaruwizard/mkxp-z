// ====================================================================================================================
// Created by Retro & Chill on 12/28/2023.
// ------------------------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
// documentation files (the “Software”), to deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so.
// ====================================================================================================================

#pragma once


#include <string>
#include <vector>
#include <memory>
#include <thread>
#include "gem-binding.h"

struct ALCcontext;

using ALCcontextPtr = std::unique_ptr<ALCcontext, void (*)(ALCcontext *)>;

class GameState {

public:
    GameState(std::string &&windowName, std::vector<std::string> &&args, bool show = true);

    ~GameState();

private:
    void runEventThread();

    std::string rgssWindowName;
    std::vector<std::string> eventThreadArgs;
    bool showWindow;

    std::jthread eventThread;
    ALCcontextPtr alcCtx;
    bool eventThreadKilled = false;
};
