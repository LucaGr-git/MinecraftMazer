#include <mcpp/mcpp.h>
#include "BlockNode.h"

class LinkedList {
private:
    BlockNode* head;

public:
    /*
    * Contract:
    * Post-conditions:
    * - a LinkedList object is instantiated
    */
    LinkedList();

    /*
    * Contract:
    * Pre-conditions:
    * - a valid coordinate and blockType is passed to the method
    * Post-conditions:
    * - a new node is created and placed at the end of the list using the given coordinate and block type
    */
    // Method to add new node to end of the list
    void append(mcpp::Coordinate coord, mcpp::BlockType block);

    /*
    * Contract:
    * Pre-conditions:
    * - a valid BlockNode is given as parameter
    * Post-conditions:
    * - given node is placed at the end of the list 
    */
    // Method to add given node to end of the list
    void append(BlockNode &newNode);

    /*
    * Contract:
    * Pre-conditions:
    * - a valid coordinate and blockType is passed to the method
    * Post-conditions:
    * - a new node is created and placed at the start of the list using given coordinate and block type
    */
    // Method to add a new node at the start of the list
    void prepend(mcpp::Coordinate coord, mcpp::BlockType block);

    /*
    * Contract:
    * Pre-conditions:
    * - a valid BlockNode is given as parameter
    * Post-conditions:
    * - given node is placed at the start of the list
    */
    // Method to add a given node at the start of the list
    void prepend(BlockNode &newNode);

    /*
    * Contract:
    * Pre-conditions:
    * - The LinkedList is instantiated with nodes
    * Post-conditions:
    * - the list is iterated through and printed
    */
    // Method to print the linked list
    void print() const ;

    /*
    * Contract:
    * Post-conditions:
    * - the object and it's elements (especially pointers) are deleted/handled
    */
    // Destructor to free the allocated memory
    ~LinkedList();
};