#include "Maze.h"


Maze::Maze()
{
    this->length = 0;
    this->width = 0;

    mazeStructure = nullptr;
    start = nullptr;
}

//Contract:
//  Pre-Condition: length and width must be greater than 1
//  Post-Condition: A new Env object is created, where data members, 
// length and width is filled.
Maze::Maze(int length, int width):
                        length(length),
                        width(width)
{
    this->mazeStructure = nullptr;
    this->start = nullptr;
}

Maze::~Maze()
{
    //delete memory
    deallocateMazeStructure();
    deallocateStart();
}


int Maze::getLength(void){
    return this->length;
}

int Maze::getWidth(void){
    return this->width;
}

//Contract:
//  Pre-Condition: length must be greater than 1
//  Post-Condition: Stores length in Env
void Maze::setLength(int length){
    this->length = length;
}

//Contract:
//  Pre-Condition: Width must be greater than 1
//  Post-Condition: Stores width in Env
void Maze::setWidth(int width){
    this->width = width;
}

//Contract:
//  Pre-Condition: Argument must not be a null pointer, and must have 3 values
//  Post-Condition: Stores coordinate in start member.
void Maze::setStart(mcpp::Coordinate* start){
    if (this->start != nullptr){
        deallocateStart();
    }

    this->start = new mcpp::Coordinate(start->x, start->y - 1, start->z);
}


mcpp::Coordinate* Maze::getStart(void){
    return this->start;
}

//Contract: 
//  Pre-Condition:
//      - Characters must be 'X' or '.'
//      - mazeStructure and its inner elements, must NOT be nullpointer
//  Post-Condition: EnvStructure is updated with 2D char pointer array.
void Maze::setMazeStructure(char** mazeStructure){
    if (this->mazeStructure != nullptr){
        deallocateMazeStructure();
    }

    this->mazeStructure = mazeStructure;
}

char** Maze::getMazeStructure(void){
    return this->mazeStructure;
}

void Maze::deallocateMazeStructure(){
    //delete memory
    if (this->mazeStructure != nullptr) {
        for(int i =0; i < this->getWidth(); i++){ 
            if (this->mazeStructure[i] != nullptr){
                delete[] this->mazeStructure[i];
                this->mazeStructure[i] = nullptr;
            }
        }
        delete[] this->mazeStructure;
        this->mazeStructure = nullptr;
    }

}

void Maze::deallocateStart(){
    //Deallocate start
    if (this->start != nullptr) {
        delete this->start;
        this->start = nullptr;
    }
}

/* Contract:
*   Pre-Conditions: Maze structure, length, and width members must be filled 
*   Post-Conditions: Member mazeGaps get filled with empty maze coords
*/
void Maze::findMazeGaps(){
    //Iterate through mazeStructure
    for (int i = 0; i < this->getWidth(); i++) { 
        for (int k = 0; k < this->getLength(); k++) {
            if (this->mazeStructure[i][k] == '.'){
                MazeCoordinate tempCoord(i+1, k+1);
                mazeGaps.push_back(tempCoord);
                std::cout << tempCoord.getWidthCoord() << " " 
                          << tempCoord.getLengthCoord() << std::endl; 
            }
        }
    }
}

/*
* Builds the maze at the start coordinate based on the maze structure given
*
*  Contract:
*  Pre-Conditions: Maze class must have all of it's data members filled
*       - Especially start, height, width
*  Post-Conditions: A maze is built in the minecraft world based on the members
*/
void Maze::buildMaze(){
        mcpp::MinecraftConnection mc;

        //Throw error when start member is a null pointer
        if (this->getStart() == nullptr) {
            throw std::invalid_argument("Start member is a null pointer");
        }
                
        for(int w =0; w < this->getWidth(); w++){
            for(int l = 0; l < this->getLength(); l++){ 
                if(tolower(this->getMazeStructure()[w][l]) == 'x'){
                    for (int i = 1; i <= HEIGHT; ++i){
                        std::this_thread::sleep_for(
                                                std::chrono::milliseconds(50));
                        mc.setBlock(*(this->getStart()) + 
                                    mcpp::Coordinate(l, i, w), 
                                    mcpp::Blocks::ACACIA_WOOD_PLANK);

                    }
                }
            }
        }
    }

