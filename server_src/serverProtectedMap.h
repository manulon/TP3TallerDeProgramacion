#ifndef SERVER_PROTECTED_MAP_H
#define SERVER_PROTECTED_MAP_H

#include "../common_src/TaTeTi.h"
#include <string>
#include <map>
#include <utility>

class ProtectedMap {
    std::map<std::string, TaTeTi*> internal;
    
public:
    ProtectedMap();
    ~ProtectedMap();

    bool contains(const std::string& key);
    void set_name(const std::string& key);
    void add_new_game(TaTeTi* game);
    std::string get_name(const std::string& key);
    std::string get_all_values();
    TaTeTi* get_game(const std::string& key);
};

#endif
