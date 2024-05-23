#include "osberver.hpp"

void Subject::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify() {
    for (Observer* observer : observers) {
        observer->onNotify();
    }
}