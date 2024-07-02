//
// Created by user on 29.06.2024.
//

#include "board.h"

#include <algorithm>
#include <utility>

#include "piece.h"
#include "piece_impl/pawn.h"

std::pair<i8, i8> unpack_pos(i16 pos) {
    return {(i8)(pos >> 8), (i8)(pos & 0xFF)};
}

i16 pack_pos(std::pair<i8, i8> pos) {
    return (i16)(pos.first << 8 | pos.second);
}

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

    white_king = pack_pos({4, 0});
    black_king = pack_pos({4, 7});

    // push the pieces
    for(i8 i = 0; i < 8; i++) {
        white_pieces.insert(pack_pos({i, 0}));
        white_pieces.insert(pack_pos({i, 1}));
        black_pieces.insert(pack_pos({i, 6}));
        black_pieces.insert(pack_pos({i, 7}));
    }
}

void board::regenerate_attacked_squares(bool turn) {
    bzero_memory(attacked_squares, sizeof(attacked_squares));
    if(turn) {
        for(auto val : white_pieces) {
            auto [x, y] = unpack_pos(val);
            auto [type, color] = get_piece(x, y);

            // ASSERT(color == piece_color::WHITE, "INVALID COLOR");
            if(color != piece_color::WHITE) {
                BDEBUG("Invalid Color! %d", color);
            }

            ptr_wrap wrap_p = piece::create(*this, {type, color}, x, y);
            if(type == piece_type::KING) white_king = pack_pos({x, y});
            for(auto& [x, y] : wrap_p->get_attack_moves()) {
                attacked_squares[x][y] = true;
            }
        }
    } else {
        for(auto val : black_pieces) {
            auto [x, y] = unpack_pos(val);
            auto [type, color] = get_piece(x, y);

            if(color != piece_color::BLACK) {
                BDEBUG("Invalid Color! %d", color);
            }

            ptr_wrap wrap_p = piece::create(*this, {type, color}, x, 7 - y);
            if(type == piece_type::KING) black_king = pack_pos({x, y});
            for(auto& [x, y] : wrap_p->get_attack_moves()) {
                attacked_squares[x][7 - y] = true;
            }
        }
    }
}

bool board::simulate_move(i8 from_x, i8 from_y, i8 to_x, i8 to_y) {
    auto [type, color] = get_piece(from_x, from_y);
    auto [to_type, to_color] = get_piece(to_x, to_y);

    bool moving_white = color == piece_color::WHITE;

    // ASSERT(type != piece_type::EMPTY, "Trying to move an empty piece");

    if(type == piece_type::EMPTY) {
        BDEBUG("Trying to move an empty piece");
        return false;
    }

    auto black_count = black_pieces.size();
    auto white_count = white_pieces.size();

    // if(color == piece_color::BLACK) to_y = 7 - to_y;

    if(color == piece_color::WHITE) {
        white_pieces.erase(pack_pos({from_x, from_y}));
        white_pieces.insert(pack_pos({to_x, to_y}));

        if(to_color == piece_color::BLACK) {
            auto packed = pack_pos({to_x, to_y});
            black_pieces.erase(packed);
        }
    } else {
        black_pieces.erase(pack_pos({from_x, from_y}));
        black_pieces.insert(pack_pos({to_x, to_y}));

        if(to_color == piece_color::WHITE) {
            white_pieces.erase(pack_pos({to_x, to_y}));
        }
    }

    // Set the king positions if the king is moved
    if(type == piece_type::KING) {
        if(color == piece_color::WHITE) white_king = pack_pos({to_x, to_y});
        else black_king = pack_pos({to_x, to_y});
    }

    set_piece(to_x, to_y, type, color);
    set_piece(from_x, from_y, piece_type::EMPTY, piece_color::NONE);

    // Regenerate attacked squares
    regenerate_attacked_squares(!moving_white);

    // Check if the king is in check
    bool moved_into_check = (moving_white && attacked_squares[unpack_pos(white_king).first][unpack_pos(white_king).second]) || !moving_white && attacked_squares[unpack_pos(black_king).first][unpack_pos(black_king).second];

    // Rollback the move
    if(type == piece_type::KING) {
        if(color == piece_color::WHITE) white_king = pack_pos({from_x, from_y});
        else black_king = pack_pos({from_x, from_y});
    }

    set_piece(from_x, from_y, type, color);
    set_piece(to_x, to_y, to_type, to_color);

    if(color == piece_color::WHITE) {
        white_pieces.erase(pack_pos({to_x, to_y}));
        white_pieces.insert(pack_pos({from_x, from_y}));

        if(to_color == piece_color::BLACK) {
            black_pieces.insert(pack_pos({to_x, to_y}));
        }
    } else {
        black_pieces.erase(pack_pos({to_x, to_y}));
        black_pieces.insert(pack_pos({from_x, from_y}));

        if(to_color == piece_color::WHITE) {
            white_pieces.insert(pack_pos({to_x, to_y}));
        }
    }

    if(black_count != black_pieces.size() || white_count != white_pieces.size()) {
        // Print black pieces
        BDEBUG("Black pieces: ");
        for(auto val : black_pieces) {
            auto [x, y] = unpack_pos(val);
            auto [type, color] = get_piece(x, y);

            BDEBUG("%s %s at %d, %d", get_piece_name(type), get_piece_color_str(color), x, y);
        }
    }

    // Regenerate attacked squares
    regenerate_attacked_squares(!moving_white);

    return !moved_into_check;
}

