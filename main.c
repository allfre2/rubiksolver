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

        char * cubeString = GetCubeString(&cube);

        printf("\nScramble: %s\n", cube.Scramble);
        printf("Position: %s\n\n", cubeString);

        Solve(&cube);

        PrintCubeRepresentation(&cube);

        printf("\nSolution (Cross only): %s\n\n", cube.Solution);

        free(cubeString);
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

            char * cubeString = GetCubeString(&cube);

            printf("Position: %s\n\n", cubeString);

            Solve(&cube);
            
            printf("\nSolution (Cross only): %s\n\n", cube.Solution);

            free(cubeString);
            DisposeCube(&cube);
            exit(0);

        } else if (StrCmp(argv[1], "-p")) {

            if (!IsValidCubeString(argv[2])) {
                PrintInvalidRepresentationMessage();
                exit(1);
            }

            Cube cube;

            ParseCube(argv[2], &cube);

            char * cubeString = GetCubeString(&cube);

            PrintCubeRepresentation(&cube);

            printf("Position: %s\n\n", cubeString);

            free(cubeString);
            DisposeCube(&cube);
            exit(0);
        }
    }

    OutputHelpText();
    exit(1);
}
