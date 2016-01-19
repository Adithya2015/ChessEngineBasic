#ifndef BOARD_H
#define BOARD_H
#include "enumerations.h"
#include "definitions.h"
#include<vector>


class board{

public:
    board();
    void undo();
    int get(int) const;
    int getside();
    int getfullmoves();
    vint getboard();
    std::string getfen();
    void setfen(std::string fen);
    std::vector<movetype> valid_moves();
    movetype random_move();
    void make_move(movetype);
    void print();
private:
    int curr_index; ///index in the history frame
    std::vector<std::string> history;
    vint currboard;
    int sidetomove;
    bool whitecastlekingside;
    bool whitecastlequeenside;
    bool blackcastlekingside;
    bool blackcastlequeenside;
    int halfmoves; /// without pawn movement/capture
    int fullmoves;
    int enpassant_square; /// 64 based
};
#endif // BOARD_H
