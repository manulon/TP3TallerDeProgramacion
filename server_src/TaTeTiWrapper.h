#ifndef TA_TE_TI_WRAPPER_H
#define TA_TE_TI_WRAPPER_H

#include "TaTeTi.h"
#include <string>
#include <mutex>
#include <condition_variable>

class TaTeTiWrapper{
    TaTeTi* game;
    bool guest_joined;
    std::mutex m;
    std::condition_variable cv;

public: 
    TaTeTiWrapper();
    ~TaTeTiWrapper(); 

    std::string get_board();
        
    std::string set_new_position(char character,int column,int row);
    
    void set_name(const std::string& name);
    
    std::string get_name();
    
    void check_game_status(char token,std::string& msg);
    
    void notify_winner();

    void guest_join_game();

    void wrap(TaTeTi* game);
    
    void unwrap();
};

#endif
