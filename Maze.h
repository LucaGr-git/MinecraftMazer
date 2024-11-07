#ifndef MAZE
#define MAZE

#include <mcpp/mcpp.h>
#include "MazeCoordinate.h"
#include "LinkedBlocks.h"
#include "BlockNode.h"
#include <cstdlib>
#include <thread>
#include <chrono>
#include <cmath>


 
class Maze
{
public:
    //Data memebers
    static const int HEIGHT = 3;
    std::vector<MazeCoordinate> mazeGaps;


    //constructors and deconstructors
    Maze();

    //Contract:
    //  Pre-Condition: length and width must be greater than 1
    //  Post-Condition: A new Env object is created, where data members, 
    //  length and width is filled.
    Maze(int length, int width);
    virtual ~Maze();

    //other methods
    virtual int getLength(void);
    virtual int getWidth(void);

    //Contract:
    //  Pre-Condition: length must be greater than 1
    //  Post-Condition: Stores length in Env
    virtual void setLength(int length);

    //Contract:
    //  Pre-Condition: Width must be greater than 1
    //  Post-Condition: Stores width in Env
    virtual void setWidth(int width);

    //Contract:
    //  Pre-Condition: coordinate must have 3 values
    //  Post-Condition: Stores coordinate in start member.
    virtual void setStart(mcpp::Coordinate start);
    virtual mcpp::Coordinate* getStart(void);

    /* Contract:
    *   Pre-Conditions: Maze structure, length, and width members must be filled
    *   Post-Conditions: Member mazeGaps get filled with empty maze coords
    */
    virtual void findMazeGaps();

    //Contract: 
    //  Pre-Condition:
    //      - Characters must be 'X' or '.'
    //      - mazeStructure and its inner elements, must NOT be nullpointer
    //      - oldWidth is correct`
    //  Post-Condition: EnvStructure is updated with 2D char pointer array.
    virtual void setMazeStructure(char** mazeStructure, int oldWidth);
    virtual char** getMazeStructure(void);
    
    /*
    * Builds the maze at the start coordinate based on the maze structure given
    *
    *  Contract:
    *  Pre-Conditions: Maze class must have all of it's data members filled.
    *       - Especially start, height, width
    *  Post-Conditions: A maze is built in the minecraft world based on the
    *   members set in the Maze class
    */
    virtual void buildMaze();

    /* Gets the values of the area that the maze is going to be built
    *  You can use this before (or after) the maze structure has been built to 
    *  getHeights in the maze area.
    *
    *  Contract:
    *  Pre-Conditions: Maze class must have all of it's data members filled.
    *       - Especially start, height, width
    *  Post-Conditions: A HeightMap 2D array is created with the area's height.
    */
    virtual mcpp::HeightMap getHeightMaze();


    /* Gets the values of the area that the maze is going to be built
    *  You can use this before (or after) the maze structure has been built to 
    *  getHeights in the maze area.
    *
    *  Contract:
    *  Pre-Conditions: Env class must have all of it's data members correctly 
    *  filled.
    *       - Especially start, height, width
    *  Post-Conditions: A HeightMap 2D array is created with the area's height 
    * The maze clears and all elements that would be changed are added to list
    */
    virtual mcpp::HeightMap getHeightMaze(LinkedBlocks& blockList);

    /* Contract:
    *  Pre-Conditions:
    *  - Assumes that Difference is a filled 2D array, that has the difference  
    *   of the highest non-air block of the world, and the
    *    player inputted y-coordinate
    *  - Maze class must be filled correctly, all members must be correct
    *  Post-Conditions: 
    *  - This function will specifically check each positive difference value, 
    *   and build up from the non-highest air block differnce times
    */
    virtual void buildUpTerrain(mcpp::HeightMap& worldHeight, 
                                int ** Difference);

    /* Contract:
    *  Pre-Conditions:
    *  - Assumes that Difference is a filled 2D array, that has the difference 
    *    of the highest non-air block of the world, and the
    *    player inputted y-coordinate
    *  - Maze class must be filled correctly, all members must be correct
    *  Post-Conditions: 
    *  - This function will specifically check each negative difference value, 
    *    and build down from the non-highest air block,
    *  decrementing by 1, difference times.
    *  - blockList will be prepended with all changed blocks original states in 
    *   the minecraft world
    */
    virtual void buildDownTerrain(mcpp::HeightMap& worldHeight, 
                                int ** Difference, 
                                LinkedBlocks& blockList);


    /* WIP : CompareHeightsFunction
    *  Parameters: mcpp::HeightMap, env object
    *  Conditions:
    */
    virtual int ** compareHeights(mcpp::HeightMap& worldHeight, int& logicalX, 
                          int& logicalZ);

    /* Contract:
    *  Pre-Conditions:
    *  - Assumes that Difference is a filled 2D array, that has the difference 
    *    of the highest non-air block of the world, and the
    *    player inputted y-coordinate
    *  - Maze class must be filled correctly, all members must be correct
    *  - the built down function must be previously called
    *  Post-Conditions: 
    *  - This function will revert the build up function and replace 
    *   all placed blocks by that function with air 
    */
    virtual const void revertBuildUpTerrain(int **  difference, int logicalX, 
                                    int logicalZ);

    /* Contract:
    *  Pre-Conditions:
    *  - array has been initalized with proper length and width members
    *  - assumes only one exit exists i.e. it is a perfect maze
    *  Post-Conditions: 
    *  - a blue carpet will be placed in minecraft at the exit point 
    */
    virtual void placeBlueCarpet(LinkedBlocks& blockList);

    /*
    * Contract:
    *  Pre-Conditions:
    *  - blockList is filled with the accurate coordinates and block types that 
    *   need to be placed
    *  Post-Conditions: 
    *  - all blocks in the passed linked list will be placed in the minecraft 
    *   world in the relevant coordinate
    */
    virtual void revertMazeBuild(LinkedBlocks& blockList);

    /* Contract:
    *  Pre-Conditions:
    *  - Assumes that the startCoord and mazeStructure is given is not nullptr
    *  - Assumes length and width are also defined correctly
    *  Post-Conditions: 
    *  - This Method will print details about the maze
    */
    virtual const void printMaze(mcpp::Coordinate startCoord);

    virtual int findClosestGapDist();
    
private:
    /* data */
    int length;
    int width;

    mcpp::Coordinate* start;

    char** mazeStructure;
    // Contract:
    // PreCondition: oldWidth is correct
    virtual void deallocateMazeStructure(int oldWidth);

    virtual void deallocateStart();

    

};

#endif //ENV