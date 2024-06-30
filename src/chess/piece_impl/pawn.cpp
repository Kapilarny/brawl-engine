//
// Created by user on 29.06.2024.
//

#include "pawn.h"

bool pawn::is_valid_move(i8 x, i8 y) {
    if(y != this->y + 1) return false; // Pawn can only move forward

    // Check diagonal
    if(x != this->x) return board_ref.get_piece(x, y, norm).color == get_opposite_color(color) && (x == this->x + 1 || x == this->x - 1);

    // Check forward
    return board_ref.get_piece(x, y).type == piece_type::EMPTY;
}

bvector<std::pair<i8, i8>> pawn::get_valid_moves() {
    bvector<std::pair<i8, i8>> moves;

    if(y == 7) return moves; // Pawn is at the end of the board

    // Check forward
    if(board_ref.get_piece(x, y + 1, norm).type == piece_type::EMPTY) moves.push_back({x, y + 1});

    // Check diagonal
    auto opposite_color = get_opposite_color(color);
    if(x + 1 <= 7 && board_ref.get_piece(x + 1, y + 1, norm).color == opposite_color) moves.push_back({x + 1, y + 1});
    if(x - 1 >= 0 && board_ref.get_piece(x - 1, y + 1, norm).color == opposite_color) moves.push_back({x - 1, y + 1});

    return moves;
}
