#include "connectfour.h"


/* This drops a piece onto the board, using only the col and color */
/* It returns that col. If col is out of bounds, or full, returns -1 */
int get_next_available_col(std::vector<std::vector<Piece>>& board, int col)
{
    // local variables
    int column_size = board[0].size();
    int row_size = board.size();
    
    // check if col is out of bounds
    if (col < 0 || col >= column_size) { return -1; }

    // if it can be dropped, drop it to next available slot
    for (int i = 0; i < row_size; i++)
    {
        if (board[i][col].color == Color::NONE)
        {
            return i;
        }
    }

    // if col is full of colors returns -1
    return -1;
}

// checks if draw is achieved by seeing if board is full (no square is "empty")
bool is_board_full(std::vector<std::vector<Piece>>& board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j].color == Color::NONE) return false;
        }
    }

    return true;
}

//checks a point in the board if its within bounds, and increments if color is the same as player color
int in_a_row_check(int count,int row, int col, std::vector<std::vector<Piece>>& board, Color& color)
{
    int c = count;
    if (row < 0 || col < 0) return -1;
    if (row >= board.size() || col >= board[0].size()) return -1;

    if (board[row][col].color != color) c = 0;
    if (board[row][col].color == color) c++;

    if (c == 4) return 4;
    return c;
}

/* checks if the player won by checking row, column and diagonals */
bool did_player_win(int row, int col, std::vector<std::vector<Piece>>& board, Color& color)
{
    int in_a_row = 0;

    // up to down vertical win checking
    for (int i = 0; i < board.size(); i++)
    {
        if ((in_a_row = in_a_row_check(in_a_row,i,col,board,color)) == 4) return true;
        /*
        if (board[i][col] != 0)
        {
            if (board[i][col].color != color) in_a_row = 0;
            if (board[i][col].color == color) in_a_row++;
        }

        if (in_a_row == 4) return true;
        */
    }
    in_a_row = 0;

    // left to right horizontal win checking
    for (int i = 0; i < board[0].size(); i++)
    {
        if ((in_a_row = in_a_row_check(in_a_row,row,i,board,color)) == 4) return true;
        /*
        if (board[i][col] != NULL)
        {
            if (board[row][i].color != color) in_a_row = 0;
            if (board[row][i].color == color) in_a_row++;
        }

        if (in_a_row == 4) return true;
        */
    }
    in_a_row = 0;

    // diagonal win checking
    for (int i = 0, j = 0; i < board.size() && j < board[0].size(); i++, j++)
    {
        if ((in_a_row = in_a_row_check(in_a_row,i,j,board,color)) == 4) return true;
        /*
        if (board[i][col] != NULL)
        {
            if (board[i][j].color != color) in_a_row = 0;
            if (board[i][j].color == color) in_a_row++;
        }

        if (in_a_row == 4) return true;
        */
    }

    in_a_row = 0;

    for (int i = board.size()-1, j = 0; i >= 0 && j < board[0].size(); i--, j++)
    {
        if ((in_a_row = in_a_row_check(in_a_row,i,j,board,color)) == 4) return true;
        /*
        if (board[i][j] != NULL)
        {
            if (board[i][j].color != color) in_a_row = 0;
            if (board[i][j].color == color) in_a_row++;
        }

        if (in_a_row == 4) return true;
        */
    }

    return false;
}

/* This function prints the connect four board */
void print_board(std::vector<std::vector<Piece>>& board)
{
    for (int i = board.size()-1; i >=0; i--)
    {
        for (int j = 0; j < 6; j++)
        {
            std::cout << "---";
        }
        
        std::cout <<  "--\n";

        for (int j = 0; j < board[0].size(); j++)
        {
            std::cout << "| " << get_player_str(board[i][j].color) << " ";
        }
        std::cout << "|" << std::endl;
        std::cout<< "\n";

        if (i == 0)
        {
            for (int j = 0; j < 6; j++)
            {
                std::cout << "---";
            }
            
            std::cout <<  "--\n";
        }
    }
}

//export PATH_TO_JAVAFX_SDK=~/Documents/coding/java-stuff/javafx-sdk-17.0.0.1/lib
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
    return color == Color::RED ? Color::YELLOW : Color::RED;
}

std::string get_player_str(Color color)
{
    std::string player_color;
    if (color == Color::RED) player_color = "R";
    if (color == Color::YELLOW) player_color = "Y";
    if (color == Color::NONE) player_color = " ";
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
        int col = 0;
        print_board(board);
        std::cout << "Current Player: " << get_player_str(current_player.color) << std::endl;
        std::cout << "Enter column to place piece: ";
        std::cin >> col;
        col-=1;

        if ((row = get_next_available_col(board, col)) == -1)
        {
            std::cout << "Cannot drop piece in this column, please try a different column!" << std::endl;
            continue;
        }

        board[row][col].color = current_player.color;
            print_board(board);
        
        // if player won
        if (did_player_win(row, col, board, current_player.color))
        {
            std::cout << "Player " << get_player_str(current_player.color) << " won!!" << std::endl;
            break;
        }

        // is the board full (no one won) so draw?
        if (is_board_full(board))
        {
            std::cout << "Both players have drawed!" << std::endl;
        }

        // switch player
        current_player.color = switch_player_colors(current_player.color);
    }
    

    return 0;
}