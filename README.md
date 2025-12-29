# TwistyPuzzle

Simulate a variety of twisty puzzles.  As of this writing, the following puzzles are supported.

 - Bagua
 - Bauhinia Dodecahedron
 - Bubbloid 3x3x3
 - Bubbloid 4x4x5
 - Corner-turning Octahedron
 - Curvy-Copter
 - Curvy-Copter 3
 - Dogic
 - Face-turning Octahedron
 - Fisher Cube
 - Flower Box (Rex Cube)
 - Gem 6
 - Gem 8
 - Icosahedron Skewb
 - Master Pyraminx
 - Megaminx
 - Mixup Cube
 - Pyraminx
 - Rubik's 2x2x2
 - Rubik's 2x2x3
 - Rubik's 2x3x3
 - Rubik's 3x3x3
 - Skewb
 - Skewb Diamond
 - Skewb Ultimate
 - Square One

## Installing

If you run Ubuntu Linux, or any flavor with `snapd` installed, you can install this program with the following command.

`$ sudo snap install twistypuzzle`

After determining that the program is a peice of crap, you can uninstall it similarly.

`$ sudo snap remove twistypuzzle`

## Building

Make sure all sub-modules are cloned, then use `cmake` as usual.

## Snapping

The program is distributed as a snap.  To create the snap, you'll find a `snapcraft.yaml` file in the Snap subfolder.  You should just be able to issue the `snapcraft` command from within this folder to build the snap file.  To test the snap file, issue the following command.

`$ sudo snap install twisty*.snap --force-dangerous`
