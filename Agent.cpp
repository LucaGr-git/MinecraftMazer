#include "Agent.h"

Agent::Agent(mcpp::Coordinate startLoc) { currentLoc = startLoc; }

Agent::~Agent() {}

MazeCoordinate Agent::getRandomCoord(Maze* maze) {

    int randomCoordIndex = rand() % maze->mazeGaps.size();

    MazeCoordinate randomCoord = maze->mazeGaps[randomCoordIndex];

    std::cout << randomCoord.getLengthCoord() << " "
              << randomCoord.getWidthCoord() << std::endl;

    return randomCoord;
}

void Agent::teleportPlayer(mcpp::Coordinate location) {
    mc.setPlayerPosition(location);
    currentLoc = location;
}

mcpp::Coordinate Agent::getPlayerCoord() { return currentLoc; }

void Agent::initialisePlayerDirection(bool mode) {
    // Set all moving directions to false
    movingZPos = false;
    movingZNeg = false;
    movingXPos = false;
    movingXNeg = false;

    // Testing mode function
    if (mode) {
        // First checking the positive x axis
        if (mc.getBlock(currentLoc + MOVE_ZPLUS) ==
            mcpp::Blocks::ACACIA_WOOD_PLANK) {
            movingXPos = true;
        }
        // Clockwise, facing Z - pos
        else if (mc.getBlock(currentLoc + MOVE_XMINUS) ==
                 mcpp::Blocks::ACACIA_WOOD_PLANK) {
            movingZPos = true;
        }
        // Clockwise, facing X - neg
        else if (mc.getBlock(currentLoc + MOVE_ZMINUS) ==
                 mcpp::Blocks::ACACIA_WOOD_PLANK) {
            movingXNeg = true;
        }
        // Clockwise, facing Z - neg
        else if (mc.getBlock(currentLoc + MOVE_XPLUS) ==
                 mcpp::Blocks::ACACIA_WOOD_PLANK) {
            movingZNeg = true;
        }

    }
    // Normal mode function
    else {
        /* First checking the blocks around the player to check if the wall can
         * be found
         */
        if (mc.getBlock(currentLoc + mcpp::Coordinate(0, 0, 1)) ==
            mcpp::Blocks::ACACIA_WOOD_PLANK) {
            // If passed, a wall is present
            movingXPos = true;
        } else if (mc.getBlock(currentLoc + mcpp::Coordinate(0, 0, -1)) ==
                   mcpp::Blocks::ACACIA_WOOD_PLANK) {
            // If passed, a wall is present
            movingXNeg = true;
        } else if (mc.getBlock(currentLoc + MOVE_XPLUS) ==
                   mcpp::Blocks::ACACIA_WOOD_PLANK) {
            movingZNeg = true;
        } else if (mc.getBlock(currentLoc + mcpp::Coordinate(-1, 0, 0)) ==
                   mcpp::Blocks::ACACIA_WOOD_PLANK) {
            movingZPos = true;
        }
        /* This means that there was no wall found that the player can follow,
         *  and thus must start walking in a random direction
         */
        else {
            randomDirectionChosen = true;

            // Creates an integer from 0-3 representing the 4 directions the
            // player can move
            int randomDirection = rand() % 4;

            if (randomDirection == 0) {
                movingZPos = true;
            } else if (randomDirection == 1) {
                movingZNeg = true;
            } else if (randomDirection == 2) {
                movingXPos = true;
            } else if (randomDirection == 3) {
                movingXNeg = true;
            }
        }
    }
}

void Agent::setPlayerCoord(mcpp::Coordinate newLoc) { currentLoc = newLoc; }

