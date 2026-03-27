#ifndef WARD_H
#define WARD_H

#include <string>

enum class WardType {
    General,
    ICU,
    Emergency
};

class Ward {
private:
    int id;
    int capacity;
    int currentOccupancy;
    WardType type;

public:
    Ward(int id, int capacity, WardType type);

    int getId() const;
    int getCapacity() const;
    int getCurrentOccupancy() const;
    WardType getType() const;
    std::string getTypeString() const;

    bool isFull() const;
    bool assignBed();
    bool releaseBed();

    // The assignment said "track bed availability", this allows overriding occupancy if needed.
    void setCurrentOccupancy(int occ);

    std::string toCSV() const;
};

std::string wardTypeToString(WardType type);
WardType stringToWardType(const std::string& s);

#endif
