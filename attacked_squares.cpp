#include "enumerations.h"
#include "definitions.h"
#include "attacked_squares.h"
#include "helper_funcs.h"
#include "stdlib.h"
#include<iostream>
#include<vector>


///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


bool isattacked(const int side, const int square, const vint& myboard)
{
    unsigned int i;
    int sq = square - 1;
    int fno = getfile(sq);
    int rno = getrank(sq);
    // knight
    if(side == black)
    {
        for(i=0;i<knightpos.size();i++)
        {
            if(sq+knightpos[i] <0 or sq+knightpos[i] >63) continue;
            if(myboard[sq + knightpos[i]] == n)
            {
                if(abs(fno - getfile(sq+knightpos[i])) == 2 and abs(rno - getrank(sq+knightpos[i])) == 1 ) return true;
                else if(abs(fno - getfile(sq+knightpos[i])) == 1 and abs(rno - getrank(sq+knightpos[i])) == 2) return true;
            }

        }

        for(i=0;i<bishoppos135up.size();i++)
        {
            if(sq+bishoppos135up[i] <0 or sq+bishoppos135up[i] >63) break;
            if(getfile(sq  + bishoppos135up[i]) > fno) break;
            else if(myboard[sq  + bishoppos135up[i]] == b or myboard[sq + bishoppos135up[i]] == q) return true;
            else if (myboard[sq + bishoppos135up[i]] == blank) continue;
            else break;
        }

        for(i=0;i<bishoppos135dn.size();i++)
        {
            if(sq+bishoppos135dn[i] <0 or sq+bishoppos135dn[i] >63) break;
            if(getfile(sq  + bishoppos135dn[i]) < fno) break;
            else if(myboard[sq + bishoppos135dn[i]] == b or myboard[sq + bishoppos135dn[i]] == q) return true;
            else if (myboard[sq + bishoppos135dn[i]] == blank) continue;
            else break;
        }

         for(i=0;i<bishoppos45up.size();i++)
        {
            if(sq+bishoppos45up[i] <0 or sq+bishoppos45up[i] >63) break;
            if(getfile(sq  + bishoppos45up[i]) < fno) break;
            else if(myboard[sq + bishoppos45up[i]] == b or myboard[sq + bishoppos45up[i]] == q) return true;
            else if(myboard[sq + bishoppos45up[i]] == blank) continue;
            else break;
        }

        for(i=0;i<bishoppos45dn.size();i++)
        {
            if(sq+bishoppos45dn[i] <0 or sq+bishoppos45dn[i] >63) break;
            if(getfile(sq  + bishoppos45dn[i]) > fno) break;
            else if(myboard[sq + bishoppos45dn[i]] == b or myboard[sq + bishoppos45dn[i]] == q) return true;
            else if(myboard[sq + bishoppos45dn[i]] == blank) continue;
            else break;
        }

         for(i=0;i<rookpos0up.size();i++)
        {
            if(sq+rookpos0up[i] <0 or sq+rookpos0up[i] >63) break;
            if(myboard[sq + rookpos0up[i]] == r or myboard[sq + rookpos0up[i]] == q)
                return true;
            else if(myboard[sq + rookpos0up[i]] == blank) continue;
            else break;
        }

        for(i=0;i<rookpos0dn.size();i++)
        {
            if(sq+rookpos0dn[i] <0 or sq+rookpos0dn[i] >63) break;
            if(myboard[sq + rookpos0dn[i]] == r or myboard[sq + rookpos0dn[i]] == q) return true;
            else if(myboard[sq+ rookpos0dn[i]] == blank)
            {
                continue;
            }
            else break;
        }

        for(i=0;i<rookpos90lf.size();i++)
        {
            if(sq+rookpos90lf[i] <0 or sq+rookpos90lf[i] >63) break;
            if(getfile(sq  + rookpos90lf[i]) > fno) break;
            else if(myboard[sq + rookpos90lf[i]] == r or myboard[sq + rookpos90lf[i]] == q)
                return true;
            else if(myboard[sq + rookpos90lf[i]] == blank) continue;
            else break;
        }

        for(i=0;i<rookpos90rt.size();i++)
        {
            if(sq+rookpos90rt[i] <0 or sq+rookpos90rt[i] >63) break;
            if(getfile(sq  + rookpos90rt[i]) < fno) break;
            else if(myboard[sq + rookpos90rt[i]] == r or myboard[sq + rookpos90rt[i]] == q)
                return true;
                else if(myboard[sq + rookpos90rt[i]] == blank) continue;
            else break;
        }

        for(i=0;i<kingpos.size();i++)
        {
            if(sq+kingpos[i] <0 or sq+kingpos[i] >63) continue;
            if(myboard[sq + kingpos[i]] == k)
            {
                if(abs(getfile(sq+kingpos[i])-fno)<=1 and abs(getrank(sq+kingpos[i])- rno)<=1) return true;
            }
        }

        for(i=0;i<pawnblackpos.size();i++)
        {
            if(sq+pawnblackpos[i] <0 or sq+pawnblackpos[i] >63) continue;
            if(myboard[sq + pawnblackpos[i]] == p)
            {
             if(abs(getfile(sq+pawnblackpos[i]) - fno) == 1) return true;
            }
        }
    }

else if(side == white)
    {
        for(i=0;i<knightpos.size();i++)
        {
            if(sq+knightpos[i] <0 or sq+knightpos[i] >63) continue;
            if(myboard[sq + knightpos[i]] == N)
            {
                if(abs(fno - getfile(sq+knightpos[i])) == 2 and abs(rno - getrank(sq+knightpos[i])) == 1 ) return true;
                else if(abs(fno - getfile(sq+knightpos[i])) == 1 and abs(rno - getrank(sq+knightpos[i])) == 2) return true;
            }

        }

        for(i=0;i<bishoppos135up.size();i++)
        {
            if(sq+bishoppos135up[i] <0 or sq+bishoppos135up[i] >63) break;
            if(getfile(sq  + bishoppos135up[i]) > fno) break;
            else if(myboard[sq  + bishoppos135up[i]] == B or myboard[sq + bishoppos135up[i]] == Q) return true;
            else if (myboard[sq + bishoppos135up[i]] == blank) continue;
            else break;
        }

        for(i=0;i<bishoppos135dn.size();i++)
        {
            if(sq+bishoppos135dn[i] <0 or sq+bishoppos135dn[i] >63) break;
            if(getfile(sq  + bishoppos135dn[i]) < fno) break;
            else if(myboard[sq + bishoppos135dn[i]] == B or myboard[sq + bishoppos135dn[i]] == Q) return true;
            else if (myboard[sq + bishoppos135dn[i]] == blank) continue;
            else break;
        }

         for(i=0;i<bishoppos45up.size();i++)
        {
            if(sq+bishoppos45up[i] <0 or sq+bishoppos45up[i] >63) break;
            if(getfile(sq  + bishoppos45up[i]) < fno) break;
            else if(myboard[sq + bishoppos45up[i]] == B or myboard[sq + bishoppos45up[i]] == Q) return true;
            else if(myboard[sq + bishoppos45up[i]] == blank) continue;
            else break;
        }

        for(i=0;i<bishoppos45dn.size();i++)
        {
            if(sq+bishoppos45dn[i] <0 or sq+bishoppos45dn[i] >63) break;
            if(getfile(sq  + bishoppos45dn[i]) > fno) break;
            else if(myboard[sq + bishoppos45dn[i]] == B or myboard[sq + bishoppos45dn[i]] == Q) return true;
            else if(myboard[sq + bishoppos45dn[i]] == blank) continue;
            else break;
        }

         for(i=0;i<rookpos0up.size();i++)
        {
            if(sq+rookpos0up[i] <0 or sq+rookpos0up[i] >63) break;
            if(myboard[sq + rookpos0up[i]] == R or myboard[sq + rookpos0up[i]] == Q)
                return true;
            else if(myboard[sq + rookpos0up[i]] == blank) continue;
            else break;
        }

        for(i=0;i<rookpos0dn.size();i++)
        {
            if(sq+rookpos0dn[i] <0 or sq+rookpos0dn[i] >63) break;
            if(myboard[sq + rookpos0dn[i]] == R or myboard[sq + rookpos0dn[i]] == Q) return true;
            else if(myboard[sq+ rookpos0dn[i]] == blank)
            {
                continue;
            }
            else break;
        }

        for(i=0;i<rookpos90lf.size();i++)
        {
            if(sq+rookpos90lf[i] <0 or sq+rookpos90lf[i] >63) break;
            if(getfile(sq  + rookpos90lf[i]) > fno) break;
            else if(myboard[sq + rookpos90lf[i]] == R or myboard[sq + rookpos90lf[i]] == Q)
                return true;
            else if(myboard[sq + rookpos90lf[i]] == blank) continue;
            else break;
        }

        for(i=0;i<rookpos90rt.size();i++)
        {
            if(sq+rookpos90rt[i] <0 or sq+rookpos90rt[i] >63) break;
            if(getfile(sq  + rookpos90rt[i]) < fno) break;
            else if(myboard[sq + rookpos90rt[i]] == R or myboard[sq + rookpos90rt[i]] == Q)
                return true;
                else if(myboard[sq + rookpos90rt[i]] == blank) continue;
            else break;
        }

        for(i=0;i<kingpos.size();i++)
        {
            if(sq+kingpos[i] <0 or sq+kingpos[i] >63) continue;
            if(myboard[sq + kingpos[i]] == K)
            {
                if(abs(getfile(sq+kingpos[i])-fno)<=1 and abs(getrank(sq+kingpos[i])- rno)<=1) return true;
            }
        }

        for(i=0;i<pawnwhitepos.size();i++)
        {
            if(sq+pawnwhitepos[i] <0 or sq+pawnwhitepos[i] >63) continue;
            if(myboard[sq + pawnwhitepos[i]] == P)
            {
             if(abs(getfile(sq+pawnwhitepos[i]) - fno) == 1) return true;
            }
        }
    }

    return false;
}
