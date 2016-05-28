#include "grid.h"
#include <cassert>

//there is a initial enviroment by defaul(definded in the book)

Grid::Grid(unsigned int r, unsigned int c):
    rows(r),
    columns(c),
    beginx(0),
    beginy(r-1),
    gridLearn(0.3, 0.4, 0.5, 4, r*c, this)
{
    clifrew = -50;
    objrew = 100;
    normrew = -1;
    posx = beginx;
    posy = beginy;
    envsetup = new unsigned int[r*c];
    unsigned int begin = (rows-1)*columns + 1;
    unsigned int end = (rows-1)*columns + (columns-2);
    for(unsigned int i = 0; i<rows*columns; i++){
        if(i>=begin && i<=end){
            envsetup[i] = 1;
        }
        else
            envsetup[i] = 2;
    }
    envsetup[rows*columns-1] = 0;
    last_mov=5; //5 = NONE
}


void Grid::setClifRew(float cr){
    clifrew = cr;
}

void Grid::setObjRew(float ord){
    objrew = ord;
}

void Grid::setNorRew(float nr){
    normrew = nr;
}

void Grid::setCliff(unsigned int x, unsigned y){
    assert(x*y<=columns*rows && x<=columns && y<=rows);
    envsetup[(x-1)*columns + (y-1)]=1;
}

void Grid::setCliffs(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2){
    assert(x1>0 && x2>0 && y1>0 && y2>0);
    assert(x2>x1);
    unsigned int begin = (x1-1)*columns + (y1-1);
    unsigned int end = (x2-1)*columns + (y2-1);
    for(unsigned int i = 0; i < rows*columns; i++){
        if(i>= begin && i <= end){
            envsetup[i]=1;
        }
    }
}

void Grid::setObjetive(unsigned int x, unsigned int y){
    assert(x < columns && y < rows);
    envsetup[(x-1)*columns + (y-1)]=0;
}

void Grid::setInitial(unsigned int x, unsigned int y){
    assert(x<columns && y<rows);
    beginx = x;
    beginy = y;
}

float Grid::getActualReward(){
    unsigned int st = actualToSt();
    assert(st<rows*columns);
    unsigned int value = envsetup[st];
    if(value == 0) return objrew;
    if(value == 1) return clifrew;
    if(value == 2) return normrew;
    return 0;
}

void Grid::doAction(unsigned int mov){
    switch (mov){
        case 0: // up
            if(posy > 0){
                posy = posy-1;
                last_mov = 0;
            }
        break;
        case 1: // down
            if(posy < rows-1){
                posy = posy+1;
                last_mov = 1;
            }
        break; // left
        case 2:
            if(posx > 0){
                posx = posx-1;
                last_mov = 2;
            }
        break;
        case 3: // right
            if(posx < columns-1){
                posx = posx+1;
                last_mov = 3;
            }
        break;
        default:
        break;
    }
}

void Grid::resetGrid(){
    posx = beginx;
    posy = beginy;
}

void Grid::configLearn(float alf, float gamm, float eps, LearnType lt){
    gridLearn.configure(alf,gamm,eps);
    gridLearn.setLearnType(lt);
}

unsigned int Grid::posToSt(unsigned int x, unsigned int y){
    assert(x<columns && y<rows);
    unsigned int st;
    st = y*columns + x;
    return st;
}

unsigned int Grid::actualToSt(){
    return (posy*columns + posx);
}

bool Grid::isFinal(){
    unsigned int st = actualToSt();
    unsigned int value = envsetup[st];
    if(value == 0 || value == 1) return true;
    else return false;
}

void Grid::makeItLearn(unsigned int cicles){
    gridLearn.run(cicles);
    gridLearn.printQ();
}

void Grid::backAction(){
    if(last_mov<4){
        doAction(last_mov);
        last_mov = 5;
    }
}

