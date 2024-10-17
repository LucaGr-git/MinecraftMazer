#ifndef MAZE_COORD
#define MAZE_COORD

class MazeCoordinate
{
private:
    /* data */
    int lengthCoord;
    int widthCoord;
public:
    MazeCoordinate(int lengthCoord, int widthCoord);
    ~MazeCoordinate();

    int getLengthCoord();
    int getWidthCoord();
};

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


#endif //MAZE_COORD