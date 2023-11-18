// ====================================================================================================================
// Created by Retro & Chill on 11/18/2023.
// ------------------------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
// documentation files (the “Software”), to deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so.
// ====================================================================================================================
#include "winsock_wrapper.h"

#include <array>

WinSock::WinSock() {
    if (WSAStartup(0x101, &wsadata) || wsadata.wVersion == 0x101)
        startupSucceeded();
    else {
        std::array<char, 200> buf{};
        snprintf(buf.data(), buf.size(), "Error initializing winsock: %08X",
                 WSAGetLastError());
        startupFailed(buf.data());
    }
}

WinSock::~WinSock() {
    if (wsadata.wVersion)
        WSACleanup();
}
