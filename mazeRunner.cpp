#include <iostream>

#include <mcpp/mcpp.h>
#include <cstring>
#include <thread>
#include <chrono>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include "LinkedBlocks.h"
#include "BlockNode.h"

#include "Utils.h"

#include "mazeGenerator.h"

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

int main(int argc, char** argv){

    bool mode = NORMAL_MODE;
    //read Mode
    // start at 1 to ignore executable
    for (int i = 1; i < argc; ++i) { 
        if (strcmp(argv[i], "-testmode") == 0){
            mode = TESTING_MODE;
        }
        else {
            std::cout << argv[i] << " is not a valid argument\n";
        }
    }

    mcpp::MinecraftConnection mc;

    mc.doCommand("time set day"); 

    States curState = ST_Main;


    // Create instance of Maze class
    Maze maze(1, 1);
    // Create a cordinate variable to keep track of inputted start coordinate
    mcpp::Coordinate* start = nullptr;

    // varaibles for 2d array
    int logicalX;
    int logicalZ;
    //Create a 2D int array that will run parallel with worldHeight and 
    // MazeStructure
    int ** difference = nullptr; 
    // create linkedblock list
    LinkedBlocks blockList;

    // boolean variable for wheteher a maze has been built
    bool hasBuilt = false;
    printStartText();
    while (curState != ST_Exit)
    {   
        // main menu options are printed
        printMainMenu(); 

        char inputChar;
        std::cin >> inputChar;

        int intState;

        if (isdigit(inputChar)){
            // if they inputted a digit the program takes the input as a digit
            intState = inputChar - '0';
        }
        else{
            // If they have inputted a non digit data type the intState and 
            // subsequent State is set to -1
            intState = -1;
        }

        // State variable is updated
        curState = States(--intState);
    
        // inputChar is reset for the
        inputChar = '0'; 
        // if statements are determine what should be done based on state
        if (curState == ST_Main){
            while (inputChar != '1'  && inputChar != '2' && inputChar != '3'){

                printGenerateMazeMenu();
                
                std::cin >> inputChar;

                if (inputChar == '2'){
                    try {

                        srand(std::time(0));

                        readMazeStart(start, false);

                           
                        //Read the width and width of maze (from user input)
                        int rows = 0;
                        int cols = 0;

                        //height = 7 cols = 5                    
                        readMazeSize(cols, rows);

                        maze.setLength(cols);
                        maze.setWidth(rows);

                        

                        // Read the structure of the maze
                        char** mazeStructure;
                        mazeStructure = new char*[rows];
                        for(int i =0; i < rows; i++){
                            mazeStructure[i] = new char[cols]; //becareful
                        }

                        //initialize maze size with walls and empty odd cells
                        unsigned int spawnRow = 0;
                        unsigned int spawnCol = 0;
                        
                        std::vector<std::vector<int>> visitedCells(rows, 
                                                std::vector<int>(cols, 0));

                        bool randomGenerate;
                        //normal mode
                        if (!mode) {
                            initializeMaze(mazeStructure, rows, cols);
        
                            //get random spawn location
                            initializeRandomSpawnPoint(rows, cols, spawnRow, 
                                                                    spawnCol);
                            //set random spawn location to '?'
                        
                            // maze[spawnRow][spawnCol] = '?';
                            // std::cout << "startin" << spawnRow << " col" << 
                            //spawnCol << std::endl;
                            randomGenerate = true;
                            
                            unsigned int exitRow = spawnRow;
                            unsigned int exitCol = spawnCol;
                            
                            initializeExitPoint(rows, cols, exitRow, exitCol);
                            // std::cout << "error: " << exitRow << " " 
                            //<< exitRow << std::endl;
                            mazeStructure[exitRow][exitCol] = '.';
                            
                            unsigned int currRows = spawnRow;
                            unsigned int currCols = spawnCol;
                            
                            generatePath(visitedCells, rows, cols, currRows, 
                                    currCols, mazeStructure, randomGenerate);
                        }
                        //test mode
                        else {
                            initializeMaze(mazeStructure, rows, cols);
                            unsigned int spawnRow = 1;
                            unsigned int spawnCol = 1;
                            mazeStructure[1][0] = '.';
                                // std::cout << "error: " << exitRow << " " 
                                //<< exitRow << std::endl;
                            randomGenerate = false;
                            unsigned int currRows = spawnRow;
                            unsigned int currCols = spawnCol;
                            generatePath(visitedCells, rows, cols, currRows, 
                                currCols, mazeStructure, randomGenerate);
                        }

                        maze.setMazeStructure(mazeStructure);

                        std::cout << "Initialize empty maze successfully\n";


                        // for (int i =0)
                        maze.printMaze(start);

                    }    
                    catch (std::invalid_argument const& e){
                        std::cout << "An error occured: " << e.what() << "\n";
                    }
                    catch (std::exception const& e){
                        std::cout << "An error occured: " << e.what() << "\n";
                        
                    }    
                    
                    
                    // flush input because input may have been incorrect
                    std::cin.clear();
                    fflush(stdin);

                }
                else if (inputChar == '1'){
                    try {
                        // Read the start coordinate
                    
                        readMazeStart(start, mode);

                        //Read the width and width of maze (from user input)
                        int mazeLength = 0;
                        int mazeWidth = 0;

                        readMazeSize(mazeLength, mazeWidth);

                        maze.setLength(mazeLength);
                        maze.setWidth(mazeWidth);


                        // Read the structure of the maze
                        char** mazeStructure;
                        mazeStructure = new char*[mazeWidth];
                        for(int i =0; i < mazeWidth; i++){
                            mazeStructure[i] = new char[mazeLength];
                        }
                        readMazeStdin(mazeStructure, mazeLength, mazeWidth);

                        maze.setMazeStructure(mazeStructure);

                        std::cout << "Maze read successfully\n";

                        maze.printMaze(start);
                    }
                    catch (std::invalid_argument const& e){
                        std::cout << "An error occured: " << e.what() << "\n";
                    }
                    catch (std::exception const& e){
                        std::cout << "An error occured: " << e.what() << "\n";
                        
                    }

                    // flush input because input may have been incorrect
                    std::cin.clear();
                    fflush(stdin);
                    

                }
                else if (inputChar == '3'){

                }
                else {
                    std::cout << 
                        "Input Error: Enter a number between 1 and 3 ....\n";
                }
            }
        }
        else if (curState == ST_GetMaze){
            // if a maze has been built it is cleaned up and reverted before 
            // a new one is placed
            if (hasBuilt){
                maze.revertBuildUpTerrain(difference, logicalX, logicalZ);
                maze.revertMazeBuild(blockList);
                // delete difference array
                for (int i = 0; i < logicalX; ++i){
                    delete [] difference[i];
                }
                delete [] difference;
                // delete the blocklist's nodes
                blockList.~LinkedBlocks();

                // Delay so the server can catch up to the getheight command
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                // Reset the height of the placed maze after a maze was deleted
                start->y = mc.getHeight(start->x, start->z) + 1;

            }

            

            // If the maze is in it's default state i.e. a maze has not been 
            // loaded a message is displayed
            if (maze.getMazeStructure() == nullptr || start == nullptr){
                std::cout << "You have not loaded a maze yet.";
            }
            else {
                // set the start coordinate of maze
                maze.setStart(start);

                // Create a HeightMap variable, and call the function to get the
                //  heights of all blocks within the maze coordinates
                mcpp::HeightMap worldHeight = maze.getHeightMaze(blockList);

                difference = maze.compareHeights(worldHeight, 
                                                 logicalX, 
                                                 logicalZ);


                //First call BuildDownTerrain function
                maze.buildDownTerrain(worldHeight, difference, blockList);

                //Then call GetHeightMaze again to generate a new heightmap
                worldHeight = maze.getHeightMaze();
                
                // Delete difference array 

                for (int i = 0; i < logicalX; ++i){
                    delete [] difference[i];
                }
                delete [] difference;

                //Similarly call difference again, to get the new difference
                difference = maze.compareHeights(worldHeight, 
                                                 logicalX, 
                                                 logicalZ);

                //Call the Build up Terrain function
                maze.buildUpTerrain(worldHeight, difference);
                //Construct the environment
                maze.buildMaze();
                // place carpet
                maze.placeBlueCarpet(blockList);
                
                hasBuilt = true;
            }

            
        }
        else if (curState == ST_SolveMaze){
            while (inputChar != '1'  && inputChar != '2' && inputChar != '3'){
                // Print the solve maze sub-menu
                printSolveMazeMenu();                

                Agent player(mcpp::Coordinate(0, 0, 0));

                std::cin >> inputChar;
                
                // Solve manually menu function
                if (inputChar == '1'){
                    if (hasBuilt){
                        maze.findMazeGaps();
                        MazeCoordinate randCoord = player.getRandomCoord(&maze);
                        player.teleportPlayer(*(maze.getStart()) + mcpp::Coordinate(randCoord.getWidthCoord(), ABOVE_GROUND_HEIGHT, randCoord.getLengthCoord()));
                    }
                    else{
                        std::cout << "You must build a maze before solving.\n";
                    }
                    

                }
                // Show escape route function
                else if (inputChar == '2'){
                    if (hasBuilt){

                        //Check if the player is within the maze
                        player.setPlayerCoord(mc.getPlayerPosition());
                        player.solveMaze();
                    }
                    else{
                        std::cout << "You must build a maze before solving.\n";
                    }


                }
                else  if (inputChar == '3'){

                }
                else{
                    std::cout << 
                        "Input Error: Enter a number between 1 and 3 ....\n";
                }
            }
        }
        else if (curState == ST_Creators){
            printTeamInfo();
        }
        else if (curState == ST_Exit){
            
        }

        else{
            std::cout << "Input Error: Enter a number between 1 and 5 ...."; 
        }

        
    }
    if (hasBuilt){
        maze.revertBuildUpTerrain(difference, logicalX, logicalZ);
        maze.revertMazeBuild(blockList);
        // delete difference array
        if (difference != nullptr && difference != NULL) {
            for (int i = 0; i < logicalX; ++i){
                if (difference[i] != nullptr) {
                    delete [] difference[i];
                }
            }
        
            delete [] difference;
        }
    }

    printExitMassage();


    return EXIT_SUCCESS;

}