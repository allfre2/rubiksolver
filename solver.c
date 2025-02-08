#include "common.h"
#include "solver.h"

const char MOVE_DOWN = _DOWN;

const char CROSS_EDGE_ALGORITHMS[ EDGE_COUNT * EDGE_ORIENTATIONS ][8] = {
    {},
    { _DOWN, _RIGHT, _DOWN_I, _FRONT },
    { _DOWN_I, _FRONT_I, _DOWN, _FRONT },
    { _RIGHT, _FRONT }, 
    { _BACK, _BACK, _UP, _UP, _FRONT, _FRONT },
    { _DOWN_I, _RIGHT, _DOWN, _FRONT },
    { _DOWN, _FRONT, _DOWN_I, _FRONT_I },
    { _LEFT_I, _FRONT_I },
    { _DOWN_I, _LEFT, _DOWN },
    { _FRONT_I },
    { _UP, _LEFT, _FRONT_I, _LEFT_I }, 
    { _FRONT, _FRONT },
    { _RIGHT, _UP, _RIGHT_I, _FRONT, _FRONT },
    { _FRONT }, 
    { _RIGHT_I, _UP, _RIGHT, _FRONT, _FRONT },
    { _RIGHT, _RIGHT, _FRONT, _RIGHT, _RIGHT },
    { _LEFT, _UP_I, _LEFT_I, _FRONT, _FRONT },
    { _LEFT, _LEFT, _FRONT_I, _LEFT, _LEFT },
    { _UP_I, _FRONT, _FRONT },
    { _LEFT, _FRONT_I, _LEFT_I },
    { _UP, _UP, _FRONT, _FRONT },
    { _UP, _RIGHT_I, _FRONT, _RIGHT },
    { _UP, _FRONT, _FRONT },
    { _RIGHT_I, _FRONT, _RIGHT }
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
    Move(cube, _DOWN);
    SolveEdge(cube, DOWN, LEFT);
    Move(cube, _DOWN);
    SolveEdge(cube, DOWN, BACK);
    Move(cube, _DOWN);
    SolveEdge(cube, DOWN, RIGHT);
    Move(cube, _DOWN);
}

void Solve(Cube * cube) {

    cube -> Solving = true;

    SolveCross(cube);

    cube -> Solving = false;
}