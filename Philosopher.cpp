//
// Created by trykr on 13.12.2020.
//

#include "Philosopher.h"

Philosopher::Philosopher(std::string name, short int idx, std::mutex* leftFork, std::mutex* rightFork, std::mutex* coutMutex)
{
    this->name = name;
    this->idx = idx;
    this->hunger = 0;
    this->leftFork = leftFork;
    this->rightFork = rightFork;
    this->coutMutex = coutMutex;
}

Philosopher::~Philosopher()
{

}

void Philosopher::philosophize()
{
    std::ostringstream ostr;
    while(true)
    {
        if (think > 100)
        {
            ostr << name << " got an idea!" << std::endl;
            print_msg(ostr.str());
            break;
        }
        if(hunger < 5)
        {
            ostr << name << " is thinking about something: " + std::to_string(think) << std::endl;
            print_msg(ostr.str());
            std::this_thread::sleep_for(std::chrono::seconds(rand() % 5));
            state = State::thinking;
            forks = Forks::hasNoForks;
            think += (rand() % 10);
        }
        hunger += rand() % 5;
        if (hunger >= 5)
        {
            ostr << name << " is hungry: " + std::to_string(hunger) << std::endl;
            print_msg(ostr.str());
            state = State::hungry;
        }

        // wait for left fork
        //while(!left_fork.try_lock()) this_thread::yield();
        if (state == State::hungry)
        {
            if (leftFork->try_lock())
            {
                ostr << name << " got left fork! " << std::endl;
                print_msg(ostr.str());
                if (forks == Forks::hasNoForks)
                    forks = Forks::hasOneFork;
                if (forks == Forks::hasOneFork)
                    forks = Forks::hasTwoForks;
            }
            if (rightFork->try_lock())
            {
                ostr << name << " got right fork! " << std::endl;
                print_msg(ostr.str());
                if (forks == Forks::hasNoForks)
                    forks = Forks::hasOneFork;
                if (forks == Forks::hasOneFork)
                    forks = Forks::hasTwoForks;
            }
        }

        // wait for left fork
        //while(!right_fork.try_lock()) this_thread::yield();

        if (state == State::hungry && forks == Forks::hasTwoForks)
        {
            ostr << name << " is eating" << std::endl;
            print_msg(ostr.str());
            hunger = 0;

            rightFork->unlock();
            leftFork->unlock();

            forks = Forks::hasNoForks;

            ostr << name << " put forks on the table" << std::endl;
            print_msg(ostr.str());

            std::this_thread::sleep_for(std::chrono::seconds(2));
            state = State::thinking;

        }
    }
}

void Philosopher::print_msg(const std::string &msg)
{
    coutMutex->lock();
    std::cout << msg << std::flush;
    coutMutex->unlock();
}



