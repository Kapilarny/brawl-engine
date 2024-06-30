//
// Created by user on 29.06.2024.
//

#ifndef BOARD_H
#define BOARD_H
#include "memory/bvector.h"
#include "renderer/renderer_2d.h"
#include "renderer/texture.h"

enum class piece_type {
    EMPTY = -1,
    BISHOP = 0,
    KING = 1,
    KNIGHT = 2,
    PAWN = 3,
    QUEEN = 4,
    ROOK = 5
};

enum class piece_color {
    NONE = -1,
    BLACK = 0,
    WHITE = 1
};

struct piece_data {
    piece_type type;
    piece_color color;
};

class board {
public:
    board();

    bool is_valid_move(piece_data data, i8 x, i8 y);

    ~board() = default;

    void update();
    void draw_board(renderer_2d& rend);
    void display_possible_moves(renderer_2d& rend, i8 x, i8 y);
    void set_piece(u8 x, u8 y, piece_type type, piece_color color);
    piece_data get_piece(u8 x, u8 y, bool norm = false);

    texture* get_texture(piece_type type, piece_color color);
private:
    bool white_turn = true;
    std::pair<i8, i8> selected_piece = {-1, -1};
    piece_data board_arr[8][8]{};
    bvector<texture*> piece_textures;
    ptr_wrap<texture> board_tex;
};

inline piece_color get_opposite_color(piece_color color) {
    return color == piece_color::WHITE ? piece_color::BLACK : piece_color::WHITE;
}

inline const char * get_piece_name(piece_type type) {
    switch (type) {
        case piece_type::BISHOP: return "Bishop";
        case piece_type::KING: return "King";
        case piece_type::KNIGHT: return "Knight";
        case piece_type::PAWN: return "Pawn";
        case piece_type::QUEEN: return "Queen";
        case piece_type::ROOK: return "Rook";
        default: return "Empty";
    }
}

inline const char * get_piece_color_str(piece_color color) {
    switch (color) {
        case piece_color::BLACK: return "Black";
        case piece_color::WHITE: return "White";
        default: return "Empty";
    }
}

#endif //BOARD_H
