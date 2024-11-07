#include "MazeEnhanced.h"

#define MS_DELAY 50
//#define MS_DELAY 0

MazeEnhanced::MazeEnhanced()
{
    this->length = 0;
    this->width = 0;

    mazeStructure = nullptr;
    start = nullptr;
}

//Contract:
//  Pre-Condition: length and width must be greater than 1
//  Post-Condition: A new MazeEnhanced object is created, where data members, 
//  length and width are filled.
MazeEnhanced::MazeEnhanced(int length, int width):
                        length(length),
                        width(width)
{
    this->mazeStructure = nullptr;
    this->start = nullptr;
}




void MazeEnhanced::buildDownTerrain(mcpp::HeightMap& worldHeight, 
                            int **  difference, 
                            LinkedBlocks& blockList) {
    
    // In enhancedmaze no terrain needs to be built down however we do need to 
    // calculate the highest point the maze should reach
}


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
mcpp::HeightMap MazeEnhanced::getHeightMaze(LinkedBlocks& blockList){
    //Sets up MinecraftConnection object
    mcpp::MinecraftConnection mc;

    mcpp::HeightMap heights = mc.getHeights(*(this->getStart()), 
                            (mcpp::Coordinate(
                                this->getStart()->x + this->getLength() - 1,
                                this->getStart()->y, 
                                this->getStart()->z + this->getWidth() -1)));

    int maxHeight = heights.get(0,0);
    // get maximum height of maze area
    for(int w =0; w < this->getWidth(); w++){
        for(int l = 0; l < this->getLength(); l++){
            int currHeight = heights.get(l, w);
            if (maxHeight < currHeight){
                maxHeight = currHeight;
            }
        }
    }
    this->highestPoint = maxHeight + HEIGHT;



    // record changed maze areas
    for(int w =0; w < this->getWidth(); w++){
        for(int l = 0; l < this->getLength(); l++){
        
            // get what the supposed block will be based on maze generation
            if (this->getMazeStructure()[w][l] != '.'){ 

                // add all air blocks found through difference between top of
                // maze and actual height onto list
                
                for (int i = this->highestPoint; i > heights.get(l, w); --i){


                    blockList.prepend(
                                mcpp::Coordinate(this->getStart()->x, 
                                0, 
                                this->getStart()->z) + 
                                mcpp::Coordinate(l, i, w), 
                                mcpp::Blocks::AIR);
                }

                
            }
            
        }
    }
    // we have used no setblocks so the heights HeightMap can be returned

    return heights;
}

void MazeEnhanced::buildUpTerrain(mcpp::HeightMap& worldHeight, 
                                int ** Difference){
    // Terrain is not changed in MazeEnhanced so nothing needs to happen
}

/* Gets the values of the area that the maze is going to be built
*  You can use this before (or after) the maze structure has been built to 
*  getHeights in the maze area.
*
*  Contract:
*  Pre-Conditions: Maze class must have all of it's data members filled.
*       - Especially start, height, width
*  Post-Conditions: A HeightMap 2D array is created with the area's height.
*/
mcpp::HeightMap MazeEnhanced::getHeightMaze(){
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

/*
* Builds the maze at the start coordinate based on the maze structure given
*
*  Contract:
*  Pre-Conditions: Maze class must have all of it's data members filled.
*       - Especially start, height, width
*  Post-Conditions: A maze is built in the minecraft world based on the
*   members set in the Maze class
*/
void MazeEnhanced::buildMaze() {
    mcpp::MinecraftConnection mc;

    mcpp::HeightMap worldHeight = this->getHeightMaze();

    //Throw error when start member is a null pointer
    if (this->getStart() == nullptr) {
        throw std::invalid_argument("Start member is a null pointer");
    }


            
    for(int w =0; w < this->getWidth(); w++){
        for(int l = 0; l < this->getLength(); l++){ 
            if(tolower(this->getMazeStructure()[w][l]) == 'x'){
                for (int i = this->highestPoint; 
                                    i > worldHeight.get(l, w); --i){

                    std::this_thread::sleep_for(
                                    std::chrono::milliseconds(MS_DELAY));
                    mc.setBlock(mcpp::Coordinate(this->getStart()->x, 0, 
                                        this->getStart()->z) + 
                                mcpp::Coordinate(l, i, w), 
                                mcpp::Blocks::ACACIA_WOOD_PLANK);
                   

                }
            }
        }
    }
}


/* Contract:
*  Pre-Conditions:
*  - array has been initalized with proper length and width members
*  - assumes only one exit exists i.e. it is a perfect maze
*  Post-Conditions: 
*  - a blue carpet will be placed in minecraft at the exit point 
*/
void MazeEnhanced::placeBlueCarpet(LinkedBlocks& blockList){

    if (this->getMazeStructure() == nullptr){
        throw std::runtime_error("Maze Structure has not been initialized yet");
    }

    // Iterate the width for nullptr errors
    for (int i = 0; i < this->getWidth(); ++i) {
        if (this->getMazeStructure()[i] == nullptr){
            throw std::runtime_error(
                "Maze Structure has not been initialized yet");
        }
    }

    mcpp::MinecraftConnection mc;

    std::vector<mcpp::Coordinate> carpetCoords;


    // Iterate the length
    for (int j = 0; j < this->getLength(); ++j) {
        if (this->getMazeStructure()[0][j] == '.'){
            carpetCoords.push_back(mcpp::Coordinate(this->getStart()->x + j,
                                                    this->getStart()->y + 1, 
                                                    this->getStart()->z - 1));
            
        }
    }
    
    // Iterate the width 
    for (int i = 1; i < this->getWidth() - 1; ++i) {
        if (this->getMazeStructure()[i][this->getLength() - 1] == '.'){
            carpetCoords.push_back(mcpp::Coordinate(
                                this->getStart()->x + this->getLength(), 
                                this->getStart()->y + 1,
                                this->getStart()->z + i));

        }
        
    }
    
    // Iterate the length at the end
    if (this->getWidth() > 1) {
        for (int j = this->getLength() - 1; j >= 0; --j) {
            if (this->getMazeStructure()[this->getWidth() - 1][j] == '.'){

                carpetCoords.push_back(mcpp::Coordinate(
                                    this->getStart()->x + j,
                                    this->getStart()->y + 1,
                                    this->getStart()->z + this->getWidth()));

            }
        }
    }
    
    // Iterate the width at the end
    if (this->getLength() > 1) {
        for (int i = this->getWidth() - 2; i > 0; --i) {
            if (this->getMazeStructure()[i][0] == '.'){
                carpetCoords.push_back(mcpp::Coordinate(
                                this->getStart()->x - 1,
                                this->getStart()->y + 1, 
                                this->getStart()->z + i));

            }
        }
    }
    
    
    for (mcpp::Coordinate curCoord: carpetCoords){

        curCoord = mcpp::Coordinate (curCoord.x,
                                mc.getHeight(curCoord.x, curCoord.z) + 1,
                                curCoord.z);
        // store and set the carpet block to air
        blockList.prepend(curCoord, mcpp::Blocks::AIR);
        std::this_thread::sleep_for(std::chrono::milliseconds(MS_DELAY));
        mc.setBlock(curCoord, mcpp::Blocks::BLUE_CARPET);

    }   
}

   