#ifndef MAZE
#define MAZE

#include <mcpp/mcpp.h>



class Maze
{
public:
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

    //Contract: 
    //  Pre-Condition:
    //      - Characters must be 'X' or '.'
    //      - envStructure and its inner elements, must NOT be nullpointer
    //  Post-Condition: EnvStructure is updated with 2D char pointer array.
    void setMazeStructure(char** mazeStructure);
    char** getMazeStructure(void);




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