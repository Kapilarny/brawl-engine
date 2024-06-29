//
// Created by user on 29.06.2024.
//

#include "pawn.h"

bool pawn::is_valid_move(i8 x, i8 y) {
    // Check diagonal
    if(y == this->y + 1) return x == this->x + 1 || x == this->x - 1 && board_ref.get_piece(x, y, norm).color != color;

    // Check forward
    return x == this->x && y == this->y + 1 && board_ref.get_piece(x, y).type == piece_type::EMPTY;
}

bvector<std::pair<i8, i8>> pawn::get_valid_moves() {
    bvector<std::pair<i8, i8>> moves;

    if(y == 7) return moves; // Pawn is at the end of the board

    // Check forward
    if(board_ref.get_piece(x, y + 1, norm).type == piece_type::EMPTY) moves.push_back({x, y + 1});

    // Check diagonal
    if(x + 1 <= 7 && board_ref.get_piece(x + 1, y + 1, norm).color != color) moves.push_back({x + 1, y + 1});
    if(x - 1 >= 0 && board_ref.get_piece(x - 1, y + 1, norm).color != color) moves.push_back({x - 1, y + 1});

    return moves;
}
