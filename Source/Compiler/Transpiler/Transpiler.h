//
// Created by spaceeye on 09.03.23.
//

#ifndef PRETTYNORMALPROGRAMMINGLANGUAGE_TRANSPILER_H
#define PRETTYNORMALPROGRAMMINGLANGUAGE_TRANSPILER_H

#include <vector>
#include <string>

#include "Tokens.h"

struct TranspilerResult {

};

class Transpiler {
public:
    TranspilerResult transpile_data(const std::string & str_data);
    static void display_tokens(const TranspilerResult & result);
};


#endif //PRETTYNORMALPROGRAMMINGLANGUAGE_TRANSPILER_H
