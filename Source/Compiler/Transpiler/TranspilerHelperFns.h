//
// Created by spaceeye on 11.03.23.
//

#ifndef PRETTYNORMALPROGRAMMINGLANGUAGE_TRANSPILERHELPERFNS_H
#define PRETTYNORMALPROGRAMMINGLANGUAGE_TRANSPILERHELPERFNS_H

struct NumberResult {
    bool is_number = false;
    bool had_dot = false;
};

#include <string>

#include <HelperFns.h>

#include "Tokens.h"

inline NumberResult is_number(const std::string & word) {
    NumberResult res;

    if (word.length() < 1) {
        return res;
    }

    int i = 0;

    if (word[0] == *"-") {
        i++;
    }
    //TODO add logic for 10f, 50d, etc.

    for (;i < word.length(); i++) {
        //for floats
        if (word[i] == *"." && !res.had_dot) {
            res.had_dot = true;
            continue;
            //if already has float, then not a number
        } else if (word[i] == *"." && res.had_dot) {
            return res;
        }

        auto chr = std::string{word[i]};
        if (!is_in(chr, Tokens::NUMERIC_CHARS)) {
            return res;
        }
    }
    res.is_number = true;
    return res;
}

#endif //PRETTYNORMALPROGRAMMINGLANGUAGE_TRANSPILERHELPERFNS_H
