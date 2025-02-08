#include "common.h"
#include "solver.h"

const char MOVE_DOWN = DOWN_CHAR;

const char CROSS_EDGE_ALGORITHMS[ EDGE_COUNT * EDGE_ORIENTATIONS ][8] = {
    {},
    { DOWN_CHAR, RIGHT_CHAR, DOWN_PRIME_CHAR, FRONT_CHAR },
    { DOWN_PRIME_CHAR, FRONT_PRIME_CHAR, DOWN_CHAR, FRONT_CHAR },
    { RIGHT_CHAR, FRONT_CHAR }, 
    { BACK_CHAR, BACK_CHAR, UP_CHAR, UP_CHAR, FRONT_CHAR, FRONT_CHAR },
    { DOWN_PRIME_CHAR, RIGHT_CHAR, DOWN_CHAR, FRONT_CHAR },
    { DOWN_CHAR, FRONT_CHAR, DOWN_PRIME_CHAR, FRONT_PRIME_CHAR },
    { LEFT_PRIME_CHAR, FRONT_PRIME_CHAR },
    { DOWN_PRIME_CHAR, LEFT_CHAR, DOWN_CHAR },
    { FRONT_PRIME_CHAR },
    { UP_CHAR, LEFT_CHAR, FRONT_PRIME_CHAR, LEFT_PRIME_CHAR }, 
    { FRONT_CHAR, FRONT_CHAR },
    { RIGHT_CHAR, UP_CHAR, RIGHT_PRIME_CHAR, FRONT_CHAR, FRONT_CHAR },
    { FRONT_CHAR }, 
    { RIGHT_PRIME_CHAR, UP_CHAR, RIGHT_CHAR, FRONT_CHAR, FRONT_CHAR },
    { RIGHT_CHAR, RIGHT_CHAR, FRONT_CHAR, RIGHT_CHAR, RIGHT_CHAR },
    { LEFT_CHAR, UP_PRIME_CHAR, LEFT_PRIME_CHAR, FRONT_CHAR, FRONT_CHAR },
    { LEFT_CHAR, LEFT_CHAR, FRONT_PRIME_CHAR, LEFT_CHAR, LEFT_CHAR },
    { UP_PRIME_CHAR, FRONT_CHAR, FRONT_CHAR },
    { LEFT_CHAR, FRONT_PRIME_CHAR, LEFT_PRIME_CHAR },
    { UP_CHAR, UP_CHAR, FRONT_CHAR, FRONT_CHAR },
    { UP_CHAR, RIGHT_PRIME_CHAR, FRONT_CHAR, RIGHT_CHAR },
    { UP_CHAR, FRONT_CHAR, FRONT_CHAR },
    { RIGHT_PRIME_CHAR, FRONT_CHAR, RIGHT_CHAR }
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

void SolveEdge(Cube * cube, u_int face1, u_int face2) {
    int algorithm = LookupCrossEdgeAlgorithm(cube, face1, face2);

    if (algorithm == ALGORITHM_NOT_FOUND) {
        printf("\n(!) Algorithm not found!\n");

        return 0;
    }

    ApplyAlgorithm(cube, CROSS_EDGE_ALGORITHMS [algorithm]);
}

void SolveCross(Cube * cube) {
    SolveEdge(cube, DOWN, FRONT);
    Move(cube, DOWN_CHAR);
    SolveEdge(cube, DOWN, LEFT);
    Move(cube, DOWN_CHAR);
    SolveEdge(cube, DOWN, BACK);
    Move(cube, DOWN_CHAR);
    SolveEdge(cube, DOWN, RIGHT);
    Move(cube, DOWN_CHAR);
}

void Solve(Cube * cube) {

    cube -> Solving = true;

    SolveCross(cube);

    cube -> Solving = false;
}