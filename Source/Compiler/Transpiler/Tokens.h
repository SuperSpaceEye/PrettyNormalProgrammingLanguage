//
// Created by spaceeye on 09.03.23.
//

#ifndef PRETTYNORMALPROGRAMMINGLANGUAGE_TOKENS_H
#define PRETTYNORMALPROGRAMMINGLANGUAGE_TOKENS_H

#include <unordered_map>
#include <string>
#include <string_view>
#include <array>

namespace Tokens {
    enum class TOKEN {
        NULLT,
        FN,
        VAR,

        VOID,
        INT,
        FLOAT,
        IF,
        ELSE,
        WHILE,
        FOR,

        SET,

        ADD,
        SUB,
        MUL,
        DIV,

        ADD_SET,
        SUB_SET,
        MUL_SET,
        DIV_SET,
        INC,
        DEC,

        AND,
        OR,
        EQ,
        NE,
        NOT,
        ME,
        LE,
        MT,
        LT,

        LCB,
        RCB,
        LBB,
        RBB,
        LFB,
        RFB,

        STR_B,

        REF,
        BOR,
        END_C,
        COMMENT,
        COMMA,

        UNK_WORD,
        NUMBER,
    };

    const int num_tokens = (int)TOKEN::NUMBER;
    const int num_words = (int)TOKEN::UNK_WORD;

    #define d(a, b) {#a, TOKEN::b},

    inline std::unordered_map<std::string_view, TOKEN> TOKENS_MAP {
        d(fn, FN)
        d(var, VAR)

        d(void, VOID)
        d(int, INT)
        d(float, FLOAT)
        d(if, IF)
        d(else, ELSE)
        d(while, WHILE)
        d(for, FOR)

        d(=, SET)

        d(+, ADD)
        d(-, SUB)
        d(*, MUL)
        d(/, DIV)

        d(+=, ADD_SET)
        d(-=, SUB_SET)
        d(*=, MUL_SET)
        d(/=, DIV_SET)
        d(++, INC)
        d(--, DEC)

        d(&&, AND)
        d(||, OR)
        d(==, EQ)
        d(!=, NE)
        d(!, NOT)
        d(>=, ME)
        d(<=, LE)
        d(>, MT)
        d(<, LT)

        {"(", TOKEN::LCB},
        {")", TOKEN::RCB},
        d([, LBB)
        d(], RBB)
        d({, LFB)
        d(}, RFB)

        {"\"", TOKEN::STR_B},

        d(&, REF)
        d(|, BOR)
        d(;, END_C)
        d(#, COMMENT)
        {",", TOKEN::COMMA},
    };

    inline std::unordered_map<TOKEN, std::string_view> INV_TOKENS_MAP = {
            []() {
        std::unordered_map<TOKEN, std::string_view> ret;

        for (auto & [k, v]: TOKENS_MAP) {ret[v] = k;}

        return ret;
    }()};

    const std::array<std::string , 10> NUMERIC_CHARS {
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
    };

    const std::array<std::string, 6> WHITESPACE {
        " ", "\f", "\n", "\r", "\t", "\v"
    };

    const std::array<TOKEN, 19> LOGIC_TOKENS {
            TOKEN::SET,
            TOKEN::ADD,
            TOKEN::SUB,
            TOKEN::MUL,
            TOKEN::DIV,
            TOKEN::REF,
            TOKEN::NOT,
            TOKEN::BOR,
            TOKEN::MT,
            TOKEN::LT,
            TOKEN::LCB,
            TOKEN::RCB,
            TOKEN::LBB,
            TOKEN::RBB,
            TOKEN::LFB,
            TOKEN::RFB,
            TOKEN::END_C,
            TOKEN::COMMENT,
            TOKEN::COMMA,
    };
}

#endif //PRETTYNORMALPROGRAMMINGLANGUAGE_TOKENS_H
