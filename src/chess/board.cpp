//
// Created by user on 29.06.2024.
//

#include "board.h"

#include "piece.h"
#include "piece_impl/pawn.h"

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
            set_piece(i, j, piece_type::EMPTY, piece_color::NONE);
        }
    }

    // Set the pawns
    for(i8 i = 0; i < 8; i++) {
        set_piece(i, 1, piece_type::PAWN, piece_color::WHITE);
        set_piece(i, 6, piece_type::PAWN, piece_color::BLACK);
    }

    // THE ROOKS
    set_piece(0, 0, piece_type::ROOK, piece_color::WHITE);
    set_piece(7, 0, piece_type::ROOK, piece_color::WHITE);
    set_piece(0, 7, piece_type::ROOK, piece_color::BLACK);
    set_piece(7, 7, piece_type::ROOK, piece_color::BLACK);

    // knights
    set_piece(1, 0, piece_type::KNIGHT, piece_color::WHITE);
    set_piece(6, 0, piece_type::KNIGHT, piece_color::WHITE);
    set_piece(1, 7, piece_type::KNIGHT, piece_color::BLACK);
    set_piece(6, 7, piece_type::KNIGHT, piece_color::BLACK);

    // bishops
    set_piece(2, 0, piece_type::BISHOP, piece_color::WHITE);
    set_piece(5, 0, piece_type::BISHOP, piece_color::WHITE);
    set_piece(2, 7, piece_type::BISHOP, piece_color::BLACK);
    set_piece(5, 7, piece_type::BISHOP, piece_color::BLACK);

    // queens
    set_piece(3, 0, piece_type::QUEEN, piece_color::WHITE);
    set_piece(3, 7, piece_type::QUEEN, piece_color::BLACK);

    // kings
    set_piece(4, 0, piece_type::KING, piece_color::WHITE);
    set_piece(4, 7, piece_type::KING, piece_color::BLACK);
}

void board::update() {
    // Check for mouse input
    if(platform_input_mouse_button_down(mouse_button::LEFT)) {
        auto pos = platform_input_get_mouse_position();
        pos.x /= 129;
        pos.y /= 129;

        i8 x = (i8)pos.x;
        i8 y = (i8)pos.y;

        auto [type, color] = get_piece(pos.x, 7 - y);
        BINFO("Selected %s %s at %d, %d", get_piece_name(type), get_piece_color_str(color), (i8)pos.x, 7 - y);
        BINFO("Last selected %d, %d", selected_piece.first, selected_piece.second);

        bool valid_turn = (selected_piece.first != -1 || (white_turn ? color == piece_color::WHITE : color == piece_color::BLACK)) || color == piece_color::NONE;

        if(valid_turn && (selected_piece.first != x || selected_piece.second != 7 - y)) {
            if(selected_piece != std::make_pair((i8)-1, (i8)-1)) {
                // Check if the move is valid
                auto [sel_type, sel_color] = get_piece(selected_piece.first, selected_piece.second);

                if(sel_color != color) {
                    i8 norm_sel_y = selected_piece.second;
                    if(sel_color == piece_color::BLACK) norm_sel_y = 7 - norm_sel_y;

                    ptr_wrap p = piece::create(*this, {sel_type, sel_color}, selected_piece.first, norm_sel_y);
                    i8 norm_y = 7 - y;
                    if(sel_color == piece_color::BLACK) norm_y = 7 - norm_y;

                    if(p->is_valid_move(x, norm_y)) {
                        set_piece(pos.x, 7 - y, sel_type, sel_color);
                        set_piece(selected_piece.first, selected_piece.second, piece_type::EMPTY, piece_color::NONE);

                        white_turn = !white_turn;
                    }

                    selected_piece = {-1, -1};
                } else {
                    selected_piece = {(i8)pos.x, 7 - y};
                }
            } else {
                if(type != piece_type::EMPTY) selected_piece = {(i8)pos.x, 7 - y};
                else selected_piece = {-1, -1};
            }
        }
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

    if(selected_piece.first != -1) display_possible_moves(rend, selected_piece.first, selected_piece.second);
}

void board::display_possible_moves(renderer_2d &rend, i8 x, i8 y) {
    // Get the piece
    auto [type, color] = get_piece(x, y);
    i8 norm_y = y;

    if(color == piece_color::BLACK) norm_y = 7 - y;

    piece* p = piece::create(*this, {type, color}, x, norm_y);

    // Get the valid moves
    auto moves = p->get_valid_moves();

    for(auto& [x, y] : moves) {
        if(color == piece_color::BLACK) y = 7 - y;
        rend.draw_quad({-4 + x * 129, -9 + y * 129}, {130, 130}, {1, 0, 0, .5f});
    }
}

void board::set_piece(u8 x, u8 y, piece_type type, piece_color color) {
    board_arr[x][y] = {type, color};
}

piece_data board::get_piece(u8 x, u8 y, bool norm) {
    if(norm) y = 7 - y;

    return board_arr[x][y];
}

texture* board::get_texture(piece_type type, piece_color color) {
    return piece_textures[(u8)type + (u8) color * 6];
}
