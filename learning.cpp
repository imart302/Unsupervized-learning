#include "learning.h"
#include <cassert>
#include <random>
#include <iostream>
#include <iomanip>

template<class T>
Learning<T>::Learning(float alf, float gam, float eps, unsigned int ac, unsigned int st, T *parnt):
    alfa(alf),
    gamma(gam),
    actions(ac),
    states(st),
    epsilon(eps),
    parent(parnt)
{
    Qtable = new float*[states];
    for(unsigned int i = 0; i<states; i++){
        Qtable[i] = new float[actions];
    }
    for(unsigned int i = 0; i<states; i++){
        for(unsigned int j = 0; j<actions; j++){
            Qtable[i][j]=0;
        }
    }
    epsilon = 0.1;
    policy = Policy::EGreddy;
    learn = LearnType::QLearning;
}

template <class T>
void Learning<T>::run(unsigned int episodes){
    std::cout<<"LEARNING"<<std::endl;
    std::cout<<"STATES: "<<states<<std::endl;
    std::cout<<"ACTIONS: "<<actions<<std::endl;
    std::cout<<"EPISODES: "<<episodes<<std::endl;
    std::default_random_engine generator;
    std::bernoulli_distribution explore(epsilon);
    std::uniform_int_distribution<int> actiongen(0,actions-1);
    if(learn == LearnType::QLearning){
        std::cout<<"TYPE: Q-LEARNING"<<std::endl;
        unsigned int action;
        float Qsa;
        float r;
        float maxA;
        unsigned int s_prime;
        if(policy == Policy::EGreddy){
            std::cout<<"POLICY: E-GREEDY"<<std::endl;
            //epsilon-greedy
            for(unsigned int i = 0; i<episodes; i++){
                actual_s = parent->actualToSt();
                //std::cout<<actual_s<<std::endl;
                while(!parent->isFinal()){
                    if(explore(generator))                //random action(explore)
                        action = actiongen(generator);
                    else                                  //better action(exploit)
                        action = getMaxAction(actual_s);

                    parent->doAction(action);
                    s_prime = parent->actualToSt();
                    Qsa = consultQ(actual_s, action);
                    r = parent->getActualReward();
                    maxA = getMaxQ(s_prime);
                    //formula
                    Qsa = Qsa + alfa*(r + gamma*maxA - Qsa);

                    updateQ(actual_s,action,Qsa);
                    actual_s = s_prime;
                }
                parent->resetGrid();
            }
        }
    }
    if(learn == LearnType::Sarsa){
        std::cout<<"TYPE: SARSA"<<std::endl;
        unsigned int action, action_prime;
        float Qsa, Qsa_prime;
        float r;
        unsigned int s_prime;
        if(policy == Policy::EGreddy){
            std::cout<<"POLICY: E-GREEDY"<<std::endl;
            for(unsigned int i = 0; i<episodes; i++){
                actual_s = parent->actualToSt();
                if(explore(generator))                //random action(explore)
                    action = actiongen(generator);
                else                                  //better action(exploit)
                    action = getMaxAction(actual_s);

                while(!parent->isFinal()){
                    parent->doAction(action);
                    s_prime = parent->actualToSt();
                    r = parent->getActualReward();

                    if(explore(generator)){
                        action_prime = actiongen(generator);
                    }
                    else{
                        action_prime = getMaxAction(s_prime);
                    }

                    Qsa = consultQ(actual_s, action);
                    Qsa_prime = consultQ(s_prime, action_prime);
                    //formula
                    Qsa = Qsa + alfa*(r + gamma*Qsa_prime - Qsa);

                    updateQ(actual_s,action,Qsa);
                    actual_s = s_prime;
                    action = action_prime;
                }
                parent->resetGrid();
            }
        }
    }
}

template<class T>
void Learning<T>::configure(float alf, float gamm, float eps){
    assert(alf>0 && gamm>0 && eps>0 && eps<1);
    alfa = alf;
    gamma = gamm;
    epsilon = eps;
}

template<class T>
void Learning<T>::setEpsilon(float e){
    assert(e>0 && e<1);
    epsilon = e;
}

template<class T>
float Learning<T>::getMaxQ(unsigned int s){
    assert(s<states);
    float max = Qtable[s][0];
    for(unsigned int j=1; j<actions; j++){
        if(Qtable[s][j]>max){
            max=Qtable[s][j];
        }
    }
    return max;
}

template<class T>
unsigned int Learning<T>::getMaxAction(unsigned int s){
    assert(s<states);
    float max = Qtable[s][0];
    unsigned int m_action = 0;
    for(unsigned int j=1; j<actions; j++){
        if(Qtable[s][j]>max){
            max=Qtable[s][j];
            m_action = j;
        }
    }
    return m_action;
}

template<class T>
float Learning<T>::consultQ(unsigned int st, unsigned int a){
    assert(st<states && a<actions);
    float value = Qtable[st][a];
    return value;
}

template<class T>
void Learning<T>::printQ(){
    std::cout<<"TABLA Q"<<std::endl;
    for(unsigned int i = 0; i<states; i++){
        for(unsigned int j = 0; j<actions; j++){
            std::cout<<std::setprecision(5)<<Qtable[i][j]<<", ";
        }
        std::cout<<std::endl;
    }
}

template <class T>
void Learning<T>::setLearnType(LearnType lt){
    learn = lt;
}

template <class T>
void Learning<T>::updateQ(unsigned int st, unsigned int a, float value){
    assert(st < states && a<actions);
    Qtable[st][a] = value;
}
