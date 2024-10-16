#include <iostream>
#include "Maze.h"
#include <mcpp/mcpp.h>
#include <cctype>

void ReadMazeSize(int& mazeLength, int& mazeWidth){
    
    std::cout << "Enter the size of the rectangular Environment (H, W): " << std::endl;
    std::cin >> mazeLength;
    std::cin >> mazeWidth;
    //Legnth and Width > 0
    //Checking if Length and Width are valid
    if (mazeLength <= 0 || mazeWidth <= 0) {
        throw std::invalid_argument("Length or width argument is incorrect!");
    }

}

void ReadMazeStart(mcpp::Coordinate** start){
    //Checking if start is nullptr
    if (start == nullptr){
        throw std::invalid_argument("The pointer must not be null!");
    }

    int x=0;
    int y=0;
    int z=0;
    std::cout << "Enter the start coordinate of rectangular Environment (X, Y, Z): " << std::endl;
    std::cin >> x;
    std::cin >> y;
    std::cin >> z;

    *start = new mcpp::Coordinate(x, y, z);
}


void readMazeStdin(char** MazeStruct, int length, int width){
    int charsRead = 0;
    char readC;

    //Checking the outer char 2D array is not a nullptr
    if (MazeStruct == nullptr){
        throw std::invalid_argument("MazeStruct outer pointer must not be null!");
    }

    for (int row = 0; row < length; row++){
        //Checking that the inner part is not null.
        if (MazeStruct[row] == nullptr){
            throw std::invalid_argument("MazeStruct inner pointer must not be null!");
        }
        for (int col = 0; col < width; col++){
            if(std::cin.good()){
                std::cin >> readC;
                readC = tolower(readC);
                //Error checking for if the user entered 'x' or '.'
                if (readC != 'x' && readC != '.') {
                    throw std::invalid_argument("Must type 'x' (or 'X') for solid block, or '.' for gap");
                }

                MazeStruct[row][col] = readC;
                ++charsRead;
            }
        }
        
    }

    //Error checking that charsRead matches the length * width formula
    if (charsRead != (length * width)) {
        throw std::invalid_argument("Height or width does not match user input");
    }
    
}


