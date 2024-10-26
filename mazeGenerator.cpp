#include <iostream>
#include <vector>
#include <algorithm>
#include <random>    // For random number generation
#include <cstdlib>   // For rand()
#include <ctime>     // For time()
#include <cmath>     // For abs()
#include <stack>
#include <utility>


void checkValid (std::vector<int>& directionChecker, int& randomDirection,  bool& directionIsUnique)
 {
    //once 4 unqiue directions stored, reset vector
    if (directionChecker.size() == 4) {
        directionChecker.clear();
    }

    bool isDuplicate = false;

        // Check if the generated direction is already in directionChecker
    for (unsigned int i = 0; i < directionChecker.size(); i++) {
        if (randomDirection == directionChecker[i]) {
            if (randomDirection == 0 && directionChecker[i])
            isDuplicate = true;
        }
    }

        // Add randomDirection if it is not a duplicate
        if (!isDuplicate) {
            directionIsUnique = true;
        }


    // for (unsigned int j = 0; j < directionChecker.size(); j++) {
    //     std::cout << "direction: " << directionChecker[j] << " ";
    // }
    // std::cout << std::endl;

}
void randomDirection(int& randomDirection) {

    randomDirection = rand() % 4;

}

// void randomDirection(std::vector<int>& directionChecker, int& randomDirection) {

//     //once 4 unqiue directions stored, reset vector
//     if (directionChecker.size() == 4) {
//         directionChecker.clear();
//     }

//     bool isValid = false;

//     //keeps generating random values til valid
//     while (!isValid) {

//         randomDirection = rand() % 4;

//         // Reset duplicate flag
//         bool isDuplicate = false;

//         //make numberd generated not 

//         // Check if the generated direction is already in directionChecker
//         for (unsigned int i = 0; i < directionChecker.size(); i++) {
//             if (randomDirection == directionChecker[i]) {
//                 if (randomDirection == 0 && directionChecker[i])
//                 isDuplicate = true;
//             }
//         }

//         // Add randomDirection if it is not a duplicate
//         if (!isDuplicate) {
//             // directionChecker.push_back(randomDirection);
//             isValid = true;  // Exit loop by setting isValid to true
//             directionValid = true;
//         }
//     }


//     for (unsigned int j = 0; j < directionChecker.size(); j++) {
//         std::cout << directionChecker[j] << " ";
//     }
//     std::cout << std::endl;
// }

void generatePath(std::vector<std::vector<int>>& visitedCells, int rows, int cols, unsigned int& currRows, unsigned int& currCols, int& randomDirections, char**& maze, std::vector<int>& directionChecker) {
    
    int tempRow = currRows; //3
    int tempCol = currCols; //1

    //checks if direction is valid for newly explored cells
    bool directionValid = false;

    //now checks if new direction is valid if not reroll
    bool directionIsValid = false;


    //
    bool directionIsUnique = false;

     std::vector<std::vector<int>> gapOddNumbered(rows, std::vector<int>(cols, 1));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (i % 2 != 0 && j % 2 != 0) {
                    gapOddNumbered[i][j] = 0;
                }
            }
        }

    while(!directionIsValid) {
        directionIsValid = false;
        directionValid = false;
        tempRow = currRows;
        tempCol = currCols;
        randomDirections = -1;
        randomDirection(randomDirections);

        

        // std::cout << "Curr rows " << currRows << " CurrCols " << currCols << std::endl;
        //initialize vector with all odd cells be 0's

        //issue of seg fault


        if (randomDirections == 0) {  // Move UP

            tempRow--;
            // if (gapOddNumbered[tempRow][tempCol] == 0) {
            //     currRows--;
            //     maze[currRows][currCols] = 0;
            // }
            if (tempRow > 0 && tempRow < (rows - 1) && visitedCells[tempRow][currCols] != 1) {  // Ensure tempRow stays within bounds and not visited
                
                visitedCells[currRows][currCols + 1] = 1;
                visitedCells[currRows][currCols - 1] = 1;
                currRows--;
                visitedCells[currRows][currCols] = 1;

                directionValid = true;

                visitedCells[currRows][tempCol + 1] = 1;
                visitedCells[currRows][tempCol - 1] = 1;
                    currRows--;
                    visitedCells[currRows][currCols] = 1;
                std::cout << "stuck" << std::endl;

            }
        } 
        else if (randomDirections == 1) {  // Move DOWN
            tempRow++; 

            if (tempRow > 0 && tempRow < (rows - 1) && visitedCells[tempRow][tempCol] != 1) {  // Ensure tempRow stays within bounds and not visited
                visitedCells[currRows][tempCol + 1] = 1;
                visitedCells[currRows][tempCol - 1] = 1;
                currRows++;
                visitedCells[currRows][currCols] = 1;
                directionValid = true;

                tempRow++;

                    visitedCells[currRows][tempCol + 1] = 1;
                    visitedCells[currRows][tempCol - 1] = 1;
                    currRows++;
                    visitedCells[currRows][currCols] = 1;

        
                std::cout << "stuck2" << std::endl;

            }
        } 
        else if (randomDirections == 2) {  // Move LEFT
            tempCol--; 

            if (tempCol > 0 && tempCol < (cols - 1) && visitedCells[tempRow][tempCol] !=1) {  // Ensure tempCol stays within bounds and not visited
                visitedCells[tempRow + 1][currCols] = 1;
                visitedCells[tempRow - 1][currCols] = 1;
                currCols--;
                visitedCells[currRows][currCols] = 1;
                directionValid = true;


                tempCol--; 
                    visitedCells[tempRow + 1][currCols] = 1;
                    visitedCells[tempRow - 1][currCols] = 1;
                    currCols--;
                    visitedCells[currRows][currCols] = 1;
                

                std::cout << "stuck3" << std::endl;
            }
        } 
        else if (randomDirections == 3) {  // Move RIGHT
            tempCol++; 

            if (tempCol > 0 && tempCol < (cols - 1) && visitedCells[tempRow][tempCol] != 1) {  // Ensure tempCol stays within bounds and not visited
                visitedCells[tempRow + 1][currCols] = 1;
                visitedCells[tempRow - 1][currCols] = 1;
                currCols++;
                visitedCells[currRows][currCols] = 1;

                directionValid = true;

                tempCol++;
                    visitedCells[tempRow + 1][currCols] = 1;
                    visitedCells[tempRow - 1][currCols] = 1;
                    currCols++;
                    visitedCells[currRows][currCols] = 1;

                



                std::cout << "stuck4" << std::endl;
            }
        }
        

        //checks if the direction that is valid for empty cells is valid for duplicated directions or not
        if (directionValid) {
            directionIsUnique = false;
            checkValid(directionChecker, randomDirections, directionIsUnique);
            if (directionIsUnique) {
            std::cout << "direction valid for non dupes and unique directions: " << randomDirections << std::endl;
                directionChecker.push_back(randomDirections);
                directionIsValid = true;
            }
        }

    }
}






