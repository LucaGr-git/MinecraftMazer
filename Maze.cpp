#include "Maze.h"

Maze::Maze()
{
    this->length = 0;
    this->width = 0;

    mazeStructure = nullptr;
    start = nullptr;
}

Maze::Maze(int length, int width):
                        length(length),
                        width(width)
{
    this->mazeStructure = nullptr;
    this->start = nullptr;
}

Maze::~Maze()
{
    //delete memory
    deallocateMazeStructure();
    deallocateStart();
}


int Maze::getLength(void){
    return this->length;
}

int Maze::getWidth(void){
    return this->width;
}

void Maze::setLength(int length){
    this->length = length;
}

void Maze::setWidth(int width){
    this->width = width;
}


void Maze::setStart(mcpp::Coordinate* start){
    if (this->start != nullptr){
        deallocateStart();
    }
    this->start = start;
}


mcpp::Coordinate* Maze::getStart(void){
    return this->start;
}

void Maze::setMazeStructure(char** mazeStructure){
    if (this->mazeStructure != nullptr){
        deallocateMazeStructure();
    }

    this->mazeStructure = mazeStructure;
}

char** Maze::getMazeStructure(void){
    return this->mazeStructure;
}

void Maze::deallocateMazeStructure(){
    //delete memory
    if (this->mazeStructure != nullptr) {
        for(int i =0; i < this->getLength(); i++){
            if (this->mazeStructure[i] != nullptr){
                delete[] this->mazeStructure[i];
                this->mazeStructure[i] = nullptr;
            }
        }
        delete[] this->mazeStructure;
        this->mazeStructure = nullptr;
    }

}

void Maze::deallocateStart(){
    //Deallocate start
    if (this->start != nullptr) {
        delete this->start;
        this->start = nullptr;
    }
}

void Maze::findMazeGaps(){
    //Iterate throught mazeStructure
    for (int i = 0; i < this->getLength(); i++) {
        for (int k = 0; i < this->getWidth(); k++) {
            if (this->mazeStructure[i][k] == '.'){
                
            }
        }
    }
}


