#include "Ward.h"
#include <sstream>

Ward::Ward(int id, int capacity, WardType type)
    : id(id), capacity(capacity), currentOccupancy(0), type(type) {}

int Ward::getId() const { return id; }
int Ward::getCapacity() const { return capacity; }
int Ward::getCurrentOccupancy() const { return currentOccupancy; }
WardType Ward::getType() const { return type; }
void Ward::setCurrentOccupancy(int occ) { currentOccupancy = occ; }

std::string wardTypeToString(WardType type) {
    if (type == WardType::ICU) return "ICU";
    if (type == WardType::Emergency) return "Emergency";
    return "General";
}

WardType stringToWardType(const std::string& s) {
    if (s == "ICU") return WardType::ICU;
    if (s == "Emergency") return WardType::Emergency;
    return WardType::General;
}

std::string Ward::getTypeString() const {
    return wardTypeToString(type);
}

bool Ward::isFull() const {
    return currentOccupancy >= capacity;
}

bool Ward::assignBed() {
    if (isFull()) return false;
    currentOccupancy++;
    return true;
}

bool Ward::releaseBed() {
    if (currentOccupancy > 0) {
        currentOccupancy--;
        return true;
    }
    return false;
}

std::string Ward::toCSV() const {
    std::ostringstream oss;
    oss << id << "," << capacity << "," << currentOccupancy << "," << getTypeString();
    return oss.str();
}
