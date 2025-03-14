#include "common.h"
#include <stdio.h>

bool debug_enabled = false;

#if defined(_WIN32) || defined(_WIN64)
    bool use_terminal_colors = false;
#else
    bool use_terminal_colors = true;
#endif

const u_int COlOR_ARRANGEMENTS[SIDES][SIDES] = {
    { FRONT, RIGHT, UP, LEFT, DOWN, BACK },
    { DOWN, FRONT, LEFT, BACK, RIGHT, UP },
    { DOWN, RIGHT, FRONT, LEFT, BACK, UP },
    { DOWN, BACK, RIGHT, FRONT, LEFT, UP },
    { DOWN, LEFT, BACK, RIGHT, FRONT, UP },
    { BACK, RIGHT, DOWN, LEFT, UP, FRONT },
};

const char LEGAL_MOVES[] = {
    _DOWN, _RIGHT, _FRONT, _LEFT, _BACK, _UP,
    _DOWN_I, _RIGHT_I, _FRONT_I, _LEFT_I, _BACK_I, _UP_I,
    0
};

const char LEGAL_COLORS[] = {
    WHITE_CHAR,
    GREEN_CHAR,
    RED_CHAR,
    BLUE_CHAR,
    ORANGE_CHAR,
    YELLOW_CHAR
};

void EnableDebug(bool flag) {
    debug_enabled = flag;
}

int Strlen(char * str) {
    int i = 0;
    while (str[i]) {
        ++i;
    }

    return i;
}

bool StrCmp(char * a, char * b) {
    while (*a && *a == *b) {
        ++a;
        ++b;
    }

    if (*a == *b) return true;

    return false;
}

bool IsLower(char * c) {
    return c >= 'a' && c <= 'z';
}

char ToLower(char c) {
    return c + ((char)32);
}

char SwitchCase(char c) {
    if (IsLower(c)) {
        return c - ((char)32);
    } else {
        return c + ((char)32);
    }
}

void Init() {

    SetOrder(DEFAULT_ORDER);
    
    SetColors(DEFAULT_ROTATION);

    SetFaceValues();
    
    SetRepresentationPatterns();
    
    SetSolvedPosition();
    
    for (int sq = 1; sq < FACE_SQUARE_COUNT+1; ++sq) {
        FACE_SQUARE_MASKS [ sq ] = ~ (SQUARE_FIRST_BYTE << (SQUARE_SIZE * (FACE_SQUARE_COUNT - sq)));
    }
}

const u_int ADJACENT_SIDES[SIDES][4] = {
    { FRONT, RIGHT, BACK, LEFT }, // DOWN
    { UP, BACK, DOWN, FRONT },    // RIGHT
    { UP, RIGHT, DOWN, LEFT },    // FRONT
    { UP, FRONT, DOWN, BACK },    // LEFT
    { UP, LEFT, DOWN, RIGHT },    // BACK
    { BACK, RIGHT, FRONT, LEFT} , // UP
};

const int ADJACENT_SQUARES[SIDES][4][3] = {
    {
        {7,6,5}, {7,6,5}, {7,6,5}, {7,6,5}   // DOWN
    },
    {
        {5,4,3}, {1,8,7}, {5,4,3}, {5,4,3}   // RIGHT
    },
    {
        {7, 6, 5}, {1,8,7}, {3,2,1}, {5,4,3} // FRONT
    },
    {
        {1,8,7}, {1,8,7}, {1,8,7}, {5,4,3}   // LEFT
    },
    {
        {3,2,1}, {1,8,7}, {7,6,5}, {5,4,3}   // BACK
    },
    {
        {3,2,1}, {3,2,1}, {3,2,1}, {3,2,1}   // UP
    },
};

