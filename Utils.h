#include <iostream>
#include "Maze.h"
#include <mcpp/mcpp.h>
#include <cctype>

// TODO sperate into .h and .cpp files


void readMazeSize(int& mazeLength, int& mazeWidth){
    
    std::cout << "Enter the size of the rectangular Environment (H, W): " << std::endl;
    std::cin >> mazeLength;
    std::cin >> mazeWidth;
    //Length and Width > 0
    //Checking if Length and Width are valid
    if (mazeLength <= 0 || mazeWidth <= 0) {
        throw std::invalid_argument("Length or width argument is incorrect!");
    }

}

void readMazeStart(mcpp::Coordinate** start){
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
