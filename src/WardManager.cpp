#include "WardManager.h"

WardManager::WardManager() {}

void WardManager::addWard(const Ward& w) {
    wards.push_back(w);
}

Ward* WardManager::getWard(int id) {
    for (auto& w : wards) {
        if (w.getId() == id) return &w;
    }
    return nullptr;
}

const std::vector<Ward>& WardManager::getAllWards() const {
    return wards;
}

void WardManager::setWards(const std::vector<Ward>& loadedWards) {
    wards = loadedWards;
}

Ward* WardManager::findAvailableWard(WardType type) {
    for (auto& w : wards) {
        if (w.getType() == type && !w.isFull()) {
            return &w;
        }
    }
    return nullptr;
}

bool WardManager::assignBed(int wardId) {
    Ward* w = getWard(wardId);
    if (w) return w->assignBed();
    return false;
}

bool WardManager::releaseBed(int wardId) {
    Ward* w = getWard(wardId);
    if (w) return w->releaseBed();
    return false;
}

void WardManager::displayAll() const {
    if (wards.empty()) {
        std::cout << "No wards registered.\n";
        return;
    }
    for (const auto& w : wards) {
        std::cout << "Ward ID: " << w.getId() << " | Type: " << w.getTypeString() 
                  << " | Capacity: " << w.getCapacity() 
                  << " | Occupied: " << w.getCurrentOccupancy() << "\n";
    }
}
