// ====================================================================================================================
// Created by Retro & Chill on 11/18/2023.
// ------------------------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
// documentation files (the “Software”), to deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so.
// ====================================================================================================================

#include "raiiwrapper.h"

bool RaiiWrapper::startedSuccessfully() const {
    return started;
}

const std::string &RaiiWrapper::getErrorMessage() const {
    return errorMessage;
}

void RaiiWrapper::startupSucceeded() {
    started = true;
}

void RaiiWrapper::startupFailed(std::string &&msg) {
    errorMessage = std::move(msg);
}
