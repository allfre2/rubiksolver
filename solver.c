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

const char F2L_ALGORITHMS[ CORNER_COUNT * CORNER_ORIENTATIONS ][ EDGE_COUNT * EDGE_ORIENTATIONS ] = {
    // FILL THIS UP
};

bool HasValidCross(Cube * cube) {

    // Get A lookup table ?
    u_int color1, color2;

    color1 = SQUARE_COLOR(cube -> Faces [DOWN], 2);
    color2 = SQUARE_COLOR(cube -> Faces [FRONT], 6);

    if (color1 != DOWN || color2 != FRONT) return false;

    color1 = SQUARE_COLOR(cube -> Faces [DOWN], 8);
    color2 = SQUARE_COLOR(cube -> Faces [LEFT], 6);

    if (color1 != DOWN || color2 != LEFT) return false;

    color1 = SQUARE_COLOR(cube -> Faces [DOWN], 6);
    color2 = SQUARE_COLOR(cube -> Faces [BACK], 6);

    if (color1 != DOWN || color2 != BACK) return false;

    color1 = SQUARE_COLOR(cube -> Faces [DOWN], 4);
    color2 = SQUARE_COLOR(cube -> Faces [RIGHT], 8);

    if (color1 != DOWN || color2 != RIGHT) return false;

    return true;
}

int LookupEdgeIndex(Cube * cube, u_int face1, u_int face2) {
    for (int i = 0; i < EDGE_COUNT * EDGE_ORIENTATIONS; ++i) {
        u_int * lookup = EDGE_LOOKUP_TABLE [ i ];

        u_int cubeFace1 = GetFace(cube, lookup [0]);
        u_int square1 = GetSquare(cube, lookup[0], lookup [1]);
        u_int cubeFace2 = GetFace(cube, lookup [2]);
        u_int square2 = GetSquare(cube, lookup[2], lookup [3]);

        u_int color1 = SQUARE_COLOR((cube -> Faces [ cubeFace1 ]), square1);
        u_int color2 = SQUARE_COLOR((cube -> Faces [ cubeFace2 ]), square2);

        u_int rotatedFace1 = GetFace(cube, face1);
        u_int rotatedFace2 = GetFace(cube, face2);

        if (rotatedFace1 == color1 && rotatedFace2 == color2) {
            return i;
        }
    }

    return ALGORITHM_NOT_FOUND;
}

int LookupCornerIndex(Cube * cube, u_int face1, u_int face2, u_int face3) {
    for (int i = 0; i < CORNER_COUNT * CORNER_ORIENTATIONS; ++i) {
        u_int * lookup = CORNER_LOOKUP_TABLE [ i ];

        u_int color1 = SQUARE_COLOR((cube -> Faces [ (lookup [0]) ]), lookup [1]);
        u_int color2 = SQUARE_COLOR((cube -> Faces [ (lookup [2]) ]), lookup [3]);
        u_int color3 = SQUARE_COLOR((cube -> Faces [ (lookup [4]) ]), lookup [5]);

        if (face1 == color1 && face2 == color2 && face3 == color3) {
            return i;
        }
    }

    return ALGORITHM_NOT_FOUND;
}

int LookupCrossEdgeAlgorithm(Cube * cube, u_int face1, u_int face2) {
    return LookupEdgeIndex(cube, face1, face2);    
}

char * LookupF2LAlgorithm(Cube * cube, u_int face1, u_int face2, u_int face3) {
    int corner = LookupCornerIndex(cube, face1, face2, face3);

    if (corner == ALGORITHM_NOT_FOUND) return ALGORITHM_NOT_FOUND;

    int edge = LookupEdgeIndex(cube, face1, face2);

    if (edge == ALGORITHM_NOT_FOUND) return ALGORITHM_NOT_FOUND;

    return & (F2L_ALGORITHMS [ corner ][ edge ]);
}

void SolveEdge(Cube * cube, u_int face1, u_int face2) {
    int algorithm = LookupCrossEdgeAlgorithm(cube, face1, face2);

    if (algorithm == ALGORITHM_NOT_FOUND) {
        printf("\n(!) Algorithm not found!\n");
    }

    ApplyAlgorithm(cube, CROSS_EDGE_ALGORITHMS [algorithm]);
}

void SolveCross(Cube * cube) {

    if (HasValidCross(cube)) return;

    SolveEdge(cube, DOWN, FRONT);
    cube -> Rotation = LEFT;
    SolveEdge(cube, DOWN, FRONT);
    cube -> Rotation = BACK;
    SolveEdge(cube, DOWN, FRONT);
    cube -> Rotation = RIGHT;
    SolveEdge(cube, DOWN, FRONT);
    cube -> Rotation = FRONT;
}

void SolveF2L(Cube * cube) {

}

void Solve(Cube * cube) {

    cube -> Solving = true;

    SolveCross(cube);

    SolveF2L(cube);

    cube -> Solving = false;

    CleanSolution(cube);
}
