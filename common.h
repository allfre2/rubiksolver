#ifndef COMMON_H
    #define COMMON_H
#endif

#define EMBEDDED_BUILD

#ifdef EMBEDDED_BUILD
    #define USE_32_BITS
#endif

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 1

#define SIDES 6
#define EMPTY_FACE -1
#define CENTER_SQUARE 9
#define CUBE_REPRESENTATION_LENGTH 48
#define MAXIMUM_SCRAMBLE_LENGTH 12
#define MAXIMUM_SOLUTION_LENGTH 300

#if defined(USE_32_BITS)
    #define SQUARE_SIZE 4
#else
    #define SQUARE_SIZE 8
#endif

#define FACE_SQUARE_COUNT 8

#define bool int
#define true 1
#define false 0

#if defined(USE_32_BITS)
    #define u_int unsigned int
#else
    #define u_int unsigned long
#endif

#define byte unsigned char

#if defined(USE_32_BITS)
    #define SQUARE_FIRST_BYTE ((u_int)0x0000000f)
#else
    #define SQUARE_FIRST_BYTE ((u_int)0x00000000000000ff)
#endif

#define SQUARE_COLOR(face, square) (((face) >> (SQUARE_SIZE * (FACE_SQUARE_COUNT - square))) & SQUARE_FIRST_BYTE)
#define SET_SQUARE_COLOR(face, square, color) ((face) |= ((color) << (SQUARE_SIZE * (FACE_SQUARE_COUNT - (square)))))
#define UPDATE_SQUARE_COLOR(face, square, color) (face = ((face & FACE_SQUARE_MASKS [square]) | (color << (SQUARE_SIZE * (FACE_SQUARE_COUNT - square)))))
#define ROTATE_RIGHT(face) ((face >> (SQUARE_SIZE * 2)) | (face << (SQUARE_SIZE * 6)))
#define ROTATE_LEFT(face) ((face << (SQUARE_SIZE * 2)) | (face >> (SQUARE_SIZE * 6)))
#define ROTATE_SQUARE_90(square) ((square + 6) % FACE_SQUARE_COUNT)
#define ROTATE_SQUARE_180(square) ((square + 4) % FACE_SQUARE_COUNT)
#define ROTATE_SQUARE_270(square) ((square + 2) % FACE_SQUARE_COUNT)


extern bool debug_enabled;
extern bool use_terminal_colors;

extern const u_int DOWN;
extern const u_int RIGHT;
extern const u_int FRONT;
extern const u_int LEFT;
extern const u_int BACK;
extern const u_int UP;

#define _DOWN 'D'
#define _RIGHT 'R'
#define _FRONT 'F'
#define _LEFT 'L'
#define _BACK 'B'
#define _UP 'U'
#define _DOWN_I 'd'
#define _RIGHT_I 'r'
#define _FRONT_I 'f'
#define _LEFT_I 'l'
#define _BACK_I 'b'
#define _UP_I 'u'

extern const u_int WHITE;
extern const u_int GREEN;
extern const u_int RED;
extern const u_int BLUE;
extern const u_int ORANGE;
extern const u_int YELLOW;

#define WHITE_CHAR 'W'
#define GREEN_CHAR 'G'
#define RED_CHAR 'R'
#define BLUE_CHAR 'B'
#define ORANGE_CHAR 'O'
#define YELLOW_CHAR 'Y'
#define EMPTY_SQUARE_CHAR '.'

extern const char SOLVED_POSITION[];
extern const char LEGAL_MOVES[];
extern const char LEGAL_COLORS[];

char COLOR_CHARS[SIDES];
char FACE_CHARS[SIDES];
char * COLOR_NAMES[SIDES];
char * COLOR_CODES[SIDES];
char * RESET_COLOR_CODE;

extern const u_int ADJACENT_SIDES[SIDES][4];
extern const int ADJACENT_SQUARES[SIDES][4][3];
u_int FACE_SQUARE_MASKS[FACE_SQUARE_COUNT+1];

u_int MOVE_FACES[SIDES*2];

extern const u_int FACE_ROTATIONS[SIDES][SIDES];

#define EDGE_COUNT 12
#define EDGE_ORIENTATIONS 2
#define CORNER_COUNT 8
#define CORNER_ORIENTATIONS 3

extern const u_int EDGE_LOOKUP_TABLE[ EDGE_COUNT * EDGE_ORIENTATIONS ][4];
extern const u_int CORNER_LOOKUP_TABLE[ CORNER_COUNT * CORNER_ORIENTATIONS ][6];

void EnableDebug(bool);
int Strlen(char *);
bool StrCmp(char *, char *);
bool IsLower(char *);
char ToLower(char);
char SwitchCase(char);
void Init();
bool IsLegalChar(char);
bool IsLegalMove(char);
bool IsValidCubeString(char *);
bool IsValidMoveString(char *);
u_int GetColorValue(char);

const u_int ORDER [SIDES];

typedef struct {
    u_int * Faces;
    char * Scramble;
    char * Solution;
    char * OriginalSolution;
    u_int Rotation;
    int scrambleIndex;
    int solutionIndex;
    bool Scrambling;
    bool Solving;
    bool Solved;
} Cube;

void InitCube(Cube *);
void ParseCube(char *, Cube *);
void PrintPositionString(Cube *);
void PrintStandardNotation(char *);

u_int RepresentationPattern[3][4];
int SquareRepresentationPattern[3][3];

void PrintCubeRepresentation(Cube *);
void PrintInvalidRepresentationMessage();
void PrintInvalidMovesMessage();

u_int GetFace(Cube *, u_int);
u_int GetSquare(Cube *, u_int, u_int);
char GetMove(Cube *, char);
void Scramble(Cube *);
void ApplyAlgorithm(Cube *, char *);
void Move(Cube *, char);
void Rotate(Cube *, u_int, bool);

void DisposeCube(Cube *);
void CleanSolution(Cube *);

void OutputHelpText();