//
// Created by user on 30.06.2024.
//

#ifndef HORSE_H
#define HORSE_H
#include "chess/piece.h"

class horse : public piece {
public:
    horse(board& board, piece_data data, i8 x, i8 y, bool norm) : piece(board, data, x, y, norm) {}

    bool is_valid_move(i8 x, i8 y) override;
    std::vector<std::pair<i8, i8>> get_valid_moves() override;
};

#endif //HORSE_H
