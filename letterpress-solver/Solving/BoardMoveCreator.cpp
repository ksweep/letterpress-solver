//
//  BoardMoveCreator.cpp
//  letterpress-solver
//
//  Copyright © 2020 Kevin Broom. All rights reserved.
//

#include "BoardMoveCreator.hpp"

#include "BoardScorer.hpp"

BoardMoveCreator::BoardMoveCreator(const Board& b, TrieNode* t, const int p) : board_(b), trie_root_(t), player_number_(p) {}

TrieNode* BoardMoveCreator::NodeFromLetters(TrieNode* trie_root, std::vector<BoardLetter>& build_letters) {
    TrieNode* result = trie_root;
    for (BoardLetter& letter : build_letters) {
        if (result->children[letter.character - 'a'] != nullptr) {
            result = result->children[letter.character - 'a'];
        } else {
            return nullptr;
        }
    }
    return result;
}

void BoardMoveCreator::SearchForWords(BacktrackingState& backtracking_state, std::vector<BoardMove>& words) {
    TrieNode* current_node = NodeFromLetters(trie_root_, backtracking_state.build_letters);

    if (current_node->is_word) {
        BoardMove move = BoardMove(current_node->prefix, backtracking_state.build_letters);
        const bool is_new_word = backtracking_state.seen_words.find(move.word) == backtracking_state.seen_words.end();
        const bool is_new_combination = backtracking_state.seen_move_id_sets.find(move.sorted_id_string) == backtracking_state.seen_move_id_sets.end();
        if (is_new_word || is_new_combination) {
            move.resulting_score = BoardScorer::ScoreForMove(board_, move, player_number_); // TODO: improve this
            words.push_back(move);
            backtracking_state.seen_words.insert(move.word);
            backtracking_state.seen_move_id_sets.insert(move.sorted_id_string);
        }
    }

    for (const BoardLetter& test_letter : board_.letters) {
        // skip if not in trie
        if (current_node->children[test_letter.character - 'a'] == nullptr) {
            continue;
        }
        // skip if letter has been used already
        if (backtracking_state.build_used_letter_ids.find(test_letter.index) != backtracking_state.build_used_letter_ids.end()) {
            continue;
        }

        // add letter
        backtracking_state.build_letters.push_back(test_letter);
        backtracking_state.build_used_letter_ids.insert(test_letter.index);

        // recurse
        SearchForWords(backtracking_state, words);

        // undo add letter
        backtracking_state.build_letters.pop_back();
        backtracking_state.build_used_letter_ids.erase(test_letter.index);
    }
}

std::vector<BoardMove> BoardMoveCreator::FindBestMoves() {
    std::vector<BoardMove> all_moves;
    BacktrackingState backtracking_state;

    SearchForWords(backtracking_state, all_moves);

    // sort by scores, then alphabetically
    std::sort(all_moves.begin(), all_moves.end(), [&]
    (const BoardMove& first, BoardMove& second) {
        const int first_h_score = first.resulting_score.heuristic_score;
        const int second_h_score = second.resulting_score.heuristic_score;
        if (first_h_score != second_h_score) {
            return first_h_score > second_h_score;
        }

        const int first_p_score = first.resulting_score.player_scores[player_number_ - 1];
        const int second_p_score = second.resulting_score.player_scores[player_number_ - 1];
        if (first_p_score != second_p_score) {
            return first_p_score > second_p_score;
        }

        return first.word < second.word;
    });

    return all_moves;
}