void Agent::solveMaze(bool mode) {
    initialisePlayerDirection(mode);
    bool foundBlueCarpet = false;
    bool foundWallRand = false;
    int numberOfSteps = 1;
    // Every coordinate moved needs to be printed
    mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);
    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc << std::endl;
    // Going to find a wall to place right hand on if randomDirection = true
    if (randomDirectionChosen == true) {
        while (foundBlueCarpet == false && foundWallRand == false) {
            if (movingXNeg == true) {
                /* If theres no plank wall in front, and theres air to the right
                 *  keep moving
                 */
                while (mc.getBlock(currentLoc + MOVE_XMINUS) !=
                           mcpp::Blocks::ACACIA_WOOD_PLANK &&
                       mc.getBlock(currentLoc + MOVE_ZMINUS) ==
                           mcpp::Blocks::AIR) {

                    // Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);
                    // Moves the player 1 coord forward
                    setPlayerCoord(currentLoc + MOVE_XMINUS);
                    ++numberOfSteps;
                    // Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }
                    // Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                    // Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                              << std::endl;

                    // There is a wall to the right
                    if (mc.getBlock(currentLoc + MOVE_ZMINUS) ==
                        mcpp::Blocks::ACACIA_WOOD_PLANK) {
                        foundWallRand = true;
                    }
                }
                // When it gets out of the while loop theres either a wall in
                // front, or to the left
                if (foundWallRand != true) {
                    movingXNeg = false;
                    movingZPos = true;
                    foundWallRand = true;
                }
            } else if (movingXPos == true) {
                /* If theres no plank wall in front, and theres air to the right
                 *  keep moving
                 */
                while (mc.getBlock(currentLoc + MOVE_XPLUS) !=
                           mcpp::Blocks::ACACIA_WOOD_PLANK &&
                       mc.getBlock(currentLoc + MOVE_ZPLUS) ==
                           mcpp::Blocks::AIR) {

                    // Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);
                    // Moves the player 1 coord forward
                    setPlayerCoord(currentLoc + MOVE_XPLUS);
                    ++numberOfSteps;
                    // Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }
                    // Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                    // Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                              << std::endl;

                    // There is a wall to the right
                    if (mc.getBlock(currentLoc + MOVE_ZPLUS) ==
                        mcpp::Blocks::ACACIA_WOOD_PLANK) {
                        foundWallRand = true;
                    }
                }
                // When it gets out of the while loop theres either a wall in
                // front, or to the left
                if (foundWallRand != true) {
                    movingXPos = false;
                    movingZNeg = true;
                    foundWallRand = true;
                }

            } else if (movingZNeg == true) {
                /* If theres no plank wall in front, and theres air to the right
                 *  keep moving
                 */
                while (mc.getBlock(currentLoc + MOVE_ZMINUS) !=
                           mcpp::Blocks::ACACIA_WOOD_PLANK &&
                       mc.getBlock(currentLoc + MOVE_XPLUS) ==
                           mcpp::Blocks::AIR) {

                    // Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);
                    // Moves the player 1 coord forward
                    setPlayerCoord(currentLoc + MOVE_ZMINUS);
                    ++numberOfSteps;
                    // Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }
                    // Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                    // Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                              << std::endl;

                    // There is a wall to the right
                    if (mc.getBlock(currentLoc + MOVE_XPLUS) ==
                        mcpp::Blocks::ACACIA_WOOD_PLANK) {
                        foundWallRand = true;
                    }
                }
                // When it gets out of the while loop theres either a wall in
                // front, or to the left
                if (foundWallRand != true) {
                    movingZNeg = false;
                    movingXNeg = true;
                    foundWallRand = true;
                }

            } else if (movingZPos == true) {
                /* If theres no plank wall in front, and theres air to the right
                 *  keep moving
                 */
                while (mc.getBlock(currentLoc + MOVE_ZPLUS) !=
                           mcpp::Blocks::ACACIA_WOOD_PLANK &&
                       mc.getBlock(currentLoc + MOVE_XMINUS) ==
                           mcpp::Blocks::AIR) {

                    // Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);
                    // Moves the player 1 coord forward
                    setPlayerCoord(currentLoc + MOVE_ZPLUS);
                    ++numberOfSteps;
                    // Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }
                    // Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                    // Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                              << std::endl;

                    // There is a wall to the right
                    if (mc.getBlock(currentLoc + MOVE_XMINUS) ==
                        mcpp::Blocks::ACACIA_WOOD_PLANK) {
                        foundWallRand = true;
                    }
                }
                // When it gets out of the while loop theres either a wall in
                // front, or to the left
                if (foundWallRand != true) {
                    movingZPos = false;
                    movingXPos = true;
                    foundWallRand = true;
                }
            }
        }
    }
    while (foundBlueCarpet == false) {
        if (movingXNeg == true) {
            // First we are going to check if the wall is to the right
            while (mc.getBlock(currentLoc + MOVE_ZMINUS) ==
                       mcpp::Blocks::ACACIA_WOOD_PLANK &&
                   (movingXNeg == true) && (foundBlueCarpet == false)) {
                // Check that we can move forward
                if ((mc.getBlock(currentLoc + MOVE_XMINUS) ==
                     mcpp::Blocks::AIR)) {

                    // Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);
                    // Moves the player 1 coord forward
                    setPlayerCoord(currentLoc + MOVE_XMINUS);
                    ++numberOfSteps;
                    // Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }
                    // Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                    // Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                              << std::endl;

                }
                /*Wall in front of player need to change orientation to face
                 * left to keep right hand on new wall
                 */
                else if ((mc.getBlock(currentLoc + MOVE_XMINUS) !=
                          mcpp::Blocks::AIR)) {
                    movingXNeg = false;
                    movingZPos = true;
                }

                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            /* If the direction wasn't changed previously due to not hitting
             *  a wall, move to keep hand on wall
             */
            if (movingXNeg == true) {
                // No longer going to move in the x neg direction
                movingXNeg = false;

                // Set block to air
                mc.setBlock(currentLoc, mcpp::Blocks::AIR);
                /* Going to move a unit in the Z neg direction to keep the
                 *  hand on the wall, and change orientation to Z neg
                 */
                setPlayerCoord(currentLoc + MOVE_ZMINUS);
                ++numberOfSteps;
                // Check if the solver has reached the
                if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                    foundBlueCarpet = true;
                }
                // Set block to carpet
                mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                // Print each movement in the terminal
                std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                          << std::endl;

                movingZNeg = true;
            }
        } else if (movingXPos == true) {
            // First we are going to check if the wall is to the right
            while (mc.getBlock(currentLoc + MOVE_ZPLUS) ==
                       mcpp::Blocks::ACACIA_WOOD_PLANK &&
                   (movingXPos == true)) {
                // Check that we can move forward
                if ((mc.getBlock(currentLoc + MOVE_XPLUS) ==
                     mcpp::Blocks::AIR)) {

                    // Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);
                    // Moves the player 1 coord forward
                    setPlayerCoord(currentLoc + MOVE_XPLUS);
                    ++numberOfSteps;
                    // Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }
                    // Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                    // Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                              << std::endl;

                } else if ((mc.getBlock(currentLoc + MOVE_XPLUS) !=
                            mcpp::Blocks::AIR)) {
                    movingXPos = false;
                    movingZNeg = true;
                }

                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            /* If the direction wasn't changed previously due to not hitting
             * a wall, move to keep hand on wall
             */
            if (movingXPos == true) {
                // No longer going to move in the Z pos direction
                movingXPos = false;

                // Set block to air
                mc.setBlock(currentLoc, mcpp::Blocks::AIR);

                /* Going to move a unit in the Z plus direction to keep the
                 * hand on the wall, and change orientation to Z plus
                 */
                setPlayerCoord(currentLoc + MOVE_ZPLUS);
                ++numberOfSteps;

                // Check if the solver has reached the
                if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                    foundBlueCarpet = true;
                }

                // Set block to carpet
                mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                // Print each movement in the terminal
                std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                          << std::endl;

                movingZPos = true;
            }
        } else if (movingZNeg == true) {
            // First we are going to check if the wall is to the right
            while (mc.getBlock(currentLoc + MOVE_XPLUS) ==
                       mcpp::Blocks::ACACIA_WOOD_PLANK &&
                   (movingZNeg == true)) {
                // Check that we can move forward
                if ((mc.getBlock(currentLoc + MOVE_ZMINUS) ==
                     mcpp::Blocks::AIR)) {

                    // Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);

                    // Moves the player 1 coord forward
                    setPlayerCoord(currentLoc + MOVE_ZMINUS);
                    ++numberOfSteps;

                    // Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }

                    // Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                    // Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                              << std::endl;

                }
                /*Wall in front of player need to change orientation to face
                 * left to keep right hand on new wall
                 */
                else if ((mc.getBlock(currentLoc + MOVE_ZMINUS) !=
                          mcpp::Blocks::AIR)) {

                    movingZNeg = false;
                    movingXNeg = true;
                }

                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            /* If the direction wasn't changed previously due to not hitting
             *  a wall, move to keep hand on wall
             */
            if (movingZNeg == true) {
                // No longer going to move in the Z neg direction
                movingZNeg = false;

                // Set block to air
                mc.setBlock(currentLoc, mcpp::Blocks::AIR);

                /* Going to move a unit in the X pos direction to keep the
                 *  hand on the wall, and change orientation to X pos
                 */
                setPlayerCoord(currentLoc + MOVE_XPLUS);
                ++numberOfSteps;

                // Check if the solver has reached the
                if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                    foundBlueCarpet = true;
                }

                // Set block to carpet
                mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                // Print each movement in the terminal
                std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                          << std::endl;

                movingXPos = true;
            }

        } else if (movingZPos == true) {
            // First we are going to check if the wall is to the right
            while (mc.getBlock(currentLoc + MOVE_XMINUS) ==
                       mcpp::Blocks::ACACIA_WOOD_PLANK &&
                   (movingZPos == true)) {

                // Check that we can move forward
                if ((mc.getBlock(currentLoc + MOVE_ZPLUS) ==
                     mcpp::Blocks::AIR)) {

                    // Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);

                    // Moves the player 1 coord forward
                    setPlayerCoord(currentLoc + MOVE_ZPLUS);
                    ++numberOfSteps;

                    // Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }

                    // Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                    // Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                              << std::endl;

                } else if ((mc.getBlock(currentLoc + MOVE_ZPLUS) !=
                            mcpp::Blocks::AIR)) {
                    movingXPos = true;
                    movingZPos = false;
                }

                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            /* If the direction wasn't changed previously due to not hitting
             * a wall, move to keep hand on wall
             */
            if (movingZPos == true) {
                // No longer going to move in the Z pos direction
                movingZPos = false;

                // Set block to air
                mc.setBlock(currentLoc, mcpp::Blocks::AIR);

                /* Going to move a unit in the X neg direction to keep the
                 * hand on the wall, and change orientation to X neg
                 */
                setPlayerCoord(currentLoc + MOVE_XMINUS);
                ++numberOfSteps;

                // Check if the solver has reached the
                if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                    foundBlueCarpet = true;
                }

                // Set block to carpet
                mc.setBlock(currentLoc, mcpp::Blocks::LIME_CARPET);

                // Print each movement in the terminal
                std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                          << std::endl;

                movingXNeg = true;
            }
        }
    }
}
