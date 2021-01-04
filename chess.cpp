#include "piece_utf.h"
#include "pieces.h"
#define blk_sqr "◼"
#define wht_sqr "◻"
std::vector <PIECE> pieces;
std::vector<std::vector<PIECE>>board;
std::set<std::string> squares ={blk_sqr, wht_sqr};
void board_creation(){
    //8X8 board
    board.resize(8,std::vector<PIECE>(8));
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[i][j].piece = squares.count(board[i][j].piece_name = i==1 ? _pawnB : i==6 ? _pawnW :
                i==0 ? (
                        j==0 || j==7 ? _rookB : 
                        j==1 || j==6 ? _knightB :
                        j==2 || j==5 ? _bishopB :
                        j==3 ? _queenB : _kingB
                       )
                : i==7 ? (
                        j==0 || j==7 ? _rookW : 
                        j==1 || j==6 ? _knightW :
                        j==2 || j==5 ? _bishopW :
                        j==3 ? _queenW : _kingW
                       )
                : ((((8-i)%2 == 0) && ((8-j)%2 == 0)) 
                    || 
                  (((8-i)%2 == 1) && ((8-j)%2 == 1))) ? blk_sqr : wht_sqr)==0;
}

void make_move(){
    std::string starting_piece;
    std::cout<<"Select a Piece: ";
    std::cin >> starting_piece;
    if (starting_piece.size()!=2){
        std::cout<<"Bad Input.\n";
        make_move();
    }
    int row = tolower(starting_piece[0])-96, col = starting_piece[1]-49;
    std::cout<<row<<"\t"<<col<<"\n";

}

void display_board(){
    int counter = 0;
    for (auto row : board){
        std::cout<<++counter<<" ";
        for (auto piece : row)
            std::cout<<piece.piece_name<<" ";
        std::cout<<"\n";    
    }
    std::cout<<"  ";
    for (int i = 0; i<counter; i++)
        std::cout<<(char)('a'+i)<<" ";
    std::cout<<"\n";
}




int main(){
    board_creation();
    display_board();
    make_move();
    return 0;
}