void initializeExitPoint(int rows, int cols, unsigned int& exitRow, unsigned int& exitCol) {
    
    int distanceFromTop = exitRow;
    int distanceFromBottom = rows - 1 - exitRow;
    int distanceFromLeft = exitCol;
    int distanceFromRight = cols - 1 - exitCol;

    int smallestDistance = std::min({distanceFromTop, distanceFromBottom, distanceFromLeft, distanceFromRight});

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

    
    

 
void initializeRandomSpawnPoint(int rows, int cols, unsigned int& spawnRow, unsigned int& spawnCol) {

    
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
        maze[i] = new char[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i % 2 != 0 && j % 2 != 0) {
                maze[i][j] = ' ';
            }
            else {
                maze[i][j] = 'X';
            }
        }
    }

}


int main() {
    //initialize seed to current time
    srand(std::time(0));
    //set maze dimensions (only odd integers)mak
     int rows = 7;
     int cols = 7;

     cols -= 2;
    //Maze created with walls (1) and empty cells (0)
    char** maze = new char*[rows];
    
    //initialize maze size with walls and empty odd cells
    initializeMaze(maze, rows, cols);

    unsigned int spawnRow = 0;
    unsigned int spawnCol = 0;
    
    //get random spawn location
    initializeRandomSpawnPoint(rows, cols, spawnRow, spawnCol);
    //set random spawn location to '?'

    maze[spawnRow][spawnCol] = '?';
    // std::cout << "startin" << spawnRow << " col" << spawnCol << std::endl;
    
    
    unsigned int exitRow = spawnRow;
    unsigned int exitCol = spawnCol;
    
    initializeExitPoint(rows, cols, exitRow, exitCol);
    // std::cout << "error: " << exitRow << " " << exitRow << std::endl;
    maze[exitRow][exitCol] = '!';



    // std::stack<std::stack<int>>& vistiedCells;

    std::vector<std::vector<int>> visitedCells(rows, std::vector<int>(cols, 0));

    int direction = -1;
    std::vector<int> directionChecker;



    unsigned int currRows = spawnRow;
    unsigned int currCols = spawnCol;
    
    while (!visitedCells.empty()) {
        
        generatePath(visitedCells, rows, cols, currRows, currCols, direction, maze, directionChecker);
        maze[currRows][currCols] = '.';

            if (direction == 0) {
                currRows++;
                maze[currRows][currCols] = '.';
            }
            else if (direction == 1) {
                currRows--;
                maze[currRows][currCols] = '.';

            }
            else if(direction == 2) {
                currCols++;
                maze[currRows][currCols] = '.';
            }
            else if (direction == 3) {
                currCols--;
                maze[currRows][currCols] = '.';
            }

            

        for (unsigned int j = 0; j < directionChecker.size(); j++) {
            std::cout << "direction: " << directionChecker[j] << " ";
        }
        std::cout << std::endl;


    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
    




    
// Free allocated memory for the maze
    for (int i = 0; i < rows; i++) {
        delete[] maze[i];
    }
    delete[] maze;

    return 0;
}
