#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
using namespace std;

class Observer
{
    public:
        virtual void onNotify() = 0;
};

class Subject
{
    private:
        vector<Observer*> observers;
    public:
        void addObserver(Observer* observer);
        void removeObserver(Observer* observer);
        void notify();
};

#endif // OBSERVER_HPP