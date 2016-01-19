#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include<vector>

const int maxmoves(200);

typedef std::vector<int> vint;
typedef std::vector<bool> vbool;

struct movetype
{
    movetype(){from = 0; to = 0; capture = false;
    rookfrom = 0;rookto = 0;castle=false,ep = false;}
    int from; /// 63 based indices;
    int to;
    bool ep;
    int rookfrom;
    int rookto;
    int piece;
    bool castle;
    bool capture;
};

 const vint knightpos = {-17,-10,6,15,17,10,-6,-15};
 const vint bishoppos45up = {-7,-14,-21,-28,-35,-42,-49};
 const vint bishoppos45dn = {7,14,21,28,35,42,49};
 const vint bishoppos135up = {-9,-18,-27,-36,-45,-54,-63};
 const vint bishoppos135dn = {9,18,27,36,45,54,63};
 const vint rookpos90lf = {-1,-2,-3,-4,-5,-6,-7};
 const vint rookpos90rt = {1,2,3,4,5,6,7};
 const vint rookpos0up = {-8,-16,-24,-32,-40,-48,-56};
 const vint rookpos0dn = {8,16,24,32,40,48,56};
 const vint pawnwhitepos = {9,7};
 const vint pawnblackpos = {-7,-9};
 const vint kingpos = {-9,-8,-7,-1,1,7,8,9};

#endif // DEFINITIONS_H