/* Gets the values of the area that the maze is going to be built
*  You can use this before (or after) the maze structure has been built to 
* getHeights in the maze area.
*
*  Contract:
*  Pre-Conditions: Env class must have all of it's data members correctly filled
*       - Especially start, height, width
*  Post-Conditions: A HeightMap 2D array is created with the area's height value
*/
mcpp::HeightMap Maze::getHeightMaze(){
    //Sets up MinecraftConnection object
    mcpp::MinecraftConnection mc;

    //heights is equal to the maze.getStart value, to the length and width 
    mcpp::HeightMap heights = mc.getHeights(*(this->getStart()), 
                        (mcpp::Coordinate(
                            this->getStart()->x + this->getLength() - 1, 
                            this->getStart()->y, 
                            this->getStart()->z + this->getWidth() -1)));

    return heights;
}

/* Gets the values of the area that the maze is going to be built
*  You can use this before (or after) the maze structure has been built to 
*  getHeights in the maze area.
*
*  Contract:
*  Pre-Conditions: Env class must have all of it's data members correctly filled
*       - Especially start, height, width
*  Post-Conditions: A HeightMap 2D array is created with the area's height value
* The maze area clears and elements that would be changed are prepended to list
*/
mcpp::HeightMap Maze::getHeightMaze(LinkedBlocks& blockList){
    //Sets up MinecraftConnection object
    mcpp::MinecraftConnection mc;
    // delete maze area
    for(int w =0; w < this->getWidth(); w++){
        for(int l = 0; l < this->getLength(); l++){
            for (int i = 1; i <= HEIGHT; ++i){
                mcpp::BlockType currMazeBlock;
                mcpp::BlockType currWorldBlock;
                // get what the supposed block will be based on maze generation
                if (mazeStructure[w][l] == '.'){ 
                    currMazeBlock = mcpp::Blocks::AIR;
                }
                else {
                    currMazeBlock = mcpp::Blocks::ACACIA_WOOD_PLANK;
                }
                currWorldBlock = mc.getBlock(*(this->getStart()) + 
                                             mcpp::Coordinate(l, i, w));

                // store this block based on if it needs to be replaced
                if (currWorldBlock != currMazeBlock){
                    blockList.prepend(*(this->getStart()) + 
                                      mcpp::Coordinate(l, i, w), 
                                      currWorldBlock);
                }
                if (currWorldBlock != mcpp::Blocks::AIR){
                    // clear the maze blocks
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(*(this->getStart()) + mcpp::Coordinate(l, i, w),
                                mcpp::Blocks::AIR);
                }
                

                
            }
        }
    }
    //heights is equal to the maze.getStart value, to length and width
    mcpp::HeightMap heights = mc.getHeights(*(this->getStart()), 
                            (mcpp::Coordinate(
                                this->getStart()->x + this->getLength() - 1,
                                this->getStart()->y, 
                                this->getStart()->z + this->getWidth() -1)));

    return heights;
}

