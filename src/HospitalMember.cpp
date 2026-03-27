#include "HospitalMember.h"

HospitalMember::HospitalMember(int id, const std::string& name) : id(id), name(name) {}

int HospitalMember::getId() const { return id; }
std::string HospitalMember::getName() const { return name; }
