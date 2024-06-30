//
// Created by user on 30.06.2024.
//

#ifndef QUEEN_H
#define QUEEN_H
#include "chess/piece.h"

class queen : public piece {
public:
    queen(board& board, piece_data data, i8 x, i8 y, bool norm) : piece(board, data, x, y, norm) {}

    bool is_valid_move(i8 x, i8 y) override;
    bvector<std::pair<i8, i8>> get_valid_moves() override;
};

#endif //QUEEN_H
