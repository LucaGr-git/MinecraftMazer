#include <iostream>
#include <vector>
#include <algorithm> // For std::shuffle
#include <random>    // For random number generation
#include <cstdlib>   // For rand()
#include <ctime>     // For time()
#include <cmath>     // For abs()

//check if cells are already visited and in bounds
void checkValid(bool& isValid, int& rows, int& cols, int randomDirections) {
    isValid = true;
    
    int tempRow = rows;
    int tempCol = cols;
    
    if (randomDirections == 1) {  // Move down
            tempRow++; 
            if (tempRow > 0 && tempRow <  (rows - 1) && (visitedCells[tempRow][tempCol] != 1)) {  // Ensure tempRow stays within inner bounds
                currRows++;
                cellMoved = true;
                process = true;
            } else {
        ranNumb(directionChecker, randomDirections);
            }
        } 
         if (randomDirections == 2) {  // Move left
            tempCol--; 
            if (tempCol > 0 && tempCol < (cols - 1) && (visitedCells[tempRow][tempCol] != 1)) {  // Ensure tempCol stays within inner bounds
                currCols--;
                cellMoved = true;
            process = true;
            } else {
        ranNumb(directionChecker, randomDirections);
            }
        } 
         if (randomDirections == 3) {  // Move right
            tempCol++; 
            if (tempCol > 0 && tempCol < (cols - 1) && (visitedCells[tempRow][tempCol] != 1)) {  // Ensure tempCol stays within inner bounds
                currCols++;
                cellMoved = true;
            process = true;
            } else {
        ranNumb(directionChecker, randomDirections);
            }
        } 
        else {
            cellMoved = false;  // No valid movement in this direction
                tempCol = currCols;
                tempRow = currRows;
        }
    
    
    
}

//makes directions unique 
void ranNumb (std::vector<int>& directionChecker, int& randomDirections, int rows, int cols, bool& isValid) {
    
    // Ensure the directionChecker is initialized with a dummy value only the first time
    if (directionChecker.empty()) {
        directionChecker.push_back(5);  // Initialize with a dummy value
    }

    bool randValid = false;
    int counter = 0;
    // int tempRow;
    // int tempCol;
    // Loop until a valid random direction is found (one that isn't already in directionChecker)
    while (!randValid) {
        counter = 0;  // Reset counter for each iteration
        
        randomDirections = rand() % 4;  // Generate a random direction between 0–3
        
        // Check if the direction is already in directionChecker
        for (int i = 0; i < directionChecker.size(); i++) {
            if (randomDirections == directionChecker[i]) {
                counter++;  // Increment counter if a match is found
            }
        }
    
        // If no match was found, it's a valid direction
        if (counter == 0) {
            randValid = true;
            
            checkValid(isValid, rows, cols, randomDirections);
            directionChecker.push_back(randomDirections);  // Add valid
        }
    }
    
    // Reset the directionChecker after all four directions have been used
    if (directionChecker.size() >= 5) {
        directionChecker.clear();  // Clear all previous directions
        directionChecker.push_back(5);  // Reinitialize with a dummy value to avoid empty state
    }
}
void detectCellSurroundings(int& currRows, int& currCols, bool& cellMoved, std::vector<int>& directionChecker, int rows, int cols, std::vector<std::vector<int>>& visitedCells,std::vector<std::vector<int>>& maze) {
    // std::cout << "rr" << currRows << " ss1 " << currCols << std::endl;
        
        
        int randomDirections;
        bool isValid = false;
        ranNumb(directionChecker, randomDirections, rows, cols, isValid);
    
        //  std::cout << tempRow << " " << tempCol << std::endl;
         if (isValid) {
             maze[currRows][currCols] = 0;
             visitedCells[currRows][currCols] = 1;
         }
         else {
             detectCellSurroundings(currRows, currCols, cellMoved,directionChecker, rows, cols, visitedCells, maze);
         }
        
    }
    



void checkClosestOuterWall(int& exitRow, int& exitCol, int rows, int cols) {


    int distanceFromTop = exitRow;
    int distanceFromBottom = rows - 1 - exitRow;
    int distanceFromLeft = exitCol;
    int distanceFromRight = cols - 1 - exitCol;

    int smallestDistance = std::min({distanceFromTop, distanceFromBottom, distanceFromLeft, distanceFromRight});

    if (smallestDistance == distanceFromTop) {
        exitRow -= 1;
    } else if (smallestDistance == distanceFromBottom) {
        exitRow += 1;
    } else if (smallestDistance == distanceFromLeft) {
        exitCol -= 1;
    } else {
        exitCol += 1;
    }
}

void generateMaze(std::vector<std::vector<int>>& maze, int& startRow, int& startCol, int rows, int cols) {

    // Initialize visited vector
    std::vector<std::vector<int>> visitedCells(rows, std::vector<int>(cols, 0));

    // Get random spawn point row near outer walls
    startRow = ((rand() % (rows - 2)) + 1); 

    // Get random spawn point col only near outer walls
    if (startRow == 1 || startRow == (rows - 1)) {
        startCol = (rand() % (cols - 2)) + 1;  // Columns 1 to 5
    } else {
        startCol = ((rand() % 2) * (cols - 3)) + 1;  // Columns 1 or 5
    }

    // Make entrance open (" ")
    maze[startRow][startCol] = 0; 
    // Mark entrance as visited
    visitedCells[startRow][startCol] = 1;

    int exitRow = startRow;
    int exitCol = startCol;
    // Find nearest exit (outer wall)
    checkClosestOuterWall(exitRow, exitCol, rows, cols);

    // Make exit open (" ")
    maze[exitRow][exitCol] = 0;
    // Mark exit as visited
    visitedCells[exitRow][exitCol] = 1;

    bool cellMoved = false;
    int currRow = startRow;
    int currCol = startCol;

    std::vector<int> directionChecker;
    // int cntr = 0;
    // Main loop to explore and update the maze
    // while (!visitedCells.empty()) {
    //     detectCellSurroundings(currRow, currCol, cellMoved, directionChecker, rows, cols, visitedCells);

    //     if (!cellMoved) {

    //         visitedCells.pop_back();
    //         std::cout << "visited" << cntr;
    //         cntr++;
    //     } else {
    //         visitedCells[currRow][currCol] = 0;  // Mark cell as visited
    //         maze[currRow][currCol] = 0;  // Mark the cell as open in the maze
    //         std::cout << "r" << currRow << " ss " << currCol << std::endl;
    //     }
    // }
    detectCellSurroundings(currRow, currCol, cellMoved,
    directionChecker, rows, cols, visitedCells, maze);
    
    // Print the updated maze
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((i == startRow) && (j == startCol)) {
                std::cout << "?";
            }  
            else if ((i == exitRow) && (j == exitCol)) {
                std::cout << "!";
            }
            else if (maze[i][j] == 0) {
                std::cout << ".";
            }
            else {
                std::cout << "X";
            }

        }
        std::cout << '\n';
    }
    
    
    // for (int k = 0; k < rows; k++) {
    //     for (int l = 0; l < cols; l++) {
    //         std::cout << maze[k][l] << " index k: " << k << " index l: " << l << std::endl;
    //     }
    // }
}

int main() {
    //initialize seed to current time
    std::srand(std::time(0));


    //set maze dimensions (only odd integers)
     int rows = 7;
     int cols = 7;

     cols -= 2;
    //Maze created with walls (1) and empty cells (0)
    std::vector<std::vector<int>> maze(rows, std::vector<int>(cols, 1));

    int startRow = -1;
    int startCol = -1;
    generateMaze(maze, startRow, startCol, rows, cols);

    return 0;
}