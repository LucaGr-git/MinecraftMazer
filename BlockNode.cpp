#include "BlockNode.h"

BlockNode::BlockNode(mcpp::Coordinate coord, mcpp::BlockType block) : 
                     coord(coord), block(block), next(nullptr) {}