const u_int FACE_ROTATIONS[SIDES][SIDES] = {
    { BACK, RIGHT, DOWN, LEFT, UP, FRONT }, // DOWN Rotation
    { DOWN, BACK, RIGHT, FRONT, LEFT, UP }, // RIGHT Rotation
    { DOWN, RIGHT, FRONT, LEFT, BACK, UP }, // FRONT Rotation (Default rotation)
    { DOWN, FRONT, LEFT, BACK, RIGHT, UP }, // LEFT Rotation
    { DOWN, LEFT, BACK, RIGHT, FRONT, UP }, // BACK Rotation
    { FRONT, RIGHT, UP, LEFT, DOWN, BACK }, // UP Rotation
};

const u_int EDGE_LOOKUP_TABLE[ EDGE_COUNT * EDGE_ORIENTATIONS ][4] = {
    { DOWN, 2, FRONT, 6 },
    { FRONT, 6, DOWN, 2 },
    { DOWN, 4, RIGHT, 6 },
    { RIGHT, 6, DOWN, 4 },
    { DOWN, 6, BACK, 6 },
    { BACK, 6, DOWN, 6 },
    { DOWN, 8, LEFT, 6 },
    { LEFT, 6, DOWN, 8 },
    { FRONT, 8, LEFT, 4 },
    { LEFT, 4, FRONT, 8 },
    { FRONT, 2, UP, 6 },
    { UP, 6, FRONT, 2 },
    { FRONT, 4, RIGHT, 8 },
    { RIGHT, 8, FRONT, 4 },
    { BACK, 8, RIGHT, 4 },
    { RIGHT, 4, BACK, 8 },
    { BACK, 4, LEFT, 8 },
    { LEFT, 8, BACK, 4 },
    { UP, 8, LEFT, 2 },
    { LEFT, 2, UP, 8 },
    { UP, 2, BACK, 2 },
    { BACK, 2, UP, 2 },
    { UP, 4, RIGHT, 2 },
    { RIGHT, 2, UP, 4 },
};

const u_int CORNER_LOOKUP_TABLE[ CORNER_COUNT * CORNER_ORIENTATIONS ][6] = {
    { FRONT, 5, RIGHT, 7, DOWN, 3 },
    { RIGHT, 7, DOWN, 3, FRONT, 5 },
    { DOWN, 3, FRONT, 5, RIGHT, 7 },

    { LEFT, 5, FRONT, 7, DOWN, 1 },
    { FRONT, 7, DOWN, 1, LEFT, 5 },
    { DOWN, 1, LEFT, 5, FRONT, 7 },

    { BACK, 5, LEFT, 7, DOWN, 7 },
    { LEFT, 7, DOWN, 7, BACK, 5 },
    { DOWN, 7, BACK, 5, LEFT, 7 },

    { RIGHT, 5, BACK, 7, DOWN, 5 },
    { BACK, 7, DOWN, 5, RIGHT, 5 },
    { DOWN, 5, RIGHT, 7, BACK, 7 },

    { RIGHT, 1, FRONT, 3, UP, 5 },
    { FRONT, 3, UP, 5, RIGHT, 1 },
    { UP, 5, RIGHT, 1, FRONT, 3 },

    { FRONT, 1, LEFT, 3, UP, 7 },
    { LEFT, 3, UP, 7, FRONT, 1 },
    { UP, 7, FRONT, 1, LEFT, 3 },

    { LEFT, 1, BACK, 3, UP, 1 },
    { BACK, 3, UP, 1, LEFT, 1 },
    { UP, 1, LEFT, 1, BACK, 3 },

    { BACK, 1, RIGHT, 3, UP, 3 },
    { RIGHT, 3, UP, 3, BACK, 1 },
    { UP, 3, BACK, 1, RIGHT, 3 },
};

bool IsLegalChar(char c) {
    int i = 0;

    while (i < SIDES) {
        if (LEGAL_COLORS[i] == c) return true;
        ++i;
    }

    return false;
}

