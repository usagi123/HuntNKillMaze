Hunt and Kill maze generator
=

Solution by Huy Mai Pham Quang (s3618861@rmit.edu.vn)

### Description
The program can be able to generate maze from user input seed, width and height. 
Then it will be saved both SVG and binary.

The maze path generator is using Hunt and Kill algorithm with hnkAllDemCells() function.
Then the program will calculate which edges between path with whereIsYourEdge() function and calculate how to draw it in SVG
<line /> file
The SVG will generate a grid of cells with total cell of that grid based on width * height. 
Then the program will remove edges to create a maze.

The Hunt and Kill algorithm logic can be found at https://weblog.jamisbuck.org/2011/1/24/maze-generation-hunt-and-kill-algorithm


### Installation
Go to the build-dir directory s and call
    'make'

To remove the compiled files, simply call
    'make clean'



### Usage

#### Flags
###### --g seed width height filename (does not need file extension suffix)
Generate maze into SVG and binary file with custom name, seed, width and height

###### -g width height filename (does not need file extension suffix)
Generate maze into SVG and binary file with custom name, seed, width and height

##### Examples

./maze --g 1234 10 10 myMaze (generate binary and SVG maze file named myMaze with seed 1234 and h/w: 10/10)

./maze -g 10 10 myMaze (generate binary and SVG maze file named myMaze with seed 1234 and h/w: 10/10)



