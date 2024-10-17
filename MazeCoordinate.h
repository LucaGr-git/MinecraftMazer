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

#endif //MAZE_COORD