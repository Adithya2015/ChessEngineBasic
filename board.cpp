#include "board.h"
#include "enumerations.h"
#include "helper_funcs.h"
#include "attacked_squares.h"
#include "stdlib.h"
#include<string>
#include<iostream>
#include<sstream>
#include<vector>
#include<cstring>

vint INITIAL = {r,n,b,q,k,b,n,r,
                        p,p,p,p,p,p,p,p,
                        blank,blank,blank,blank,blank,blank,blank,blank,
                        blank,blank,blank,blank,blank,blank,blank,blank,
                        blank,blank,blank,blank,blank,blank,blank,blank,
                        blank,blank,blank,blank,blank,blank,blank,blank,
                        P,P,P,P,P,P,P,P,
                        R,N,B,Q,K,B,N,R};
vint EMPTY_BOARD = {blank,blank,blank,blank,blank,blank,blank,blank,
                        blank,blank,blank,blank,blank,blank,blank,blank,
                        blank,blank,blank,blank,blank,blank,blank,blank,
                        blank,blank,blank,blank,blank,blank,blank,blank,
                        blank,blank,blank,blank,blank,blank,blank,blank,
                        blank,blank,blank,blank,blank,blank,blank,blank,
                        blank,blank,blank,blank,blank,blank,blank,blank,
                        blank,blank,blank,blank,blank,blank,blank,blank};

std::string INITIAL_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";

board::board()
{
    halfmoves = 0;
    fullmoves = 0;
    whitecastlekingside = true;
    whitecastlequeenside = true;
    blackcastlekingside = true;
    blackcastlequeenside =(true);
    sidetomove = (white);
    curr_index = 0;
    enpassant_square = -1;
    currboard = INITIAL;
    for(int i=0;i<maxmoves;i++)
    {
        history.push_back(INITIAL_FEN);
    }
}

void board::undo()
{
    if(curr_index >0)
    {
        curr_index--;
        setfen(history[curr_index]);
    }
}

void board::make_move(movetype mymove)
{
    curr_index++;
    currboard[mymove.from] = blank;
    currboard[mymove.to] = mymove.piece;

    if(mymove.castle)
    {
        currboard[mymove.rookfrom] = blank;
        currboard[mymove.rookto] = (sidetomove==white)?R:r;
    }
    if(mymove.ep)
    {
        if(sidetomove == white)
        {
            currboard[enpassant_square - 1 +8] = blank;
        }
        else{
            currboard[enpassant_square - 1 -8] = blank;
        }
    }

    if(mymove.piece == p or mymove.piece == P)
    {
        if(abs(getrank(mymove.from) - getrank(mymove.to)) == 2)
        {
            enpassant_square = 0.5*(mymove.from + mymove.to) + 1;
        }
    }


    if(whitecastlekingside){
        if(mymove.from == 60 or mymove.from == 63) whitecastlekingside = false;
    }

    if(blackcastlekingside){
        if(mymove.from == 4 or mymove.from == 7) blackcastlekingside = false;
    }

    if(whitecastlequeenside){
        if(mymove.from == 60 or mymove.from == 56) whitecastlequeenside = false;
    }

    if(blackcastlequeenside){
        if(mymove.from == 4 or mymove.from == 0) blackcastlequeenside = false;
    }
    sidetomove = (1-sidetomove);
    history[curr_index] = getfen();
}

int board::getfullmoves()
{
    return fullmoves;
}

std::string board::getfen()
{
    std::string s = "";
    int es = 0,i=0,j=0;

    while(8*i + j < 64)
    {
        switch(currboard[8*i + j])
        {
                case blank:
                while(currboard[8*i + j] == blank and j<=7)
                {
                    es++;
                    j++;
                }
                s += tostring(es);
                es = 0;
                break;

                case p: s += "p"; j++; break;
                case P: s += "P"; j++; break;
                case b: s += "b"; j++; break;
                case B: s += "B"; j++; break;
                case r: s += "r"; j++; break;
                case R: s += "R"; j++; break;
                case k: s += "k"; j++; break;
                case K: s += "K"; j++; break;
                case q: s += "q"; j++; break;
                case Q: s += "Q"; j++; break;
                case n: s += "n"; j++; break;
                case N: s += "N"; j++; break;
        }

        if(j==8 and i<7)
        {
            i++; j=0;
            s += "/";
        }
    }
    s += " ";
    if(sidetomove == white) s += "w";
    else s += "b";

    s += " ";
if(whitecastlekingside) s += "K";
if(whitecastlequeenside) s += "Q";
if(blackcastlekingside) s += "k";
if(blackcastlequeenside) s += "q";
if(!whitecastlekingside and !whitecastlequeenside and !blackcastlekingside and !blackcastlequeenside) s += "-";

s += " ";

if(enpassant_square == -1) s += "-";
else s += toalgebsquare(enpassant_square);

s += " ";

s += tostring(halfmoves);
s += " ";
s += tostring(fullmoves);
return s;
}

