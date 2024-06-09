#include "observer.hpp"
#include <algorithm>
using namespace std;

void Subject::addObserver(Observer* observer) {                                                 // Add observer to the vector of observers
    observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {                                              // Remove observer from the vector of observers       
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify(EventType EventType) {                                                     // Notify the observers          
    for (Observer* observer : observers) {
        observer->onNotify(EventType);
    }
}