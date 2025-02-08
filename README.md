# UniSolver (3x3 Rubik's Cube)

3x3 Rubik's Cube scrambler and solver.

Stress relief / hobby for a few days.

In Progress ...

**Status**:

![33%](https://progress-bar.xyz/33)

- ~~Done~~: Build [white cross](https://ruwix.com/the-rubiks-cube/advanced-cfop-fridrich/white-cross/)
- Next: [F2L](https://ruwix.com/the-rubiks-cube/advanced-cfop-fridrich/first-two-layers-f2l/) 

## Build

```bash
make
```

## Install

```bash
make install
```

## Details

* Uses BitMaps to represent the cube.
* Rotations are done by using [bit twiddiling tricks](https://graphics.stanford.edu/~seander/bithacks.html).
* Implements [Fridrich (CFOP)](https://ruwix.com/the-rubiks-cube/advanced-cfop-fridrich/) method to solve the cube.
* Supports 32 or 64 bit modes.
* Intended to fit in an [Arduino UNO](https://docs.arduino.cc/hardware/uno-rev3/#tech-specs) (32k + 2k SRAM)

## Usage

unisolver

        -s => Generates a scramble.

        -s [algorithm/moves] => Performs the second argument's moves on the cube, outputs solution.

        -p [position string] => Sets the second argument's position on the cube, outputs solution.

## Screenshots

![Screenshot](./images/scramble.png)

## dude ...

![Screenshot](./images/dude_where_s_my_car.png)
