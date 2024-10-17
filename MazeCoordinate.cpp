#include "MazeCoordinate.h"

MazeCoordinate::MazeCoordinate(int lengthCoord, int widthCoord) : lengthCoord(lengthCoord), widthCoord(widthCoord){}

MazeCoordinate::~MazeCoordinate()
{
}

int MazeCoordinate::getLengthCoord(){
    return this->lengthCoord;
}

int MazeCoordinate::getWidthCoord(){
    return this->widthCoord;
}
