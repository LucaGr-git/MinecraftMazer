#ifndef MAZE
#define MAZE

#include <mcpp/mcpp.h>
#include "MazeCoordinate.h"
#include <cstdlib>


 
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
    //  Post-Condition: A new Env object is created, where data members, length and width is filled.
    Maze(int length, int width);
    ~Maze();

    //other methods
    int getLength(void);
    int getWidth(void);

    //Contract:
    //  Pre-Condition: length must be greater than 1
    //  Post-Condition: Stores length in Env
    void setLength(int length);

    //Contract:
    //  Pre-Condition: Width must be greater than 1
    //  Post-Condition: Stores width in Env
    void setWidth(int width);

    //Contract:
    //  Pre-Condition: Argument must not be a null pointer, and must have 3 integer values
    //  Post-Condition: Stores coordinate in start member.
    void setStart(mcpp::Coordinate* start);
    mcpp::Coordinate* getStart(void);

    /* Contract:
    *   Pre-Conditions: Maze structure, length, and width members must be filled correctly
    *   Post-Conditions: Member mazeGaps get filled with empty maze coords
    */
    void findMazeGaps();

    //Contract: 
    //  Pre-Condition:
    //      - Characters must be 'X' or '.'
    //      - envStructure and its inner elements, must NOT be nullpointer
    //  Post-Condition: EnvStructure is updated with 2D char pointer array.
    void setMazeStructure(char** mazeStructure);
    char** getMazeStructure(void);


    void buildMaze();

    /* Gets the values of the area that the maze is going to be built
    *  You can use this before (or after) the maze structure has been built to getHeights
    *  in the maze area.
    *
    *  Contract:
    *  Pre-Conditions: Env class must have all of it's data members correctly filled.
    *       - Especially start, height, width
    *  Post-Conditions: A HeightMap 2D array is created with the area's height values.
    */
    mcpp::HeightMap getHeightMaze();


    /* Contract:
    *  Pre-Conditions:
    *  - Assumes that Difference is a filled 2D array, that has the difference of the highest non-air block of the world, and the
    *    player inputted y-coordinate
    *  - Maze class must be filled correctly, all members must be correct
    *  Post-Conditions: 
    *  - This function will specifically check each positive difference value, and build up from the non-highest air block differnce times
    */
    void buildUpTerrain(mcpp::HeightMap& worldHeight, int ** Difference);

    /* Contract:
    *  Pre-Conditions:
    *  - Assumes that Difference is a filled 2D array, that has the difference of the highest non-air block of the world, and the
    *    player inputted y-coordinate
    *  - Maze class must be filled correctly, all members must be correct
    *  Post-Conditions: 
    *  - This function will specifically check each negative difference value, and build down from the non-highest air block,
    *  decrementing by 1, difference times.
    */
    void buildDownTerrain(mcpp::HeightMap& worldHeight, int ** Difference);


    /* WIP : CompareHeightsFunction
    *  Parameters: mcpp::HeightMap, env object
    *  Conditions:
    */
    int ** compareHeights(mcpp::HeightMap& worldHeight, int& logicalX, int& logicalZ);
    
    const void RevertBuildUpTerrain(int **  difference, int logicalX, int logicalZ);


private:
    /* data */
    int length;
    int width;

    mcpp::Coordinate* start;

    char** mazeStructure;

    void deallocateMazeStructure();

    void deallocateStart();




};

#endif //ENV