// ====================================================================================================================
// Created by Retro & Chill on 11/18/2023.
// ------------------------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
// documentation files (the “Software”), to deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so.
// ====================================================================================================================
#pragma once

#include "raiiwrapper.h"

namespace SDL2 {

    class TTF : public RaiiWrapper {
    public:
        explicit TTF();
        ~TTF();

        TTF(const TTF &) = delete;
        TTF(TTF&&) = delete;

        TTF &operator=(const TTF &) = delete;
        TTF &operator=(TTF &&) = delete;
    };

} // SDL2
