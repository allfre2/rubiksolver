// Cross
// 24 edge algorithms
// scan for 24 positions
// repeat 4 times for each edge

// F2L
// ...

// OLL
// 57 algorithms
// scan for 57 different positions (use hash map to do it in O(1))

// PLL
// 21 algorithms (3 rotations)
// scan for 63 different positions

#ifndef SOlVER_H
    #define SOLVER_H
#endif

#define ALGORITHM_NOT_FOUND -1

extern const char CROSS_EDGE_ALGORITHMS[ EDGE_COUNT * EDGE_ORIENTATIONS ][8];
extern const char F2L_ALGORITHMS[ CORNER_COUNT * CORNER_ORIENTATIONS ][ EDGE_COUNT * EDGE_ORIENTATIONS ];

char * LookupEdgeAlgorithm(Cube *, u_int, u_int);
char * LookupF2LAlgorithm(Cube *, u_int, u_int, u_int);
void SolveCross(Cube *);
void SolveF2L(Cube *);
void Solve(Cube *);