int board::get(int sq) const
{
    if(1<= sq and sq<= 64)
    return currboard[sq - 1];
    else return -1;
}

int board::getside()
{
    return sidetomove;
}

vint board::getboard(){
return currboard;
}

void board::print()
{
    int i,j;
    std::cout<<std::endl;
    for(i=0;i<8;i++)
    {
        std::cout<<Rank[i]<<"   ";
        for(j=0;j<8;j++)
        {
            std::cout<<Piece[currboard[i*8 + j]]<<"  ";
        }
        std::cout<<std::endl; std::cout<<std::endl;
    }
std::cout<<"    ";
    for(i=0;i<8;i++)
        std::cout << File[i]<<"  ";

    std::cout<<std::endl; std::cout<<std::endl;
}


void board::setfen(std::string fen)
{
int i = 0,j=0;
unsigned int pos=0;
    for(i=0;i<64;i++)
    {
        currboard[i] = blank;
    }
    i=0;
    while(pos < fen.length() and fen[pos] != ' ')
    {

        char temp = fen[pos];
                switch(temp)
                {
                case '/':
                        i++; j=0; break;
                case 'p':currboard[8*i+j] = p; j++;break;
                case 'P':currboard[8*i+j] = P; j++;break;
                case 'n':currboard[8*i+j] = n; j++;break;
                case 'N':currboard[8*i+j] = N; j++;break;
                case 'b':currboard[8*i+j] = b; j++;break;
                case 'B':currboard[8*i+j] = B; j++;break;
                case 'q':currboard[8*i+j] = q; j++;break;
                case 'Q':currboard[8*i+j] = Q; j++;break;
                case 'k':currboard[8*i+j] = k; j++;break;
                case 'K':currboard[8*i+j] = K; j++;break;
                case 'r':currboard[8*i+j] = r; j++;break;
                case 'R':currboard[8*i+j] = R; j++;break;

                case '1': j += 1; break;
                case '2': j += 2; break;
                case '3': j += 3; break;
                case '4': j += 4; break;
                case '5': j += 5; break;
                case '6': j += 6; break;
                case '7': j += 7; break;
                case '8': j += 8; break;
                }
            pos++;
    }
        pos++;
        if(fen[pos] == 'b') {sidetomove = black;}
        else {sidetomove = white;}
        pos++;
        whitecastlekingside = false;
        blackcastlekingside = false;
        whitecastlequeenside = false;
        blackcastlequeenside = false;

        for(int i=0;i<=3;i++)
        {
            pos++;
            if(fen[pos] == '-' or fen[pos] == ' ') break;
            switch(fen[pos])
            {
            case 'K': whitecastlekingside = true; break;
            case 'Q': whitecastlequeenside = true; break;
            case 'k': blackcastlekingside = true; break;
            case 'q': blackcastlequeenside = true; break;
            }
        }
        pos++;
        if(fen[pos] == ' ') {pos++;}

        if(fen[pos] == '-') {
                enpassant_square = -1;
                pos ++;}
        else
        {
            int fi = fen[pos] - 'a';
            pos++;
            int ra = fen[pos] - '0';
            enpassant_square = 8*(8 - ra) + fi + 1;
            pos++;
        }
        pos++;

        halfmoves = fen[pos] - '0'; ///number of half moves without a pawn capture
        pos++;
        pos++;
        fullmoves = fen[pos] - '0';
    history[curr_index] = fen;


    /// other board related stuff goes here....
}

