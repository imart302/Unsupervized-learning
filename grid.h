#ifndef GRID_H
#define GRID_H

#include "learning.cpp"

/*
 movements: up=action0=0, down=action1=1, left=action2=2, right=action3=3
 enviroment settings:
    cliff = 1
    normal = 2
    objetive = 0
 states are enumerated from 0 to m, beggining from top-left to buttom-right
 s0    s1    s2   ...  sn
 sn+1  sn+2  sn+3 ...  s2n
 .                     .
 .                     .
 .                     .
 ......................sm

*/

class Grid
{
private:
    unsigned int rows;
    unsigned int columns;

    float clifrew;
    float objrew;
    float normrew;

    unsigned int *envsetup; // define the values of the enviroment
    unsigned int beginx;
    unsigned int beginy;
    unsigned int posx;
    unsigned int posy;
    unsigned int last_mov;

    Learning<Grid> gridLearn; //provides learning to the class

public:
    Grid(unsigned int r, unsigned int c);
    void setClifRew(float cr);
    void setObjRew(float ord);
    void setNorRew(float nr);

    void setCliff(unsigned int x, unsigned y); //set a cliff in the coordinate x,y
    void setCliffs(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2); //set cliffs from x1,y1 to x2,y2

    void setObjetive(unsigned int x, unsigned int y);
    void setInitial(unsigned int x, unsigned int y);
    float getRewardOf(unsigned int st);
    float getActualReward();
    void doAction(unsigned int mov);
    void resetGrid();
    void configLearn(float alf, float gamm, float eps, LearnType lt);
    unsigned int posToSt(unsigned int x, unsigned int y);
    unsigned int actualToSt();
    bool isFinal();
    void makeItLearn(unsigned int cicles);
    void backAction();
};

#endif // GRID_H