bool IsLegalMove(char c) {
    int i = 0;

    while (i < (SIDES*2)) {
        if (LEGAL_MOVES[i] == c) return true;
        ++i;
    }

    return false;
}

bool IsValidCubeString(char * string) {

    if (Strlen(string) != CUBE_REPRESENTATION_LENGTH) return false;

    int i = 0;

    while (string[i]) {
        if (!IsLegalChar(string[i])) return false;
        ++i;
    }

    return true;
}

bool IsValidMoveString(char * str) {
    while(*str) {
        if (!IsLegalMove(*str)) return false;
        ++str;
    }

    return true;
}

u_int GetColorValue(char color_char) {
    switch (color_char) {
        case WHITE_CHAR:
            return WHITE;
        break;
        case GREEN_CHAR:
            return GREEN;
        break;
        case RED_CHAR:
            return RED;
        break;
        case BLUE_CHAR:
            return BLUE;
        break;
        case ORANGE_CHAR:
            return ORANGE;
        break;
        case YELLOW_CHAR:
            return YELLOW;
        break;
    }
}

const u_int DEFAULT_ORDER[SIDES] = {
    LEFT,
    FRONT,
    RIGHT,
    BACK,
    UP,
    DOWN
};

void InitCube(Cube * cube) {
    ParseCube(SOLVED_POSITION, cube);
    cube -> Solved = true;
}

void ParseCube(char * position, Cube * cube) {

    cube -> Faces = malloc(sizeof(u_int) * SIDES);
    memset(cube -> Faces, 0, sizeof(u_int) * SIDES);

    cube -> Scramble = malloc(sizeof(char) * MAXIMUM_SCRAMBLE_LENGTH);
    memset(cube -> Scramble, 0, sizeof(char) * MAXIMUM_SCRAMBLE_LENGTH);

    cube -> Solution = malloc(sizeof(char) * MAXIMUM_SOLUTION_LENGTH);
    memset(cube -> Solution, 0, sizeof(char) * MAXIMUM_SOLUTION_LENGTH);

    cube -> scrambleIndex = 0;
    cube -> solutionIndex = 0;
    cube -> Scrambling = false;
    cube -> Solving = false;
    cube -> Rotation = FRONT;

    cube -> OriginalSolution = 0;

    int i = 0;
    int face = 0;
    int square = 1;

    while (position[i]) {

        u_int color = GetColorValue ( position [i] );

        SET_SQUARE_COLOR(
            cube -> Faces [ ORDER [ face ] ],
            square,
            color
        );

        face = (square == FACE_SQUARE_COUNT) ? (face + 1) : face;
        square = (square == FACE_SQUARE_COUNT) ? 1 : square + 1;
        ++i;
    }

    return cube;
}

void SetOrder(u_int * order) {
    for (int i = 0; i < SIDES; ++i) {
        ORDER [i] = order [i];
    }
}

void SetColors(u_int rotation) {

    u_int * arrangement = COlOR_ARRANGEMENTS [rotation];

    WHITE  = arrangement[0];
    GREEN  = arrangement[1];
    RED    =  arrangement[2];
    BLUE   =  arrangement[3];
    ORANGE = arrangement[4];
    YELLOW = arrangement[5];

    COLOR_CHARS[WHITE]  = WHITE_CHAR;
    COLOR_CHARS[GREEN]  = GREEN_CHAR;
    COLOR_CHARS[RED]    = RED_CHAR;
    COLOR_CHARS[BLUE]   = BLUE_CHAR;
    COLOR_CHARS[ORANGE] = ORANGE_CHAR;
    COLOR_CHARS[YELLOW] = YELLOW_CHAR;
    
    COLOR_NAMES[WHITE]  = "White";
    COLOR_NAMES[GREEN]  = "Green";
    COLOR_NAMES[RED]    = "Red";
    COLOR_NAMES[BLUE]   = "Blue";
    COLOR_NAMES[ORANGE] = "Orange";
    COLOR_NAMES[YELLOW] = "Yellow";
    
    COLOR_CODES[WHITE]  = "\e[0;107m";
    COLOR_CODES[GREEN]  = "\e[0;102m";
    COLOR_CODES[RED]    = "\e[0;101m";
    COLOR_CODES[BLUE]   = "\e[0;104m";
    COLOR_CODES[ORANGE] = "\e[0m";
    COLOR_CODES[YELLOW] = "\e[43m";
    RESET_COLOR_CODE = "\e[0m";
}

