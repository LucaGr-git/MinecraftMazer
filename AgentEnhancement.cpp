#include "AgentEnhancement.h"

AgentEnhancement::AgentEnhancement() {
    setPlayerCoord(mcpp::Coordinate(0, 0, 0));
}

AgentEnhancement::~AgentEnhancement() {}

void AgentEnhancement::solveMaze() {
    currentLoc = mc.getPlayerPosition();
    bool blueCarpetFound = false;
    int numberOfSteps = 1;

    // Coordinate vector
    std::vector<mcpp::Coordinate> directions = {
        currentLoc + MOVE_XPLUS, currentLoc + MOVE_XMINUS,
        currentLoc + MOVE_ZPLUS, currentLoc + MOVE_ZMINUS};

    // Initialises the vector with the base node
    mazeNodes.push_back(currentLoc);

    // Vector to track predecessors, initialized with -1
    std::vector<int> predecessors;
    // Start node has no predessors
    predecessors.push_back(-1);

    // Sets the base node coordinate as visited
    visitedNodes.push_back(true);

    // Going to check adjacent blocks around base node
    // X positive
    for (unsigned int z = 0; z < mazeNodes.size() && (blueCarpetFound == false);
         z++) {
        currentLoc = mazeNodes[z];

        if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
            // Found blue carpet, construct shortest path
            blueCarpetFound = true;
            std::vector<mcpp::Coordinate> shortestPath;
            int pathIndex = z;

            // Backtrack from the blue carpet to the start
            while (pathIndex != -1) {
                shortestPath.push_back(mazeNodes[pathIndex]);
                pathIndex = predecessors[pathIndex];
            }

            std::reverse(shortestPath.begin(), shortestPath.end());

            // Iterates over shortestPath, and places lime carpets on each coord
            for (size_t m = 0; m < shortestPath.size(); m++) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if (m == 0) {
                    mc.setBlock(shortestPath[m], mcpp::Blocks::LIME_CARPET);
                } else {
                    // Removes the previous carpet.
                    mc.setBlock(shortestPath[m - 1], mcpp::Blocks::AIR);
                    mc.setBlock(shortestPath[m], mcpp::Blocks::LIME_CARPET);
                }
                std::cout << "Step[" << numberOfSteps
                          << "]: " << shortestPath[m] << std::endl;
                ++numberOfSteps;
            }
        }

        bool foundCoord = false;
        if (mc.getBlock(currentLoc + MOVE_XPLUS) != acaciaPlank) {
            nextCoord = mcpp::Coordinate(currentLoc + MOVE_XPLUS);
            for (unsigned int i = 0; i < mazeNodes.size(); i++) {
                if (mazeNodes[i] == nextCoord) {
                    // The node hasn't been visited yet
                    foundCoord = true;
                }
            }
            if (foundCoord == false) {
                mazeNodes.push_back(nextCoord);
                predecessors.push_back(z);
            }
            foundCoord = false;
        }
        // X negative
        if (mc.getBlock(currentLoc + MOVE_XMINUS) != acaciaPlank) {
            nextCoord = mcpp::Coordinate(currentLoc + MOVE_XMINUS);
            for (unsigned int i = 0; i < mazeNodes.size(); i++) {
                if (mazeNodes[i] == nextCoord) {
                    // The node hasn't been visited yet
                    foundCoord = true;
                }
            }
            if (foundCoord == false) {
                mazeNodes.push_back(nextCoord);
                predecessors.push_back(z);
            }
            foundCoord = false;
        }
        // Z positive
        if (mc.getBlock(currentLoc + MOVE_ZPLUS) != acaciaPlank) {
            nextCoord = mcpp::Coordinate(currentLoc + MOVE_ZPLUS);
            for (unsigned int i = 0; i < mazeNodes.size(); i++) {
                if (mazeNodes[i] == nextCoord) {
                    // The node hasn't been visited yet
                    foundCoord = true;
                }
            }
            if (foundCoord == false) {
                mazeNodes.push_back(nextCoord);
                predecessors.push_back(z);
            }
            foundCoord = false;
        }
        // Z negative
        if (mc.getBlock(currentLoc + MOVE_ZMINUS) != acaciaPlank) {
            nextCoord = mcpp::Coordinate(currentLoc + MOVE_ZMINUS);
            for (unsigned int i = 0; i < mazeNodes.size(); i++) {
                if (mazeNodes[i] == nextCoord) {
                    // The node hasn't been visited yet
                    foundCoord = true;
                }
            }
            if (foundCoord == false) {
                mazeNodes.push_back(nextCoord);
                predecessors.push_back(z);
            }
            foundCoord = false;
        }
    }
}