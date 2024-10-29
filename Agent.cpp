#include "Agent.h"

Agent::Agent(mcpp::Coordinate startLoc)
{
    currentLoc = startLoc;
}

Agent::~Agent()
{
}

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

mcpp::Coordinate Agent::getPlayerCoord(){
    return currentLoc;
}

void Agent::initialisePlayerDirection() {
    // Set all moving directions to false
    movingZPos = false;
    movingZNeg = false;
    movingXPos = false;
    movingXNeg = false;

    /* First checking the blocks around the player to check if the wall can be 
    * found
    */
    if (mc.getBlock(currentLoc + mcpp::Coordinate(0, 0, 1)) 
        == mcpp::Blocks::ACACIA_WOOD_PLANK){
        //If passed, a wall is present
        movingXPos = true;
    }
    else if (mc.getBlock(currentLoc + mcpp::Coordinate(0, 0, -1)) 
             == mcpp::Blocks::ACACIA_WOOD_PLANK) {
        //If passed, a wall is present
        movingXNeg = true;
    }
    else if (mc.getBlock(currentLoc + MOVE_XPLUS) 
             == mcpp::Blocks::ACACIA_WOOD_PLANK) {
        movingZNeg = true;
    }
    else if (mc.getBlock(currentLoc + mcpp::Coordinate(-1, 0, 0)) 
             == mcpp::Blocks::ACACIA_WOOD_PLANK) {
        movingZPos = true;
    }
    /* This means that there was no wall found that the player can follow, 
    *  and thus must start walking in a random direction
    */
    else {
        randomDirectionChosen = true;

        //Creates an integer from 0-3 representing the 4 directions the player 
        //can move
        int randomDirection = rand() % 4;

        if (randomDirection == 0) {
            movingZPos = true;
        }
        else if (randomDirection == 1) {
            movingZNeg = true;
        }
        else if (randomDirection == 2) {
            movingXPos = true;
        }
        else if (randomDirection == 3) {
            movingXNeg = true; 
        }
    }
}

void Agent::setPlayerCoord(mcpp::Coordinate newLoc){
    currentLoc = newLoc;
}