/* Contract:
*  Pre-Conditions:
*  - Assumes that Difference is a filled 2D array, that has the difference of 
*  the highest non-air block of the world, and the
*    player inputted y-coordinate
*  - Maze class must be filled correctly, all members must be correct
*  Post-Conditions: 
*  - This function will specifically check each positive difference value,
*   and build up from the non-highest air block differnce times
*/
void Maze::buildUpTerrain(mcpp::HeightMap& worldHeight, int ** difference) {
    //Set up minecraft connection
    mcpp::MinecraftConnection mc;  
    mcpp::BlockType blockToPlace;

    
    for (int i = 0; i < worldHeight.x_len(); i++) {
        for (int k = 0; k < worldHeight.z_len(); k++) {
            //Checks if the integer value at the difference array is positive
            if(difference[i][k] > 0) {
                // Sets the block to place as the non-highest airblock at the 
                //combination of x, z coordinates.
                // Where worldHeight.get(i, k) holds the y-coordinate 
                //(See GetHeightWorld function for more info)
                blockToPlace = mc.getBlock(
                                           mcpp::Coordinate(
                                            this->getStart()->x +  i,
                                            worldHeight.get(i, k),
                                            this->getStart()->z + k));
        

                //m starts at 1
                //m will increment while m <= Difference at that x,z coordinate
                for (int m = 1; m <= difference[i][k]; m++) {
                    //Will set the block at that coordinate to the previous type
                    //Will go up by 1 in the positive y-direction incrementally
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(mcpp::Coordinate(this->getStart()->x + i,
                                worldHeight.get(i, k) + m, 
                                this->getStart()->z + k),
                                blockToPlace);
                }
            }
        }
    }
}


/* Contract:
*  Pre-Conditions:
*  - Assumes that Difference is a filled 2D array, that has the difference of 
*  the highest non-air block of the world, and the
*    player inputted y-coordinate
*  - Maze class must be filled correctly, all members must be correct
*  Post-Conditions: 
*  - This function will specifically check each negative difference value, 
*  and build down from the non-highest air block,
*  decrementing by 1, difference times.
* - blockList will be prepended with all changed blocks original states in the 
* minecraft world
*/
void Maze::buildDownTerrain(mcpp::HeightMap& worldHeight, int **  difference, 
                            LinkedBlocks& blockList){
    //Set up minecraft connection
    mcpp::MinecraftConnection mc;  
    mcpp::BlockType airBlock = mcpp::BlockType(0);
    mcpp::Coordinate startBlock;

    for (int i = 0; i < worldHeight.x_len(); i++) {
        for (int k = 0; k < worldHeight.z_len(); k++) {
            if(difference[i][k] < 0) {
                //Sets the start coord, going to iterate y-down difference times
                startBlock = mcpp::Coordinate(this->getStart()->x + i, 
                                              worldHeight.get(i, k), 
                                              this->getStart()->z + k);
                for (int m = 0; m > difference[i][k] + HEIGHT; m--) {

                    mcpp::Coordinate currCoord = mcpp::Coordinate(
                                                    this->getStart()->x + i, 
                                                    startBlock.y + m, 
                                                    this->getStart()->z + k);
                    mcpp::BlockType currBlock = mc.getBlock(currCoord);
                    // if the block will be changed it's original state is kept 
                    // in the given LinkedBlocks data structure
                    if (currBlock != airBlock){
                        blockList.prepend(currCoord, currBlock);
                        std::this_thread::sleep_for(
                            std::chrono::milliseconds(50));
                        mc.setBlock(currCoord, airBlock);
                    }
                }
            }
        }
    }
}



/* Contract:
* Pre-conditions:
*  int array is handled and deleted
* Post-conditions:
* an array is instantiated of difference 
* logical length and width of array is given to pass-by-reference integers
*/
int ** Maze::compareHeights(mcpp::HeightMap& worldHeight, int& logicalX, 
                            int& logicalZ) {
    logicalX = worldHeight.x_len();
    logicalZ = worldHeight.z_len();

    // bcreate inbuilt array
    int ** differenceOfHeights = new int*[logicalX];

    for (int i = 0; i < logicalX; ++i){
        differenceOfHeights[i] = new int[logicalZ];
    }

    //For loop to iterate through worldHeight y-values, and envStructure y-value
    for (int i = 0; i < worldHeight.x_len(); i++) {
        for (int k = 0; k < worldHeight.z_len(); k++) {
            int difference = worldHeight.get(i, k) - this->getStart()->y;
            //Negate the difference to indicate that world height is higher 
            if (worldHeight.get(i, k) > this->getStart()->y) {
                if (difference > 0) {
                    difference *= -1;
                }
            }
            //Absolute the difference to indicate world height is less 
            else {
                difference = abs(difference);
            }
            differenceOfHeights[i][k] = difference;
        }
       
    }

    return differenceOfHeights;
}

