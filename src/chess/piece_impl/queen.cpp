//
// Created by user on 30.06.2024.
//

#include "queen.h"

bool queen::is_valid_move(i8 x, i8 y) {
    // Check if the move is a valid queen move
    return (x == this->x || y == this->y || std::abs(x - this->x) == std::abs(y - this->y));
}

std::vector<std::pair<i8, i8>> queen::get_valid_moves() {
    std::vector<std::pair<i8, i8>> moves;

    // Check all possible rook moves
    for(i8 i = x + 1; i <= 7; i++) {
        moves.push_back({i, y});
        if(board_ref.get_piece(i, y, norm).color == color) break;
        if(board_ref.get_piece(i, y, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = x - 1; i >= 0; i--) {
        moves.push_back({i, y});
        if(board_ref.get_piece(i, y, norm).color == color) break;
        if(board_ref.get_piece(i, y, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = y + 1; i <= 7; i++) {
        moves.push_back({x, i});
        if(board_ref.get_piece(x, i, norm).color == color) break;
        if(board_ref.get_piece(x, i, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = y - 1; i >= 0; i--) {
        moves.push_back({x, i});
        if(board_ref.get_piece(x, i, norm).color == color) break;
        if(board_ref.get_piece(x, i, norm).color == get_opposite_color(color)) break;
    }

    // You can probably do it in 2 loops, hell even one. Am i going to? No.
    for(i8 i = 1; x + i <= 7 && y + i <= 7; i++) {
        moves.push_back({x + i, y + i});
        if(board_ref.get_piece(x + i, y + i, norm).color == color) break;
        if(board_ref.get_piece(x + i, y + i, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = 1; x + i <= 7 && y - i >= 0; i++) {
        moves.push_back({x + i, y - i});
        if(board_ref.get_piece(x + i, y - i, norm).color == color) break;
        if(board_ref.get_piece(x + i, y - i, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = 1; x - i >= 0 && y + i <= 7; i++) {
        moves.push_back({x - i, y + i});
        if(board_ref.get_piece(x - i, y + i, norm).color == color) break;
        if(board_ref.get_piece(x - i, y + i, norm).color == get_opposite_color(color)) break;
    }

    for(i8 i = 1; x - i >= 0 && y - i >= 0; i++) {
        moves.push_back({x - i, y - i});
        if(board_ref.get_piece(x - i, y - i, norm).color == color) break;
        if(board_ref.get_piece(x - i, y - i, norm).color == get_opposite_color(color)) break;
    }

    return moves;
}
