#include <iostream>

#include <mcpp/mcpp.h>



template <typename type> class BlockArray { 

    // a pointer to the array in memory of the given type
    type * arrPtr;

    // total storage capacity of the array
    int storageCap;

    // Current number of objects stored in the ArrayList
    int logicalLen;

    public:

        // Default Constructor
        BlockArray() {
            arrPtr = new type[1];
            storageCap = 1;
            logicalLen = 0;
        }

        // Destuctor to prevent memory leaks
        ~BlockArray() { 
            delete[] arrPtr; 
        }

        // method to place an element at the end of an array
        void pushBack(type newBlock) {
            
            // If the storage cap is reached then a new array is created with more space and the old one is deleted

            if (storageCap == logicalLen){
                type* tempArrPtr = new type[2 * storageCap]; // Storage capacity is doubled

                storageCap = 2 * storageCap;
                // old elements are copied into the new array
                for (int i = 0; i < logicalLen; ++i){
                    tempArrPtr[i] = this->arrPtr[i];
                }

                delete[] this->arrPtr; // current array is deleted

                this->arrPtr = tempArrPtr;

            
            }

            this->arrPtr[this->logicalLen++] = newBlock; // final element is updataded and logical length is iterated

        }

        // method to set a specific element of the list
        void set(int index, type newBlock){
            
            // if index equals the capacity the pushBack function is called
            if (index == this->storageCap){
                pushBack(newBlock);
            }
            // otherwise the data at the index is replaced
            else{
                this->arrPtr[index] = newBlock;
            }
        }


        // method that returns the elelment at given index
        type get(int index)
        {
            // if index is in array
            if (index < this->logicalLen)
                return this->arrPtr[index];
            // if index is not in array
            return this->arrPtr[this->logicalLen - 1];
        }
    
        
        // method to remove final element of array
        void popBack() { 
            this->logicalLen--; 
        }
    

        // method that returns logical length of array
        int getSize() { 
            return this->logicalLen; 
        }

        // method to print the array's elements and members
        void printArray(const std::ostream &oss) {
            // Print out array members
            oss << "Printing BlockArray:\n";
            oss << "    Current Maximum length:" << this->storageCap << "\n";
            oss << "    Logical length:" << this->logicalLen << "\n";
            oss << "Array:\n{";
            // Print out each individual element in the array
            for (int i = 0; i < this->logicalLen; ++i) {
                // a comma or curly-bracket is added depending on if it is the last item in the list
                oss << this->arrPtr[i] << ((i != this->logicalLen - 1)? ",":"}\n"); 
            }


        }

};

// The function is only intended to work to store heights (int) and BlockType class objects 
template class BlockArray<mcpp::BlockType>;
template class BlockArray<int>;