#include<iostream>
#include "board.h"
#include "enumerations.h"
#include "attacked_squares.h"
#include "helper_funcs.h"
#include <string>

/// CURRENT PACE: APPROX 8K moves/sec...too slow
/// 22s for the current position upto depth 6 "4k2r/6K1/8/8/8/8/8/8 b k - 0 1"


using namespace std;

void countmoves(int depth,board& myboard,int& counter,int level,int& epflag,int& captflag,int& castleflag)
{
    if(depth == 0)
    {
        counter ++;
        return;
    }
    vector<movetype>M = myboard.valid_moves();
    for(int i=0;i<M.size();i++)
    {
        myboard.make_move(M[i]);

        if(M[i].ep) epflag ++;
        if(M[i].castle) castleflag ++;
        if(M[i].capture) captflag ++;

        //cout<<level<<"."<<toalgebsquare(M[i].from +1)<<toalgebsquare(M[i].to +1)<<endl;
        //cout<<myboard.getfen()<<endl;
        countmoves(depth-1,myboard,counter,level+1,epflag,captflag,castleflag);
        myboard.undo();

    }
    return;
}

int main()
{
    board myboard;
    string fen = "4k2r/6K1/8/8/8/8/8/8 b k - 0 1";
    myboard.setfen(fen);
    myboard.print();
    vector<movetype> M;
    M = myboard.valid_moves();
    myboard.print();
    string check = myboard.getfen();
    cout<<"The no of valid moves are: "<<M.size()<<endl;
    cout<<"The original and generated FENs match?: "<<(check == fen)<<endl;
    cout<<"The generated FEN is: "<<check<<endl;
    int i=7;

    //cout<<"Enter depth: "<<endl;
    //cin>>i;
    int counter = 0;
    int level = 1;
    int epflag = 0;
    int castleflag = 0,captflag = 0;
    countmoves(i,myboard,counter,level,epflag,captflag,castleflag);
    cout<<"The no of moves at depth i are: "<<counter<<endl;
    cout<<"Enpassant  moves: "<<epflag<<endl;
    cout<<"Capture  moves: "<<captflag<<endl;
    cout<<"Castling  moves: "<<castleflag<<endl;
    return 0;
}

