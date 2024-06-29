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
    PAWN = 2,
    QUEEN = 3,
    KNIGHT = 4,
    ROOK = 5
};

enum class piece_color {
    BLACK = 0,
    WHITE = 1
};

struct piece {
    piece_type type;
    piece_color color;
};

class board {
public:
    board();
    ~board() = default;

    void draw_board(renderer_2d& rend);
    void set_piece(u8 x, u8 y, piece_type type, piece_color color);
    piece get_piece(u8 x, u8 y);

    texture* get_texture(piece_type type, piece_color color);
private:
    piece board_arr[8][8]{};
    bvector<texture*> piece_textures;
    ptr_wrap<texture> board_tex;
};

#endif //BOARD_H
