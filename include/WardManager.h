#ifndef WARD_MANAGER_H
#define WARD_MANAGER_H

#include "Ward.h"
#include <vector>
#include <iostream>

class WardManager {
private:
    std::vector<Ward> wards;

public:
    WardManager();

    void addWard(const Ward& w);
    Ward* getWard(int id);
    const std::vector<Ward>& getAllWards() const;
    void setWards(const std::vector<Ward>& loadedWards);

    Ward* findAvailableWard(WardType type);
    bool assignBed(int wardId);
    bool releaseBed(int wardId);

    void displayAll() const;
};

#endif
