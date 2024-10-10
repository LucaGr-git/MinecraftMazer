#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"

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

    //? unsure of what this is 
    //bool mode = NORMAL_MODE;
    //read Mode

    

    mcpp::MinecraftConnection mc; 
    mc.doCommand("time set day"); 

    States curState = ST_Main;

    //State machine for menu        
    while (curState != ST_Exit)
    {
        printMainMenu(); // main menu options are printed

        int intState;
        std::cin >> intState;
        --intState;
        // TODO FIX LOOPING ERROR WHEN NON INTEGER INPUTS


        curState = States(intState);
    
        
        // if statements are used to determine what should be done based on menu 'State'
        if (curState == ST_Main){
            // TODO complete menu portion
        }
        else if (curState == ST_GetMaze){
            // TODO complete menu portion
        }
        else if (curState == ST_SolveMaze){
            // TODO complete menu portion
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