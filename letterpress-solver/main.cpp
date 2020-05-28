//
//  main.cpp
//  letterpress-solver
//
//  Copyright © 2020 Kevin Broom. All rights reserved.
//

#include <iostream>

#include "Board.hpp"
#include "BoardMove.hpp"
#include "BoardMoveCreator.hpp"
#include "TrieCreator.hpp"
#include "TrieNode.hpp"
#include "WordListCreator.hpp"
#include "BoardScorer.hpp"

void TimeBlock (const std::function <void ()>& my_block) {
    const auto total_start = std::chrono::high_resolution_clock::now();
    my_block();
    const auto total_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = total_finish - total_start;
    std::cout << "Total Elapsed Time: " << elapsed.count() << " s" << std::endl;
}

int main(int argc, const char * argv[]) {
    TimeBlock([] {
        const int player_number = 1;
        
        TrieNode* trie_root = TrieCreator::MakeTrie("words_en.txt");
        const Board board = Board("dealyturiwcsbobstnmqxncas", "1111122111221122221012221");
        std::cout << "initial heuristic score is " << BoardScorer::ScoreForBoard(board, player_number).heuristic_score << std::endl;

        std::vector<BoardMove> all_moves = BoardMoveCreator(board, trie_root, player_number).FindBestMoves();

        // print best move
        const BoardMove& best_move = all_moves.front();
        std::cout << "best move is \"" << best_move.word << "\", \"" << best_move.sorted_id_string << "\", heuristic score is " <<  BoardScorer::ScoreForMove(board, best_move, player_number).heuristic_score << std::endl;
    });
    return 0;
}
