//
//  Board.hpp
//  letterpress-solver
//
//  Copyright © 2020 Kevin Broom. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <string>
#include <vector>

#include "BoardLetter.hpp"

class BoardLetter;

class Board{
public:
    std::vector<BoardLetter> letters;

    Board(std::string letter_string) : Board(letter_string, "0000000000000000000000000") {}

    Board(std::string letter_string, std::string color_string) {
        assert(letter_string.size() == 25 && color_string.size() == 25);
        for (int i = 0; i < letter_string.size(); i++) {
            const int color_value = color_string[i] - '0';
            letters.push_back(BoardLetter(letter_string[i], i, color_value));
        }
    }
private:
};

#endif /* Board_hpp */
