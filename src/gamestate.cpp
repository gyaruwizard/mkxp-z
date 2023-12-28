// ====================================================================================================================
// Created by Retro & Chill on 12/28/2023.
// ------------------------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
// documentation files (the “Software”), to deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so.
// ====================================================================================================================
#include "gamestate.h"
#include "debugwriter.h"
#include "rgssthreadmanager.h"

#include <alc.h>

int startGameWindow(int argc, char *argv[], bool showWindow = true);
ALCcontextPtr startRgssThread(RGSSThreadData *threadData);
int killRgssThread(RGSSThreadData *threadData);

GameState::GameState(std::string &&windowName, std::vector<std::string> &&args, bool show)
        : rgssWindowName(std::move(windowName)), eventThreadArgs(std::move(args)), showWindow(show), eventThread(&GameState::runEventThread, this), alcCtx(nullptr, alcDestroyContext) {

    const auto &threadManager = RgssThreadManager::getInstance();
    while (threadManager.getThreadData() == nullptr) {
        if (eventThreadKilled)
            return;
        std::this_thread::yield();
    }

    try {
        alcCtx = startRgssThread(threadManager.getThreadData());
    } catch (const std::system_error &e) {
        Debug() << e.what();
    }
}

GameState::~GameState() {
    if (const auto &threadManager = RgssThreadManager::getInstance(); threadManager.getThreadData() != nullptr) {
        killRgssThread(threadManager.getThreadData());
    }
}

void GameState::runEventThread() {
    std::vector<char *> argv;
    argv.push_back(rgssWindowName.data());
    for (auto &a: eventThreadArgs) {
        argv.push_back(a.data());
    }
    startGameWindow((int) argv.size(), argv.data(), showWindow);
    eventThreadKilled = true;
    Debug() << "Event thread exiting!";
}
