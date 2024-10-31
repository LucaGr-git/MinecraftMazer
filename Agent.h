#ifndef ASSIGN3_AGENT_H
#define ASSIGN3_AGENT_H
//
#include "Maze.h"
#include "MazeCoordinate.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mcpp/mcpp.h>
#include <thread>

#define MOVE_XPLUS mcpp::Coordinate(1, 0, 0)
#define MOVE_XMINUS mcpp::Coordinate(-1, 0, 0)
#define MOVE_ZPLUS mcpp::Coordinate(0, 0, 1)
#define MOVE_ZMINUS mcpp::Coordinate(0, 0, -1)

enum solveAlgorithm {
    RIGHT_HAND_FOLLOW,
    BREATH_FIRST_SEARCH,
};

enum AgentOrientation { X_PLUS, Z_PLUS, X_MINUS, Z_MINUS };

class Agent {

  public:
    /* Contract:
     *  Pre-Conditions, coordinate needs to be filled
     *  Post-Conditions, Agent has data member currentLoc filled
     */
    Agent(mcpp::Coordinate startLoc);

    ~Agent();

    /* Contract:
     *  Pre-Conditions, Maze has to be filled, and the findMazeGaps function has
     *  had to have been called previously
     *  Post-Conditions, a random coordinate is chosen from the vector mazeGaps
     *  and returns a MazeCoordiate
     *
     */
    MazeCoordinate getRandomCoord(Maze* maze);

    /* Contract:
     *  Pre-Conditions, player must exist in the minecraft world
     *  Post-Condition, returns the coordinate of where the player is
     *
     */
    mcpp::Coordinate getPlayerCoord();

    /* Contract:
     * Pre-Condtitions, newLoc must be a valid mcpp coordinate.
     * Post-Condtitions, agent is set to the newLoc
     *
     */
    void setPlayerCoord(mcpp::Coordinate newLoc);

    /* Contract:
     *  Pre-Conditions, location must be a valid mcpp coordinate
     *  Post-Conditions, player in minecraft is moved to the mcpp coord
     *
     */
    void teleportPlayer(mcpp::Coordinate location);

    /** Contract:
     * Pre-Conditions, mode has to be passed
     * Post-Conditions, iterates through the maze until a blue carpet is found
     */
    void solveMaze(bool mode);

  private:
    /* data */
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate currentLoc;
    bool movingZPos;
    bool movingZNeg;
    bool movingXPos;
    bool movingXNeg;
    bool randomDirectionChosen = false;

    // Helper method to solve maze
    void initialisePlayerDirection(bool mode);
};

#endif // ASSIGN3_AGENT_H