void board::move_piece(i8 x, i8 y) {
    auto [type, color] = get_piece(x, y);
    BINFO("Selected %s %s at %d, %d", get_piece_name(type), get_piece_color_str(color), x, y);
    BINFO("Last selected %d, %d", selected_piece.first, selected_piece.second);

    bool is_selected = selected_piece.first != -1;
    bool valid_color = white_turn ? color == piece_color::WHITE : color == piece_color::BLACK;

    if(!is_selected && valid_color) {
        selected_piece = {x, y};
        return;
    }

    bool valid_turn = is_selected && (color == (white_turn ? piece_color::BLACK : piece_color::WHITE) || color == piece_color::NONE);

    if(!valid_turn && is_selected) {
        selected_piece = {x, y};
        return;
    }

    if(!valid_turn || (selected_piece.first == x && selected_piece.second == y)) return;

    // Check if the move is valid
    auto [sel_type, sel_color] = get_piece(selected_piece.first, selected_piece.second);

    if(sel_color == color) {
        selected_piece = {x, y};
        return;
    }

    i8 norm_sel_y = selected_piece.second;
    if(sel_color == piece_color::BLACK) norm_sel_y = 7 - norm_sel_y;

    ptr_wrap p = piece::create(*this, {sel_type, sel_color}, selected_piece.first, norm_sel_y);
    i8 norm_y = y;
    if(sel_color == piece_color::BLACK) norm_y = 7 - norm_y;

    if(!p->is_valid_move(x, norm_y)) {
        selected_piece = {-1, -1};
        return;
    }

    // Check if the move doesn't put the king in check
    if(!simulate_move(selected_piece.first, selected_piece.second, x, y)) return;

    if(sel_color == piece_color::WHITE) {
        white_pieces.erase(pack_pos({selected_piece.first, selected_piece.second}));
        white_pieces.insert(pack_pos({x, y}));

        if(color == piece_color::BLACK) {
            black_pieces.erase(pack_pos({x, y}));
        }
    } else {
        black_pieces.erase(pack_pos({selected_piece.first, selected_piece.second}));
        black_pieces.insert(pack_pos({x, y}));

        if(color == piece_color::WHITE) {
            white_pieces.erase(pack_pos({x, y}));
        }
    }

    set_piece(x, y, sel_type, sel_color);
    set_piece(selected_piece.first, selected_piece.second, piece_type::EMPTY, piece_color::NONE);

    if(sel_type == piece_type::KING) {
        if(sel_color == piece_color::WHITE) white_king = pack_pos({x, y});
        else black_king = pack_pos({x, y});
    }

    // Regenerate attacked squares
    regenerate_attacked_squares(white_turn);

    // TODO: Checkmate/Check logic
    bool in_check = (!white_turn && attacked_squares[unpack_pos(white_king).first][unpack_pos(white_king).second]) || white_turn && attacked_squares[unpack_pos(black_king).first][unpack_pos(black_king).second];
    if(in_check) {
        // Check if it's a checkmate
        bool checkmate = true;
        for(auto val : (!white_turn ? white_pieces : black_pieces)) {
            auto [from_x, from_y] = unpack_pos(val);
            auto [type, color] = get_piece(from_x, from_y);

            // if(color != (white_turn ? piece_color::WHITE : piece_color::BLACK)) continue;

            if(color == piece_color::BLACK) from_y = 7 - from_y;

            ptr_wrap p = piece::create(*this, {type, color}, from_x, from_y);
            auto moves = p->get_possible_moves();

            if(color == piece_color::BLACK) {
                from_y = 7 - from_y;
            }

            for(auto& [x, y] : moves) {
                i8 norm_move_y = y;
                if(color == piece_color::BLACK) {
                    norm_move_y = 7 - norm_move_y;
                }

                if(simulate_move(from_x, from_y, x, norm_move_y)) {
                    checkmate = false;
                    break;
                }
            }

            if(!checkmate) break;
        }

        if(checkmate) {
            display_text("Checkmate!", 10000);
            checkmated = true;
            return;
        }

        display_text("CHECK", 180);
    }

    white_turn = !white_turn;
    selected_piece = {-1, -1};
}