/* Contract:
*  Pre-Conditions:
*  - array has been initalized with proper length and width members
*  - assumes only one exit exists i.e. it is a perfect maze
*  Post-Conditions: 
*  - a blue carpet will be placed in minecraft at the exit point 
*/
void Maze::placeBlueCarpet(LinkedBlocks& blockList){
    if (mazeStructure == nullptr){
        throw std::runtime_error("Maze Structure has not been initialized yet");
    }

    // Iterate the width for nullptr errors
    for (int i = 0; i < width; ++i) {
        if (mazeStructure[i] == nullptr){
            throw std::runtime_error(
                "Maze Structure has not been initialized yet");
        }
    }

    mcpp::MinecraftConnection mc;

    std::vector<mcpp::Coordinate> carpetCoords;


    // Iterate the length
    for (int j = 0; j < length; ++j) {
        if (mazeStructure[0][j] == '.'){
            carpetCoords.push_back(mcpp::Coordinate(this->getStart()->x + j,
                                                    this->getStart()->y + 1, 
                                                    this->getStart()->z - 1));
            
        }
    }
    
    // Iterate the width 
    for (int i = 1; i < width - 1; ++i) {
        if (mazeStructure[i][length - 1] == '.'){
            carpetCoords.push_back(mcpp::Coordinate(
                                this->getStart()->x + this->getLength(), 
                                this->getStart()->y + 1,
                                this->getStart()->z + i));

        }
        
    }
    
    // Iterate the length at the end
    if (width > 1) {
        for (int j = length - 1; j >= 0; --j) {
            if (mazeStructure[width - 1][j] == '.'){

                carpetCoords.push_back(mcpp::Coordinate(
                                    this->getStart()->x + j,
                                    this->getStart()->y + 1,
                                    this->getStart()->z + this->getWidth()));

            }
        }
    }
    
    // Iterate the width at the end
    if (length > 1) {
        for (int i = width - 2; i > 0; --i) {
            if (mazeStructure[i][0] == '.'){
                carpetCoords.push_back(mcpp::Coordinate(
                                this->getStart()->x - 1,
                                this->getStart()->y + 1, 
                                this->getStart()->z + i));

            }
        }
    }
    
    
    for (mcpp::Coordinate curCoord: carpetCoords){
        // store and set the carpet block to air
        blockList.prepend(curCoord, mc.getBlock(curCoord));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        mc.setBlock(curCoord, mcpp::Blocks::AIR);
        

        // build down 
        mcpp::Coordinate startBlock;
        int height = mc.getHeight(curCoord.x, curCoord.z);
        int diffHeight = height - curCoord.y;
        mcpp::BlockType airBlock = mcpp::BlockType(0);

        if (diffHeight > 0){
            
            //Sets the start coord, going to iterate y-down difference times
            startBlock = mcpp::Coordinate(curCoord.x, height, curCoord.z);
            for (int m = 0; m < diffHeight; ++m) {

                mcpp::BlockType currBlock = mc.getBlock(mcpp::Coordinate(
                                            startBlock.x, 
                                            startBlock.y - m, 
                                            startBlock.z));
                if (currBlock == airBlock){
                }
                else {
                    blockList.prepend(mcpp::Coordinate(startBlock.x, 
                                                    startBlock.y - m, 
                                                    startBlock.z), 
                                        currBlock);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock((mcpp::Coordinate(
                                            startBlock.x, 
                                            startBlock.y - m,
                                            startBlock.z)),
                                mcpp::Blocks::AIR);
                }
            }
        }
        // now build up
        height = mc.getHeight(curCoord.x, curCoord.z);
        diffHeight = curCoord.y - height;

        if (diffHeight > 0){

            mcpp::BlockType blockToPlace = mc.getBlock(mcpp::Coordinate(
                                            curCoord.x,
                                            height, 
                                            curCoord.z));
            
            //Sets the start coord, going to iterate y-up difference times
            startBlock = mcpp::Coordinate(curCoord.x, height, curCoord.z);
            for (int m = 1; m < diffHeight; ++m) {
                mcpp::BlockType currBlock = mc.getBlock(mcpp::Coordinate(
                                        startBlock.x, 
                                        height + m, 
                                        startBlock.z));

                blockList.prepend(mcpp::Coordinate(
                                                    startBlock.x,
                                                    height + m, 
                                                    startBlock.z), 
                                    currBlock);

                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                mc.setBlock((mcpp::Coordinate(startBlock.x, height + m,
                                                startBlock.z)), blockToPlace);
                
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        mc.setBlock(curCoord, mcpp::Blocks::BLUE_CARPET);

    }   
}

/*
* Contract:
*  Pre-Conditions:
*  - blockList is filled with the accurate coordinates and block types that need
*  to be placed
*  Post-Conditions: 
*  - all blocks in the passed linked list will be placed in the minecraft world 
* in the relevant coordinate
*/
void Maze::revertMazeBuild(LinkedBlocks& blockList){
    BlockNode* tempNode = blockList.getHead();
    mcpp::MinecraftConnection mc;
    // iterate through linked list
    while (tempNode) {
        // set block in node
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        mc.setBlock(tempNode->coord, tempNode->block);
        // iterate to next node
        tempNode = tempNode->next;
    }


}

/* Contract:
*  Pre-Conditions:
*  - Assumes that Difference is a filled 2D array, that has the difference of 
* the highest non-air block of the world, and the
*    player inputted y-coordinate
*  - Maze class must be filled correctly, all members must be correct
*  - the built down function must be previously called
*  Post-Conditions: 
*  - This function will revert the build up function and replace all placed 
* blocks by that function with air 
*/
const void Maze::revertBuildUpTerrain(int **  difference, int logicalX, 
                                      int logicalZ){


    //Set up minecraft connection
    mcpp::MinecraftConnection mc;  
    mcpp::BlockType airBlock = mcpp::BlockType(0);
    mcpp::Coordinate startBlock;

    for (int i = 0; i < logicalX; i++) {
        for (int k = 0; k < logicalZ; k++) {
            if(difference[i][k] > 0) {

                //Sets the start coord, going to iterate y-down difference times
                startBlock = mcpp::Coordinate(
                            this->getStart()->x + i,
                            this->getStart()->y, 
                            this->getStart()->z + k);
                for (int m = 0; m < difference[i][k]; m++) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(mcpp::Coordinate(
                                    this->getStart()->x + i, 
                                    startBlock.y - m, 
                                    this->getStart()->z + k), 
                                airBlock);
                    
                }
            }
        }
    }
}

/* Contract:
*  Pre-Conditions:
*  - Assumes that the startCoord and mazeStructure member given is not a nullptr
*  - Assumes length and width are also defined correctly
*  Post-Conditions: 
*  - This Method will print details about the maze
*/
const void Maze::printMaze(mcpp::Coordinate* startCoord) {
    // Check for null pointer
    if (startCoord == nullptr){
        throw std::runtime_error("startCoord given is a null pointer");
    }

    std::cout << "**Printing Maze**\n";
    
    std::cout << "BasePoint: (" << startCoord->x << ", " << startCoord->y 
              << ", "  << startCoord->z << ")\n";
    std::cout << "Structure:\n";

    // Check for null pointer
    if (mazeStructure == nullptr) {
        throw std::runtime_error("mazeStructure is a null pointer");

    }
    // print maze and check for null pointer
    for (int w = 0; w < width; ++w) {
        // Check if each row is a null pointer
        if (mazeStructure[w] == nullptr) {
            throw std::runtime_error(
                        "mazeStructure contains an inner null pointer");
        }
        
        for (int l = 0; l < length; ++l) {
            std::cout << static_cast<char>(tolower(mazeStructure[w][l]));
        }
        std::cout << std::endl;
    }
    std::cout << "**End Printing Maze**\n";
}