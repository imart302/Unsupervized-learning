/*
 *  Author: Ivan Martinez
 *  Assigment: QLearning y Sarsa
 *  Signature: Agentes Inteligentes
 *
 */
#include <iostream>
#include "grid.h"

/*
 * The class with the problem must have
 * 6 functions for communicate with Learning
 * these are:
 *      unsigned int actualToSt() return the actual
 *              state of the enviroment
 *      bool isObj() return true if actually is terminated
 *      void doAction(unsigned int action)
 *      float getActualReward() the value of the actual reward
 *      void reset() set proble to initial conditions
 *
 */

int main(){
    //parameters rows, colums
    Grid test(5,7);
    // parameter : alfa, gamma, epsilon, type of learninr(qlearnin or sarsa)
    test.configLearn(0.6,0.95,0.3, LearnType::Sarsa);
    //parameter num of exetutions
    test.makeItLearn(4000);
    return 0;
}
