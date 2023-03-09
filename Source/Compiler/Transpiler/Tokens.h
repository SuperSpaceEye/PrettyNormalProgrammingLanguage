//
// Created by spaceeye on 09.03.23.
//

#ifndef PRETTYNORMALPROGRAMMINGLANGUAGE_TOKENS_H
#define PRETTYNORMALPROGRAMMINGLANGUAGE_TOKENS_H

#include <unordered_map>
#include <string>
#include <string_view>
#include <array>

enum class TOKENS {
    FN,
    VAR,

    VOID,
    INT,
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
    END_C,
    COMMENT,
    COMMA,

    UNK_WORD,
    NUMBER,
};

const int num_tokens = (int)TOKENS::NUMBER+1;
const int num_words = (int)TOKENS::UNK_WORD+1;

#define d(a, b) {#a, TOKENS::b},

const std::unordered_map<std::string, TOKENS> TOKENS_MAP{
    d(fn, FN)
    d(var, VAR)

    d(void, VOID)
    d(int, INT)
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

    {"(", TOKENS::LCB},
    {")", TOKENS::RCB},
    d([, LBB)
    d(], RBB)
    d({, LFB)
    d(}, RFB)

    {"\"", TOKENS::STR_B},

    d(&, REF)
    d(;, END_C)
    d(#, COMMENT)
    {",", TOKENS::COMMA},
};

const std::array<std::string_view , 10> NUMERIC_CHARS {
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
};

#endif //PRETTYNORMALPROGRAMMINGLANGUAGE_TOKENS_H
