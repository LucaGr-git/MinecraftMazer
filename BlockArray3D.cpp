#include <iostream>
#include <mcpp/mcpp.h>

class BlockArray3D {
    private:
        mcpp::BlockType*** blockArr;    // Pointer to the 3D array of BlockType objects
        mcpp::Coordinate startCoord;    // start coordinate of 3d array
        mcpp::Coordinate endCoord;      // end coordinate of 3d array
        mcpp::Coordinate diffCoord;     //Difference in coordinate of 3d array


    public:
        // Constructor
        /*
        CONTRACT 
        PRE-CONDITION:
        User of class correctly instantiates an object and gives necessary parameters
        POST-CONDITION:
        AN object of BlockArray3D is created and the array + coordinate members are initialized

        */
        BlockArray3D(mcpp::Coordinate initialStartCoord = mcpp::Coordinate(0,0,0), mcpp::Coordinate initialEndCoord = mcpp::Coordinate(5,5,5)) {
            // set X and Y blocks to given amount
            startCoord = initialStartCoord;
            endCoord = initialEndCoord;

            // get the difference in x, y and z
            diffCoord =  endCoord - startCoord;

            std::cout << diffCoord;


            // return error if the given coordinates are not in proper order
            if (diffCoord.x < 0 || diffCoord.y < 0 || diffCoord.z < 0){
                throw std::runtime_error("Coordinate Error: Make sure that the start coordinate is lower than the end coordinate");
            }

            // create the 3d array
            blockArr = new mcpp::BlockType**[diffCoord.x];

            // Fill in inner elements of 3d array with 2d array
            for (int i = 0; i < diffCoord.x; ++i) {
                blockArr[i] = new mcpp::BlockType*[diffCoord.y];  
                // Fill in inner elements of 2d array with zeroes
                for (int j = 0; j < diffCoord.y; ++j) {
                    blockArr[i][j] = new mcpp::BlockType[diffCoord.y]{0};  

                }

            }
        }

        // Destructor
        /*
        CONTRACT 
        PRE-CONDITION:
        User of class correctly instantiates an object and gives necessary parameters
        POST-CONDITION:
        BlockArray3D array is cleaned up to prevent memory leaks
        */
        ~BlockArray3D() {
            // get the difference in x, y and z
            mcpp::Coordinate diffCoord = startCoord - endCoord;

            // Before deleting outer array delete the innermost rows 
            for (int i = 0; i < diffCoord.x; ++i) {
                for (int j = 0; j < diffCoord.y; ++j) {
                    delete[] blockArr[i][j]; 
                }
                
                delete[] blockArr[i]; 
            }
            // finally delete outer array / column
            delete[] blockArr; 


        }

        // Access element
        /*
        CONTRACT 
        PRE-CONDITION:
        User of class correctly gives index x and z values that are not out of range
        POST-CONDITION:
        The integer at given x/y /zcoordinates are returned
        */
        mcpp::BlockType& at(int xVal, int yVal, int zVal) {
            xVal -= startCoord.x;
            yVal -= startCoord.y;
            zVal -= startCoord.z;

            // if the given values are out of range an error is thrown
            if (xVal >= diffCoord.x ||  yVal >= diffCoord.y || zVal >= diffCoord.z) {
                throw std::out_of_range("Index out of bounds");
            }

            // otherwise the correct value is returned
            return blockArr[xVal][yVal][zVal];
        }

        // Access element
        /*
        CONTRACT 
        PRE-CONDITION:
        User of class correctly gives coordinate that are not out of range
        POST-CONDITION:
        The integer at given x/y/z coordinates are returned
        */
        mcpp::BlockType& at(mcpp::Coordinate indexCoords) {
            return at(indexCoords.x, indexCoords.y, indexCoords.z);
        }



        // Get the coordinate of difference between start and end
        /*
        CONTRACT 
        PRE-CONDITION:
        the classes members are well defined
        POST-CONDITION:
        The diffCoord member is returned
        */
        mcpp::Coordinate getDiffInCoords() const { 
            return diffCoord; 
        }

        // Get the start coordinate
        /*
        CONTRACT 
        PRE-CONDITION:
        the member startCoord is well defined
        POST-CONDITION:
        The startCoord member is returned
        */
        mcpp::Coordinate getStartCoord() const { 
            return startCoord; 
        }

        // Get the end coordinate
        /*
        CONTRACT 
        PRE-CONDITION:
        the member endCoord is well defined
        POST-CONDITION:
        The endCoord member is returned
        */
        mcpp::Coordinate getEndCoord() const { 
            return endCoord; 
        }



        // Set the X coordinate
        /*
        CONTRACT 
        PRE-CONDITION:
        Given coordinates must be ordered correctly i.e. the start coordinate is smaller in x, y and z
        POST-CONDITION:
        The start, end and difference coordinate member is changed to the given coordinate parameters
        */
        void setCoords(mcpp::Coordinate newStartCoord = mcpp::Coordinate(0,0,0), mcpp::Coordinate newEndCoord = mcpp::Coordinate(5,5,5)) { 
            // set X and Y blocks to given amount
            startCoord = newStartCoord;
            endCoord = newEndCoord;

            // get the difference in x, y and z
            diffCoord = endCoord - startCoord;

            
            // return error if the given coordinates are not in proper order
            if (diffCoord.x < 0 || diffCoord.y < 0 || diffCoord.z < 0){
                throw std::runtime_error("Coordinate Error: Make sure that the start coordinate is lower than the end coordinate");
            }
        }
        
        
        // populate the array with the heights at the given coordinate
        /*
        CONTRACT 
        User has used changed data members to accurately select the portion of the minecraft world (x, y and z) to make a block array
        i.e. not extremely large numbers or 0 for no reason
        POST-CONDITION:
        The mccp getBlock function is called for all x, y and z elements in the array 
        */
        void generateBlockArray() {
            //TODO see if optimization is possible? 
            mcpp::MinecraftConnection mc;
            // Iterate through list and update each element with the mccp getHeight at that location
            for (int i = 0; i < diffCoord.x; ++i) {
                for (int j = 0; j < diffCoord.y; ++j) {
                    for (int k = 0; k < diffCoord.z; ++k) {

                        mcpp::BlockType block = mc.getBlock(mcpp::Coordinate(i + startCoord.x,j + startCoord.y,k + startCoord.z));
                        
                        blockArr[i][j][k] = block;

                    }
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
            for (int i = 0; i < diffCoord.x; ++i) {
                std::cout << "Layer " << i << ":\n";
                for (int j = 0; j < diffCoord.y; ++j) {
                    for (int k = 0; k < diffCoord.z; ++k) {
                        std::cout << blockArr[i][j][k] << " ";
                    }
                    std::cout << "\n";
                }
                std::cout << std::endl;
            }
        }
};

