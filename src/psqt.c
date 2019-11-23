// psqt.c

#include "board.h"
#include "evaluate.h"
#include "types.h"


int PSQT[PIECE_NB][64];


// Initialize the piece square tables with piece values included
CONSTR InitPSQT() {

    const int pieceValue[PIECE_NB] = { 0, S(P_MG, P_EG), S(N_MG, N_EG), S(B_MG, B_EG), S(R_MG, R_EG), S(Q_MG, Q_EG), 0, 0,
                                       0, S(P_MG, P_EG), S(N_MG, N_EG), S(B_MG, B_EG), S(R_MG, R_EG), S(Q_MG, Q_EG), 0, 0 };

    const int tempPSQT[7][64] = {
        { 0 }, // Unused
        { // Pawn
        S( 0,  0), S( 0,  0), S( 0,  0), S(  0,   0), S(  0,   0), S( 0,  0), S( 0,  0), S( 0,  0),
        S(20, 20), S(20, 20), S(20, 20), S( 30,  30), S( 30,  30), S(20, 20), S(20, 20), S(20, 20),
        S(10, 10), S(10, 10), S(10, 10), S( 20,  20), S( 20,  20), S(10, 10), S(10, 10), S(10, 10),
        S( 5,  5), S( 5,  5), S( 5,  5), S( 10,  10), S( 10,  10), S( 5,  5), S( 5,  5), S( 5,  5),
        S( 0,  0), S( 0,  0), S(10, 10), S( 20,  20), S( 20,  20), S(10, 10), S( 0,  0), S( 0,  0),
        S( 5,  5), S( 5,  5), S( 0,  0), S(  5,   5), S(  5,   5), S( 0,  0), S( 5,  5), S( 5,  5),
        S(10, 10), S(10, 10), S( 0,  0), S(-10, -10), S(-10, -10), S( 5,  5), S(10, 10), S(10, 10),
        S( 0,  0), S( 0,  0), S( 0,  0), S(  0,   0), S(  0,   0), S( 0,  0), S( 0,  0), S( 0,  0)},

        { // Knight
        S(-50, -50), S(-10, -10), S(-10, -10), S( -5,  -5), S( -5,  -5), S(-10, -10), S(-10, -10), S(-50, -50),
        S(-25, -25), S(  0,   0), S(  5,   5), S( 10,  10), S( 10,  10), S(  5,   5), S(  0,   0), S(-25, -25),
        S(-10, -10), S( 10,  10), S( 10,  10), S( 20,  20), S( 20,  20), S( 10,  10), S( 10,  10), S(-10, -10),
        S(-10, -10), S( 10,  10), S( 15,  15), S( 20,  20), S( 20,  20), S( 15,  15), S( 10,  10), S(-10, -10),
        S(-10, -10), S(  5,   5), S( 10,  10), S( 20,  20), S( 20,  20), S( 10,  10), S(  5,   5), S(-10, -10),
        S(-10, -10), S(  5,   5), S( 10,  10), S( 10,  10), S( 10,  10), S( 10,  10), S(  5,   5), S(-10, -10),
        S(-25, -25), S(  0,   0), S(  0,   0), S(  5,   5), S(  5,   5), S(  0,   0), S(  0,   0), S(-25, -25),
        S(-50, -50), S(-10, -10), S(-10, -10), S( -5,  -5), S( -5,  -5), S(-10, -10), S(-10, -10), S(-50, -50)},

        { // Bishop
        S(0, 0), S( 0,  0), S(  0,   0), S( 0,  0), S( 0,  0), S(  0,   0), S( 0,  0), S(0, 0),
        S(0, 0), S( 0,  0), S(  0,   0), S(10, 10), S(10, 10), S(  0,   0), S( 0,  0), S(0, 0),
        S(0, 0), S( 0,  0), S( 10,  10), S(15, 15), S(15, 15), S( 10,  10), S( 0,  0), S(0, 0),
        S(0, 0), S(10, 10), S( 15,  15), S(20, 20), S(20, 20), S( 15,  15), S(10, 10), S(0, 0),
        S(0, 0), S(10, 10), S( 15,  15), S(20, 20), S(20, 20), S( 15,  15), S(10, 10), S(0, 0),
        S(0, 0), S( 0,  0), S( 10,  10), S(15, 15), S(15, 15), S( 10,  10), S( 0,  0), S(0, 0),
        S(0, 0), S(10, 10), S(  0,   0), S(10, 10), S(10, 10), S(  0,   0), S(10, 10), S(0, 0),
        S(0, 0), S( 0,  0), S(-10, -10), S( 0,  0), S( 0,  0), S(-10, -10), S( 0,  0), S(0, 0)},

        { // Rook
        S( 0,  0), S( 0,  0), S( 5,  5), S(10, 10), S(10, 10), S( 5,  5), S( 0,  0), S( 0,  0),
        S(25, 25), S(25, 25), S(25, 25), S(25, 25), S(25, 25), S(25, 25), S(25, 25), S(25, 25),
        S( 0,  0), S( 0,  0), S( 5,  5), S(10, 10), S(10, 10), S( 5,  5), S( 0,  0), S( 0,  0),
        S( 0,  0), S( 0,  0), S( 5,  5), S(10, 10), S(10, 10), S( 5,  5), S( 0,  0), S( 0,  0),
        S( 0,  0), S( 0,  0), S( 5,  5), S(10, 10), S(10, 10), S( 5,  5), S( 0,  0), S( 0,  0),
        S( 0,  0), S( 0,  0), S( 5,  5), S(10, 10), S(10, 10), S( 5,  5), S( 0,  0), S( 0,  0),
        S( 0,  0), S( 0,  0), S( 5,  5), S(10, 10), S(10, 10), S( 5,  5), S( 0,  0), S( 0,  0),
        S( 0,  0), S( 0,  0), S( 5,  5), S(10, 10), S(10, 10), S( 5,  5), S( 0,  0), S( 0,  0)},

        { 0 }, // Queen

        { // King
        S(-70, -50), S(-70, -10), S(-70,  0), S(-70,  0), S(-70,  0), S(-70,  0), S(-70, -10), S(-70, -50),
        S(-70, -10), S(-70,   0), S(-70, 10), S(-70, 10), S(-70, 10), S(-70, 10), S(-70,   0), S(-70, -10),
        S(-70,   0), S(-70,  10), S(-70, 20), S(-70, 20), S(-70, 20), S(-70, 20), S(-70,  10), S(-70,   0),
        S(-70,   0), S(-70,  10), S(-70, 20), S(-70, 40), S(-70, 40), S(-70, 20), S(-70,  10), S(-70,   0),
        S(-70,   0), S(-70,  10), S(-70, 20), S(-70, 40), S(-70, 40), S(-70, 20), S(-70,  10), S(-70,   0),
        S(-50,   0), S(-50,  10), S(-50, 20), S(-50, 20), S(-50, 20), S(-50, 20), S(-50,  10), S(-50,   0),
        S(-30, -10), S(-30,   0), S(-30, 10), S(-30, 10), S(-30, 10), S(-30, 10), S(-30,   0), S(-30, -10),
        S(  0, -50), S( 10, -10), S(  5,  0), S(-10,  0), S(-10,  0), S( -5,  0), S( 10, -10), S(  5, -50)}};

    // Black scores are negative (white double negated -> positive)
    for (int piece = bP; piece <= bK; ++piece)
        for (int sq = A1; sq <= H8; ++sq) {
            PSQT[piece][sq] = -(tempPSQT[piece][sq] + pieceValue[piece]);
            PSQT[piece+8][mirror_square[sq]] = -PSQT[piece][sq];
        }
}