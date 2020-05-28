//
//  Score.hpp
//  letterpress-solver
//
//  Copyright © 2020 Kevin Broom. All rights reserved.
//

#ifndef Score_hpp
#define Score_hpp

#include <vector>

class Score {
public:
    int heuristic_score = 0;
    std::vector<int> player_scores = {0, 0};

    Score() : Score(0, {0, 0}) {};
    Score(int h, std::vector<int> p) : heuristic_score(h), player_scores(p) {}
};

#endif /* Score_hpp */
