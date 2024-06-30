//
// Created by user on 30.06.2024.
//

#include "rook.h"

bool rook::is_valid_move(i8 x, i8 y) {
    // Check if the move is a valid rook move
    return (x == this->x || y == this->y);
}

bvector<std::pair<i8, i8>> rook::get_valid_moves() {
    bvector<std::pair<i8, i8>> moves;

    // Check all possible rook moves
    for(i8 i = x + 1; i <= 7; i++) {
        if(board_ref.get_piece(i, y, norm).color == color) break;
        moves.push_back({i, y});
        if(board_ref.get_piece(i, y, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = x - 1; i >= 0; i--) {
        if(board_ref.get_piece(i, y, norm).color == color) break;
        moves.push_back({i, y});
        if(board_ref.get_piece(i, y, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = y + 1; i <= 7; i++) {
        if(board_ref.get_piece(x, i, norm).color == color) break;
        moves.push_back({x, i});
        if(board_ref.get_piece(x, i, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = y - 1; i >= 0; i--) {
        if(board_ref.get_piece(x, i, norm).color == color) break;
        moves.push_back({x, i});
        if(board_ref.get_piece(x, i, norm).color == get_opposite_color(color)) break;
    }

    return moves;
}
