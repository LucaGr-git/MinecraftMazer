#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"

#include "HeightArray.cpp"

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

    HeightArray2D arr(3,4, 10, 10); // 3 rows, 4 columns

    

    std::cout << "Original 2D array:\n";
    arr.print();

    // after reading
    std::cout << "New 2D array:\n";
    arr.generateHeightArray();
    arr.print();

  


    return 0;




    mc.doCommand("time set day"); 

    States curState = ST_Main;

    //State machine for menu        
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
            // TODO complete this menu porion
            std::cout << "TODO : You pressed 1: this hasn't been developed yet";
        }
        else if (curState == ST_GetMaze){
            // TODO complete menu portion
            std::cout << "TODO : You pressed 1: this hasn't been developed yet";
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