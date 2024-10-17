#ifndef MAZE
#define MAZE

#include <mcpp/mcpp.h>
#include "MazeCoordinate.h"
#include <cstdlib>


 
class Maze
{
public:

    static const int HEIGHT = 3;

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

    /*Contract:
    *   Pre-Conditions: Maze structure, length, and width members must be filled correctly
    *   Post-Conditions: Member mazeGaps get filled with empty maze coords
    */
    void findMazeGaps();

    MazeCoordinate getRandomCoord();

    //Contract: 
    //  Pre-Condition:
    //      - Characters must be 'X' or '.'
    //      - envStructure and its inner elements, must NOT be nullpointer
    //  Post-Condition: EnvStructure is updated with 2D char pointer array.
    void setMazeStructure(char** mazeStructure);
    char** getMazeStructure(void);


    void buildMaze(){
        mcpp::MinecraftConnection mc;

        //Throw error when start member is a null pointer
        if (this->getStart() == nullptr) {
            throw std::invalid_argument("Start member is a null pointer");
        }
        
        // mc.setPlayerPosition(*(env->getStart()) + mcpp::Coordinate(0, 1, 0));
        
        for(int h =0; h < this->getLength(); h++){
            for(int w = 0; w < this->getWidth(); w++){
                if((this->getMazeStructure())[h][w] == 'x'){
                    for (int i = 1; i <= HEIGHT; ++i){
                        mc.setBlock(*(this->getStart()) + mcpp::Coordinate(h, i, w), mcpp::Blocks::ACACIA_WOOD_PLANK);
                    }
                }
            }
        }
    }


    /* Gets the values of the area that the maze is going to be built
    *  You can use this before (or after) the maze structure has been built to getHeights
    *  in the maze area.
    *
    *  Contract:
    *  Pre-Conditions: Env class must have all of it's data members correctly filled.
    *       - Especially start, height, width
    *  Post-Conditions: A HeightMap 2D vector is created with the area's height values.
    */
    mcpp::HeightMap getHeightMaze(){
        //Sets up MinecraftConnection object
        mcpp::MinecraftConnection mc;
        // delete maze area
        for(int h =0; h < this->getLength(); h++){
            for(int w = 0; w < this->getWidth(); w++){
                for (int i = 1; i <= HEIGHT; ++i){
                    mc.setBlock(*(this->getStart()) + mcpp::Coordinate(h, i, w), mcpp::Blocks::AIR);
                    
                    
                }
            }
        }
        //heights is equal to the maze.getStart value, to the length and width values specified by the user
        mcpp::HeightMap heights = mc.getHeights(*(this->getStart()), (mcpp::Coordinate(this->getStart()->x + this->getLength() - 1, this->getStart()->y, this->getStart()->z + this->getWidth() -1)));
        
        //FIXME: DEBUG PRINT STATEMENT TO CHECK heights values
        // for (int i = 0; i < heights.x_len(); i++) {
        //     for (int k = 0; k < heights.z_len(); k++) {
        //         std::cout << heights.get(i, k) << " ";
        //     }
        //     std::cout << std::endl;

        // }

        return heights;
    }

