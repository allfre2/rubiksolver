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

const char F2L_ALGORITHMS[ CORNER_COUNT * CORNER_ORIENTATIONS ][ EDGE_COUNT * EDGE_ORIENTATIONS ][24] = {
    {
        {},{},{},{},{},{},{},{},{},{},
        "URurufUF",
        {},{},
        "RurUfUUFUfUUF",
        {},{},{},{},{},{},{},{},{},
        "ufUFURur"
    },
    {
        {},{},{},{},{},{},{},{},{},{},
        "fuFUfuF",
        {},
        "RuruRUruRUUr",
        "RurUfuFufuF",
        {},{},{},{},{},{},{},{},{},
        "RurURur"
    },
    {
        {},{},{},{},{},{},{},{},{},{},
        "fUFufUF",
        {},
        "RurURUUrURur",
        "RUruRurUUfuF",
        {},{},{},{},{},{},{},{},{},
        "RuruRUr"
    },

    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},

    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},

    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},

    {
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {},
        "fUUFUfuF",
        "RUruuRUruRUr",
        "RUruRUruRUr", 
        "RurUfUF",
        {}, {}, {}, {},
        "UURUrURur",
        "ufUUFufUF",
        "URUUrURur",
        "UUfuFufUF",
        "RUUruRUr",
        "fuFUUfuFUfuF",
    },
    {
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {},
        "ufUF",
        "UfUUFuRUr",
        "UfUFUfUUF",
        "UfuFuRUr",
        {}, {}, {}, {},
        "uRUrURUr",
        "UfuFUfUUF", 
        "RUr",
        "UfUUFUfUUF",
        "uRurURUr",
        "RurUUfuF", 
    },
    {
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, 
        "UfUFufuF",
        "fUFuuRUr",
        "uRuruRUUr",
        "uRUrUfuF",
        {}, {}, {}, {},
        "uRUUruRUUr",
        "fuF", 
        "uRUruRUUr",
        "UfuFufuF",
        "URur",
        "uRUUrUfuF", 
    },

    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},

    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},

    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
    { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},},
};

bool HasValidCross(Cube * cube) {

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

bool CornerEdgeIsSolved(Cube * cube, u_int face1, u_int face2, u_int face3) {
    u_int cubeFace1 = GetFace(cube, face1);
    u_int cubeFace2 = GetFace(cube, face2);
    u_int cubeFace3 = GetFace(cube, face3);

    u_int cornerSquare1 = GetSquare(cube, face1, 5);
    u_int cornerSquare2 = GetSquare(cube, face2, 7);
    u_int cornerSquare3 = GetSquare(cube, face3, 3);
    u_int edgeSquare1 = GetSquare(cube, face1, 4);
    u_int edgeSquare2 = GetSquare(cube, face2, 8);

    u_int cornerColor1 = SQUARE_COLOR(cube -> Faces [cubeFace1], cornerSquare1);
    u_int cornerColor2 = SQUARE_COLOR(cube -> Faces [cubeFace2], cornerSquare2);
    u_int cornerColor3 = SQUARE_COLOR(cube -> Faces [cubeFace3], cornerSquare3);

    u_int edgeColor1 = SQUARE_COLOR(cube -> Faces [cubeFace1], edgeSquare1);
    u_int edgeColor2 = SQUARE_COLOR(cube -> Faces [cubeFace2], edgeSquare2);

    return
        cornerColor1 == cubeFace1
        && cornerColor2 == cubeFace2
        && cornerColor3 == cubeFace3
        && edgeColor1 == cubeFace1
        && edgeColor2 == cubeFace2;
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

        u_int rotatedFace1 = GetFace(cube, lookup[0]);
        u_int rotatedFace2 = GetFace(cube, lookup[2]);
        u_int rotatedFace3 = GetFace(cube, lookup[4]);
        u_int square1 = GetSquare(cube, lookup[0], lookup [1]);
        u_int square2 = GetSquare(cube, lookup[2], lookup [3]);
        u_int square3 = GetSquare(cube, lookup[4], lookup [5]);

        u_int color1 = SQUARE_COLOR((cube -> Faces [ rotatedFace1 ]), square1);
        u_int color2 = SQUARE_COLOR((cube -> Faces [ rotatedFace2 ]), square2);
        u_int color3 = SQUARE_COLOR((cube -> Faces [ rotatedFace3 ]), square3);

        if (rotatedFace1 == color1 && rotatedFace2 == color2 && rotatedFace3 == color3) {
            return i;
        }
    }

    return ALGORITHM_NOT_FOUND;
}

char * LookupCrossEdgeAlgorithm(Cube * cube, u_int face1, u_int face2) {
    int index = LookupEdgeIndex(cube, face1, face2);

    if (index == ALGORITHM_NOT_FOUND) return ALGORITHM_NOT_FOUND;

    return CROSS_EDGE_ALGORITHMS [index];    
}

char * LookupF2LAlgorithm(Cube * cube, u_int face1, u_int face2, u_int face3) {
    int corner = LookupCornerIndex(cube, face1, face2, face3);

    if (corner == ALGORITHM_NOT_FOUND) return ALGORITHM_NOT_FOUND;

    int edge = LookupEdgeIndex(cube, face1, face2);

    if (edge == ALGORITHM_NOT_FOUND) return ALGORITHM_NOT_FOUND;

    return & (F2L_ALGORITHMS [ corner ][ edge ]);
}

void SolveEdge(Cube * cube, u_int face1, u_int face2) {
    char * algorithm = LookupCrossEdgeAlgorithm(cube, face1, face2);

    if (algorithm == ALGORITHM_NOT_FOUND) {
        printf("\n(!) Algorithm not found!\n");
        return;
    }

    ApplyAlgorithm(cube, algorithm);
}

int SolveCornerEdge(Cube * cube, u_int face1, u_int face2, u_int face3) {
    char * algorithm = LookupF2LAlgorithm(cube, face1, face2, face3);

    if (algorithm == ALGORITHM_NOT_FOUND || *algorithm == 0) {
        printf("\n(!) Algorithm not found!\n");
        return ALGORITHM_NOT_FOUND;
    }

    ApplyAlgorithm(cube, algorithm);

    return algorithm;
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

    u_int rotations[4] = { FRONT, LEFT, BACK, RIGHT };
    int currentRotation = 0;

    int missed = 0;

    while (currentRotation < 4) {

        u_int rotation = rotations[currentRotation];

        cube -> Rotation = rotation;
        
        int found = ALGORITHM_NOT_FOUND;
        
        if (!CornerEdgeIsSolved(cube, FRONT, RIGHT, DOWN)) {
            found = SolveCornerEdge(cube, FRONT, RIGHT, DOWN);
        }

        ++currentRotation;
    }

    cube -> Rotation = FRONT;
}

void Solve(Cube * cube) {

    cube -> Solving = true;

    SolveCross(cube);

    SolveF2L(cube);

    cube -> Solving = false;

    CleanSolution(cube);
}
