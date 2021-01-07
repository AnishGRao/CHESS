#include "pieces.h"
#define blk_sqr "◼"
#define wht_sqr "◻"
std::vector<PIECE> pieces;
std::set<std::string> squares = {blk_sqr, wht_sqr};
void board_creation()
{
    // 8X8 board
    board.resize(8, std::vector<PIECE>(8));
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[i][j].piece_color = i <= 1 ? 'b' : i >= 6 ? 'w' : 'n',
            board[i][j].piece =
                squares.count(
                    board[i][j].piece_name =
                        i == 1 ? _pawnB
                               : i == 6 ? _pawnW
                                        : i == 0 ? (j == 0 || j == 7
                                                        ? _rookB
                                                        : j == 1 || j == 6
                                                              ? _knightB
                                                              : j == 2 || j == 5 ? _bishopB
                                                                                 : j == 3 ? _queenB : _kingB)
                                                 : i == 7
                                                       ? (j == 0 || j == 7
                                                              ? _rookW
                                                              : j == 1 || j == 6
                                                                    ? _knightW
                                                                    : j == 2 || j == 5 ? _bishopW
                                                                                       : j == 3 ? _queenW : _kingW)
                                                       : ((((8 - i) % 2 == 0) && ((8 - j) % 2 == 0)) ||
                                                          (((8 - i) % 2 == 1) && ((8 - j) % 2 == 1)))
                                                             ? blk_sqr
                                                             : wht_sqr) == 0,
            board[i][j].latent_square =
                ((((8 - i) % 2 == 0) && ((8 - j) % 2 == 0)) || (((8 - i) % 2 == 1) && ((8 - j) % 2 == 1)))
                    ? blk_sqr
                    : wht_sqr;
}
void display_board()
{
    int counter = 0;
    for (auto row : board)
    {
        std::cout << ++counter << " ";
        int i = 0;
        for (auto piece : row)
            std::cout << (piece.piece ? piece.piece_name : piece.latent_square) << " ";
        std::cout << "\n";
    }
    std::cout << "  ";
    for (int i = 0; i < counter; i++)
        std::cout << (char)('a' + i) << " ";
    std::cout << "\n";
}

void make_move()
{
    std::string starting_piece;
    std::cout << "Select a Piece: ";
    std::cin >> starting_piece;
    if (starting_piece.size() != 2)
    {
        std::cout << "Bad Input.\n";
        make_move();
    }
    int col = tolower(starting_piece[0]) - 97, row = starting_piece[1] - 49;
    if (row < 0 || row > 7 || col < 0 || col > 7 || !board[row][col].piece)
    {
        std::cout << "\nBad Input, that is an illegal piece to select.\n";
        make_move();
    }
second_pos:
    std::string ending_piece;
    std::cout << "Select a Position: ";
    std::cin >> ending_piece;
    if (ending_piece.size() != 2)
    {
        std::cout << "Bad Input.\n";
        goto second_pos;
    }

    int ecol = tolower(ending_piece[0]) - 97, erow = ending_piece[1] - 49;
    if (erow < 0 || erow > 7 || ecol < 0 || ecol > 7)
    {
        std::cout << "\nBad Input, that is an illegal move.\n";
        goto second_pos;
    }
    board[row][col].make_move(row, col, erow, ecol);
    display_board();
}

int main()
{
    board_creation();
    display_board();
    while (true)
    {
        make_move();
    }
    return 0;
}
