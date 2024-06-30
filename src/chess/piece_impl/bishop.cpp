//
// Created by user on 30.06.2024.
//

#include "bishop.h"

bool bishop::is_valid_move(i8 x, i8 y) {
    // Check if the move is a valid bishop move
    return std::abs(x - this->x) == std::abs(y - this->y);
}

bvector<std::pair<i8, i8>> bishop::get_valid_moves() {
    // Check all possible bishop moves
    bvector<std::pair<i8, i8>> moves;

    // You can probably do it in 2 loops, hell even one. Am i going to? No.
    for(i8 i = 1; x + i <= 7 && y + i <= 7; i++) {
        if(board_ref.get_piece(x + i, y + i, norm).color == color) break;
        moves.push_back({x + i, y + i});
        if(board_ref.get_piece(x + i, y + i, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = 1; x + i <= 7 && y - i >= 0; i++) {
        if(board_ref.get_piece(x + i, y - i, norm).color == color) break;
        moves.push_back({x + i, y - i});
        if(board_ref.get_piece(x + i, y - i, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = 1; x - i >= 0 && y + i <= 7; i++) {
        if(board_ref.get_piece(x - i, y + i, norm).color == color) break;
        moves.push_back({x - i, y + i});
        if(board_ref.get_piece(x - i, y + i, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = 1; x - i >= 0 && y - i >= 0; i++) {
        if(board_ref.get_piece(x - i, y - i, norm).color == color) break;
        moves.push_back({x - i, y - i});
        if(board_ref.get_piece(x - i, y - i, norm).color == get_opposite_color(color)) break;
    }

    return moves;
}
