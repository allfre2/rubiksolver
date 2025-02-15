#include "common.h"
#include "solver.h"

int main(int argc, char const *argv[])
{
    EnableDebug(true);

    Init();

    if (argc == 2 && StrCmp(argv[1], "-s")) {

        Cube cube;

        InitCube(&cube);
    
        Scramble(&cube);

        PrintCubeRepresentation(&cube);

        printf("\nScramble: %s", cube.Scramble);

        printf("\nPosition: ");
        PrintPositionString(&cube);
        printf("\n\n");

        Solve(&cube);

        PrintCubeRepresentation(&cube);
        
        printf("\nOriginal Solution: %s", cube.OriginalSolution);
        printf("\nOptimized Solution (Cross only): %s\n\n", cube.Solution);

        DisposeCube(&cube);
        exit(0);
    }

    if (argc == 3) {

        if (StrCmp(argv[1], "-s")) {

            if (!IsValidMoveString(argv[2])) {
                PrintInvalidMovesMessage();
                exit(1);
            }

            Cube cube;

            InitCube(&cube);
            
            cube.Solved = false;

            ApplyAlgorithm(&cube, argv[2]);

            PrintCubeRepresentation(&cube);

            printf("\nPosition: ");
            PrintPositionString(&cube);
            printf("\n\n");
            
            Solve(&cube);
            
            printf("\nOriginal Solution: %s", cube.OriginalSolution);
            printf("\nOptimized Solution (Cross only): %s\n\n", cube.Solution);

            DisposeCube(&cube);
            exit(0);

        } else if (StrCmp(argv[1], "-p")) {

            if (!IsValidCubeString(argv[2])) {
                PrintInvalidRepresentationMessage();
                exit(1);
            }

            Cube cube;

            ParseCube(argv[2], &cube);

            PrintCubeRepresentation(&cube);

            printf("\nPosition: ");
            PrintPositionString(&cube);
            printf("\n\n");

            DisposeCube(&cube);
            exit(0);
        }
    }

    OutputHelpText();
    exit(1);
}
