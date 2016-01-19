#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H
#include<string>

    enum{nocolor = -1,white,black};
    enum{blank=0,p,r,n,b,q,k,P,R,N,B,Q,K}; //white: capitals, black: smalls
    enum{file_a,file_b,file_c,file_d,file_e,file_f,file_g,file_h};
    enum{rank_1,rank_2,rank_3,rank_4,rank_5,rank_6,rank_7,rank_8};
    enum{
    a1 = 57,  b1, c1, d1, e1, f1, g1, h1,
    a2 = 49,  b2, c2, d2, e2, f2, g2, h2,
    a3 = 41, b3, c3, d3, e3, f3, g3, h3,
    a4 = 33, b4, c4, d4, e4, f4, g4, h4,
    a5 = 25, b5, c5, d5, e5, f5, g5, h5,
    a6 = 17, b6, c6, d6, e6, f6, g6, h6,
    a7 = 9, b7, c7, d7, e7, f7, g7, h7,
    a8 = 1, b8, c8, d8, e8, f8, g8, h8
    };
    const std::string Piece = ".prnbqkPRNBQK";
    const std::string File = "abcdefgh";
    const std::string Rank = "87654321";

#endif // ENUMERATIONS_H
