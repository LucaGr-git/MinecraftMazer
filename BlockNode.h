
#include <mcpp/mcpp.h>


class BlockNode {
public:
    mcpp::Coordinate coord;       // coordinate data member
    mcpp::BlockType block;        // blockType data member
    BlockNode* next;              // Pointer to next node

    BlockNode(mcpp::Coordinate coord, mcpp::BlockType block); 
};