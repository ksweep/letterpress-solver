//
//  BoardScorer.hpp
//  letterpress-solver
//
//  Copyright © 2020 Kevin Broom. All rights reserved.
//

#ifndef BoardScorer_hpp
#define BoardScorer_hpp

#include "Board.hpp"
#include "BoardMove.hpp"
#include "Score.hpp"

static const int kGridSideSize = 5;
static const int kTotalGridSize = kGridSideSize * kGridSideSize;

static const std::vector<std::vector<int>> kNeighborDirections = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} }; // up, right, down, left

static inline bool ValidRowOrColumn(const int index) {
    return index >= 0 && index < kGridSideSize;
}

static inline bool ValidCellIndex(const int row, const int col) {
    return ValidRowOrColumn(row) && ValidRowOrColumn(col);
}

static inline int RowOfIndex(const int index) {
    return index / kGridSideSize;
}

static inline int ColumnOfIndex(const int index) {
    return index % kGridSideSize;
}

static inline int OpponentNumberForPlayerNumber(const int player_number) {
    return player_number == 1 ? 2 : 1;
}

class BoardScorer {
private:

    static bool NeighborsHaveSameColor(const Board& board, const BoardLetter& letter) {
        const int row = RowOfIndex(letter.index);
        const int col = ColumnOfIndex(letter.index);
        for (const std::vector<int>& direction : kNeighborDirections) {
            const int neighbor_row = row + direction[1];
            const int neighbor_col = col + direction[0];
            const int neighbor_index = neighbor_row * kGridSideSize + neighbor_col;
            if (ValidCellIndex(neighbor_row, neighbor_col) && board.letters[neighbor_index].color != letter.color) {
                return false;
            }
        }
        return true;
    }

    static std::vector<int> PointsPerPlayer(const Board& board) {
        std::vector<int> points_per_player = {0, 0};
        for (const BoardLetter& letter : board.letters) {
            if (letter.color != 0) {
                points_per_player[letter.color - 1] += 1;
            }
        }
        return points_per_player;
    }

    static int HeuristicScore (const Board& board, const int player_number, const int opponent_player_number) {
        int result = 0;
        for (const BoardLetter& letter : board.letters) {
            if (letter.color == player_number) {
                result += NeighborsHaveSameColor(board, letter) ? 2 : 1;
            } else if (letter.color == opponent_player_number) {
                result -= NeighborsHaveSameColor(board, letter) ? 2 : 1;
            }
        }
        return result;
    }

    static int WinningPlayer(const std::vector<int>& points_per_player) {
        if (points_per_player[0] + points_per_player[1] == kTotalGridSize) {
            return points_per_player[0] > points_per_player[1] ? 1 : 2;
        }
        return 0;
    }

public:

    static Score ScoreForBoard(const Board& board, const int player_number) {
        const int opponent_player_number = OpponentNumberForPlayerNumber(player_number);
        const std::vector<int> points_per_player = PointsPerPlayer(board);

        const int winning_player = WinningPlayer(points_per_player);
        if (winning_player == player_number) {
            return Score(std::numeric_limits<int>::max(), points_per_player);
        } else if (winning_player == opponent_player_number) {
            return Score(std::numeric_limits<int>::min(), points_per_player);
        }

        const int h_score =  HeuristicScore(board, player_number, opponent_player_number);
        return Score(h_score, points_per_player);
    }

    static Score ScoreForMove(const Board& board, const BoardMove& move, const int player_number) {
        const int opponent_player_number = OpponentNumberForPlayerNumber(player_number);
        Board modified_board = board;
        for (const BoardLetter& move_letter : move.letters) {
            BoardLetter existing_letter = board.letters[move_letter.index];
            assert(existing_letter.character == move_letter.character);
            if (existing_letter.color != opponent_player_number || !NeighborsHaveSameColor(board, existing_letter)) {
                modified_board.letters[move_letter.index].color = player_number;
            }
        }
        return ScoreForBoard(modified_board, player_number);
    }
};

#endif /* BoardScorer_hpp */
