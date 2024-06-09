#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
using namespace std;

enum class EventType {                                                                  // Enum class for the event types 
    TOWER_CREATION,
    TILE_CLICKED,
    ENEMY_IN_RANGE_BT,
    ENEMY_IN_RANGE_NT,
    ENEMY_IN_RANGE_ST,
    TOWER_READY_TO_FIRE,
    ENEMY_OUT_OF_RANGE,
    GAME_CLOSE
};

class Observer                                                                          // Observer class          
{
    public:                                                                             // Public members
        virtual ~Observer() {}                                                          // Virtual destructor     
        virtual void onNotify(EventType eventType) = 0;                                 // Virtual function to notify the observer       
};

class Subject                                                                           // Subject class   
{
    private:                                                                            // Private members      
        vector<Observer*> observers;
    public:                                                                             // Public members        
        void addObserver(Observer* observer);
        void removeObserver(Observer* observer);
        void notify(EventType eventType);
};

#endif // OBSERVER_HPP