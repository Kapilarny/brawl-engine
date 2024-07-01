//
// Created by user on 30.06.2024.
//

#include "horse.h"

bool horse::is_valid_move(i8 x, i8 y) {
    // Check if the move is a valid horse move
    return (std::abs(x - this->x) == 2 && std::abs(y - this->y) == 1) || (std::abs(x - this->x) == 1 && std::abs(y - this->y) == 2);
}

bvector<std::pair<i8, i8>> horse::get_valid_moves() {
    bvector<std::pair<i8, i8>> moves;

    // Check all possible horse moves
    if(x + 2 <= 7 && y + 1 <= 7) moves.push_back({x + 2, y + 1});
    if(x + 2 <= 7 && y - 1 >= 0) moves.push_back({x + 2, y - 1});
    if(x - 2 >= 0 && y + 1 <= 7) moves.push_back({x - 2, y + 1});
    if(x - 2 >= 0 && y - 1 >= 0) moves.push_back({x - 2, y - 1});
    if(x + 1 <= 7 && y + 2 <= 7) moves.push_back({x + 1, y + 2});
    if(x + 1 <= 7 && y - 2 >= 0) moves.push_back({x + 1, y - 2});
    if(x - 1 >= 0 && y + 2 <= 7) moves.push_back({x - 1, y + 2});
    if(x - 1 >= 0 && y - 2 >= 0) moves.push_back({x - 1, y - 2});

    return moves;
}
