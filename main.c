#include "common.h"

int main(int argc, char const *argv[])
{
    EnableDebug(true);

    Init();

    if (argc < 2 || !IsValidCubeString(argv[1])) {
        PrintInvalidRepresentationMessage();
        exit(1);
    }

    Cube cube;

    ParseCube(argv[1], &cube);

    char * representation = GetCubeString(&cube);

    PrintCubeRepresentation(&cube);

    printf("%s\n\n", representation);

    free(representation);
    DisposeCube(&cube);
    return 0;
}
