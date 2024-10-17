#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"

#include "Utils.h"

#include "HeightArray2D.cpp"
#include "BlockArray3D.cpp"

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States{
    ST_Main,
    ST_GetMaze,
    ST_SolveMaze,
    ST_Creators,
    ST_Exit
};

int main(void){

    // ?unsure of what this is 
    //bool mode = NORMAL_MODE;
    //read Mode

    mcpp::MinecraftConnection mc;

    mc.doCommand("time set day"); 

    States curState = ST_Main;


    
    Maze maze;

    while (curState != ST_Exit)
    {   



        printMainMenu(); // main menu options are printed

        char inputChar;
        std::cin >> inputChar;

        int intState;

        if (isdigit(inputChar)){
            // if they inputted a digit the program takes the input as a digit
            intState = static_cast<int>(inputChar);
            // subtract 1 because enum states start at 0 not 1
            --intState;
        }
        else{
            // If they have inputted a non digit data type the intState and subsequent State is set to -1
            intState = -1;
        }

        // State variable is updated
        curState = States(--intState);
    
    
        
        // if statements are used to determine what should be done based on menu 'State'
        if (curState == ST_Main){
            while (inputChar != '3'){

                printGenerateMazeMenu();
                
                std::cin >> inputChar;

                if (inputChar == '1'){
                    // TODO complete menu portion
                    std::cout << "TODO : You pressed 1: this hasn't been developed yet";
                }
                else if (inputChar == '2'){
                    int mazeLength = 0;
                    int mazeWidth = 0;



                    readMazeSize(mazeLength, mazeWidth);

                    maze.setLength(mazeLength);
                    maze.setWidth(mazeWidth);

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
            if (maze.getStart() == nullptr || maze.getMazeStructure() == nullptr || maze.getMazeStructure()[0] == nullptr){
                std::cout << "You have not loaded a maze yet.";
            }
            else {
                // TODO complete menu portion
                std::cout << "TODO : You pressed 1: this hasn't been developed yet";
            }

            
        }
        else if (curState == ST_SolveMaze){
            // TODO complete menu portion
            std::cout << "TODO : You pressed 1: this hasn't been developed yet";
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

    printExitMassage();


    return EXIT_SUCCESS;

}