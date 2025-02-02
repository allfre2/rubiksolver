#define SIDES 6
#define EMPTY_FACE -1
#define CENTER_SQUARE 9

#define bool int
#define true 1
#define false 0
#define uint_64 unsigned long
#define uint_32 unsigned int
#define byte unsigned char

#define SQUARE_COLOR(face, square) (((face) >> (8 * (8 - square))) & 0xff)
#define SET_SQUARE_COLOR(face, square, color) (face |= (color << ( 8 * (8 - square)))) 

extern bool debug_enabled;
extern bool use_terminal_colors;

extern const uint_64 WHITE;
extern const uint_64 GREEN;
extern const uint_64 RED;
extern const uint_64 BLUE;
extern const uint_64 ORANGE;
extern const uint_64 YELLOW;

extern const uint_64 DOWN;
extern const uint_64 RIGHT;
extern const uint_64 FRONT;
extern const uint_64 LEFT;
extern const uint_64 BACK;
extern const uint_64 UP;

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
char * COLOR_NAMES[];
char * COLOR_CODES[10];

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

void DisposeCube(Cube *);
