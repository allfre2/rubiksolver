# UniSolver (3x3 Rubik's Cube)

3x3 Rubik's Cube scrambler and solver.

Stress relief for some days.

In Progress ...

![25%](https://progress-bar.xyz/25)

## Build

```bash
make
```

## Details

* Uses BitMaps to represent the cube.
* Rotations are done by using bit twiddiling tricks.
* Going to use Fridrich (CFOP) method to solve the cube.
* Supports 32 or 64 bit modes.
* Intended to fit in an Arduino UNO (32k + 2k SRAM)

## Usage

unisolver

        -s => Generates a scramble.

        -s [algorithm/moves] => Performs the second argument's moves on the cube, outputs solution.

        -p [position string] => Sets the second argument's position on the cube, outputs solution.

## Screenshots

![Screenshot](./images/scramble.png)

## :|

![Screenshot](./images/dude_where_s_my_car.png)
