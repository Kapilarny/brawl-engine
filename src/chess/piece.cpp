//
// Created by user on 29.06.2024.
//
#include "piece.h"

#include "piece_impl/bishop.h"
#include "piece_impl/horse.h"
#include "piece_impl/king.h"
#include "piece_impl/pawn.h"
#include "piece_impl/queen.h"
#include "piece_impl/rook.h"

piece* piece::create(board &board, piece_data data, i8 x, i8 y) {
    switch (data.type) {
        case piece_type::PAWN: return new pawn(board, data, x, y, data.color == piece_color::BLACK);
        case piece_type::KNIGHT: return new horse(board, data, x, y, data.color == piece_color::BLACK);
        case piece_type::BISHOP: return new bishop(board, data, x, y, data.color == piece_color::BLACK);
        case piece_type::ROOK: return new rook(board, data, x, y, data.color == piece_color::BLACK);
        case piece_type::QUEEN: return new queen(board, data, x, y, data.color == piece_color::BLACK);
        case piece_type::KING: return new king(board, data, x, y, data.color == piece_color::BLACK);
        default: FATAL_ERROR("Piece type not implemented!");
    }

    return nullptr;
}

std::vector<std::pair<i8, i8>> piece::get_possible_moves() {
    std::vector<std::pair<i8, i8>> moves;

    for(auto move : get_valid_moves()) {
        if(board_ref.get_piece(move.first, move.second, norm).color != color) {
            moves.push_back(move);
        }
    }

    return moves;
}
