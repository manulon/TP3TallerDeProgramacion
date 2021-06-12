#ifndef TA_TE_TI_H
#define TA_TE_TI_H

#define ROW_LENGTH 3
#define COLUMN_LENGTH 3

#include <string>
#include <mutex>
#include <condition_variable>

class TaTeTi {
private:
    char board[ROW_LENGTH][COLUMN_LENGTH];
    std::string name;
    bool there_is_a_winner;
    bool first_get_board;
    
    //Inicializa el tablero, poniendo todos los valores en espacios
    //vacios.
    void initialize_board();
    
    //Asigna el mensaje de victoria en el mensaje recibido por parametro.
    //diciendo asi que se encontro a un ganador.
    void game_finished_with_a_winner(bool status,std::string& msg);

    //Estas funciones verifican si hay un ganador en las filas, columnas
    //o diagonales respectivamente. Y finalmente la ultima de estas
    //chequea si hay un empate.
    bool check_rows(char token);
    bool check_columns(char token);
    bool check_diagonals(char token);
    bool game_tied();

public:
    explicit TaTeTi(const std::string& key);
    ~TaTeTi();

    //Devuelve el estado del tablero actual.
    std::string get_board();
        
    //Realiza un movimiento en el tablero con los valores recibidos por
    //parametro.
    void set_new_position(char character,int column,int row);
    
    //Asigna el nombre del juego recibido por parametro.
    void set_name(const std::string& name);
    
    //Devuelve el nombre del juego
    std::string get_name();
    
    //Chequea el estado actual del juego. Y setea en el parametro msg su
    //estado si es necesario
    void check_game_status(char token,std::string& msg);
};

#endif