    /* Contract:
    *  Pre-Conditions:
    *  - Assumes that Difference is a filled 2D vector, that has the difference of the highest non-air block of the world, and the
    *    player inputted y-coordinate
    *  - Maze class must be filled correctly, all members must be correct
    *  Post-Conditions: 
    *  - This function will specifically check each positive difference value, and build up from the non-highest air block differnce times
    */
    void buildUpTerrain(mcpp::HeightMap& worldHeight, std::vector<std::vector<int>> Difference) {
        //Set up minecraft connection
        mcpp::MinecraftConnection mc;  
        mcpp::BlockType blockToPlace;

        
        for (int i = 0; i < worldHeight.x_len(); i++) {
            for (int k = 0; k < worldHeight.z_len(); k++) {
                //Checks if the integer value at the difference vector is positive
                if(Difference[i][k] > 0) {
                    // Sets the block to place as the non-highest airblock at the combination of x, z coordinates.
                    // Where worldHeight.get(i, k) holds the y-coordinate (See GetHeightWorld function for more info)
                    blockToPlace = mc.getBlock(mcpp::Coordinate(this->getStart()->x + i, worldHeight.get(i, k), this->getStart()->z + k));
                    
                    //FIXME: Remove cout (USED FOR DEBUG)
                    // std::cout << blockToPlace.id << ": " << Difference[i][k] << std::endl;

                    //m starts at 1
                    //m will increment while m <= Difference at that x,z coordinate
                    for (int m = 1; m <= Difference[i][k]; m++) {
                        //Will set the block at that coordinate to the type specified earlier in function
                        //Will go up by 1 in the positive y-direction incrementally
                        mc.setBlock(mcpp::Coordinate(this->getStart()->x + i, worldHeight.get(i, k) + m, this->getStart()->z + k), blockToPlace);
                    }
                }
            }
        }
    }

    /* Contract:
    *  Pre-Conditions:
    *  - Assumes that Difference is a filled 2D vector, that has the difference of the highest non-air block of the world, and the
    *    player inputted y-coordinate
    *  - Maze class must be filled correctly, all members must be correct
    *  Post-Conditions: 
    *  - This function will specifically check each negative difference value, and build down from the non-highest air block,
    *  decrementing by 1, difference times.
    */
    void buildDownTerrain(mcpp::HeightMap& worldHeight, std::vector<std::vector<int>> Difference){
        //Set up minecraft connection
        mcpp::MinecraftConnection mc;  
        mcpp::BlockType airBlock = mcpp::BlockType(0);
        mcpp::Coordinate startBlock;

        
        for (int i = 0; i < worldHeight.x_len(); i++) {
            for (int k = 0; k < worldHeight.z_len(); k++) {
                if(Difference[i][k] < 0) {
                    //Sets the start coord, going to iterate y-down difference times
                    startBlock = mcpp::Coordinate(this->getStart()->x + i, worldHeight.get(i, k), this->getStart()->z + k);
                    for (int m = 0; m > Difference[i][k] + HEIGHT; m--) {
                        mc.setBlock(mcpp::Coordinate(this->getStart()->x + i, startBlock.y + m, this->getStart()->z + k), airBlock);
                    }
                }
            }
        }
    }



    /* WIP : CompareHeightsFunction
    *  Parameters: mcpp::HeightMap, env object
    *  Conditions:
    */
    std::vector<std::vector<int>> compareHeights(mcpp::HeightMap& worldHeight) {
        std::vector<std::vector<int>> differenceOfHeights(worldHeight.x_len(), std::vector<int>(worldHeight.z_len()));

        //For loop to iterate through worldHeight y-values, and envStructure y-values
        for (int i = 0; i < worldHeight.x_len(); i++) {
            for (int k = 0; k < worldHeight.z_len(); k++) {
                int difference = worldHeight.get(i, k) - this->getStart()->y;
                //Negate the difference to indicate that world height is higher than user-y height
                if (worldHeight.get(i, k) > this->getStart()->y) {
                    if (difference > 0) {
                        difference *= -1;
                    }
                }
                //Absolute the difference to indicate world height is less than user-y height
                else {
                    difference = abs(difference);
                }
                differenceOfHeights[i][k] = difference;
                //FIXME: TEST PRINT TO CHECK DIFFERNCE SHOWS UP CORRECTLY
                // std::cout << differenceOfHeights[i][k] << " ";
            }
            //FIXME: TEST PRINT TO CHECK DIFFERENCE SHOWS UP CORRECTLY
            // std::cout << std::endl;
        }

        return differenceOfHeights;
    }



private:
    /* data */
    int length;
    int width;

    mcpp::Coordinate* start;

    std::vector<MazeCoordinate> mazeGaps;

    char** mazeStructure;

    void deallocateMazeStructure();

    void deallocateStart();




};

#endif //ENV