//
// Created by trykr on 13.12.2020.
//

#ifndef PHILOSOPHERS_PHILOSOPHER_H
#define PHILOSOPHERS_PHILOSOPHER_H
#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

enum class State
{
    thinking = 0,
    hungry,
    eating
};
enum class Forks
{
    hasNoForks = 0,
    hasOneFork,
    hasTwoForks
};
class Philosopher
{
private:
    int think = 0;
    std::mutex* coutMutex;
    std::string name;
    short int idx;
    int hunger = 0;
    State state;
    Forks forks;
    std::mutex* leftFork;
    std::mutex* rightFork;
public:
    Philosopher(std::string name, short int idx, std::mutex* leftFork, std::mutex* rightFork, std::mutex* coutMutex);
    ~Philosopher();
    void philosophize();
    void print_msg(const std::string& msg);

};


#endif //PHILOSOPHERS_PHILOSOPHER_H