std::vector<movetype>board::valid_moves()
{
    std::vector<movetype> ans;
    movetype M;
    vint tempboard = currboard;
    int kingloc;
    for(int i=0;i<64;i++)
    {
        if(currboard[i] == K and sidetomove == white)
        {
            kingloc = i;
            break;
        }

        if(currboard[i] == k and sidetomove == black)
        {
            kingloc = i;
            break;
        }
    }

    if(sidetomove == white)
    {
        for(int i=0;i<64;i++)
        {
            int fno = getfile(i);
            int rno = getrank(i);

            int x = currboard[i];
            if(x == blank) continue;
            M.from = i;
            if(x == P)
            {
                if(rno<=6 and currboard[i-8] == blank) ///normal pawn one step advance
                {
                    M.to = i-8;
                    M.piece = P;
                    M.capture = false;
                    if(!incheck(kingloc,M,currboard))
                    ans.push_back(M);
                }

                if(rno == 2 and currboard[i-8] == blank and currboard[i-16] == blank) /// two initial steps for pawn
                {
                    M.to = i-16;
                    M.piece = P;
                    M.capture = false;
                    if(!incheck(kingloc,M,currboard))
                    ans.push_back(M);
                }

                if(rno == 7 and currboard[i-8] == blank) ///pawn promotion to queen(for now)
                {
                    M.to = i-8;
                    M.capture = false;
                    M.piece = Q;
                    if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    M.piece = N;
                    if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    M.piece = R;
                    if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    M.piece = B;
                    if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                }

                if(rno<= 7) /// pawn capture
                {
                    if(colors(currboard,i-7) == black and abs(getrank(i-7)-rno)== 1)
                    {
                        M.to = i-7;
                        M.capture = true;
                        if(rno < 7)
                        {
                            M.piece = P;
                        if(!incheck(kingloc,M,currboard))
                        {
                            ans.push_back(M);
                        }
                        // else std::cout<<"White king is in check if captures"<<std::endl;
                        }
                        else if(rno == 7) {
                                M.piece = Q; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = R; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = B; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = N; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                            }
                    }

                    if(colors(currboard,i-9) == black and abs(getrank(i-9)-rno)== 1)
                    {
                        M.to = i-9;
                        M.capture = true;
                        if(rno < 7)
                        {
                            M.piece = P;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                        }
                        else if(rno == 7) {

                                M.piece = Q; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = R; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = B; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = N; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                            }
                    }
                }

                if(enpassant_square > 0 and rno == 5 and abs(fno - getfile(enpassant_square -1)) == 1)
                {
                    M.ep = true;
                    M.to = enpassant_square - 1;
                    M.piece = P;
                    if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    M.ep = false;
                }
                ///en passant
            }
            else if(x == N)
            {
                for(unsigned int j=0;j<knightpos.size();j++)
                {
                    if(i+knightpos[j]<0 or i+knightpos[j] >= 64) continue;

                    if((abs(getrank(i+knightpos[j])-rno) == 1 and abs(getfile(i+knightpos[j])-fno) == 2) or (abs(getrank(i+knightpos[j])-rno) == 2 and abs(getfile(i+knightpos[j])-fno) == 1))
                    {
                        /// checking knight jump conditions
                        if(colors(currboard,i+knightpos[j]) == black) ///Knight capture
                        {
                            M.to = i+knightpos[j];
                            M.capture = true;
                            M.piece = N;
                            if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                        }

                        if(currboard[i+knightpos[j]] == blank) /// normal knight moveblack
                        {
                            M.to = i+knightpos[j];
                            M.capture = false;
                            M.piece = N;
                            if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                        }
                    }
                }
            }

            if(x == B or x == Q)
            {
                for(unsigned int j = 0; j<bishoppos45up.size();j++)
                {
                    if(i + bishoppos45up[j] <0 or i + bishoppos45up[j] >63) break;
                    if(getfile(i + bishoppos45up[j]) < fno) break;
                    else if(currboard[i + bishoppos45up[j]] == blank)
                    {
                        M.to = i + bishoppos45up[j];
                        M.piece = x;
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + bishoppos45up[j]) == black)
                {
                        M.to = i + bishoppos45up[j];
                        M.piece = x;
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<bishoppos45dn.size();j++)
                {
                    if(i + bishoppos45dn[j] <0 or i + bishoppos45dn[j] >63) break;
                    if(getfile(i + bishoppos45dn[j]) > fno) break;
                    else if(currboard[i + bishoppos45dn[j]] == blank)
                    {
                        M.to = i + bishoppos45dn[j];
                        M.piece = x;
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + bishoppos45dn[j])== black)
                {
                        M.to = i + bishoppos45dn[j];
                        M.piece = x;
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<bishoppos135up.size();j++)
                {
                    if(i + bishoppos135up[j] <0 or i + bishoppos135up[j] >63) break;
                    if(getfile(i + bishoppos135up[j]) > fno) break;
                    else if(currboard[i + bishoppos135up[j]] == blank)
                    {
                        M.to = i + bishoppos135up[j];
                        M.piece = x;
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + bishoppos135up[j]) == black)
                {
                        M.to = i + bishoppos135up[j];
                        M.piece = x;
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<bishoppos135dn.size();j++)
                {
                    if(i + bishoppos135dn[j] <0 or i + bishoppos135dn[j] >63) break;
                    if(getfile(i + bishoppos135dn[j]) < fno) break;
                    else if(currboard[i + bishoppos135dn[j]] == blank)
                    {
                        M.to = i + bishoppos135dn[j];
                        M.piece = x;
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + bishoppos135dn[j]) == black)
                {
                        M.to = i + bishoppos135dn[j];
                        M.piece = x;
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

            }

            if(x == R or x == Q)
            {
                    M.piece = x;

                 for(unsigned int j = 0; j<rookpos0up.size();j++)
                {
                     M.to = i + rookpos0up[j];
                    if(i + rookpos0up[j] <0 or i + rookpos0up[j] >63) break;

                    else if(currboard[i + rookpos0up[j]] == blank)
                    {
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + rookpos0up[j]) == black)
                {
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {
                                ans.push_back(M);
                        }

                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<rookpos0dn.size();j++)
                {
                     M.to = i + rookpos0dn[j];
                    if(i + rookpos0dn[j] <0 or i + rookpos0dn[j] >63) break;

                    else if(currboard[i + rookpos0dn[j]] == blank)
                    {
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + rookpos0dn[j]) == black)
                {
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<rookpos90lf.size();j++)
                {
                     M.to = i + rookpos90lf[j];
                    if(i + rookpos90lf[j] <0 or i + rookpos90lf[j] >63) break;
                    if(getfile(i + rookpos90lf[j]) > fno) break;
                    else if(currboard[i + rookpos90lf[j]] == blank)
                    {
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + rookpos90lf[j]) == black)
                {
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<rookpos90rt.size();j++)
                {
                     M.to = i + rookpos90rt[j];
                    if(i + rookpos90rt[j] <0 or i + rookpos90rt[j] >63) break;
                    if(getfile(i + rookpos90rt[j]) < fno) break;
                    else if(currboard[i + rookpos90rt[j]] == blank)
                    {
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + rookpos90rt[j]) == black)
                {
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }
            }

             if(x == K)
            {
                for(unsigned int j=0;j<kingpos.size();j++)
                {
                    M.to = kingpos[j] + i;
                    if(i + kingpos[j] <0 or i + kingpos[j] >63) continue;
                    if(abs(getrank(kingpos[j] + i)-rno)<=1 and abs(getfile(kingpos[j] + i)-fno)<=1)
                    {
                        if(colors(currboard,kingpos[j] + i) == black)
                        {
                            M.capture = true;
                            M.piece = K;
                            if(!incheck(M.to,M,currboard)) ans.push_back(M);
                        }

                        else if(currboard[kingpos[j] + i] == blank)
                        {
                            M.capture = false;
                            M.piece = K;
                            if(!incheck(M.to,M,currboard)) ans.push_back(M);
                        }
                    }
                }

            /// Castling moves!!

            if(whitecastlekingside)
            {
                M.capture = false;
                M.to = 62;
                M.piece = K;
                if(!isattacked(black,61,currboard) and !isattacked(black,62,currboard) and !isattacked(black,63,currboard) and currboard[61]== blank
                   and currboard[62] == blank)
                {
                    M.castle = true;
                    M.rookfrom = 63;
                    M.rookto = 61;
                    ans.push_back(M);
                }
                M.castle = false;
            }

            if(whitecastlequeenside)
            {
                M.capture = false;
                M.to = 58;
                M.piece = K;
                if(!isattacked(black,59,currboard) and !isattacked(black,60,currboard) and !isattacked(black,61,currboard)
                   and currboard[57] == blank
                   and currboard[58] == blank and currboard[59] == blank)
                {
                    M.castle = true;
                    M.rookfrom = 56;
                    M.rookto = 59;
                    ans.push_back(M);
                }
                M.castle = false;
            }
            }


        }
    }




///5%%%%%%%%%%%%%%%%  Same, repeated for black.



     else if(sidetomove == black)
    {
        for(int i=0;i<64;i++)
        {
            int fno = getfile(i);
            int rno = getrank(i);

            int x = currboard[i];
            if(x == blank) continue;
            M.from = i;

            if(x == p)
            {
                if(rno >=3 and currboard[i+8] == blank) ///normal pawn one step advance
                {
                    M.to = i+8;
                    M.piece = p;
                    M.capture = false;
                    if(!incheck(kingloc,M,currboard))
                    ans.push_back(M);
                }

                if(rno == 7 and currboard[i+8] == blank and currboard[i+16] == blank) /// two initial steps for pawn
                {
                    M.to = i+16;
                    M.piece = p;
                    M.capture = false;
                    if(!incheck(kingloc,M,currboard))
                    ans.push_back(M);
                }

                if(rno == 2 and currboard[i+8] == blank) ///pawn promotion to queen(for now)
                {
                    M.to = i+8;
                    M.piece = q;
                    M.capture = false;
                    if(!incheck(kingloc,M,currboard))
                    ans.push_back(M);
                    M.piece = n;
                    if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    M.piece = r;
                    if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    M.piece = b;
                    if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                }

                if(rno>=2) /// pawn capture
                {
                    if(colors(currboard,i+7) == white and abs(getrank(i+7)-rno)== 1)
                    {
                        M.to = i+7;
                        M.capture = true;
                        if(rno > 2)
                        {
                            M.piece = p;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                        }
                        else if(rno == 2) {

                                M.piece = q; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = r; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = b; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = n; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                            }
                        }

                    if(colors(currboard,i+9) == white and abs(getrank(i+9)-rno)== 1)
                    {
                        M.to = i+9;
                        M.capture = true;
                        if(rno > 2)
                        {
                            M.piece = p;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                        }
                        else if(rno == 2) {

                                M.piece = q; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = r; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = b; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                                M.piece = n; if(!incheck(kingloc,M,currboard))ans.push_back(M);
                            }
                    }
                }

                if(enpassant_square > 0 and rno == 4 and abs(fno - getfile(enpassant_square -1)) == 1)
                {
                    M.ep = true;
                    M.to = enpassant_square - 1;
                    M.piece = p;
                    if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    M.ep = false;
                }

                }

            if(x == n)
            {
                for(unsigned int j=0;j<knightpos.size();j++)
                {
                    if(i+knightpos[j]<0 or i+knightpos[j] >= 64) continue;

                    if((abs(getrank(i+knightpos[j])-rno) == 1 and abs(getfile(i+knightpos[j])-fno) == 2) or (abs(getrank(i+knightpos[j])-rno) == 2 and abs(getfile(i+knightpos[j])-fno) == 1))
                    {
                        /// checking knight jump conditions
                        if(colors(currboard,i+knightpos[j]) == white) ///Knight capture
                        {
                            M.to = i+knightpos[j];
                            M.capture = true;
                            M.piece = n;
                            if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                        }

                        if(currboard[i+knightpos[j]] == blank) /// normal knight moveblack
                        {
                            M.to = i+knightpos[j];
                            M.capture = false;
                            M.piece = n;
                            if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                        }
                    }
                }
            }

           if(x == b or x == q)
            {
                for(unsigned int j = 0; j<bishoppos45up.size();j++)
                {
                    if(i + bishoppos45up[j] <0 or i + bishoppos45up[j] >63) break;
                    if(getfile(i + bishoppos45up[j]) < fno) break;
                    else if(currboard[i + bishoppos45up[j]] == blank)
                    {
                        M.to = i + bishoppos45up[j];
                        M.piece = x;
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + bishoppos45up[j]) == white)
                {
                        M.to = i + bishoppos45up[j];
                        M.piece = x;
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<bishoppos45dn.size();j++)
                {
                    if(i + bishoppos45dn[j] <0 or i + bishoppos45dn[j] >63) break;
                    if(getfile(i + bishoppos45dn[j]) > fno) break;
                    else if(currboard[i + bishoppos45dn[j]] == blank)
                    {
                        M.to = i + bishoppos45dn[j];
                        M.piece = x;
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + bishoppos45dn[j]) == white)
                {
                        M.to = i + bishoppos45dn[j];
                        M.piece = x;
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<bishoppos135up.size();j++)
                {
                    if(i + bishoppos135up[j] <0 or i + bishoppos135up[j] >63) break;
                    if(getfile(i + bishoppos135up[j]) > fno) break;
                    else if(currboard[i + bishoppos135up[j]] == blank)
                    {
                        M.to = i + bishoppos135up[j];
                        M.piece = x;
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + bishoppos135up[j]) == white)
                {
                        M.to = i + bishoppos135up[j];
                        M.piece = x;
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<bishoppos135dn.size();j++)
                {
                    if(i + bishoppos135dn[j] <0 or i + bishoppos135dn[j] >63) break;
                    if(getfile(i + bishoppos135dn[j]) < fno) break;
                    else if(currboard[i + bishoppos135dn[j]] == blank)
                    {
                        M.to = i + bishoppos135dn[j];
                        M.piece = x;
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + bishoppos135dn[j]) == white)
                {
                        M.to = i + bishoppos135dn[j];
                        M.piece = x;
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

            }

             if(x == r or x == q)
            {
                //std::cout<<"Entered black rook!"<<std::endl;
                    M.piece = x;

                 for(unsigned int j = 0; j<rookpos0up.size();j++)
                {
                    M.to = i + rookpos0up[j];
                    if(i + rookpos0up[j] <0 or i + rookpos0up[j] >63) break;

                    else if(currboard[i + rookpos0up[j]] == blank)
                    {

                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);

                    }
                else if(colors(currboard,i + rookpos0up[j]) == white)
                {
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<rookpos0dn.size();j++)
                {
                    M.to = i + rookpos0dn[j];
                    if(i + rookpos0dn[j] <0 or i + rookpos0dn[j] >63) break;

                    else if(currboard[i + rookpos0dn[j]] == blank)
                    {
                       // std::cout<<"Entered rook king check!"<<std::endl;
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                       // std::cout<<"King location: "<<kingloc<<std::endl;
                       // std::cout<<"Black is in check?!: "<<incheck(kingloc,M,currboard)<<std::endl;
                    }
                else if(colors(currboard,i + rookpos0dn[j]) == white)
                {
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<rookpos90lf.size();j++)
                {
                    M.to = i + rookpos90lf[j];
                    if(i + rookpos90lf[j] <0 or i + rookpos90lf[j] >63) break;
                    if(getfile(i + rookpos90lf[j]) > fno) break;
                    else if(currboard[i + rookpos90lf[j]] == blank)
                    {
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + rookpos90lf[j]) == white)
                {
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }

                for(unsigned int j = 0; j<rookpos90rt.size();j++)
                {
                    M.to = i + rookpos90rt[j];
                    if(i + rookpos90rt[j] <0 or i + rookpos90rt[j] >63) break;
                    if(getfile(i + rookpos90rt[j]) < fno) break;
                    else if(currboard[i + rookpos90rt[j]] == blank)
                    {
                        M.capture = false;
                        if(!incheck(kingloc,M,currboard)) ans.push_back(M);
                    }
                else if(colors(currboard,i + rookpos90rt[j]) == white)
                {
                        M.capture = true;
                        if(!incheck(kingloc,M,currboard)) {ans.push_back(M);}
                        break;
                }
                else break;
                }
            }

            else if(x == k)
            {
                for(unsigned int j=0;j<kingpos.size();j++)
                {
                    M.to = kingpos[j] + i;
                    if(i + kingpos[j] <0 or i + kingpos[j] >63) continue;
                    if(abs(getrank(kingpos[j] + i)-rno)<=1 and abs(getfile(kingpos[j] + i)-fno)<=1)
                    {
                        if(colors(currboard,kingpos[j] + i) == white)
                        {
                            M.capture = true;
                            M.piece = k;
                            if(!incheck(M.to,M,currboard)) ans.push_back(M);
                        }

                        else if(currboard[kingpos[j] + i] == blank)
                        {
                            M.capture = false;
                            M.piece = k;
                            if(!incheck(M.to,M,currboard)) ans.push_back(M);
                        }
                    }
                }

                if(blackcastlekingside)
            {
                M.capture = false;
                M.to = 6;
                M.piece = k;
                if(!isattacked(white,5,currboard) and !isattacked(white,6,currboard) and !isattacked(white,7,currboard) and currboard[5]== blank
                   and currboard[6] == blank)
                {
                    M.castle = true;
                    M.rookfrom = 7;
                    M.rookto = 5;
                    ans.push_back(M);
                }
                M.castle = false;
            }

            if(blackcastlequeenside)
            {
                M.capture = false;
                M.to = 2;
                M.piece = k;
                if(!isattacked(white,3,currboard) and !isattacked(white,4,currboard)and !isattacked(white,5,currboard) and
                   currboard[1] == blank
                   and currboard[2] == blank and currboard[3] == blank)
                {
                    M.castle = true;
                    M.rookfrom = 0;
                    M.rookto = 3;
                    ans.push_back(M);
                }
                M.castle = false;
            }


            }


        }
    }

    return ans;
}
