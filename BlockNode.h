#ifndef BLOCKNODE
#define BLOCKNODE

#include <mcpp/mcpp.h>


class BlockNode {
public:
    // coordinate data member
    mcpp::Coordinate coord;    
    // blockType data member   
    mcpp::BlockType block;   
    // Pointer to next node     
    BlockNode* next;              

    BlockNode(mcpp::Coordinate coord, mcpp::BlockType block); 
};

#endif