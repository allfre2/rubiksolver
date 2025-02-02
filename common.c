#include "common.h"

bool debug_enabled = false;

#if defined(_WIN32) || defined(_WIN64)
    bool use_terminal_colors = false;
#else
    bool use_terminal_colors = false;
#endif

const uint_64 WHITE =  0x00;
const uint_64 GREEN =  0x01;
const uint_64 RED =    0x02;
const uint_64 BLUE =   0x03;
const uint_64 ORANGE = 0x04;
const uint_64 YELLOW = 0x05;

const uint_64 DOWN = WHITE;
const uint_64 RIGHT = GREEN;
const uint_64 FRONT = RED;
const uint_64 LEFT = BLUE;
const uint_64 BACK = ORANGE;
const uint_64 UP = YELLOW;

const char WHITE_CHAR = 'W';
const char GREEN_CHAR = 'G';
const char RED_CHAR = 'R';
const char BLUE_CHAR = 'B';
const char ORANGE_CHAR = 'O';
const char YELLOW_CHAR = 'Y';
const char EMPTY_SQUARE_CHAR = '.';

const int CUBE_REPRESENTATION_LENGTH = 48;

const char LEGAL_COLORS[] = {
    WHITE_CHAR,
    GREEN_CHAR,
    RED_CHAR,
    BLUE_CHAR,
    ORANGE_CHAR,
    YELLOW_CHAR
};

const uint_64 ORDER [SIDES] = {
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
    COLOR_VALUES[WHITE_CHAR] = WHITE;
    COLOR_VALUES[GREEN_CHAR] = GREEN;
    COLOR_VALUES[RED_CHAR] = RED;
    COLOR_VALUES[BLUE_CHAR] = BLUE;
    COLOR_VALUES[ORANGE_CHAR] = ORANGE;
    COLOR_VALUES[YELLOW_CHAR] = YELLOW;

    CHAR_VALUES[WHITE] = WHITE_CHAR;
    CHAR_VALUES[GREEN] = GREEN_CHAR;
    CHAR_VALUES[RED] = RED_CHAR;
    CHAR_VALUES[BLUE] = BLUE_CHAR;
    CHAR_VALUES[ORANGE] = ORANGE_CHAR;
    CHAR_VALUES[YELLOW] = YELLOW_CHAR;

    COLOR_NAMES[WHITE] = "White";
    COLOR_NAMES[GREEN] = "Green";
    COLOR_NAMES[RED] = "Red";
    COLOR_NAMES[BLUE] = "Blue";
    COLOR_NAMES[ORANGE] = "Orange";
    COLOR_NAMES[YELLOW] = "Yellow";

    COLOR_CODES[WHITE] = "\e[0;107m"; //"\e[47m";
    COLOR_CODES[GREEN] = "\e[0;102m"; //"\e[42m";
    COLOR_CODES[RED] = "\e[0;101m"; //"\e[41m";
    COLOR_CODES[BLUE] = "\e[0;104m"; //"\e[44m";
    COLOR_CODES[ORANGE] = "\e[45m"; //"\e[45m";
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
}

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

    cube -> Faces = malloc(sizeof(uint_64) * SIDES);
    memset(cube -> Faces, 0, sizeof(uint_64) * SIDES);

    int i = 0;
    int face = 0;
    int square = 1;

    while (position[i]) {

        uint_64 color = COLOR_VALUES [ position [i] ];

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
            unsigned char color = SQUARE_COLOR(cube -> Faces [ ORDER [ i ] ], square);
            cubeString [ strIndex++ ] = CHAR_VALUES [ color ];
        }
    }

    return cubeString;
}

void DisposeCube(Cube * cube) {
    free(cube -> Faces);
}

void PrintColorNames() {
    for (int i = 0; i < SIDES; ++i) {
        printf("%s: %c\n", COLOR_NAMES [ ORDER [ i ] ], CHAR_VALUES [ ORDER [ i ] ]);
    }
}

void PrintFaceOrder() {
    int i = 0;
    while (i < SIDES) {
        printf("%c", CHAR_VALUES [ ORDER [ i ] ]);
        ++i;
    }
}

void PrintFaceRow(Cube * cube, uint_64 face, int square1, int square2, int square3) {

    uint_64 
        color1 = SQUARE_COLOR( cube -> Faces [face], square1 ),
        color2 = SQUARE_COLOR( cube -> Faces [face], square2 ),
        color3 = SQUARE_COLOR( cube -> Faces [face], square3 );

    char
        * code1 = COLOR_CODES [ color1 ],
        * code2 = (square2 == CENTER_SQUARE) ? COLOR_CODES [ face ] : COLOR_CODES [ color2 ],
        * code3 = COLOR_CODES [ color3 ];

    char
        char1 = CHAR_VALUES [ color1 ],
        char2 = (square2 == CENTER_SQUARE) ? CHAR_VALUES [ face ] :  CHAR_VALUES [ color2 ],
        char3 = CHAR_VALUES [ color3 ];

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

                uint_64 face = RepresentationPattern[row][column];

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

        printf("\n\nTOP: %c, FRONT: %c", CHAR_VALUES [ UP ], CHAR_VALUES [ FRONT ]);

        printf("\n\n");
}