void SetFaceValues() {
    FACE_CHARS[DOWN]  = _DOWN;
    FACE_CHARS[RIGHT] = _RIGHT;
    FACE_CHARS[FRONT] = _FRONT;
    FACE_CHARS[LEFT]  = _LEFT;
    FACE_CHARS[BACK]  = _BACK;
    FACE_CHARS[UP]    = _UP;
    
    MOVE_FACES [ _DOWN ]    = DOWN;
    MOVE_FACES [ _RIGHT ]   = RIGHT;
    MOVE_FACES [ _FRONT ]   = FRONT;
    MOVE_FACES [ _LEFT ]    = LEFT;
    MOVE_FACES [ _BACK ]    = BACK;
    MOVE_FACES [ _UP ]      = UP;
    MOVE_FACES [ _DOWN_I ]  = DOWN;
    MOVE_FACES [ _RIGHT_I ] = RIGHT;
    MOVE_FACES [ _FRONT_I ] = FRONT;
    MOVE_FACES [ _LEFT_I ]  = LEFT;
    MOVE_FACES [ _BACK_I ]  = BACK;
    MOVE_FACES [ _UP_I ]    = UP;
}

void SetRepresentationPatterns() {
    RepresentationPattern[0][0] = EMPTY_FACE;
    RepresentationPattern[0][1] = UP;
    RepresentationPattern[0][2] = EMPTY_FACE;
    RepresentationPattern[0][3] = EMPTY_FACE;
    
    RepresentationPattern[1][0] = LEFT;
    RepresentationPattern[1][1] = FRONT;
    RepresentationPattern[1][2] = RIGHT;
    RepresentationPattern[1][3] = BACK;
    
    RepresentationPattern[2][0] = EMPTY_FACE;
    RepresentationPattern[2][1] = DOWN;
    RepresentationPattern[2][2] = EMPTY_FACE;
    RepresentationPattern[2][3] = EMPTY_FACE;
    
    SquareRepresentationPattern[0][0] = 1;
    SquareRepresentationPattern[0][1] = 2;
    SquareRepresentationPattern[0][2] = 3;
    SquareRepresentationPattern[1][0] = 8;
    SquareRepresentationPattern[1][1] = CENTER_SQUARE;
    SquareRepresentationPattern[1][2] = 4;
    SquareRepresentationPattern[2][0] = 7;
    SquareRepresentationPattern[2][1] = 6;
    SquareRepresentationPattern[2][2] = 5;
}

void SetSolvedPosition() {
    int positionIndex = 0;
    for (int i = 0; ORDER [i]; ++i) {
        for (int j = 0; j < FACE_SQUARE_COUNT; ++j) {
            SOLVED_POSITION [positionIndex++] = COLOR_CHARS [ ORDER [i] ];
        }
    }
    SOLVED_POSITION[positionIndex] = 0;
}

void PrintPositionString(Cube * cube) {
    for (int i = 0; i < SIDES; ++i) {
        for (int square = 1; square <= 8; ++square) {
            u_int color = SQUARE_COLOR(cube -> Faces [ ORDER [ i ] ], square);
            printf("%c", COLOR_CHARS [ color ]);
        }
    }
}

void PrintStandardNotation(char * str) {
    int i = 0;
    while (str [i]) {
        char c = IsLower(str[i]) ? SwitchCase(str[i]) : str[i];
        
        if (str [i+1] && str[i] == str[i+1]) {
            printf("%c2 ", c);
            i += 2;
        } else {
            printf("%c%c ", c, IsLower(str[i]) ? '\'' : 0);
            ++i;
        }
    }
}