void BuildMaze(Maze* maze){
    mcpp::MinecraftConnection mc;

    //Throw error when start member is a null pointer
    if (maze->getStart() == nullptr) {
        throw std::invalid_argument("Start member is a null pointer");
    }
    
    // mc.setPlayerPosition(*(env->getStart()) + mcpp::Coordinate(0, 1, 0));
    
    for(int h =0; h < maze->getLength(); h++){
        for(int w = 0; w < maze->getWidth(); w++){
            if((maze->getMazeStructure())[h][w] == 'x'){
                mc.setBlock(*(maze->getStart()) + mcpp::Coordinate(h, 1, w), mcpp::Blocks::ACACIA_WOOD_PLANK);
                mc.setBlock(*(maze->getStart()) + mcpp::Coordinate(h, 2, w), mcpp::Blocks::ACACIA_WOOD_PLANK);
                mc.setBlock(*(maze->getStart()) + mcpp::Coordinate(h, 3, w), mcpp::Blocks::ACACIA_WOOD_PLANK);
            }
            else if ((maze->getMazeStructure())[h][w] == '.'){
                mc.setBlock(*(maze->getStart()) + mcpp::Coordinate(h, 1, w), mcpp::Blocks::AIR);
                mc.setBlock(*(maze->getStart()) + mcpp::Coordinate(h, 2, w), mcpp::Blocks::AIR);
                mc.setBlock(*(maze->getStart()) + mcpp::Coordinate(h, 3, w), mcpp::Blocks::AIR);
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
mcpp::HeightMap GetHeightMaze(Maze* maze){
    //Sets up MinecraftConnection object
    mcpp::MinecraftConnection mc;

    //heights is equal to the maze.getStart value, to the length and width values specified by the user
    mcpp::HeightMap heights = mc.getHeights(*(maze->getStart()), (mcpp::Coordinate(maze->getStart()->x + maze->getLength() - 1, maze->getStart()->y, maze->getStart()->z + maze->getWidth() -1)));
    
    //FIXME: DEBUG PRINT STATEMENT TO CHECK heights values
    // for (int i = 0; i < heights.x_len(); i++) {
    //     for (int k = 0; k < heights.z_len(); k++) {
    //         std::cout << heights.get(i, k) << " ";
    //     }
    //     std::cout << std::endl;

    // }

    return heights;
}

/* WIP : CompareHeightsFunction
*  Parameters: mcpp::HeightMap, env object
*  Conditions:
*/
std::vector<std::vector<int>> CompareHeights(mcpp::HeightMap& worldHeight, Maze* maze) {
    std::vector<std::vector<int>> differenceOfHeights(worldHeight.x_len(), std::vector<int>(worldHeight.z_len()));

    //For loop to iterate through worldHeight y-values, and envStructure y-values
    for (int i = 0; i < worldHeight.x_len(); i++) {
        for (int k = 0; k < worldHeight.z_len(); k++) {
            int difference = worldHeight.get(i, k) - maze->getStart()->y;
            //Negate the difference to indicate that world height is higher than user-y height
            if (worldHeight.get(i, k) > maze->getStart()->y) {
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

/* Contract:
*  Pre-Conditions:
*  - Assumes that Difference is a filled 2D vector, that has the difference of the highest non-air block of the world, and the
*    player inputted y-coordinate
*  - Maze class must be filled correctly, all members must be correct
*  Post-Conditions: 
*  - This function will specifically check each positive difference value, and build up from the non-highest air block differnce times
*/
void BuildUpTerrain(mcpp::HeightMap& worldHeight, std::vector<std::vector<int>> Difference, Maze* maze) {
    //Set up minecraft connection
    mcpp::MinecraftConnection mc;  
    mcpp::BlockType blockToPlace;
    
    for (int i = 0; i < worldHeight.x_len(); i++) {
        for (int k = 0; k < worldHeight.z_len(); k++) {
            //Checks if the integer value at the difference vector is positive
            if(Difference[i][k] > 0) {
                // Sets the block to place as the non-highest airblock at the combination of x, z coordinates.
                // Where worldHeight.get(i, k) holds the y-coordinate (See GetHeightWorld function for more info)
                blockToPlace = mc.getBlock(mcpp::Coordinate(maze->getStart()->x + i, worldHeight.get(i, k), maze->getStart()->z + k));
                
                //FIXME: Remove cout (USED FOR DEBUG)
                // std::cout << blockToPlace.id << ": " << Difference[i][k] << std::endl;

                //m starts at 1
                //m will increment while m <= Difference at that x,z coordinate
                for (int m = 1; m <= Difference[i][k]; m++) {
                    //Will set the block at that coordinate to the type specified earlier in function
                    //Will go up by 1 in the positive y-direction incrementally
                    mc.setBlock(mcpp::Coordinate(maze->getStart()->x + i, worldHeight.get(i, k) + m, maze->getStart()->z + k), blockToPlace);
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
void BuildDownTerrain(mcpp::HeightMap& worldHeight, std::vector<std::vector<int>> Difference, Maze* maze){
    //Set up minecraft connection
    mcpp::MinecraftConnection mc;  
    mcpp::BlockType airBlock = mcpp::BlockType(0);
    mcpp::Coordinate startBlock;

    
    for (int i = 0; i < worldHeight.x_len(); i++) {
        for (int k = 0; k < worldHeight.z_len(); k++) {
            if(Difference[i][k] < 0) {
                //Sets the start coord, going to iterate y-down difference times
                startBlock = mcpp::Coordinate(maze->getStart()->x + i, worldHeight.get(i, k), maze->getStart()->z + k);
                for (int m = 0; m > Difference[i][k] + 3; m--) {
                    mc.setBlock(mcpp::Coordinate(maze->getStart()->x + i, startBlock.y + m, maze->getStart()->z + k), airBlock);
                }
            }
        }
    }
}