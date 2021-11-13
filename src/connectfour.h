#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#include <iostream>
#include <string>
#include <vector>
#include <map>

enum Color {RED, NONE, YELLOW};

struct Piece
{
    int x;
    int y;
    Color color;
};

/*
class Board
{
    public:
        Board(int x = 7, int y = 6);
        void init_board();
        void set_row_size(int y);
        void set_col_size(int x);

        int get_row_size();
        int get_col_size();

        void print_board();

        Piece get_piece(int x, int y);
        void add_piece(int x = 0, int y = 0, Piece piece = NONE);
        std::string get_piece_val(Piece piece);
    private:
        std::vector<std::vector<Piece>> board;
        int sizex;
        int sizey;
};
*/

#endif