//
// Created by user on 30.06.2024.
//

#ifndef BISHOP_H
#define BISHOP_H

#include "chess/piece.h"

class bishop : public piece {
public:
    bishop(board& board, piece_data data, i8 x, i8 y, bool norm) : piece(board, data, x, y, norm) {}

    bool is_valid_move(i8 x, i8 y) override;
    std::vector<std::pair<i8, i8>> get_valid_moves() override;
};

#endif //BISHOP_H
