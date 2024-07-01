//
// Created by user on 01.07.2024.
//

#ifndef KING_H
#define KING_H
#include "chess/piece.h"

class king : public piece {
public:
    king(board& board, piece_data data, i8 x, i8 y, bool norm) : piece(board, data, x, y, norm) {}

    bool is_valid_move(i8 x, i8 y) override;
    bvector<std::pair<i8, i8>> get_valid_moves() override;
};

#endif //KING_H
