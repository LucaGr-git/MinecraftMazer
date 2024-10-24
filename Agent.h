#ifndef ASSIGN3_AGENT_H
#define ASSIGN3_AGENT_H

#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <mcpp/mcpp.h>
#include "MazeCoordinate.h"
#include "Maze.h"

#define MOVE_XPLUS mcpp::Coordinate(1,0,0)
#define MOVE_XMINUS mcpp::Coordinate(-1,0,0)
#define MOVE_ZPLUS mcpp::Coordinate(0,0,1)
#define MOVE_ZMINUS mcpp::Coordinate(0,0,-1)

enum solveAlgorithm{
        RIGHT_HAND_FOLLOW,
        BREATH_FIRST_SEARCH,
};

enum AgentOrientation{
    X_PLUS,
    Z_PLUS,
    X_MINUS,
    Z_MINUS
};

class Agent
{

public:
    Agent(mcpp::Coordinate startLoc);
    ~Agent();
    MazeCoordinate getRandomCoord(Maze* maze);
    mcpp::Coordinate getPlayerCoord();
    void setPlayerCoord(mcpp::Coordinate newLoc);
    void teleportPlayer(mcpp::Coordinate location);

    void solveMaze();

    

private:
    /* data */
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate currentLoc;
    bool movingZPos;
    bool movingZNeg;
    bool movingXPos;
    bool movingXNeg;
    bool randomDirectionChosen = false;


    //Helper method to solve maze
    void initialisePlayerDirection();

};



#endif //ASSIGN3_AGENT_H