//
// Created by fcors on 10/22/2023.
//

#include "gem-binding.h"
#include "binding-util.h"
#include "debugwriter.h"

#include <ruby.h>
#include <alc.h>

#include "gamestate.h"

#if RAPI_FULL > 187
DEF_TYPE(GameState);
#else
DEF_ALLOCFUNC(GameState);
#endif

RB_METHOD(gameStateInitialize) {
    VALUE windowName;
    VALUE args;
    VALUE visible;
    rb_scan_args(argc, argv, "21", &windowName, &args, &visible);

    if (NIL_P(visible))
        visible = Qtrue;


    std::string appName(rb_string_value_cstr(&windowName));
    std::vector<std::string> argList;
    if (TYPE(args) == T_ARRAY) {
        long len = rb_array_len(args);
        for (long i = 0; i < len; i++) {
            auto a = rb_ary_entry(args, i);
            if (TYPE(a) == T_STRING) {
                argList.emplace_back(rb_string_value_cstr(&a));
            }
        }
    }
    bool windowVisible;
    rb_bool_arg(visible, &windowVisible);

    auto state = initInstance<GameState>(std::move(appName), std::move(argList), windowVisible);
    setPrivateData(self, state);

    return self;
}

extern "C" {
MKXPZ_GEM_EXPORT void Init_mkxpz() {
    auto klass = rb_define_class("GameState", rb_cObject);
#if RAPI_FULL > 187
    rb_define_alloc_func(klass, classAllocate<&GameStateType>);
#else
    rb_define_alloc_func(klass, GameStateAllocate);
#endif
    _rb_define_method(klass, "initialize", gameStateInitialize);
}
}

