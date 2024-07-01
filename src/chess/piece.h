//
// Created by user on 29.06.2024.
//

#ifndef PIECE_H
#define PIECE_H
#include "board.h"

class piece {
public:
    virtual ~piece() = default;

    piece(board& board, piece_data data, i8 x, i8 y, bool norm) : board_ref(board), type(data.type), color(data.color), x(x), y(y), norm(norm) {}

    static piece* create(board& board, piece_data data, i8 x, i8 y);

    virtual bool is_valid_move(i8 x, i8 y) = 0;
    virtual bvector<std::pair<i8, i8>> get_valid_moves() = 0;

    bvector<std::pair<i8, i8>> get_possible_moves();

    void move(i8 x, i8 y) {
        this->x = x;
        this->y = y;
    }

    [[nodiscard]] piece_type get_type() const { return type; }
    [[nodiscard]] piece_color get_color() const { return color; }

    [[nodiscard]] i8 get_x() const { return x; }
    [[nodiscard]] i8 get_y() const { return y; }
protected:
    i8 x, y;
    bool norm;

    board& board_ref;
    piece_type type;
    piece_color color;
};

#endif //PIECE_H
