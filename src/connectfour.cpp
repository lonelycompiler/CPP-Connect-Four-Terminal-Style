#include "connectfour.h"


/* This drops a piece onto the board, using only the row and color */
/* It returns that row. If row is out of bounds, or full, returns -1 */
int drop_piece(std::vector<std::vector<Piece>>& board, int& row, Color& color)
{
    // check if row is out of bounds
    if (row < 1 || row > board.size()+1) { return -1; }

    // check if row is full of colors (look at top most)
    int col_size = board[0].size();
    if (board[row-1][col_size-1].color == Color::NONE) return -1;

    // if it can be dropped, drop it to next available slot


    return row;
}

/* This function prints the connect four board */
void print_board(std::vector<std::vector<Piece>>& board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            std::cout << "---";
        }
        
        std::cout <<  "\n";

        for (int j = 0; j < board[0].size(); j++)
        {
            std::cout << "|" << get_player_str(board[i][j].color) << "|";
        }
        std::cout<< "\n";

        if (i == board.size()-1)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                std::cout << "---";
            }
            
            std::cout <<  "\n";
        }
    }
}

/* This function generates an empty connect four board */
std::vector<std::vector<Piece>> generate_empty_board(int size_x, int size_y)
{
    std::vector<std::vector<Piece>> board;
    for (int i = 0; i < size_x; i++)
    {
        board.push_back(std::vector<Piece>());
        for (int j = 0; j < size_y; j++)
        {
            Piece temp;
            temp.x = i;
            temp.y = j;
            temp.color = NONE;
            board[i].push_back(temp);
        }
    }
    return board;
}

Color switch_player_colors(Color color)
{
    int new_color_integer = static_cast<int>(color);
    Color other_player = static_cast<Color>(new_color_integer*-1);
    return other_player;
}

std::string get_player_str(Color color)
{
    std::string player_color;
    if (color == Color::RED) player_color = "R";
    if (color == Color::YELLOW) player_color = "Y";
    return player_color;
}


int main(void)
{
    std::vector<std::vector<Piece>> board = generate_empty_board(7,6);
    Piece current_player;
    current_player.color = Color::RED;

    bool game = true;
    while (game)
    {
        int row = 0;
        print_board(board);
        std::cout << "Current Player: " << get_player_str(current_player.color) << std::endl;
        std::cout << "Enter row to place piece: ";
        std::cin >> row;

        if (drop_piece(board,row, current_player.color) == -1)
        {
            std::cout << "Cannot drop piece in this row, please try a different row!" << std::endl;
            continue;
        }



        // switch player
        current_player.color = switch_player_colors(current_player.color);
    }
    

    return 0;
}