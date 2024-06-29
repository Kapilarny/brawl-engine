//
// Created by user on 29.06.2024.
//
#include "piece.h"

#include "piece_impl/pawn.h"

piece* piece::create(board &board, piece_data data, i8 x, i8 y) {
    switch (data.type) {
        case piece_type::PAWN: return new pawn(board, data, x, y, data.color == piece_color::BLACK);
        default: FATAL_ERROR("Piece type not implemented!");
    }

    return nullptr;
}
