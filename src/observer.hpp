#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
using namespace std;

enum class EventType {
    TOWER_CREATION,
    TILE_CLICKED,
    ENEMY_IN_RANGE,
    TOWER_READY_TO_FIRE,
    ENEMY_OUT_OF_RANGE,
    GAME_CLOSE
};

class Observer
{
    public:
        virtual ~Observer() {}
        virtual void onNotify(EventType eventType) = 0;
};

class Subject
{
    private:
        vector<Observer*> observers;
    public:
        void addObserver(Observer* observer);
        void removeObserver(Observer* observer);
        void notify(EventType eventType);
};

#endif // OBSERVER_HPP