void PrintColorNames() {
    for (int i = 0; i < SIDES; ++i) {
        if (use_terminal_colors) {
            printf("%s: %c %s%c%s\n",
                COLOR_NAMES [ ORDER [ i ] ],
                COLOR_CHARS [ ORDER [ i ] ],
                COLOR_CODES [ ORDER [ i ] ],
                ' ',
                RESET_COLOR_CODE);
        } else {
            printf("%s: %c\n",
                COLOR_NAMES [ ORDER [ i ] ],
                COLOR_CHARS [ ORDER [ i ] ]);    
        }
    }
}

void PrintFaceOrder() {
    int i = 0;
    while (i < SIDES) {
        if (use_terminal_colors) {
            printf("%s%c%s",
                COLOR_CODES [ ORDER [ i ] ],
                COLOR_CHARS [ ORDER [ i ] ],
                RESET_COLOR_CODE);
        } else {
            printf("%c", COLOR_CHARS [ ORDER [ i ] ]);
        }

        ++i;
    }
}

void PrintFaceRow(Cube * cube, u_int face, int face_row) {

    int
        square1 = SquareRepresentationPattern[face_row][0],
        square2 = SquareRepresentationPattern[face_row][1],
        square3 = SquareRepresentationPattern[face_row][2];

    u_int 
        color1 = SQUARE_COLOR( cube -> Faces [face], square1 ),
        color2 = SQUARE_COLOR( cube -> Faces [face], square2 ),
        color3 = SQUARE_COLOR( cube -> Faces [face], square3 );

    char
        * code1,
        * code2,
        * code3;
    
    if (use_terminal_colors) {
        code1 = COLOR_CODES [ color1 ];
        code2 = (square2 == CENTER_SQUARE) ? COLOR_CODES [ face ] : COLOR_CODES [ color2 ];
        code3 = COLOR_CODES [ color3 ];
    }

    char
        char1 = COLOR_CHARS [ color1 ],
        char2 = (square2 == CENTER_SQUARE) ? FACE_CHARS [ face ] :  COLOR_CHARS [ color2 ],
        char3 = COLOR_CHARS [ color3 ];

    if (use_terminal_colors)
    {
        printf("%s%c", code1, EMPTY_SQUARE_CHAR);
        printf("%s%c", code2, (square2 == CENTER_SQUARE) ? char2 : EMPTY_SQUARE_CHAR);
        printf("%s%c", code3, EMPTY_SQUARE_CHAR);
        printf("%s", RESET_COLOR_CODE);
    } else {
        printf("%c%c%c", char1, char2, char3);
    }
}

void PrintCubeRepresentation(Cube * cube) {
        
    printf("\n");
        
    for (int row = 0; row < 3; ++row) {
        for (int face_row = 0; face_row < 3; ++face_row) {
            for (int column = 0; column < 4; ++column) {

                u_int face = RepresentationPattern[row][column];

                if (face == EMPTY_FACE) {
                    printf("    ");
                    continue;
                }

                PrintFaceRow(cube, face, face_row);
                printf(" ");
            }

            printf("\n");
        }

        printf("\n");
    }
}

void PrintInvalidRepresentationMessage() {
        printf("\n\nYou must provide a valid cube representation string.\n\n");        
        
        PrintColorNames();

        printf("\nFace Order is: ");
        PrintFaceOrder();

        if (use_terminal_colors) {
            printf("\n\nTOP: %s%c%s, FRONT: %s%c%s",
                COLOR_CODES [ UP ],
                COLOR_CHARS [ UP ],
                RESET_COLOR_CODE,
                COLOR_CODES [ FRONT ],
                COLOR_CHARS [ FRONT ],
                RESET_COLOR_CODE);
        } else {
            printf("\n\nTOP: %c, FRONT: %c",
                COLOR_CHARS [ UP ],
                COLOR_CHARS [ FRONT ]);
        }

        printf("\n\n");
}

