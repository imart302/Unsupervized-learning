#ifndef LEARNING_H
#define LEARNING_H

/*
 * table format
 *     |action 0| action 1| action 2|...| action n
state 0|
state 1|
.      |
.      |
.      |
state m|


*/
// T represents the problem to solve
enum Policy {EGreddy};
enum LearnType {QLearning, Sarsa};



template <class T>
class Learning
{
protected:

    float alfa;
    float gamma;

    unsigned int actions;
    unsigned int states;
    unsigned int actual_s; // actual state

    float **Qtable;
    float epsilon;

    Policy policy;
    LearnType learn;
    T *parent; //This is for obtain the metods of the problem easily the parent must have a
               //metod called float getRewardOf(unsigned int state)
public:
    explicit Learning(float alf, float gam, float eps, unsigned int ac, unsigned int st, T *parnt);
    void configure(float alf, float gamm, float eps);
    void setEpsilon(float e);
    void updateQ(unsigned int st, unsigned int a, float value);
    void run(unsigned int episodes);
    unsigned int getMaxAction(unsigned int s);
    float getMaxQ(unsigned int s);
    float consultQ(unsigned int st, unsigned int a);
    void printQ();
    void setLearnType(LearnType lt);
};

#endif // LEARNING_H
