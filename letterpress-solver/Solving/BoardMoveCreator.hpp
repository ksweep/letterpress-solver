//
//  BoardMoveCreator.hpp
//  letterpress-solver
//
//  Copyright © 2020 Kevin Broom. All rights reserved.
//

#ifndef BoardMoveCreator_hpp
#define BoardMoveCreator_hpp

#include <unordered_set>
#include <vector>

#include "Board.hpp"
#include "BoardMove.hpp"
#include "TrieNode.hpp"

struct BacktrackingState {
    std::vector<BoardLetter> build_letters;
    std::unordered_set<int> build_used_letter_ids;
    std::unordered_set<std::string> seen_words;
    std::unordered_set<std::string> seen_move_id_sets;
};

class BoardMoveCreator {
public:
    BoardMoveCreator(const Board& b, TrieNode* tr, const int player_number);
    std::vector<BoardMove> FindBestMoves();

private:
    Board board_;
    TrieNode* trie_root_;
    const int player_number_;

    void SearchForWords(BacktrackingState& backtracking_state, std::vector<BoardMove>& words);
    TrieNode* NodeFromLetters(TrieNode* trie_root, std::vector<BoardLetter>& build_letters);
};

#endif /* BoardMoveCreator_hpp */
