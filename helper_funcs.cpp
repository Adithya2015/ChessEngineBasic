#include "helper_funcs.h"
#include "attacked_squares.h"
/// 0-63 format of squares for getrank and getfile...

int getrank(int a)
{
    return (8 - a/8);
}

int getfile(int a)
{
    return (1 + (a%8));
}

bool incheck(int king_location, movetype mymove, vint& myboard)
{
    int mem1 = myboard[mymove.from],mem2 = myboard[mymove.to];
    myboard[mymove.from] = blank;
    myboard[mymove.to] = mymove.piece;
    int side = (myboard[king_location] == K)?black:white;
    bool ans = isattacked(side,king_location + 1,myboard);
        ///isattacked takes 64 based positions
    myboard[mymove.from] = mem1;
    myboard[mymove.to] = mem2;
 return ans;
}


bool incheck(int king_location, vint& myboard)
{
    int side = (myboard[king_location] == K)?black:white;
        if(isattacked(side,king_location + 1,myboard)) return true; ///isattacked takes 64 based positions
        else return false;
}


std::string tostring(int x)
{
    std::ostringstream temp;
    temp << x;
    return temp.str();
}

std::string toalgebsquare(int x)
{
    std::string s1,s2;
    switch(getfile(x-1))
        {
            case 1: s1 = "a"; break;
            case 2: s1 = "b"; break;
            case 3: s1 = "c"; break;
            case 4: s1 = "d"; break;
            case 5: s1 = "e"; break;
            case 6: s1 = "f"; break;
            case 7: s1 = "g"; break;
            case 8: s1 = "h"; break;
        }


    switch(getrank(x-1))
        {
            case 1: s2 = "1"; break;
            case 2: s2 = "2"; break;
            case 3: s2 = "3"; break;
            case 4: s2 = "4"; break;
            case 5: s2 = "5"; break;
            case 6: s2 = "6"; break;
            case 7: s2 = "7"; break;
            case 8: s2 = "8"; break;
        }

        return s1+s2;
}

int colors(const vint& currboard,int index)
{
        if(currboard[index] == blank) return nocolor;
        else if(currboard[index]<=6) return black;
        else return white;
}
