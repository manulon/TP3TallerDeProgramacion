#include "serverProtectedMap.h"
#include <iostream>

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

void ProtectedMap:: print_all_values(){
    std::cout << "Partidas: " << std::endl;
    for ( auto& element: internal ){
        std::cout<< "- "<< element.second.get_name() << std::endl;
    }
}

ProtectedMap:: ~ProtectedMap() {}