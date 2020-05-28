//
//  BoardMove.hpp
//  letterpress-solver
//
//  Copyright © 2020 Kevin Broom. All rights reserved.
//

#ifndef BoardMove_hpp
#define BoardMove_hpp

#include <string>
#include <vector>
#include <unordered_set>

#include "BoardLetter.hpp"
#include "Score.hpp"

class BoardMove {
public:
    BoardMove(std::string& s, std::vector<BoardLetter>& p) : word(s), letters(p) {
        std::vector<int> ids;
        for (const BoardLetter& letter : letters) {
            ids.push_back(letter.index);
        }
        sort(ids.begin(), ids.end());
        for (const int id : ids) {
            sorted_id_string += std::to_string(id) + " ";
        }
        resulting_score = Score(0, {0, 0});
    };

    std::string word;
    std::vector<BoardLetter> letters;
    std::string sorted_id_string;
    Score resulting_score;
};

#endif /* BoardMove_hpp */