void PrintValidMoves() {
    for (int i = 0; i < SIDES*2; ++i) {
        printf("%c ", LEGAL_MOVES [i]);
    }
}

void PrintInvalidMovesMessage() {
    printf("\n\nYou must provide valid moves.\n\n");

    printf("\n Valid moves are: ");
    PrintValidMoves();
    printf("\n\n");
}

u_int GetFace(Cube * cube, u_int face) {
    return FACE_ROTATIONS [cube -> Rotation] [face];
}

u_int GetSquare(Cube * cube, u_int face, u_int square) {
    switch (cube -> Rotation)
    {
        case DOWN:
            switch (face) {
                case DOWN: return ROTATE_SQUARE_180(square);
                case RIGHT: return ROTATE_SQUARE_90(square);
                case LEFT: return ROTATE_SQUARE_270(square);
                case BACK: return ROTATE_SQUARE_180(square);
            }
        break;
        case RIGHT:
            switch (face) {
                case DOWN: return ROTATE_SQUARE_270(square);
                case UP: return ROTATE_SQUARE_90(square);
            }
        break;
        case LEFT:
            switch (face) {
                case DOWN: return ROTATE_SQUARE_90(square);
                case UP: return ROTATE_SQUARE_270(square);
            }
        break;
        case BACK:
            switch (face) {
                case DOWN: return ROTATE_SQUARE_180(square);
                case UP: return ROTATE_SQUARE_180(square);
            }
        break;
        case UP:
            switch (face) {
                case RIGHT: return ROTATE_SQUARE_270(square);
                case LEFT: return ROTATE_SQUARE_90(square);
                case BACK: return ROTATE_SQUARE_90(square);
                case UP: return ROTATE_SQUARE_180(square);
            }
        break;
    }

    return square;
}

char GetMove(Cube * cube, char move) {
    switch (cube -> Rotation) {

        case DOWN:
            switch (move) {
                case _DOWN: return _BACK; break;
                case _FRONT: return _DOWN; break;
                case _BACK: return _UP; break;
                case _UP: return _FRONT; break;
                case _DOWN_I: return _BACK_I; break;
                case _FRONT_I: return _DOWN_I; break;
                case _BACK_I: return _UP_I; break;
                case _UP_I: return _FRONT_I; break;
            }
        break;

        case RIGHT:
            switch (move) {
                case _FRONT: return _RIGHT; break;
                case _BACK: return _LEFT; break;
                case _LEFT: return _FRONT; break;
                case _RIGHT: return _BACK; break;
                case _FRONT_I: return _RIGHT_I; break;
                case _BACK_I: return _LEFT_I; break;
                case _LEFT_I: return _FRONT_I; break;
                case _RIGHT_I: return _BACK_I; break;
            }
        break;

        case FRONT:

        break;

        case LEFT:
            switch (move) {
                case _FRONT: return _LEFT; break;
                case _BACK: return _RIGHT; break;
                case _LEFT: return _BACK; break;
                case _RIGHT: return _FRONT; break;
                case _FRONT_I: return _LEFT_I; break;
                case _BACK_I: return _RIGHT_I; break;
                case _LEFT_I: return _BACK_I; break;
                case _RIGHT_I: return _FRONT_I; break;
            }
        break;

        case BACK:
            switch (move) {
                case _FRONT: return _BACK; break;
                case _BACK: return _FRONT; break;
                case _LEFT: return _RIGHT; break;
                case _RIGHT: return _LEFT; break;
                case _FRONT_I: return _BACK_I; break;
                case _BACK_I: return _FRONT_I; break;
                case _LEFT_I: return _RIGHT_I; break;
                case _RIGHT_I: return _LEFT_I; break;
            }
        break;

        case UP:
            switch (move) {
                case _DOWN: return _FRONT; break;
                case _FRONT: return _UP; break;
                case _BACK: return _DOWN; break;
                case _UP: return _BACK; break;
                case _DOWN_I: return _FRONT_I; break;
                case _FRONT_I: return _UP_I; break;
                case _BACK_I: return _DOWN_I; break;
                case _UP_I: return _BACK_I; break;
            }
        break;
    }

    return move;
}

