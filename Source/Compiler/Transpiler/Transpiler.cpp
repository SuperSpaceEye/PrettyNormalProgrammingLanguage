//
// Created by spaceeye on 09.03.23.
//

#include "Transpiler.h"
#include "TranspilerHelperFns.h"

using namespace TranspilerNS;
using namespace Tokens;

TranspilerResult Transpiler::transpile_data(const std::string &str_data) {
    TranspilerResult to_return{};
    auto & data = str_data;

    for (int i = 0; i < data.length(); i++) {
        auto chr = std::string{data[i]};

        chrp++;
        if (!started_token) {
            tchrp = chrp;
            started_token = true;
        }

        if (chr == "\n") {
            row++;
            chrp = 0;
        }

        if (chr == "\n" && comment) {
            comment = false;
            started_token = false;
            continue;
        }

        if (comment) {
            started_token = false;
            continue;
        }

        if (is_in(chr, WHITESPACE)) {
            if (!word.empty()) {
                add_token();
            }
            started_token = false;
            continue;
        }

        auto tk = TOKENS_MAP[chr];

        if (tk == TOKEN::NULLT) {
            word += chr;
            continue;
        }

        if (tk == TOKEN::END_C) {
            if (!word.empty()) {; started_token = false;}
            continue;
        }

        if (tk == TOKEN::COMMENT) {
            comment = true;
            continue;
        }

        if (tk == TOKEN::STR_B) {
            tokenized.emplace_back(TOKEN::STR_B, row, tchrp);
            while (i < data.length() && data[++i] != *"\"") {
                //TODO
//                if (data[i] == *"\\") {
//                    if (i + 1 < data.length()) {
//                        if (data[i+1] == *"n") {
//                            tokenized.emplace_back((TOKEN)(*"\n"+num_tokens), row, tchrp); i++;
//                        } else if (data[i+1] == *"\"") {
//                            tokenized.emplace_back((TOKEN)(*"\""+num_tokens), row, tchrp); i++;
//                        } else if (data[i+1] == *"\\") {
//                            tokenized.emplace_back((TOKEN)(*"\\"+num_tokens), row, tchrp); i++;
//                        } else {
//                            tokenized.emplace_back((TOKEN)(*"\\"+num_tokens), row, tchrp);
//                        }
//                    }
//                } else {
//                    tokenized.emplace_back((TOKEN)(data[i]+num_tokens), row, tchrp);
//                }
            }
            tokenized.emplace_back(TOKEN::STR_B, row, tchrp);
            started_token = false;
            continue;
        }

        if (is_in(tk, LOGIC_TOKENS)) {
            if (!word.empty()) {
                add_token();
                started_token = false;
                tchrp = chrp;
            }

            word += chr;

            if (i+1 < data.length()) {
                auto nchr = std::string{data[i+1]};

                if (tk == TOKEN::SUB && is_in(nchr, NUMERIC_CHARS)) {
                    continue;
                }

                //Logic constructs can be either 1 or 2 char length
                if (is_in(TOKENS_MAP[nchr], LOGIC_TOKENS)) {
                    auto temp_w = word + nchr;
                    if (TOKENS_MAP[temp_w] != TOKEN::NULLT) {
                        add_token();
                        word = "";
                        i++;
                        continue;
                    }
                }
            }
            add_token();
            started_token = false;
            continue;
        }
    }

    to_return.tokens = std::move(tokenized);
    to_return.wreg   = std::move(wreg);

    return to_return;
}

void Transpiler::add_token() {
    auto tk = TOKENS_MAP[word];
    if (tk != TOKEN::NULLT) {
        tokenized.emplace_back(tk, row, chrp);
        word = "";
        return;
    }

    auto n_res = is_number(word);
    if (n_res.is_number) {
        tokenized.emplace_back(TOKEN::NUMBER, row, chrp);

        if (n_res.had_dot) {
            tokenized.emplace_back(TOKEN::FLOAT, row, chrp);
            auto num = std::stof(word);
            tokenized.emplace_back(*(TOKEN*)&num, row, chrp);
        } else {
            tokenized.emplace_back(TOKEN::INT, row, chrp);
            auto num = std::stoi(word);
            tokenized.emplace_back(*(TOKEN*)&num, row, chrp);
        }
        word = "";
        return;
    }

    tokenized.emplace_back(TOKEN::UNK_WORD, row, chrp);
    tokenized.emplace_back((TOKEN)wreg.register_word(word), row, chrp);
    word = "";
}

#include <iostream>

void Transpiler::display_tokens(const TranspilerResult &result) {
    for (int i = 0; i < result.tokens.size(); i++) {
        auto token = result.tokens[i].token;

        if (token == TOKEN::NUMBER) {
            switch (result.tokens[i+1].token) {
                case TOKEN::INT:
                    std::cout << *(int32_t*)&result.tokens[i + 2].token;
                    break;
//                case TOKEN::UINT:
//                    std::cout << (uint32_t) result.tokens[i + 2].first;
//                    break;
                case TOKEN::FLOAT:
                    std::cout << *(float*)&result.tokens[i + 2].token;
                    break;
                default:
                    throw std::logic_error("Unknown type token");
            }
            i += 2;
            continue;
        }

        if (token == TOKEN::UNK_WORD) {
            std::cout << result.wreg.get_word(result.tokens[i+1].token) << " ";
            i++;
            continue;
        }

//        if (token == Token::STR_BRACKET) {
//            std::cout << "\"";
//            while (result.tokens[++i].first != Token::STR_BRACKET) {
//                std::cout << (char)((int)result.tokens[i].first-num_tokens);
//            }
//            std::cout << "\"";
//            i++;
//            continue;
//        }
        std::cout << INV_TOKENS_MAP[token];
    }
    std::cout << "\nWords: ";
    for (auto & word: result.wreg.names) {
        std::cout << "\"" << word << "\" ";
    }
    std::cout << "\n";
}
