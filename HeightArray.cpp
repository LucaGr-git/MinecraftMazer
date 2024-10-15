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
        /*
        CONTRACT 
        PRE-CONDITION:
        User of class correctly instantiates an object and gives necessary parameters
        POST-CONDITION:
        AN object of HeightArray2D is created and the array + members are initialized

        */
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
        /*
        CONTRACT 
        PRE-CONDITION:
        User of class correctly instantiates an object and gives necessary parameters
        POST-CONDITION:
        HeightArray2D array is cleaned up to prevent memory leaks
        */
        ~HeightArray2D() {
            // Before deleting outer array delete inner rows
            for (int i = 0; i < numXBlocks; ++i) {
                delete[] heightArr[i]; 
            }
            // finally delete outer array / column
            delete[] heightArr; 
        }

        // Access element
        /*
        CONTRACT 
        PRE-CONDITION:
        User of class correctly gives index x and z values that are not out of range
        POST-CONDITION:
        The integer at given x/y coordinates are returned
        */
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
        /*
        CONTRACT 
        PRE-CONDITION:
        numXBlocks is well defined
        POST-CONDITION:
        The numXBlocks member is returned
        */
        int getXBlocks() const { 
            return numXBlocks; 
        }

        // Get number of columns
        /*
        CONTRACT 
        PRE-CONDITION:
        numZBlocks is well defined
        POST-CONDITION:
        The numZBlocks member is returned
        */
        int geZXBlocks() const { 
            return numZBlocks; 
        }

        // Get the X coordinate
        /*
        CONTRACT 
        PRE-CONDITION:
        xCoord is well defined
        POST-CONDITION:
        The xCoord member is returned
        */
        int getXCoord() const { 
            return xCoord; 
        }

        // Get the Z coordinate
        /*
        CONTRACT 
        PRE-CONDITION:
        zCoord is well defined
        POST-CONDITION:
        The zCoord member is returned
        */
        int getZCoord() const { 
            return zCoord; 
        }

        // Set the X coordinate
        /*
        CONTRACT 
        POST-CONDITION:
        The xCoord member is changed to the given integer parameter
        */
        void setXcoord(int newXCoord) { 
            xCoord = newXCoord; 
        }

        // Set the Z coordinate
        /*
        CONTRACT 
        POST-CONDITION:
        The zCoord member is changed to the given integer parameter
        */
        void setZCoord(int newZcoord) { 
            zCoord = newZcoord; 
        }

        // Resize the 2D array
        /*
        CONTRACT 
        User inputs realistic integer values for newNumXBlocks/newNumXZBlocks 
        i.e. not extremely large numbers or 0 for no reason
        POST-CONDITION:
        The array is resized and relevant elements are copied in
        */
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
        /*
        CONTRACT 
        User has used changed data members to accurately select the portion of the minecraft world (x and z) to make a heightArray
        i.e. not extremely large numbers or 0 for no reason
        POST-CONDITION:
        THe mccp getheight function is called for all x and z elements in the array 
        */
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
        /*
        CONTRACT 
        POST-CONDITION:
        The array is printed for all elements
        */
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

