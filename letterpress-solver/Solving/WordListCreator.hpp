//
//  WordListCreator.hpp
//  letterpress-solver
//
//  Copyright © 2020 Kevin Broom. All rights reserved.
//

#ifndef WordListCreator_hpp
#define WordListCreator_hpp

#include <fstream>
#include <string>
#include <vector>

#include "Board.hpp"

// NOTE: this can be used for debugging and is not used when solving

class WordListCreator {
public:
    static std::vector<std::string> GetValidWordList(const Board& board) {
        std::vector<std::string> result;

        std::vector<int> grid_counts = std::vector<int>(26, 0);
        for (int i = 0; i < 26; i++) {
            grid_counts[board.letters[i].character - 'a'] += 1;
        }

        std::ifstream word_file("words_en.txt");
        std::string current_word;
        while (word_file >> current_word) {
            bool add_word = true;
            std::vector<int> current_word_character_counts = std::vector<int>(26, 0);
            for (const char c : current_word) {
                const int index = c - 'a';
                current_word_character_counts[index] += 1;
                if (current_word_character_counts[index] > grid_counts[index]) {
                    add_word = false;
                    break;
                }
            }
            if (add_word) {
                result.push_back(current_word);
            }
        }

        // sort by descending length, then alphabetically
        std::sort(result.begin(), result.end(), []
        (const std::string& first, std::string& second){
            return first.size() != second.size() ? first.size() > second.size() : first < second;
        });

        return result;
    }
private:
};

#endif /* WordListCreator_hpp */