void Agent::solveMaze(){
    initialisePlayerDirection();
    bool foundBlueCarpet = false;
    int numberOfSteps = 1;
    //Every coordinate moved needs to be printed
    mc.setBlock(currentLoc, mcpp::Blocks::GREEN_CARPET);
    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc << std::endl;
    // Checking if the intitial direction was a random choice
    if (randomDirectionChosen != true) {
        while (foundBlueCarpet == false) {
            if (movingXNeg == true) {
                //First we are going to check if the wall is to the right
                while (mc.getBlock(currentLoc + MOVE_ZMINUS) 
                       == mcpp::Blocks::ACACIA_WOOD_PLANK 
                       && (movingXNeg == true) && (foundBlueCarpet == false)) {
                    //Check that we can move forward
                    if ((mc.getBlock(currentLoc + MOVE_XMINUS) 
                        == mcpp::Blocks::AIR)) {
                        
                        //Set block to air
                        mc.setBlock(currentLoc, mcpp::Blocks::AIR);
                        //Moves the player 1 coord forward
                        setPlayerCoord(currentLoc + MOVE_XMINUS);
                        ++numberOfSteps;                       
                        //Check if the solver has reached the
                        if (mc.getBlock(currentLoc) 
                           == mcpp::Blocks::BLUE_CARPET) {
                            foundBlueCarpet = true;
                        }
                        //Set block to carpet
                        mc.setBlock(currentLoc, mcpp::Blocks::GREEN_CARPET);

                        //Print each movement in the terminal
                        std::cout << "Step[" << numberOfSteps << "]: "
                                  << currentLoc << std::endl;

                    }
                    /*Wall in front of player need to change orientation to face
                    * left to keep right hand on new wall
                    */
                    else if ((mc.getBlock(currentLoc + MOVE_XMINUS) 
                             != mcpp::Blocks::AIR)) {
                        movingXNeg = false;
                        movingZPos = true;
                    }


                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
                /* If the direction wasn't changed previously due to not hitting
                *  a wall, move to keep hand on wall
                */
                if (movingXNeg == true) {
                    //No longer going to move in the x neg direction
                    movingXNeg = false;

                    //Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);
                    /* Going to move a unit in the Z neg direction to keep the 
                    *  hand on the wall, and change orientation to Z neg
                    */
                    setPlayerCoord(currentLoc + MOVE_ZMINUS);
                    ++numberOfSteps;                       
                    //Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }
                    //Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::GREEN_CARPET);
                            
                    //Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                              << std::endl;
            
                    movingZNeg = true;
                }
            }
            else if (movingXPos == true) {
                //First we are going to check if the wall is to the right
                while (mc.getBlock(currentLoc + MOVE_ZPLUS) == 
                      mcpp::Blocks::ACACIA_WOOD_PLANK && (movingXPos == true)) {
                    //Check that we can move forward
                    if ((mc.getBlock(currentLoc + MOVE_XPLUS) 
                        == mcpp::Blocks::AIR)) {
                        
                        //Set block to air
                        mc.setBlock(currentLoc, mcpp::Blocks::AIR);
                        //Moves the player 1 coord forward
                        setPlayerCoord(currentLoc + MOVE_XPLUS);
                        ++numberOfSteps;                       
                        //Check if the solver has reached the
                        if (mc.getBlock(currentLoc) == 
                            mcpp::Blocks::BLUE_CARPET) {
                            foundBlueCarpet = true;
                        }
                        //Set block to carpet
                        mc.setBlock(currentLoc, mcpp::Blocks::GREEN_CARPET);

                        //Print each movement in the terminal
                        std::cout << "Step[" << numberOfSteps << "]: " 
                        << currentLoc << std::endl;

                    }
                    else if ((mc.getBlock(currentLoc + MOVE_XPLUS) 
                             != mcpp::Blocks::AIR)) {
                        movingXPos = false;
                        movingZNeg = true;
                    }


                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
                /* If the direction wasn't changed previously due to not hitting
                * a wall, move to keep hand on wall
                */
                if (movingXPos == true) {
                    //No longer going to move in the Z pos direction
                    movingXPos = false;

                    //Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);

                    /* Going to move a unit in the Z plus direction to keep the 
                    * hand on the wall, and change orientation to Z plus
                    */
                    setPlayerCoord(currentLoc + MOVE_ZPLUS);
                    ++numberOfSteps;                       

                    //Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }

                    //Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::GREEN_CARPET);
                    
               
                    //Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc
                              << std::endl;
            
                    movingZPos = true;
                }
            }
            else if (movingZNeg == true) {
                //First we are going to check if the wall is to the right
                while (mc.getBlock(currentLoc + MOVE_XPLUS) 
                       == mcpp::Blocks::ACACIA_WOOD_PLANK 
                       && (movingZNeg == true)) {
                    //Check that we can move forward
                    if ((mc.getBlock(currentLoc + MOVE_ZMINUS) 
                        == mcpp::Blocks::AIR)) {
                        
                        //Set block to air
                        mc.setBlock(currentLoc, mcpp::Blocks::AIR);

                        //Moves the player 1 coord forward
                        setPlayerCoord(currentLoc + MOVE_ZMINUS);
                        ++numberOfSteps;                       

                        //Check if the solver has reached the
                        if (mc.getBlock(currentLoc) 
                            == mcpp::Blocks::BLUE_CARPET) {
                            foundBlueCarpet = true;
                        }

                        //Set block to carpet
                        mc.setBlock(currentLoc, mcpp::Blocks::GREEN_CARPET);


                        //Print each movement in the terminal
                        std::cout << "Step[" << numberOfSteps << "]: " 
                                  << currentLoc << std::endl;

                    }
                    /*Wall in front of player need to change orientation to face
                    * left to keep right hand on new wall
                    */
                    else if ((mc.getBlock(currentLoc + MOVE_ZMINUS) 
                             != mcpp::Blocks::AIR)) {

                        movingZNeg = false;
                        movingXNeg = true;
                    }


                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
                /* If the direction wasn't changed previously due to not hitting
                *  a wall, move to keep hand on wall
                */
                if (movingZNeg == true) {
                    //No longer going to move in the Z neg direction
                    movingZNeg = false;

                    //Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);

                    /* Going to move a unit in the X pos direction to keep the 
                    *  hand on the wall, and change orientation to X pos
                    */
                    setPlayerCoord(currentLoc + MOVE_XPLUS);
                    ++numberOfSteps;                       

                    //Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }

                    //Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::GREEN_CARPET);
                            
                    //Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc 
                              << std::endl;
            
                    movingXPos = true;
                }

            }
            else if (movingZPos == true) {
                //First we are going to check if the wall is to the right
                while (mc.getBlock(currentLoc + MOVE_XMINUS) 
                       == mcpp::Blocks::ACACIA_WOOD_PLANK 
                       && (movingZPos == true)) {

                    //Check that we can move forward
                    if ((mc.getBlock(currentLoc + MOVE_ZPLUS) 
                        == mcpp::Blocks::AIR)) {

                        //Set block to air
                        mc.setBlock(currentLoc, mcpp::Blocks::AIR);
                        
                        //Moves the player 1 coord forward
                        setPlayerCoord(currentLoc + MOVE_ZPLUS);
                        ++numberOfSteps;                       


                        //Check if the solver has reached the
                        if (mc.getBlock(currentLoc) 
                            == mcpp::Blocks::BLUE_CARPET) {
                            foundBlueCarpet = true;
                        }

                        //Set block to carpet
                        mc.setBlock(currentLoc, mcpp::Blocks::GREEN_CARPET);


                        //Print each movement in the terminal
                        std::cout << "Step[" << numberOfSteps << "]: " 
                                  << currentLoc << std::endl;

                    }
                    else if ((mc.getBlock(currentLoc + MOVE_ZPLUS) 
                             != mcpp::Blocks::AIR)) {
                        movingXPos = true;
                        movingZPos = false;
                    }


                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
                /* If the direction wasn't changed previously due to not hitting
                * a wall, move to keep hand on wall
                */
                if (movingZPos == true) {
                    //No longer going to move in the Z pos direction
                    movingZPos = false;

                    //Set block to air
                    mc.setBlock(currentLoc, mcpp::Blocks::AIR);

                    /* Going to move a unit in the X neg direction to keep the 
                    * hand on the wall, and change orientation to X neg
                    */
                    setPlayerCoord(currentLoc + MOVE_XMINUS);
                    ++numberOfSteps;                       


                    //Check if the solver has reached the
                    if (mc.getBlock(currentLoc) == mcpp::Blocks::BLUE_CARPET) {
                        foundBlueCarpet = true;
                    }

                    //Set block to carpet
                    mc.setBlock(currentLoc, mcpp::Blocks::GREEN_CARPET);

                            
                    //Print each movement in the terminal
                    std::cout << "Step[" << numberOfSteps << "]: " << currentLoc 
                              << std::endl;
            
                    movingXNeg = true;
                }

            }
        }
    }
    else {
        
    }
}
