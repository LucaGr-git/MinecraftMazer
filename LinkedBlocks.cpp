#include "LinkedBlocks.h"

/*
* Contract:
* Post-conditions:
* - a LinkedList object is instantiated
*/
LinkedList::LinkedList() : head(nullptr) {}

/*
* Contract:
* Pre-conditions:
* - a valid coordinate and blockType is passed to the method
* Post-conditions:
* - a new node is created and placed at the end of the list using the given coordinate and block type
*/
// Method to add new node to end of the list
void LinkedList::append(mcpp::Coordinate coord, mcpp::BlockType block) {
    BlockNode* newNode = new BlockNode(coord, block);
    // if there is no head the node becomes is the head
    if (!head) {
        head = newNode;
    }
    else {
        // list is iterated through and the final node now points to the created node
        BlockNode* tempNode = head;
        while (tempNode->next) {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
    }
}

/*
* Contract:
* Pre-conditions:
* - a valid BlockNode is given as parameter
* Post-conditions:
* - given node is placed at the end of the list 
*/
// Method to add new node to end of the list
void LinkedList::append(BlockNode &newNode) {
    // if there is no head the node becomes is the head
    if (!head) {
        head = &newNode;
    }
    else {
        // list is iterated through and the final node now points to the given node
        BlockNode* tempNode = head;
        while (tempNode->next) {
            tempNode = tempNode->next;
        }
        tempNode->next = &newNode;
    }
}

/*
* Contract:
* Pre-conditions:
* - a valid coordinate and blockType is passed to the method
* Post-conditions:
* - a new node is created and placed at the start of the list using given coordinate and block type
*/
// Method to add a new node at the start of the list
void LinkedList::prepend(mcpp::Coordinate coord, mcpp::BlockType block){
    BlockNode* newNode = new BlockNode(coord, block);
    newNode->next = head; // New node points to head
    head = newNode;       // stored head pointer points to the new start of list (head))
}

/*
* Contract:
* Pre-conditions:
* - a valid BlockNode is given as parameter
* Post-conditions:
* - given node is placed at the start of the list
*/
// Method to add a given node at the start of the list
void LinkedList::prepend(BlockNode &newNode){
    newNode.next = head; // New node points to head
    head = &newNode;     // stored head pointer points to the new start of list (head))
}


/*
* Contract:
* Pre-conditions:
* - The LinkedList is instantiated with nodes
* Post-conditions:
* - the list is iterated through and printed
*/
// Method to print the linked list
void LinkedList::print() const {
    BlockNode* tempNode = head;
    while (tempNode) {
        std::cout << "Coordinate: " << tempNode->coord << ", BlockType: " << tempNode->block << std::endl;
        tempNode = tempNode->next;
    }
}

/*
* Contract:
* Post-conditions:
* - the object and it's elements (especially pointers) are deleted/handled
*/
// Destructor to free the allocated memory
LinkedList::~LinkedList() {
    BlockNode* tempNode;
    // all nodes are sequentially deleted
    while (head) {
        tempNode = head;
        head = head->next;
        delete tempNode;
    }
}