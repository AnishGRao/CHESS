#include <bits/stdc++.h>
#include <pthread.h>
//#define testing true
#ifdef testing
#define exit(A) 0 + A == 0 ? A : 0;
#endif
std::string _rookB = "♜", _knightB = "♞", _bishopB = "♝", _queenB = "♛", _kingB = "♚", _pawnB = "♟";
std::string _rookW = "♖", _knightW = "♘", _bishopW = "♗", _queenW = "♕", _kingW = "♔", _pawnW = "♙";
class PIECE;
std::vector<std::vector<PIECE>> board, backupBoard;
int curr_turn_w = 0, curr_turn_b = 0;
class PIECE
{
  public:
    std::string piece_type;
    std::string piece_name;
    std::string latent_square;
    bool piece;
    char piece_color;
    bool first_move = 1;
    bool kill_via_en_passant = 0;
    std::pair<int, int> enpassant_end;
    int enpassant_turn = -1;
    PIECE() {}
    void make_move(int srow, int scol, int erow, int ecol)
    {

        if (piece_name == _pawnB || piece_name == _pawnW)
        {
            pawn(srow, scol, erow, ecol);
        }
        else if (piece_name == _bishopB || piece_name == _bishopW)
        {
            bishop(srow, scol, erow, ecol);
        }
        else if (piece_name == _knightB || piece_name == _knightW)
        {
            knight(srow, scol, erow, ecol);
        }
        else if (piece_name == _rookB || piece_name == _rookW)
        {
            rook(srow, scol, erow, ecol);
        }
        else if (piece_name == _queenB || piece_name == _queenW)
        {
            queen(srow, scol, erow, ecol);
        }
        else if (piece_name == _kingB || piece_name == _kingW)
        {
            king(srow, scol, erow, ecol);
        }
        else
            std::cout << "\nAn illegal move has lost you the game.\n", exit(0);
    }

