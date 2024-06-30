//
// Created by user on 30.06.2024.
//

#ifndef ROOK_H
#define ROOK_H
#include "chess/piece.h"

class rook : public piece {
public:
    rook(board& board, piece_data data, i8 x, i8 y, bool norm) : piece(board, data, x, y, norm) {}

    bool is_valid_move(i8 x, i8 y) override;
    bvector<std::pair<i8, i8>> get_valid_moves() override;
};

#endif //ROOK_H
