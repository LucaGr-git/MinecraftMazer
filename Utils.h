#include <iostream>
#include "Maze.h"
#include <mcpp/mcpp.h>
#include <cctype>



void readMazeSize(int& mazeLength, int& mazeWidth){
    mazeLength = 2; 
    mazeWidth = 2;
    std::cout << "Enter the length and width of maze: " << std::endl;
    while (mazeLength % 2 == 0 ||  mazeWidth % 2 == 0 ) {
        

        std::cin >> mazeLength;
        std::cin >> mazeWidth;

        // Check if the input is valid
        if (std::cin.fail()) {
            // clear buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid input. Please enter two odd integers.\n" << std::endl;
        } else {
            // Clear buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

}

void readMazeStart(mcpp::Coordinate &start, bool mode){
    /*
    //Checking if start is nullptr
    if (start != nullptr){
        delete start;
    }
    start = new mcpp::Coordinate();
    */
    

    mcpp::MinecraftConnection mc;

    
    
    std::string input;
    std::cout << "In Minecraft, navigate to where you need the maze to be built"
                  " in Minecraft and type - done:\n";
    while (input != "done"){
        std::cin >> input;
    }

    if (mode == 1){
        mc.setPlayerPosition(mcpp::Coordinate(4848, 71, 4369));
    }

    mcpp::Coordinate playerPos = mc.getPlayerPosition();

    start = mcpp::Coordinate(playerPos.x, 
                                  mc.getHeight(playerPos.x, playerPos.z) + 1,
                                  playerPos.z);

    
}


void readMazeStdin(char** MazeStruct, int length, int width){
    int charsRead = 0;
    char readC;

    std::cout << "Enter the maze structure: " << std::endl;

    //Checking the outer char 2D array is not a nullptr
    if (MazeStruct == nullptr){
        throw std::invalid_argument(
                        "MazeStruct outer pointer must not be null!");
    }

    for (int row = 0; row < width; row++){ 
        //Checking that the inner part is not null.
        if (MazeStruct[row] == nullptr){
            throw std::invalid_argument(
                        "MazeStruct inner pointer must not be null!");
        }
        for (int col = 0; col < length; col++){
            if(std::cin.good()){
                std::cin >> readC;
                readC = tolower(readC);
                //Error checking for if the user entered 'x' or '.'
                if (readC != 'x' && readC != '.') {
                    throw std::invalid_argument("Must type 'x' (or 'X')" 
                                    " for solid block, or '.' for gap");
                }

                MazeStruct[row][col] = readC;
                ++charsRead;
            }
        }
    }
        // Now check if exits are correct
        int exitsCount = 0;

        // Iterate the length
        for (int j = 0; j < length - 1; ++j) {
            if (MazeStruct[0][j] == '.'){
                ++exitsCount;
            }
        }
        
        // Iterate the width 
        for (int i = 0; i < width - 1; ++i) {
            if (MazeStruct[i][length - 1] == '.'){
                ++exitsCount;
            }
            
        }
        
        // Iterate the length at the end
        if (width > 1) {
            for (int j = length - 1; j >= 1; --j) {
                if (MazeStruct[width - 1][j] == '.'){
                    ++exitsCount;
                }
            }
        }
        
        // Iterate the width at the end
        if (length > 1) {
            for (int i = width - 1; i >= 1; --i) {
                if (MazeStruct[i][0] == '.'){
                    ++exitsCount;
                }
            }
        }

        if (exitsCount != 1 || 
                MazeStruct[0][0] == '.' ||
                MazeStruct[0][length - 1] == '.' ||
                MazeStruct[width - 1][0] == '.' ||
                MazeStruct[width - 1][length - 1] == '.'){
            throw std::invalid_argument(
                "Make sure you have exactly one exit (not corners)");
        }
    

    //Error checking that charsRead matches the length * width formula
    if (charsRead != (length * width)) {
        throw std::invalid_argument(
                            "Height or width does not match user input");
    }
    
}
