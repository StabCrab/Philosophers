
#include "Philosopher.h"
using namespace std;

int main()
{
    mutex forks[5];
    mutex cout_mutex;
    srand(time(0));
    Philosopher* philosophers[5];

    philosophers[0] = new Philosopher("Socrat",0, &forks[4], &forks[0], &cout_mutex);
    philosophers[1] = new Philosopher("Platon",1, &forks[0], &forks[1], &cout_mutex);
    philosophers[2] = new Philosopher("Decart",2, &forks[1], &forks[2], &cout_mutex);
    philosophers[3] = new Philosopher("Popper",3, &forks[2], &forks[3], &cout_mutex);
    philosophers[4] = new Philosopher("Aristotel",4, &forks[3], &forks[4], &cout_mutex);
    std::vector<thread> threads;
    threads.push_back(thread(&Philosopher::philosophize, philosophers[0]));
    threads.push_back(thread(&Philosopher::philosophize, philosophers[1]));
    threads.push_back(thread(&Philosopher::philosophize, philosophers[2]));
    threads.push_back(thread(&Philosopher::philosophize, philosophers[3]));
    threads.push_back(thread(&Philosopher::philosophize, philosophers[4]));


    for(auto &t : threads)
        t.join();

    for (int i = 0; i < 5; i++)
    {
        delete philosophers[i];
    }
    return 0;
}

