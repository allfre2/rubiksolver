#include "common.h"

int main(int argc, char const *argv[])
{
    EnableDebug(true);

    Init();

    if (argc == 2 && StrCmp(argv[1], "-s")) {

        char * scramble = GenerateRandomScramble(12);
    
        Cube cube;

        ParseCube(SOLVED_POSITION, &cube);

        ApplyAlgorithm(&cube, scramble);

        PrintCubeRepresentation(&cube);

        char * cubeString = GetCubeString(&cube);

        printf("\nScramble: %s\n", scramble);
        printf("Position: %s\n\n", cubeString);

        free(cubeString);
        free(scramble);
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

            ParseCube(SOLVED_POSITION, &cube);
            
            ApplyAlgorithm(&cube, argv[2]);

            PrintCubeRepresentation(&cube);

            char * cubeString = GetCubeString(&cube);

            printf("Position: %s\n\n", cubeString);

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
