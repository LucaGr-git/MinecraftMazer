#include <iostream>

#include <mcpp/mcpp.h>



template <typename type> class BlockArray { 

    // a pointer to the array in memory of the given type
    type * arrPtr;

    // total storage capacity of the array
    int storageCap;

    // Current number of objects stored in the ArrayList
    int currStored;

    public:

        // Default Constructor
        BlockArray() {
            arrPtr = new type[1];
            storageCap = 2;
            currStored = 0;
        }

        // Destuctor to prevent memory leaks
        ~BlockArray() { 
            delete[] arrPtr; 
        }

        void push_back(type newBlock) {
            
            // If the storage cap is reached then a new array is created with more space and the old one is deleted

            if (storageCap == currStored){
                type* tempArrPtr = new type[2 * storageCap]; // Storage capacity is doubled

                storageCap = 2 * storageCap;
                // old elements are copied into the new array
                for (int i = 0; i < currStored; ++i){
                    tempArrPtr[i] = this->arrPtr[i];
                }

                delete[] this->arrPtr; // current array is deleted

                this->arrPtr = tempArrPtr;

            
            }

            this->arrPtr[this->currStored++] = newBlock; // final element is updataded and currStored is iterated

        }

        void set(int index, type newBlock){
            
            // if index equals the capacity the push_back function is called
            if (index == this->storageCap){
                push_back(newBlock);
            }
            // otherwise the data at the index is replaced
            else{
                this->arrPtr[index] = newBlock;
            }
        }

        
        type get(int index)
        {
            // if index is in array
            if (index < this->currStored)
                return this->arrPtr[index];
            // if index is not in array
            return this->arrPtr[this->currStored - 1];
        }
    
        
        void pop_back() { 
            this->currStored--; 
        }
    

        int getSize() { 
            return this->currStored; 
        }

};

// The function is only intended to work to store heights (int) and BlockType class objects 
template class BlockArray<mcpp::BlockType>;
template class BlockArray<int>;