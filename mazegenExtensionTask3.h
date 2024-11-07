#include <iostream>
#include <vector>
#include <queue>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cstring>

void readEnv(char**& env, int& height, int& width) ;
void printEnv(char** env, int height, int width) ;

void checkUnfilledCells(char**& env, int height, int width, 
            std::vector<std::pair<int,int>>& isolatedCells);

//for removing isolation
void floodFill(char**& env, int height, int width, int entranceRows, 
                                                    int entranceCols);
void findEntrance(char**& env, int height, int width, int& entranceRows, 
                                                    int& entranceCols) {
    

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((i == 0) ||  i == (height  -1)) {
                if (env[i][j] == '.') {
                    entranceRows = i;
                    entranceCols = j;
                }

            }
            else {
                if ((j == 0 ) || j == (width -1)) {
                    if (env[i][j] == '.') {
                        entranceRows = i;
                        entranceCols = j;
                    }

                }
            }
        }
    }
}


void checkUnfilledWalls(char**& env, int height, int width, 
            std::vector<std::pair<int,int>>& isolatedCells);



//for removing loop

void floodFillLoop(char**& env, int height, int width, int entranceRows, 
                                                        int entranceCols);
void fixMazeStructure(char**& env, int height, int width);


void fixMazeStructure(char**& env, int height, int width) {
    for (int i = 0 ; i < height ; i++ ) {
        for(int j = 0 ; j < width ; j++ ) {
            if (env[i][j] == '?') {
                env[i][j] = 'x';
            }
            else if (env[i][j] == '!') {
                env[i][j] = ' ';
            }
        }
    }
}


void checkUnfilledCells(char**& env, int height, int width, 
                std::vector<std::pair<int,int>>& isolatedCells) {

    int newlyRow = 0;
    int newlyCol = 0;

    std::vector<std::pair<int, int>> directions;
    bool adjacentCellFound = false;
    bool adjacentCellFilled = false;
    directions.push_back({-1, 0});
    directions.push_back({1, 0});
    directions.push_back({0, -1});
    directions.push_back({0, 1});

    
    

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (env[i][j] == '.') {
                isolatedCells.push_back({i, j});
                env[i][j] = '!';
            }
        }
    }

    
    std::random_device rng;

    std::mt19937 urng(rng());
    std::shuffle(isolatedCells.begin(), isolatedCells.end(), urng);

    for (std::vector<std::pair<int, int>>::const_iterator it = isolatedCells.begin(); it != isolatedCells.end(); it++) {    
            // if doesnt equal a  '?' or a 'x' then unfilled cell
            int x = it->first;
            int y = it->second;
            // std::cout << "before: " << x << " col " << y << std::endl;

            for (std::vector<std::pair<int, int>>::const_iterator it = directions.begin(); it != directions.end(); it++) {
                int newRow = x + it->first;
                int newCol = y + it->second;

                if (newRow > 0 && newRow < (height - 1) && newCol > 0 && newCol < (width - 1) && (env[newRow][newCol] == 'x')) {
                    // std::cout << newRow << " col " << newCol << std::endl;
                    if (!adjacentCellFound) {
                        adjacentCellFound = true;
                        adjacentCellFilled = true;
                        newlyRow = newRow;
                        newlyCol = newCol;
                        // std::cout << " works" << std::endl;
                    }

                }

                adjacentCellFound = false;


            }
            // std::cout << "acf: " << adjacentCellFilled << std::endl;

            if (adjacentCellFilled) {
                // env[newlyRow][newlyCol] = '!';
                floodFill(env, height, width, newlyRow, newlyCol);
                                            // std::cout << "works" << std::endl;


            }
        }
    }


void floodFill(char**& env, int height, int width, int entranceRows, 
                                                    int entranceCols) {
    std::queue<std::pair<int, int>> q;

    char targetCharToReplace;
        targetCharToReplace = env[entranceRows][entranceCols];
    char charToFill = ' ';

    if (!(targetCharToReplace == charToFill)) {
        q.push({entranceRows, entranceCols});
        env[entranceRows][entranceCols] = charToFill;

        //up, down, left, right
        std::vector<std::pair<int, int>> directions;

        directions.push_back({-1, 0});
        directions.push_back({1, 0});
        directions.push_back({0, -1});
        directions.push_back({0, 1});

        //iterate till empty
        while (!q.empty()) {
            //assign variable to first element of stack
            int x = q.front().first;
            int y = q.front().second;

            //remove first element of stack
            q.pop();

            
            for (std::vector<std::pair<int, int>>::const_iterator it = directions.begin(); it != directions.end(); it++) {
                int newRow = x + it->first;
                int newCol = y + it->second;
                        
                if (newRow > 0 && newRow < (height - 1) && newCol > 0 && newCol < (width - 1) && env[newRow][newCol] == '.') {
                    env[newRow][newCol] = charToFill;
                    q.push({newRow, newCol});
                }
            }   

        }        
    }

}


