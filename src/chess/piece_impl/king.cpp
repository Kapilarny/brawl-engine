//
// Created by user on 01.07.2024.
//

#include "king.h"

bool king::is_valid_move(i8 x, i8 y) {
    // Check if the move is a valid king move
    return (std::abs(this->x - x) <= 1 && std::abs(this->y - y) <= 1);
}

bvector<std::pair<i8, i8>> king::get_valid_moves() {
    // Check all possible king moves
    bvector<std::pair<i8, i8>> moves;

    if(x - 1 >= 0 && y - 1 >= 0) moves.push_back({x - 1, y - 1});
    if(y - 1 >= 0) moves.push_back({x, y - 1});
    if(x + 1 <= 7 && y - 1 >= 0) moves.push_back({x + 1, y - 1});
    if(x - 1 >= 0) moves.push_back({x - 1, y});
    if(x + 1 <= 7) moves.push_back({x + 1, y});
    if(x - 1 >= 0 && y + 1 <= 7) moves.push_back({x - 1, y + 1});
    if(y + 1 <= 7) moves.push_back({x, y + 1});
    if(x + 1 <= 7 && y + 1 <= 7) moves.push_back({x + 1, y + 1});

    return moves;
}