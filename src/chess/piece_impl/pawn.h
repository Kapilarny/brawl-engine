//
// Created by user on 29.06.2024.
//

#ifndef PAWN_H
#define PAWN_H
#include "chess/piece.h"

class pawn : public piece {
public:
    pawn(board& board, piece_data data, i8 x, i8 y, bool norm) : piece(board, data, x, y, norm) {}

    bool is_valid_move(i8 x, i8 y) override;
    std::vector<std::pair<i8, i8>> get_valid_moves() override;
    std::vector<std::pair<i8, i8>> get_attack_moves() override;
};



#endif //PAWN_H
