//
// Created by spaceeye on 11.03.23.
//

#ifndef PRETTYNORMALPROGRAMMINGLANGUAGE_COMPILE_H
#define PRETTYNORMALPROGRAMMINGLANGUAGE_COMPILE_H

#include <Transpiler/Transpiler.h>

inline void compile(const std::string & data) {
    auto transpiler = TranspilerNS::Transpiler();

    auto res = transpiler.transpile_data(data);
    transpiler.display_tokens(res);

}

#endif //PRETTYNORMALPROGRAMMINGLANGUAGE_COMPILE_H
