//
// Created by spaceeye on 09.03.23.
//

#ifndef PRETTYNORMALPROGRAMMINGLANGUAGE_TRANSPILER_H
#define PRETTYNORMALPROGRAMMINGLANGUAGE_TRANSPILER_H

#include <vector>
#include <string>

#include <HelperFns.h>

#include "Tokens.h"

namespace TranspilerNS {
    struct Token_C {
        Tokens::TOKEN token;
        int row;
        int col;

        Token_C(Tokens::TOKEN token, int row, int col): token(token), row(row), col(col) {}
    };

    struct WordRegister {
        std::vector<std::string> names;

        int64_t register_word(const std::string & word) {
            if (word.empty()) {throw std::logic_error("Impossible situation. Empty word entry.");}
            auto idx = index_of(word, names);
            if (idx != -1) {return idx;}
            names.emplace_back(word);
            return names.size()-1;
        }
        std::string get_word(Tokens::TOKEN token) {return names[(int)token];}

        WordRegister()=default;
    };

    struct TranspilerResult {
        std::vector<Token_C> tokens;
        WordRegister wreg;
    };

    class Transpiler {
    private:
        int row=1;
        int chrp=0;
        // for position of start of token
        int tchrp=0;

        bool started_token = false;
        bool comment = false;

        std::vector<Token_C> tokenized{};
        std::string word{};

        WordRegister wreg{};

        void add_token();
    public:
        TranspilerResult transpile_data(const std::string &str_data);
        static void display_tokens(const TranspilerResult &result);
    };

}

#endif //PRETTYNORMALPROGRAMMINGLANGUAGE_TRANSPILER_H
