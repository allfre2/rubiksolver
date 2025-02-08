#include "common.h"
#include "solver.h"

const char CROSS_EDGE_ALGORITHMS[ EDGE_COUNT * EDGE_ORIENTATIONS ][8] = {
    "",// { DOWN, 2, FRONT, 6 },
    "DRdF",// { FRONT, 6, DOWN, 2 },
    "dfDF",// { DOWN, 4, RIGHT, 6 },
    "RF",// { RIGHT, 6, DOWN, 4 },
    "BBUUFF",// { DOWN, 6, BACK, 6 }, // ????
    "dRDF",// { BACK, 6, DOWN, 6 },
    "DFdf",// { DOWN, 8, LEFT, 6 },
    "lf",// { LEFT, 6, DOWN, 8 },
    "dLD",// { FRONT, 8, LEFT, 4 },
    "f",// { LEFT, 4, FRONT, 8 },
    "ULfl",// { FRONT, 2, UP, 6 },
    "FF",// { UP, 6, FRONT, 2 },
    "RUrFF",// { FRONT, 4, RIGHT, 8 },
    "F",// { RIGHT, 8, FRONT, 4 },
    "rURFF",// { BACK, 8, RIGHT, 4 },
    "RRFRR",// { RIGHT, 4, BACK, 8 },
    "LulFF",// { BACK, 4, LEFT, 8 },
    "LLfLL",// { LEFT, 8, BACK, 4 },
    "uFF",// { UP, 8, LEFT, 2 },
    "Lfl",// { LEFT, 2, UP, 8 },
    "UUFF",// { UP, 2, BACK, 2 },
    "UrFR",// { BACK, 2, UP, 2 },
    "UFF",// { UP, 4, RIGHT, 2 },
    "rFR"// { RIGHT, 2, UP, 4 },
};

int LookupCrossEdgeAlgorithm(Cube * cube, u_int face1, u_int face2) {
    for (int i = 0; i < EDGE_COUNT * EDGE_ORIENTATIONS; ++i) {
        u_int * lookup = EDGE_LOOKUP_TABLE [ i ];

        u_int color1 = SQUARE_COLOR((cube -> Faces [ (lookup [0]) ]), lookup [1]);
        u_int color2 = SQUARE_COLOR((cube -> Faces [ (lookup [2]) ]), lookup [3]);

        if (face1 == color1 && face2 == color2) {
            return i;
        }
    }

    return ALGORITHM_NOT_FOUND;
}

char * SolveCross(Cube * cube) {

    int algorithm = LookupCrossEdgeAlgorithm(cube, DOWN, FRONT);

    if (algorithm == ALGORITHM_NOT_FOUND) {
        printf("\n(!) Algorithm not found!\n");

        return 0;
    }

    ApplyAlgorithm(cube, CROSS_EDGE_ALGORITHMS [algorithm]);
}

char * Solve(Cube * cube) {
    SolveCross(cube);
}