  private:
    void terminate()
    {

        piece = 0;
        piece_name = piece_type = "";
        // kill_via_en_passant = 0;
        first_move = 0;
    }
    void pawn(int srow, int scol, int erow, int ecol)
    {
        bool termFlag = false;
        if (((piece_color == 'b' && erow > srow) &&
             ((first_move && erow - srow == 2 && ecol == scol && !board[erow][ecol].piece) ||
              (erow - srow == 1 &&
               ((ecol - scol == 0 && !board[erow][ecol].piece) ||
                (std::abs(ecol - scol) == 1 &&
                 (board[erow][ecol].piece ||
                  (board[erow][ecol].kill_via_en_passant && (curr_turn_b == board[erow][ecol].enpassant_turn))) &&
                 board[erow][ecol].piece_color != board[srow][scol].piece_color))))) ||
            ((piece_color == 'w' && srow > erow) &&
             ((first_move && srow - erow == 2 && ecol == scol) ||
              (erow - srow == -1 &&
               ((ecol - scol == 0 && !board[erow][ecol].piece) ||
                (std::abs(ecol - scol) == 1 &&
                 (board[erow][ecol].piece ||
                  (board[erow][ecol].kill_via_en_passant && (curr_turn_w == board[erow][ecol].enpassant_turn))) &&
                 board[erow][ecol].piece_color != board[srow][scol].piece_color))))))
            termFlag = true;

        else
            std::cout << "\nAn illegal move has lost you the game.\n", exit(0);
        board[srow + 1 > 7 || srow - 1 < 0 ? 0 : srow - erow > 0 ? srow - 1 : srow + 1][scol].kill_via_en_passant =
            board[srow][scol].first_move && std::abs(erow - srow) == 2 ? 1 : 0;
        board[srow + 1 > 7 || srow - 1 < 0 ? 0 : srow - erow > 0 ? srow - 1 : srow + 1][scol].enpassant_end =
            board[srow][scol].first_move && std::abs(erow - srow) == 2 ? std::pair<int, int>{erow, ecol}
                                                                       : std::pair<int, int>{-1, -1};
        board[srow + 1 > 7 || srow - 1 < 0 ? 0 : srow - erow > 0 ? srow - 1 : srow + 1][scol].enpassant_turn =
            board[srow][scol].first_move && std::abs(erow - srow) == 2
                ? board[srow][scol].piece_color == 'b' ? curr_turn_b : curr_turn_w
                : enpassant_turn;
        if (termFlag)
        {
            if (board[erow][ecol].kill_via_en_passant)
                board[board[erow][ecol].enpassant_end.first][board[erow][ecol].enpassant_end.second].terminate();
            board[erow][ecol] = board[srow][scol], board[srow][scol].terminate();
        }
        board[erow][ecol].first_move = 0;
    }
    void bishop(int srow, int scol, int erow, int ecol)
    {
        bool valid = 1;
        if (std::abs(erow - srow) == std::abs(ecol - scol))
        {
            for (int i = srow, j = scol; erow > srow ? erow >= i : i >= erow;
                 erow > srow ? (i++, j++) : (i--, j--))
                if (i != srow && i != erow && board[i][j].piece)
                    valid = false, i = erow + 1;
            if (!valid ||
                ((board[erow][ecol].piece_color == board[srow][scol].piece_color) && (board[erow][ecol].piece)))
                std::cout << "\nAn illegal move has lost you the game.\n", exit(0);
            board[erow][ecol] = board[srow][scol];
            board[srow][scol].terminate();
        }
    }
    void knight(int srow, int scol, int erow, int ecol)
    {
        if (((std::abs(ecol - scol) == 2 && std::abs(erow - srow) == 1) ||
             (std::abs(ecol - scol) == 1 && std::abs(erow - srow) == 2)) &&
            ((((board[erow][ecol].piece_color != board[srow][scol].piece_color) && (board[erow][ecol].piece)) ||
              (!board[erow][ecol].piece))))
            board[erow][ecol] = board[srow][scol], board[srow][scol].terminate();

        else
            std::cout << "\nAn illegal move has lost you the game.\n", exit(0);
    }
    void rook(int srow, int scol, int erow, int ecol)
    {
        if (((std::abs(erow - srow) > 0 && std::abs(ecol - scol) == 0) ||
             (std::abs(erow - srow) == 0 && std::abs(ecol - scol) > 0)) &&
            (!board[erow][ecol].piece ||
             ((board[erow][ecol].piece) && (board[erow][ecol].piece_color != board[srow][scol].piece_color))))
            board[erow][ecol] = board[srow][scol], board[srow][scol].terminate();
        else
            std::cout << "\nAn illegal move has lost you the game.\n", exit(0);
    }
    void queen(int srow, int scol, int erow, int ecol)
    {

        if ((((std::abs(erow - srow) > 0 && std::abs(ecol - scol) == 0) ||
              (std::abs(erow - srow) == 0 && std::abs(ecol - scol) > 0)) ||
             std::abs(erow - srow) == std::abs(ecol - scol)) &&
            (!board[erow][ecol].piece ||
             ((board[erow][ecol].piece) && (board[erow][ecol].piece_color != board[srow][scol].piece_color))))
            board[erow][ecol] = board[srow][scol], board[srow][scol].terminate();
        else
            std::cout << "\nAn illegal move has lost you the game.\n", exit(0);
    }
    void king(int srow, int scol, int erow, int ecol)
    {
        if ((((std::abs(erow - srow) == 1 && std::abs(ecol - scol) == 0) ||
              (std::abs(erow - srow) == 0 && std::abs(ecol - scol) == 1)) ||
             (std::abs(erow - srow) == std::abs(ecol - scol) && std::abs(ecol - scol) == 1)) &&
            (!board[erow][ecol].piece ||
             ((board[erow][ecol].piece) && board[erow][ecol].piece_color != board[srow][scol].piece_color)))
            board[erow][ecol] = board[srow][scol], board[srow][scol].terminate();
        else
            std::cout << "\nAn illegal move has lost you the game.\n", exit(0);
    }

    // todo more lmao
};
