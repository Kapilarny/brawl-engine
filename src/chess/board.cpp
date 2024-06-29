//
// Created by user on 29.06.2024.
//

#include "board.h"

board::board() {
    // Create the textures
    board_tex = texture::create("../resources/chess/board.jpg", texture_format::RGB);

    piece_textures.push_back(texture::create("../resources/chess/bB.png", texture_format::RGBA));
    piece_textures.push_back(texture::create("../resources/chess/bK.png", texture_format::RGBA));
    piece_textures.push_back(texture::create("../resources/chess/bN.png", texture_format::RGBA));
    piece_textures.push_back(texture::create("../resources/chess/bP.png", texture_format::RGBA));
    piece_textures.push_back(texture::create("../resources/chess/bQ.png", texture_format::RGBA));
    piece_textures.push_back(texture::create("../resources/chess/bR.png", texture_format::RGBA));
    piece_textures.push_back(texture::create("../resources/chess/wB.png", texture_format::RGBA));
    piece_textures.push_back(texture::create("../resources/chess/wK.png", texture_format::RGBA));
    piece_textures.push_back(texture::create("../resources/chess/wN.png", texture_format::RGBA));
    piece_textures.push_back(texture::create("../resources/chess/wP.png", texture_format::RGBA));
    piece_textures.push_back(texture::create("../resources/chess/wQ.png", texture_format::RGBA));
    piece_textures.push_back(texture::create("../resources/chess/wR.png", texture_format::RGBA));

    BINFO("Loaded %d piece textures", piece_textures.size());

    // Set the pieces
    for(i8 i = 0; i < 8; i++) {
        for(i8 j = 0; j < 8; j++) {
            set_piece(i, j, piece_type::EMPTY, piece_color::WHITE);
        }
    }

    // Set the pawns
    for(i8 i = 0; i < 8; i++) {
        set_piece(i, 1, piece_type::PAWN, piece_color::WHITE);
        set_piece(i, 6, piece_type::PAWN, piece_color::BLACK);
    }
}

void board::draw_board(renderer_2d &rend) {
    rend.draw_quad({0, 0}, {1024, 1024}, board_tex.get());

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            auto [type, color] = get_piece(i, j);
            if(type != piece_type::EMPTY) {
                rend.draw_quad({i * 129, j * 129}, {130, 130}, get_texture(type, color));
            }
        }
    }
}

void board::set_piece(u8 x, u8 y, piece_type type, piece_color color) {
    board_arr[x][y] = {type, color};
}

piece board::get_piece(u8 x, u8 y) {
    return board_arr[x][y];
}

texture* board::get_texture(piece_type type, piece_color color) {
    return piece_textures[(u8)type+1 + (u8) color * 6];
}
