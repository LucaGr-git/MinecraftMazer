#include "Agent.h"
#include <algorithm>

class AgentEnhancement : public Agent {
private:
    const mcpp::BlockType acaciaPlank = mcpp::Blocks::ACACIA_WOOD_PLANK;
    std::vector<mcpp::Coordinate> mazeNodes;
    std::vector<bool> visitedNodes;
    mcpp::Coordinate nextCoord;
public:
    //Default constructor for the AgentEnhancement class
    AgentEnhancement();
    ~AgentEnhancement();
    virtual void solveMaze();
};