void Scramble(Cube * cube) {
    
    cube -> Solved = false;
    cube -> Scrambling = true;

    srand(time(0));
    int size = MAXIMUM_SCRAMBLE_LENGTH;
    int i = 0;

    while (i++ < size) {
        Move(cube, LEGAL_MOVES [rand() % (SIDES * 2)]);
    }

    cube -> Scrambling = false;
}

void ApplyAlgorithm(Cube * cube, char * move) {
    while (*move) {
        Move(cube, *move);
        ++move;
    }
}

void Move(Cube * cube, char move) {

    move = GetMove(cube, move);

    if (cube -> Solving) {
        if (cube -> solutionIndex == MAXIMUM_SOLUTION_LENGTH) {
            printf("\n(!) Solution buffer is full!\n");
            return; //TODO: handle error
        }
        cube -> Solution [cube -> solutionIndex] = move;
        cube -> solutionIndex++;
    }
    
    if (cube -> Scrambling) {
        if (cube -> scrambleIndex == MAXIMUM_SCRAMBLE_LENGTH) {
            printf("\n(!) Scramble buffer is full!\n");
            return; // Same
        }
        cube -> Scramble [cube -> scrambleIndex] = move;
        cube -> scrambleIndex++;
    }

    bool inverted = IsLower(move);
    Rotate(cube, MOVE_FACES [ move ], inverted);
}

void Rotate(Cube * cube, u_int face, bool inverted) {

    if (inverted) {
        cube -> Faces [face] = ROTATE_LEFT(cube -> Faces [face]);
    } else {
        cube -> Faces [face] = ROTATE_RIGHT(cube -> Faces [face]);
    }

    RotateSides(cube, face, inverted);
}

void RotateSides(Cube * cube, u_int face, bool inverted) {
    u_int * adjacentSides = ADJACENT_SIDES [ face ];

    u_int faces[SIDES];
    memcpy(faces, cube -> Faces, sizeof(u_int) * SIDES);

    if (inverted) {
        RotateSquares(cube, &faces, face, 3, 2);
        RotateSquares(cube, &faces, face, 2, 1);
        RotateSquares(cube, &faces, face, 1, 0);
        RotateSquares(cube, &faces, face, 0, 3);
    } else {
        RotateSquares(cube, &faces, face, 0, 1);
        RotateSquares(cube, &faces, face, 1, 2);
        RotateSquares(cube, &faces, face, 2, 3);
        RotateSquares(cube, &faces, face, 3, 0);
    }
}

void RotateSquares(Cube * cube, u_int * faces, u_int face, int source, int destination) {

        u_int * adjacentSides = ADJACENT_SIDES [ face ];

        int * sourceSquares = ADJACENT_SQUARES[face][source];
        int * destinationSquares = ADJACENT_SQUARES[face][destination];

        u_int color;

        color = SQUARE_COLOR(faces [ adjacentSides [ source ] ], sourceSquares [0]);

        UPDATE_SQUARE_COLOR(
            cube -> Faces [ adjacentSides [destination] ],
            destinationSquares [0],
            color);

        color = SQUARE_COLOR(faces [ adjacentSides [ source ] ], sourceSquares [1]);

        UPDATE_SQUARE_COLOR(
            cube -> Faces [ adjacentSides [destination] ],
            destinationSquares [1],
            color);

        color = SQUARE_COLOR(faces [ adjacentSides [ source ] ], sourceSquares [2]);

        UPDATE_SQUARE_COLOR(
            cube -> Faces [ adjacentSides [destination] ],
            destinationSquares [2],
            color);
}

