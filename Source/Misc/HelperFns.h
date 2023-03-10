//
// Created by spaceeye on 10.03.23.
//

#ifndef PRETTYNORMALPROGRAMMINGLANGUAGE_HELPERFNS_H
#define PRETTYNORMALPROGRAMMINGLANGUAGE_HELPERFNS_H

#include <algorithm>

template<typename I, typename T>
bool is_in(const T & item, const I & iter) {
    return std::any_of(iter.begin(), iter.end(), [&](const T & it){return it == item;});
}

template<typename I, typename T>
int64_t index_of(const T & item, const I & iter) {
    auto it = std::find(iter.begin(), iter.end(), item);
    if (it == iter.end()) {return -1;}
    return it - iter.begin();
}

#endif //PRETTYNORMALPROGRAMMINGLANGUAGE_HELPERFNS_H
