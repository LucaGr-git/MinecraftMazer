#include <iostream>
#include <mcpp/mcpp.h>

class HeightArray2D {
    private:
        int** heightArr;       // Pointer to the 2D array of integers
        int numXBlocks;      // Number of blocks on x-axis (rows)
        int numZBlocks;      // Number of blocks on z-axis (columns)
        int xCoord;         // Actual x-coordinate
        int zCoord;         // Actual z-Coordinate

    public:
        // Constructor
        HeightArray2D(int startXBlocks = 5, int startZBlocks = 5, int startXCoord = 0,int startZCoord = 0) {
            // set X and Y blocks to given amount
            numXBlocks = startXBlocks;
            numZBlocks = startZBlocks;

            xCoord = startXCoord;
            zCoord = startZCoord;

            // create the 2d array
            heightArr = new int*[numXBlocks];

            // Fill in inner elements of array with zeroes
            for (int i = 0; i < numXBlocks; ++i) {
                heightArr[i] = new int[numZBlocks]{0};  
            }
        }

        // Destructor
        ~HeightArray2D() {
            // Before deleting outer array delete inner rows
            for (int i = 0; i < numXBlocks; ++i) {
                delete[] heightArr[i]; 
            }
            // finally delete outer array / column
            delete[] heightArr; 
        }

        // Access element
        int& at(int xVal, int zVal) {
            xVal -= xCoord;
            zVal -= zCoord;

            // if the given values are out of range an error is thrown
            if (xVal >= numXBlocks || zVal >= numZBlocks) {
                throw std::out_of_range("Index out of bounds");
            }
            // otherwise the correct value is
            return heightArr[xVal][zVal];
        }

        // Get number of rows 
        int getRows() const { 
            return numXBlocks; 
        }

        // Get number of columns
        int getCols() const { 
            return numZBlocks; 
        }

        // Get the X coordinate
        int getXcoord() const { 
            return xCoord; 
        }

        // Get the Z coordinate
        int getZCoord() const { 
            return zCoord; 
        }

        // Set the X coordinate
        void setXcoord(int newXCoord) { 
            xCoord = newXCoord; 
        }

        // Set the Z coordinate
        void setZCoord(int newZcoord) { 
            zCoord = newZcoord; 
        }

        // Resize the 2D array
        void resize(int newNumXBlocks, int newNumZBlocks) {

            // Make new array and fill with zeroes
            int** newData = new int*[newNumXBlocks];
            for (int i = 0; i < newNumXBlocks; ++i) {
                newData[i] = new int[newNumZBlocks]{0}; 
            }

            // Copy old array to new array
            // get smallest value of x-axis blocks (rows) in the two different arrays
            int minX = std::min(numXBlocks, newNumXBlocks);
            // get smallest value of z-axis blocks (rows) in the two different arrays
            int minZ = std::min(numZBlocks, newNumZBlocks);

            // Copy elements
            for (int i = 0; i < minX; ++i) {
                for (int j = 0; j < minZ; ++j) {
                    newData[i][j] = heightArr[i][j];
                }
            }

            // delete old array
            for (int i = 0; i < numXBlocks; ++i) {
                delete[] heightArr[i];
            }
            delete[] heightArr;

            // Change old array, x-blocks (rows) and z-blocks (columns) to updated values
            heightArr = newData;
            numXBlocks = newNumXBlocks;
            numZBlocks = newNumZBlocks;
        }

        // populate the array with the heights at the given xCoord and zCoord
        void generateHeightArray(){
            mcpp::MinecraftConnection mc;
            for (int i = 0; i < numXBlocks; ++i){
                for (int j = 0; j < numZBlocks; ++j){
                    int height = mc.getHeight(i + xCoord, j + zCoord);

                    
                    heightArr[i][j] = height;

                }
            }
        }


        // Print the 2D array (for demonstration)
        void print() const {
            std::cout << "{";
            for (int i = 0; i < numXBlocks; ++i) {
                for (int j = 0; j < numZBlocks; ++j) {
                    
                    std::cout << heightArr[i][j];

                    if ((i == numXBlocks - 1) && (j == numZBlocks - 1)){
                        std::cout << "}";
                    }
                    else{
                        std::cout << ",";
                    }

                }
                std::cout << std::endl;
            }
        }
};

