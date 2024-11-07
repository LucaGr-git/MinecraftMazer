#ifndef MAZEENHANCED
#define MAZEENHANCED

#include <mcpp/mcpp.h>
#include "MazeCoordinate.h"
#include "LinkedBlocks.h"
#include "BlockNode.h"
#include <cstdlib>
#include <thread>
#include <chrono>
#include <cmath>
#include "Maze.h"


 
class MazeEnhanced : public Maze
{
public:

    //constructors and deconstructors
    MazeEnhanced();

    //Contract:
    //  Pre-Condition: length and width must be greater than 1
    //  Post-Condition: A new MazeEnhanced object is created, where data members, 
    //  length and width are filled.
    MazeEnhanced(int length, int width);


    void buildDownTerrain(mcpp::HeightMap& worldHeight, 
                                int **  difference, 
                                LinkedBlocks& blockList) override;

    /* Gets the values of the area that the maze is going to be built
    *  You can use this before (or after) the maze structure has been built to 
    *  getHeights in the maze area.
    *
    *  Contract:
    *  Pre-Conditions: Env class must have all of it's data members correctly 
    *  filled.
    *       - Especially start, height, width
    *  Post-Conditions: A HeightMap 2D array is created with the area's height 
    * This will after getting the Heightmaze update the highestPoint member
    */
    mcpp::HeightMap getHeightMaze(LinkedBlocks& blockList) override;

    /* Gets the values of the area that the maze is going to be built
    *  You can use this before (or after) the maze structure has been built to 
    *  getHeights in the maze area.
    *
    *  Contract:
    *  Pre-Conditions: Maze class must have all of it's data members filled.
    *       - Especially start, height, width
    *  Post-Conditions: A HeightMap 2D array is created with the area's height.
    */
    mcpp::HeightMap getHeightMaze() override;

    void buildUpTerrain(mcpp::HeightMap& worldHeight, 
                                int ** Difference) override;
                                


    /*
    * Builds the maze at the start coordinate based on the maze structure given
    *
    *  Contract:
    *  Pre-Conditions: Maze class must have all of it's data members filled.
    *       - Especially start, height, width
    *  Post-Conditions: A maze is built in the minecraft world based on the
    *   members set in the Maze class
    */
    void buildMaze() override;


    /* Contract:
    *  Pre-Conditions:
    *  - array has been initalized with proper length and width members
    *  - assumes only one exit exists i.e. it is a perfect maze
    *  Post-Conditions: 
    *  - a blue carpet will be placed in minecraft at the exit point 
    */
    void placeBlueCarpet(LinkedBlocks& blockList) override;

private:
    /* data */
    int length;
    int width;
    int highestPoint;

    mcpp::Coordinate* start;

    char** mazeStructure;
};

#endif //ENV