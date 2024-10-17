#include "Agent.h"

Agent::Agent(mcpp::Coordinate startLoc)
{
}

Agent::~Agent()
{
}

MazeCoordinate Agent::getRandomCoord(Maze* maze) {

    int randomCoordIndex = rand() % maze->mazeGaps.size();

    MazeCoordinate randomCoord = maze->mazeGaps[randomCoordIndex];

    std::cout << randomCoord.getLengthCoord() << " " << randomCoord.getWidthCoord() << std::endl;

    return randomCoord;
}

void Agent::teleportPlayer(mcpp::Coordinate location) {
    mc.setPlayerPosition(location);
}

