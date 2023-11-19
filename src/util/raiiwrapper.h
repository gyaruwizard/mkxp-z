// ====================================================================================================================
// Created by Retro & Chill on 11/18/2023.
// ------------------------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
// documentation files (the “Software”), to deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so.
// ====================================================================================================================

#pragma once

#include <string>

class RaiiWrapper {
public:
    inline bool startedSuccessfully() const {
        return started;
    }

    inline const std::string &getErrorMessage() const {
        return errorMessage;
    }

protected:
    inline void startupSucceeded() {
        started = true;
    }

    inline void startupFailed(std::string &&msg) {
        errorMessage = std::move(msg);
    }

private:
    bool started = false;
    std::string errorMessage;
};
