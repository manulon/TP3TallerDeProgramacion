#include "serverProtectedMap.h"

ProtectedMap:: ProtectedMap() {}

bool ProtectedMap:: contains(const std::string& key) {
    return this->internal.find(key) != this->internal.end();
}

void ProtectedMap:: set_name(const std::string& key){
    this->internal[key].set_name(key);
}

std::string ProtectedMap::get_name(const std::string& key){
    return this->internal[key].get_name();
}

ProtectedMap:: ~ProtectedMap() {}