void checkUnfilledWalls(char**& env, int height, int width, 
                std::vector<std::pair<int,int>>& isolatedCells) {

    int newlyRow = 0;
    int newlyCol = 0;

    std::vector<std::pair<int, int>> directions;
    bool adjacentCellFound = false;
    bool adjacentCellFilled = false;
    directions.push_back({-1, 0});
    directions.push_back({1, 0});
    directions.push_back({0, -1});
    directions.push_back({0, 1});



    // int lastRow = -1;
    // int lastCol = -1;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (env[i][j] == 'x') {
                isolatedCells.push_back({i, j});
                // std::cout << "i: " << i << " j: " << j << std::endl;
            }
        }
    }

    // lastRow = isolatedCells[0].first;
    // lastCol = isolatedCells[0].second;
    // std::cout << "lastRow: " << lastRow << " col: " << lastCol << std::endl;
    std::random_device rng;

    std::mt19937 urng(rng());
    std::shuffle(isolatedCells.begin(), isolatedCells.end(), urng);

            // if doesnt equal a  '?' or a 'x' then unfilled cell
            int x = isolatedCells[0].first;
            int y = isolatedCells[0].second;
            // std::cout << "before: " << x << " col " << y << std::endl;

            for (std::vector<std::pair<int, int>>::const_iterator it = directions.begin(); it != directions.end(); it++) {
                 int newRow = x + it->first;
                 int newCol = y + it->second;

                if (newRow >= 0 && newRow <= (height - 1) && newCol >= 0 && newCol <= (width - 1) && env[newRow][newCol] == ' ' && env[newRow][newCol] != '!') {
                    // std::cout << newRow << " col " << newCol << std::endl;
                    if (!adjacentCellFound) {
                        adjacentCellFound = true;
                        adjacentCellFilled = true;
                        newlyRow = newRow;
                        newlyCol = newCol;

                        std::cout << newlyCol << newlyRow;
                        // std::cout << " works" << std::endl;
                    }

                }

                adjacentCellFound = false;


            }
            // std::cout << "acf: " << adjacentCellFilled << std::endl;

            if (adjacentCellFilled) {
                env[newlyRow][newlyCol] = 'x';

                floodFillLoop(env, height, width, newlyRow, newlyCol);


            }
        }
void floodFillLoop(char**& env, int height, int width, int entranceRows, 
                                                        int entranceCols) {
    std::queue<std::pair<int, int>> q;

    char targetCharToReplace;
        targetCharToReplace = env[entranceRows][entranceCols];
    char charToFill = '?';

    // int rowss = 0;
    // int colss =0;
    //push element into stack
    // int counter = 0;
    if (!(targetCharToReplace == charToFill)) {
        q.push({entranceRows, entranceCols});
        env[entranceRows][entranceCols] = charToFill;

        //up, down, left, right
        std::vector<std::pair<int, int>> directions;

        directions.push_back({-1, 0});
        directions.push_back({1, 0});
        directions.push_back({0, -1});
        directions.push_back({0, 1});

        //iterate till empty
        while (!q.empty()) {
            //assign variable to first element of stack
            int x = q.front().first;
            int y = q.front().second;
            // std::cout << "row " << x << std::endl;
            // std::cout << "col " << y << std::endl;

            //remove first element of stack
            q.pop();

            
            for (std::vector<std::pair<int, int>>::const_iterator it = directions.begin(); it != directions.end(); it++) {
                int newRow = x + it->first;
                int newCol = y + it->second;
                        
                // std::cout << "Nrow " << newRow << std::endl;
                // std::cout << "Ncol " << newCol << std::endl;
                if (newRow >= 0 && newRow <= (height - 1) && newCol >= 0 && newCol <= (width - 1) && env[newRow][newCol] == 'x') {
                    env[newRow][newCol] = charToFill;
                    // std::cout << "new " << env[newRow][newCol] << std::endl;
                    // rowss = newRow;
                    // colss = newCol;
                    q.push({newRow, newCol});
                }

                // counter++;


                // if (counter == 4) {
                //     floodFill(env, height, width, rowss, colss) ;
                // }
            }   

        }        
    }

}