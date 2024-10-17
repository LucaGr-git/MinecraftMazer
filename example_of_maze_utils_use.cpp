#include <iostream>
#include "Maze.h"
#include <mcpp/mcpp.h>
#include "Utils.h"
#include <vector>


int main(void){

    //Read the width and width of maze (from user input)
    int mazeLength = 0;
    int mazeWidth = 0;

    readMazeSize(mazeLength, mazeWidth);

    // Create instance of Maze class
    Maze maze(mazeLength, mazeWidth);
    // std::cout << "Height: " << env.getHeight() << ", Width: " 
    //                                 << env.getWidth() << std::endl;

    // Read the structure of the maze
    char** mazeStructure;
    mazeStructure = new char*[mazeLength];
    for(int i =0; i < mazeLength; i++){
        mazeStructure[i] = new char[mazeWidth];
    }
    readMazeStdin(mazeStructure, mazeLength, mazeWidth);

    maze.setMazeStructure(mazeStructure);

    // for (int row = 0; row < env.getHeight(); row++){
    //     for (int col = 0; col < env.getWidth(); col++){
    //         std::cout << env.getEnvStructure()[row][col];
    //     }
    //     std::cout << std::endl;
    // }

    
    // Read the start coordinate
    mcpp::Coordinate* start = nullptr;
    readMazeStart(&start);
    // std::cout << start->x << "," << start->y << "," << start->z << std::endl;

    maze.setStart(start);


    // Create a HeightMap variable, and call the function to get the heights of all blocks within the maze coordinates
    mcpp::HeightMap worldHeight = getHeightMaze(&maze);

    //Create a 2D int vector that will run parallel with worldHeight and MazeStructure
    std::vector<std::vector<int>> difference = compareHeights(worldHeight, &maze);


    
    //IMPORTANT: FROM THIS SECTION ONWARDS ITS VERY IMPORTANT THE FUNCTION ARE IN THIS ORDER TO SUPPORT EDGE CASES

    //First call BuildDownTerrain function
    buildDownTerrain(worldHeight, difference, &maze);

    //Then call GetHeightMaze again to generate a new heightmap
    worldHeight = getHeightMaze(&maze);

    //Similarly call difference again, to get the new difference
    difference = compareHeights(worldHeight, &maze);

    //Call the Build up Terrain function
    buildUpTerrain(worldHeight, difference, &maze);
    //Construct the environment
    buildMaze(&maze);

    
    return EXIT_SUCCESS;
}