void board::update() {
    if(checkmated) return;

    // If F3 is pressed, print all the pieces
    if(platform_input_key_down(input_key::F3)) {
        BINFO("White pieces: ");
        for(auto val : white_pieces) {
            auto [x, y] = unpack_pos(val);
            auto [type, color] = get_piece(x, y);

            BINFO("%s %s at %d, %d", get_piece_name(type), get_piece_color_str(color), x, y);
        }

        BINFO("Black pieces: ");
        for(auto val : black_pieces) {
            auto [x, y] = unpack_pos(val);
            auto [type, color] = get_piece(x, y);

            BINFO("%s %s at %d, %d", get_piece_name(type), get_piece_color_str(color), x, y);
        }
    }

    if(frames_remaining > 0) return; // Don't update if there is text displayed

    // Check for mouse input
    if(platform_input_mouse_button_down(mouse_button::LEFT)) {
        auto pos = platform_input_get_mouse_position();
        pos.x /= 129;
        pos.y /= 129;

        i8 x = (i8)pos.x;
        i8 y = 7 - (i8)pos.y;

        if(x >= 0 && y >= 0) move_piece(x, y);
    }
}

void board::display_text(std::string text, u64 frames) {
    this->displayed_text = std::move(text);
    this->frames_remaining = frames;
}

void board::draw_board(renderer_2d& rend, font_renderer& font) {
    rend.draw_quad({0, 0}, {1024, 1024}, board_tex.get());

    if(!checkmated) {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                auto [type, color] = get_piece(i, j);
                if(type != piece_type::EMPTY) {
                    rend.draw_quad({i * 129, j * 129}, {130, 130}, get_texture(type, color));
                }
            }
        }

        if(selected_piece.first != -1) display_possible_moves(rend, selected_piece.first, selected_piece.second);

        // Draw the attacked squares
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(attacked_squares[i][j]) {
                    rend.draw_quad({i * 129, j * 129}, {130, 130}, {0, 0, 1, .5f});
                }
            }
        }
    }

    // Draw the text
    if(frames_remaining > 0) {
        // Draw a rect behind the text
        rend.draw_quad({512-256, 512-128}, {512, 256}, {0, 0, 0, .8f});
        font.render_text(displayed_text.c_str(), {512-128, 512-32}, 1, {1, 1, 1});
        frames_remaining--;
    }
}

void board::display_possible_moves(renderer_2d &rend, i8 p_x, i8 p_y) {
    // Get the piece
    auto [type, color] = get_piece(p_x, p_y);
    i8 norm_y = p_y;

    if(color == piece_color::BLACK) norm_y = 7 - p_y;

    piece* p = piece::create(*this, {type, color}, p_x, norm_y);

    // Get the valid moves
    auto moves = p->get_possible_moves();

    for(auto& [x, y] : moves) {
        if(color == piece_color::BLACK) y = 7 - y;
        if(!simulate_move(p_x, p_y, x, y)) continue;
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
