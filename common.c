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

const char DOWN_CHAR        = 'D';
const char RIGHT_CHAR       = 'R';
const char FRONT_CHAR       = 'F';
const char LEFT_CHAR        = 'L';
const char BACK_CHAR        = 'B';
const char UP_CHAR          = 'U';
const char DOWN_PRIME_CHAR  = 'd';
const char RIGHT_PRIME_CHAR = 'r';
const char FRONT_PRIME_CHAR = 'f';
const char LEFT_PRIME_CHAR  = 'l';
const char BACK_PRIME_CHAR  = 'b';
const char UP_PRIME_CHAR    = 'u';

const u_int WHITE  = DOWN;
const u_int GREEN  = RIGHT;
const u_int RED    = FRONT;
const u_int BLUE   = LEFT;
const u_int ORANGE = BACK;
const u_int YELLOW = UP;

const char WHITE_CHAR  = 'W';
const char GREEN_CHAR  = 'G';
const char RED_CHAR    = 'R';
const char BLUE_CHAR   = 'B';
const char ORANGE_CHAR = 'O';
const char YELLOW_CHAR = 'Y';
const char EMPTY_SQUARE_CHAR = '.';

const char SOLVED_POSITION[] = {
    BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,BLUE_CHAR,
    RED_CHAR,RED_CHAR,RED_CHAR,RED_CHAR,RED_CHAR,RED_CHAR,RED_CHAR,RED_CHAR,
    GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,GREEN_CHAR,
    ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,ORANGE_CHAR,
    YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,YELLOW_CHAR,
    WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,WHITE_CHAR,
    0
}; //"BBBBBBBBRRRRRRRRGGGGGGGGOOOOOOOOYYYYYYYYWWWWWWWW";

const char * LEGAL_MOVES = {
    DOWN_CHAR, RIGHT_CHAR, FRONT_CHAR, LEFT_CHAR, BACK_CHAR, UP_CHAR,
    DOWN_PRIME_CHAR, RIGHT_PRIME_CHAR, FRONT_PRIME_CHAR, LEFT_PRIME_CHAR, BACK_PRIME_CHAR, UP_PRIME_CHAR
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
    COLOR_CODES[ORANGE] = "\e[45m";
    COLOR_CODES[YELLOW] = "\e[43m";

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
}

const u_int ADJACENT_SIDES[SIDES][4] = {
    { FRONT, RIGHT, BACK, LEFT }, // DOWN
    { UP, BACK, DOWN, FRONT },    // RIGHT
    { UP, RIGHT, DOWN, LEFT },    // FRONT
    { UP, FRONT, DOWN, BACK },    // LEFT
    { UP, LEFT, DOWN, RIGHT },    // BACK
    { BACK, RIGHT, FRONT, LEFT} , // TOP
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
        {3,2,1}, {1,2,3}, {3,2,1}, {3,2,1}   // TOP
    },
};

bool IsLegalChar(char c) {
    int i = 0;

    while (i < SIDES) {
        if (LEGAL_COLORS[i] == c) return true;
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

void ParseCube(char * position, Cube * cube) {

    cube -> Faces = malloc(sizeof(u_int) * SIDES);
    memset(cube -> Faces, 0, sizeof(u_int) * SIDES);

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

        face = (square == 8) ? (face + 1) : face;
        square = (square == 8) ? 1 : square + 1;
        ++i;
    }

    return cube;
}

/*

Binary Representation of a face
Squares in the cube go from top left corner (Most Significant Byte) clockwise

7        6        5        4        3        2        1        0
00000000 00000001 00000010 00000011 00000100 00000101 00000000 00000001

*/

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
        printf("%s: %c %s%c\e[0m\n",
            COLOR_NAMES [ ORDER [ i ] ],
            COLOR_CHARS [ ORDER [ i ] ],
            use_terminal_colors ?  COLOR_CODES [ ORDER [ i ] ] : "",
            ' ');
    }
}

void PrintFaceOrder() {
    int i = 0;
    while (i < SIDES) {
        printf("%c", COLOR_CHARS [ ORDER [ i ] ]);
        ++i;
    }
}

void PrintFaceRow(Cube * cube, u_int face, int square1, int square2, int square3) {

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
        printf("%s%c", code1, '.');
        printf("%s%c", code2, (square2 == CENTER_SQUARE) ? char2 : '.');
        printf("%s%c", code3, '.');
        printf("\e[0m");
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

                int square1, square2, square3;

                if (face == EMPTY_FACE) {
                    printf("    ");
                    continue;
                }

                square1 = SquareRepresentationPattern[face_row][0];
                square2 = SquareRepresentationPattern[face_row][1];
                square3 = SquareRepresentationPattern[face_row][2];

                PrintFaceRow(cube, face, square1, square2, square3);
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

void Rotate(Cube * cube, u_int face, bool inverted) {
    if (inverted) {
        cube -> Faces [face] = ROTATE_LEFT(cube -> Faces [face]);
    } else {
        cube -> Faces [face] = ROTATE_RIGHT(cube -> Faces [face]);
    } 
    RotateSides(cube, face, inverted);
}

// Sorry for this one too
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

        for (int square = 0; square < 3; ++square) {

            u_int color = SQUARE_COLOR(faces [ adjacentSides [ source ] ], sourceSquares [square]);

            UPDATE_SQUARE_COLOR(
                cube -> Faces [ adjacentSides [destination] ],
                destinationSquares [square],
                color);
        }
}


void DisposeCube(Cube * cube) {
    free(cube -> Faces);
}
