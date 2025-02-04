#define SIDES 6
#define EMPTY_FACE -1
#define CENTER_SQUARE 9
#define SQUARE_SIZE 8 // bits
#define SQUARE_COUNT 8

#define bool int
#define true 1
#define false 0
#define uint_64 unsigned long
#define uint_32 unsigned int
#define byte unsigned char

#define SQUARE_FIRST_BYTE ((uint_64)0x00000000000000ff)

#define SQUARE_COLOR(face, square) (((face) >> (SQUARE_SIZE * (SQUARE_COUNT - square))) & SQUARE_FIRST_BYTE)
#define SET_SQUARE_COLOR(face, square, color) (face |= (color << (SQUARE_SIZE * (SQUARE_COUNT - square)))) 
#define ROTATE_RIGHT(face) ((face >> (SQUARE_SIZE * 2)) | (face << (SQUARE_SIZE * 6)))
#define ROTATE_LEFT(face) ((face << (SQUARE_SIZE * 2)) | (face >> (SQUARE_SIZE * 6)))

extern bool debug_enabled;
extern bool use_terminal_colors;

extern const uint_64 DOWN;
extern const uint_64 RIGHT;
extern const uint_64 FRONT;
extern const uint_64 LEFT;
extern const uint_64 BACK;
extern const uint_64 UP;

extern const uint_64 WHITE;
extern const uint_64 GREEN;
extern const uint_64 RED;
extern const uint_64 BLUE;
extern const uint_64 ORANGE;
extern const uint_64 YELLOW;

extern const char WHITE_CHAR;
extern const char GREEN_CHAR;
extern const char RED_CHAR;
extern const char BLUE_CHAR;
extern const char ORANGE_CHAR;
extern const char YELLOW_CHAR;
extern const char EMPTY_SQUARE_CHAR;

extern const char LEGAL_COLORS[];

uint_64 COLOR_VALUES [100];
char CHAR_VALUES[SIDES];
char FACE_CHARS[SIDES];
char * COLOR_NAMES[SIDES];
char * COLOR_CODES[SIDES];

extern const uint_64 ADJACENT_SIDES[SIDES][4];
extern const int ADJACENT_SQUARES[SIDES][4][3];
uint_64 SQUARE_MASKS[SQUARE_COUNT+1];

extern const int CUBE_REPRESENTATION_LENGTH;

void EnableDebug(bool);
int Strlen(char *);
void Init();
bool IsLegalChar(char);
bool IsValidCubeString(char *);

const uint_64 ORDER [SIDES];

typedef struct {
    uint_64 * Faces; 
} Cube;

void ParseCube(char *, Cube *);
char * GetCubeString(Cube *);

uint_64 RepresentationPattern[3][4];
int SquareRepresentationPattern[3][3];

void PrintCubeRepresentation(Cube *);
void PrintInvalidRepresentationMessage();

void Rotate(Cube *, uint_64, bool);

void DisposeCube(Cube *);
