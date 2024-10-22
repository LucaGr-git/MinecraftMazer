#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"

#include "Utils.h"


#define NORMAL_MODE 0
#define TESTING_MODE 1
const int ABOVE_GROUND_HEIGHT = 1;

enum States{
    ST_Main,
    ST_GetMaze,
    ST_SolveMaze,
    ST_Creators,
    ST_Exit
};

int main(void){

    //bool mode = NORMAL_MODE;
    //read Mode

    mcpp::MinecraftConnection mc;

    mc.doCommand("time set day"); 

    States curState = ST_Main;


    // Create instance of Maze class
    Maze maze(1, 1);

    // varaibles for 2d array
    int logicalX;
    int logicalZ;
    //Create a 2D int array that will run parallel with worldHeight and MazeStructure
    int ** difference; 

    // boolean variable for wheteher a maze has been built
    bool hasBuilt = false;
    while (curState != ST_Exit)
    {   

        printMainMenu(); // main menu options are printed

        char inputChar;
        std::cin >> inputChar;

        int intState;

        if (isdigit(inputChar)){
            // if they inputted a digit the program takes the input as a digit
            intState = inputChar - '0';
        }
        else{
            // If they have inputted a non digit data type the intState and subsequent State is set to -1
            intState = -1;
        }

        // State variable is updated
        curState = States(--intState);
    

        inputChar = '0'; // inputChar is reset for the
        // if statements are used to determine what should be done based on menu 'State'
        if (curState == ST_Main){
            while (inputChar != '1'  && inputChar != '2' && inputChar != '3'){

                printGenerateMazeMenu();
                
                std::cin >> inputChar;

                if (inputChar == '2'){
                    // TODO complete menu portion
                    std::cout << "TODO : You pressed 1: this hasn't been developed yet";

                }
                else if (inputChar == '1'){
                    //Read the width and width of maze (from user input)
                    int mazeLength = 0;
                    int mazeWidth = 0;

                    readMazeSize(mazeLength, mazeWidth);

                    maze.setLength(mazeLength);
                    maze.setWidth(mazeWidth);


                    // Read the structure of the maze
                    char** mazeStructure;
                    mazeStructure = new char*[mazeLength];
                    for(int i =0; i < mazeLength; i++){
                        mazeStructure[i] = new char[mazeWidth];
                    }
                    readMazeStdin(mazeStructure, mazeLength, mazeWidth);

                    maze.setMazeStructure(mazeStructure);


                    // Read the start coordinate
                    mcpp::Coordinate* start = nullptr;
                    readMazeStart(&start);
                    // std::cout << start->x << "," << start->y << "," << start->z << std::endl;

                    maze.setStart(start);

                    
                }
                else if (inputChar == '3'){

                }
                else {
                    std::cout << "Error: input a valid number between 1 and 3 ...\n";
                }
            }
        }
        else if (curState == ST_GetMaze){
            // If the maze is in it's default state i.e. a maze has not been loaded a message is displayed
            if (maze.getStart() == nullptr || maze.getMazeStructure() == nullptr){
                std::cout << "You have not loaded a maze yet.";
            }
            else {
                
                // Create a HeightMap variable, and call the function to get the heights of all blocks within the maze coordinates
                mcpp::HeightMap worldHeight = maze.getHeightMaze();

                difference = maze.compareHeights(worldHeight, logicalX, logicalZ);



                
                //IMPORTANT: FROM THIS SECTION ONWARDS ITS VERY IMPORTANT THE FUNCTION ARE IN THIS ORDER TO SUPPORT EDGE CASES

                //First call BuildDownTerrain function
                maze.buildDownTerrain(worldHeight, difference);

                //Then call GetHeightMaze again to generate a new heightmap
                worldHeight = maze.getHeightMaze();
                
                // Delete difference array 

                for (int i = 0; i < logicalX; ++i){
                    delete [] difference[i];
                }
                delete [] difference;

                //Similarly call difference again, to get the new difference
                difference = maze.compareHeights(worldHeight, logicalX, logicalZ);

                //Call the Build up Terrain function
                maze.buildUpTerrain(worldHeight, difference);
                //Construct the environment
                maze.buildMaze();
                hasBuilt = true;
            }

            
        }
        else if (curState == ST_SolveMaze){
            while (inputChar != '1'  && inputChar != '2' && inputChar != '3'){
                // Print the solve maze sub-menu
                printSolveMazeMenu();

                std::cin >> inputChar;
                
                // Solve manually menu function
                if (inputChar == '1'){
                    Agent player(mcpp::Coordinate(0, 0, 0));
                    maze.findMazeGaps();
                    MazeCoordinate randCoord = player.getRandomCoord(&maze);
                    player.teleportPlayer(*(maze.getStart()) + mcpp::Coordinate(randCoord.getLengthCoord(), ABOVE_GROUND_HEIGHT, randCoord.getWidthCoord()));
                    

                }
                else if (inputChar == '2'){
                    std::cout << "TODO : You pressed 2: this hasn't been developed yet";
                    


                }
                else  if (inputChar == '3'){

                }
                else{
                    std::cout << "Error: input a valid number between 1 and 3 ...\n";
                }
            }
        }
        else if (curState == ST_Creators){
            printTeamInfo();
        }
        else if (curState == ST_Exit){
            
        }

        else{
            std::cout << "Error: input a valid number between 1 and 5 ...\n";
        }

        
    }
    if (hasBuilt){
        maze.RevertBuildUpTerrain(difference, logicalX, logicalZ);
    }

    printExitMassage();


    return EXIT_SUCCESS;

}