void DisposeCube(Cube * cube) {
    free(cube -> Faces);
    free(cube -> Scramble);
    free(cube -> Solution);

    if (cube -> OriginalSolution) free(cube -> OriginalSolution);
}

void CleanSolution(Cube * cube) {

    cube -> OriginalSolution = malloc(sizeof(char) * MAXIMUM_SOLUTION_LENGTH);
    memcpy(cube -> OriginalSolution, cube -> Solution, sizeof(char) * MAXIMUM_SOLUTION_LENGTH);

    Clean4Repeated(cube);
    Clean3Repeated(cube);
    CleanConsecutiveOpposites(cube);
}

void Clean4Repeated(Cube * cube) {
    char * cleanSolution = malloc(sizeof(char) * MAXIMUM_SOLUTION_LENGTH);
    memset(cleanSolution, 0, sizeof(char) * MAXIMUM_SOLUTION_LENGTH);

    int i = 0;
    int solutionIndex = 0;

    for (; i < MAXIMUM_SOLUTION_LENGTH && cube -> Solution [i];) {
        if ((cube -> Solution [i] == cube -> Solution [i+1])
            && (cube -> Solution [i+1] == cube -> Solution [i+2])
            && (cube -> Solution [i+2] == cube -> Solution [i+3])) {
                i = i + 4;
                continue;
        }

        cleanSolution [solutionIndex++] = cube -> Solution [i];
        ++i;
    }

    free (cube -> Solution);
    cube -> Solution = cleanSolution;
    cube -> solutionIndex = solutionIndex;
}

void Clean3Repeated(Cube * cube) {
    char * cleanSolution = malloc(sizeof(char) * MAXIMUM_SOLUTION_LENGTH);
    memset(cleanSolution, 0, sizeof(char) * MAXIMUM_SOLUTION_LENGTH);

    int i = 0;
    int solutionIndex = 0;
    for (; i < MAXIMUM_SOLUTION_LENGTH && cube -> Solution [i];) {
        if (cube -> Solution [i] == cube -> Solution [i+1]
            && cube -> Solution [i+1] == cube -> Solution [i+2]) {
                cleanSolution [solutionIndex++] = SwitchCase(cube -> Solution [i]);
                i = i + 3;
                continue;
        }

        cleanSolution [solutionIndex++] = cube -> Solution [i];
        ++i;
    }

    free (cube -> Solution);
    cube -> Solution = cleanSolution;
    cube -> solutionIndex = solutionIndex;
}

void CleanConsecutiveOpposites(Cube * cube) {
    char * cleanSolution = malloc(sizeof(char) * MAXIMUM_SOLUTION_LENGTH);
    memset(cleanSolution, 0, sizeof(char) * MAXIMUM_SOLUTION_LENGTH);
    
    int i = 0;
    int solutionIndex = 0;
    for (; i < MAXIMUM_SOLUTION_LENGTH-1; ++i) {
        if (cube -> Solution [i] == ToLower(cube -> Solution [i+1])
            || cube -> Solution [i+1] == ToLower(cube -> Solution [i])) {
                ++i;
                continue;
        }

        cleanSolution [solutionIndex++] = cube -> Solution [i];
    }

    free (cube -> Solution);
    cube -> Solution = cleanSolution;
    cube -> solutionIndex = solutionIndex;
}

void OutputHelpText() {
    printf("\nrubiksolver\n");

    printf("\n\t-s => Generates a scramble.\n");
    printf("\n\t-s [algorithm/moves] => Performs the second argument's moves on the cube, outputs solution.\n");
    printf("\n\t-p [position string] =>");
    printf(" Sets the second argument's position on the cube, outputs solution.\n");
    printf("\n");
}
