#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>   // For rand()
#include <ctime>     // For time()

void generatePath(std::vector<std::vector<int>>& visitedCells, int rows, 
                        int cols, int currRow, int currCol, char** maze, 
                            bool& randomGenerate, int lastDirection = -1) {
    // Makes current Cell visited 
    visitedCells[currRow][currCol] = 1;
    // Makes current Cell an empty cell
    maze[currRow][currCol] = '.';

    //0 = UP, 1 = DOWN, 2 = LEFT, 3 = RIGHT
    std::vector<int> directions = {0, 1, 2, 3};
    //Make directions randomstd::vector<int> directions = {0, 1, 2, 3};
    if (randomGenerate) {
        std::random_shuffle(directions.begin(), directions.end()); 
    }
    else {
        std::vector<int> diretionsTest = {0, 3, 1, 2};
        directions = diretionsTest;
    }
    
    
    //Loops for unqiue integers, avoids two consecutive 
    //integers with opposite directions
    for (int dir : directions) {
        // Only proceed if the direction is not the opposite 
        //of the last direction
        bool isOpposite = false;
        
        //Avoids two consecutive directions being opposites e.g. 
        //up and down cannot be consecutive
        if (lastDirection == 0 && dir == 1) {         
            isOpposite = true;
        } 
        else if (lastDirection == 1 && dir == 0) { 
            isOpposite = true;
        } 
        else if (lastDirection == 2 && dir == 3) {  
            isOpposite = true;
        } 
        else if (lastDirection == 3 && dir == 2) {  
            isOpposite = true;
        }

        if (!isOpposite) {  // Process only if not the opposite direction
            int newRow = currRow;
            int newCol = currCol;

            // Calculate the new cell based on direction
            if (dir == 0 && currRow > 1) {       // Move UP
                newRow -= 2;
            } else if (dir == 1 && currRow < rows - 2) { // Move DOWN
                newRow += 2;
            } else if (dir == 2 && currCol > 1) { // Move LEFT
                newCol -= 2;
            } else if (dir == 3 && currCol < cols - 2) { // Move RIGHT
                newCol += 2;
            } 

            // Check if the new cell is unvisited
            if (visitedCells[newRow][newCol] == 0) {
                // Remove the wall between the current cell and the new cell
                maze[(currRow + newRow) / 2][(currCol + newCol) / 2] = '.';

                // Recursively visit the new cell, passing the current
                //direction as the last direction
                //If everything is valid, the function is called again and all 
                //parameters are passed by reference meaning that are all saved
                
                generatePath(visitedCells, rows, cols, newRow, newCol, maze, 
                                                            randomGenerate);
            }
        }
    }
    
    //If for loop ends and never reaches isOpposite if statement, this means 
    //that the current Cell has no options left, and doesnt add any new stack 
    //frame to the function. Thus, uses previous stack 
    //frame (goes back to previous coordinates) as 
    
    //If for loop ends and never reaches isOpposite if statement, this means 
    //that the current Cell has no options left, and since the function isn't 
    //called this means that the parameters are not saved as they are not beign 
    //passed by reference.
}





void initializeExitPoint(int rows, int cols, unsigned int& exitRow,
                         unsigned int& exitCol) {
    
    int distanceFromTop = exitRow;
    int distanceFromBottom = rows - 1 - exitRow;
    int distanceFromLeft = exitCol;
    int distanceFromRight = cols - 1 - exitCol;

    int smallestDistance = std::min({distanceFromTop, distanceFromBottom, 
                                     distanceFromLeft, distanceFromRight});

    if (smallestDistance == distanceFromTop) { //good
        exitRow -= 1;
                // std::cout << "1" << std::endl;

    } else if (smallestDistance == distanceFromBottom) {
        exitRow += 1;
                // std::cout << "2" << std::endl;

    } else if (smallestDistance == distanceFromLeft) {
        exitCol -= 1;
                // std::cout << "3" << std::endl;

    } else {
        // std::cout << "4" << std::endl;
        exitCol += 1;
    }
    
    // std::cout << exitCol <<std::endl;
}

    
    

 
void initializeRandomSpawnPoint(int rows, int cols, unsigned int& spawnRow, 
                                unsigned int& spawnCol) {

    
    // int randNum = rand();
    int randomRow;
    bool isOdd = false;
    //randomises a odd integer for row
    while (!isOdd) {
        randomRow = (rand() % (rows - 2) + 1);
        if (randomRow % 2 != 0) {
            isOdd = true;
        }
    }
    
    
    bool isColOdd = false;
    int randomCol;
    
    //randomises a random integer to 1 or col - 1
    while(!isColOdd) {
        randomCol = (rand() % (cols - 2)) + 1;
        // std::cout << " col :" << randomCol << std::endl;
        if ((randomCol == 1) || (randomCol == cols -2)) {
            isColOdd = true;
        }
    }
    
    spawnRow = randomRow;
    spawnCol = randomCol;
    
    // spawnRow = randomSpawnCells.size();
    // spawnCol = randomSpawnCells[randomCol].size();
    // std::cout <<" row: " << spawnRow << " col: " << spawnCol << std::endl;

}

void initializeMaze(char** maze, int rows, int cols) {

    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i % 2 != 0 && j % 2 != 0) {
                maze[i][j] = '.';
            }
            else {
                maze[i][j] = 'X';
            }
        }
    }

}

void deallocateCharArray(char** charArray, int rows, int cols){
    if (charArray != nullptr){
        for (int i = 0 ; i < rows; ++i){
            if (charArray[i] != nullptr){
                delete charArray[i];
            }
        }
        delete [] charArray;
    }
}
