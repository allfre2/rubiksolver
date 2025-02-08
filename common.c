#include "common.h"

bool debug_enabled = false;

#if defined(_WIN32) || defined(_WIN64)
    bool use_terminal_colors = false;
#else
    bool use_terminal_colors = true;
#endif

const u_int DOWN  = 0x00;
const u_int RIGHT = 0x01;
const u_int FRONT = 0x02;
const u_int LEFT  = 0x03;
const u_int BACK  = 0x04;
const u_int UP    = 0x05;

const u_int WHITE  = DOWN;
const u_int GREEN  = RIGHT;
const u_int RED    = FRONT;
const u_int BLUE   = LEFT;
const u_int ORANGE = BACK;
const u_int YELLOW = UP;

const char SOLVED_POSITION[] = {
    BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,
    RED_CHAR,RED_CHAR,RED_CHAR,RED_CHAR,RED_CHAR,RED_CHAR,RED_CHAR,RED_CHAR,
    GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,
    ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,
    YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,
    WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,
    0
};

const char LEGAL_MOVES[] = {
    DOWN_CHAR, RIGHT_CHAR, FRONT_CHAR, LEFT_CHAR, BACK_CHAR, UP_CHAR,
    DOWN_PRIME_CHAR, RIGHT_PRIME_CHAR, FRONT_PRIME_CHAR, LEFT_PRIME_CHAR, BACK_PRIME_CHAR, UP_PRIME_CHAR,
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

const u_int ORDER [SIDES] = {
    LEFT,
    FRONT,
    RIGHT,
    BACK,
    UP,
    DOWN
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

void Init() {
    COLOR_VALUES[WHITE_CHAR]  = WHITE;
    COLOR_VALUES[GREEN_CHAR]  = GREEN;
    COLOR_VALUES[RED_CHAR]    = RED;
    COLOR_VALUES[BLUE_CHAR]   = BLUE;
    COLOR_VALUES[ORANGE_CHAR] = ORANGE;
    COLOR_VALUES[YELLOW_CHAR] = YELLOW;

    COLOR_CHARS[WHITE]  = WHITE_CHAR;
    COLOR_CHARS[GREEN]  = GREEN_CHAR;
    COLOR_CHARS[RED]    = RED_CHAR;
    COLOR_CHARS[BLUE]   = BLUE_CHAR;
    COLOR_CHARS[ORANGE] = ORANGE_CHAR;
    COLOR_CHARS[YELLOW] = YELLOW_CHAR;

    FACE_CHARS[DOWN]  = 'D';
    FACE_CHARS[RIGHT] = 'R';
    FACE_CHARS[FRONT] = 'F';
    FACE_CHARS[LEFT]  = 'L';
    FACE_CHARS[BACK]  = 'B';
    FACE_CHARS[UP]    = 'U';

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

    for (int sq = 1; sq < FACE_SQUARE_COUNT+1; ++sq) {
        FACE_SQUARE_MASKS [ sq ] = ~ (SQUARE_FIRST_BYTE << (SQUARE_SIZE * (FACE_SQUARE_COUNT - sq)));
        if (debug_enabled) {
            //printf("\n%016llx\n", FACE_SQUARE_MASKS [sq]);
        }
    }

    MOVE_FACES [ DOWN_CHAR ]        = DOWN;
    MOVE_FACES [ RIGHT_CHAR ]       = RIGHT;
    MOVE_FACES [ FRONT_CHAR ]       = FRONT;
    MOVE_FACES [ LEFT_CHAR ]        = LEFT;
    MOVE_FACES [ BACK_CHAR ]        = BACK;
    MOVE_FACES [ UP_CHAR ]          = UP;
    MOVE_FACES [ DOWN_PRIME_CHAR ]  = DOWN;
    MOVE_FACES [ RIGHT_PRIME_CHAR ] = RIGHT;
    MOVE_FACES [ FRONT_PRIME_CHAR ] = FRONT;
    MOVE_FACES [ LEFT_PRIME_CHAR ]  = LEFT;
    MOVE_FACES [ BACK_PRIME_CHAR ]  = BACK;
    MOVE_FACES [ UP_PRIME_CHAR ]    = UP;
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

extern u_int EDGE_LOOKUP_TABLE[ EDGE_COUNT * EDGE_ORIENTATIONS ][4] = {
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

void ParseCube(char * position, Cube * cube) {

    cube -> Faces = malloc(sizeof(u_int) * SIDES);
    memset(cube -> Faces, 0, sizeof(u_int) * SIDES);

    cube -> Scramble = malloc(sizeof(char) * MAXIMUM_SCRAMBLE_LENGTH);
    memset(cube -> Scramble, 0, sizeof(char) * MAXIMUM_SCRAMBLE_LENGTH);

    cube -> Solution = malloc(sizeof(char) * MAXIMUM_SOLUTION_LENGTH);
    memset(cube -> Solution, 0, sizeof(char) * MAXIMUM_SCRAMBLE_LENGTH);

    cube -> scrambleIndex = 0;
    cube -> solutionIndex = 0;
    cube -> Solving = false;

    int i = 0;
    int face = 0;
    int square = 1;

    while (position[i]) {

        u_int color = COLOR_VALUES [ position [i] ];

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

char * GetCubeString(Cube * cube) {
    
    char * cubeString = malloc(sizeof(char) * CUBE_REPRESENTATION_LENGTH);
    memset(cubeString, 0, CUBE_REPRESENTATION_LENGTH);

    int strIndex = 0;

    for (int i = 0; i < SIDES; ++i) {
        for (int square = 1; square <= 8; ++square) {
            u_int color = SQUARE_COLOR(cube -> Faces [ ORDER [ i ] ], square);
            cubeString [ strIndex++ ] = COLOR_CHARS [ color ];
        }
    }

    return cubeString;
}

void PrintColorNames() {
    for (int i = 0; i < SIDES; ++i) {
        printf("%s: %c %s%c%s\n",
            COLOR_NAMES [ ORDER [ i ] ],
            COLOR_CHARS [ ORDER [ i ] ],
            use_terminal_colors ?  COLOR_CODES [ ORDER [ i ] ] : "",
            ' ',
            RESET_COLOR_CODE);
    }
}

void PrintFaceOrder() {
    int i = 0;
    while (i < SIDES) {
        printf("%c", COLOR_CHARS [ ORDER [ i ] ]);
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
        * code1 = COLOR_CODES [ color1 ],
        * code2 = (square2 == CENTER_SQUARE) ? COLOR_CODES [ face ] : COLOR_CODES [ color2 ],
        * code3 = COLOR_CODES [ color3 ];

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

// I'm sorry for this code :(
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

        printf("\n\nTOP: %c, FRONT: %c", COLOR_CHARS [ UP ], COLOR_CHARS [ FRONT ]);

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

void GenerateRandomScramble(Cube * cube) {
    
    int size = MAXIMUM_SCRAMBLE_LENGTH;
    srand(time(0));

    int i = 0;

    while (i++ < size) {
        Move(cube, LEGAL_MOVES [rand() % (SIDES * 2)]);
    }
}

void ApplyAlgorithm(Cube * cube, char * move) {
    while (*move) {
        Move(cube, *move);
        ++move;
    }
}

void Move(Cube * cube, char move) {
    if (cube -> Solving) {
        if (cube -> solutionIndex == MAXIMUM_SOLUTION_LENGTH) {
            printf("\n(!) Solution buffer filled!\n");
            return; //TODO: handle error
        }
        cube -> Solution [cube -> solutionIndex] = move;
        cube -> solutionIndex++;
    } else {
        if (cube -> scrambleIndex == MAXIMUM_SCRAMBLE_LENGTH) {
            printf("\n(!) Scramble buffer filled!\n");
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
        for (int side = 3; side > -1; --side) {
            int destination = (side == 0) ? 3 : side - 1;
            RotateSquares(cube, &faces, face, side, destination);
        }
    } else {
        for (int side = 0; side < 4; ++side) {
            int destination = (side == 3) ? 0 : side + 1;
            RotateSquares(cube, &faces, face, side, destination);
        }
    }
}

void RotateSquares(Cube * cube, u_int * faces, u_int face, int source, int destination) {

        u_int * adjacentSides = ADJACENT_SIDES [ face ];

        int * sourceSquares = ADJACENT_SQUARES[face][source];
        int * destinationSquares = ADJACENT_SQUARES[face][destination];

        for (int n = 0; n < 3; ++n) {

            u_int color = SQUARE_COLOR(faces [ adjacentSides [ source ] ], sourceSquares [n]);

            UPDATE_SQUARE_COLOR(
                cube -> Faces [ adjacentSides [destination] ],
                destinationSquares [n],
                color);
        }
}

void DisposeCube(Cube * cube) {
    free(cube -> Faces);
    free(cube -> Scramble);
    free(cube -> Solution);
}

void OutputHelpText() {
    printf("\nunisolver\n");

    printf("\n\t-s => Generates a scramble.\n");
    printf("\n\t-s [algorithm/moves] => Performs the second argument's moves on the cube, outputs solution.\n");
    printf("\n\t-p [position string] =>");
    printf(" Sets the second argument's position on the cube, outputs solution.\n");
    printf("\n");
}
