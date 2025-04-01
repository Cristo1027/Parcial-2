#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include "jugador.h"

// Clase que representa el tablero del juego
class Tablero {
private:
    std::vector<Jugador> jugadores; // Jugadores en el juego
    bool juegoFinalizado; // Estado del juego

public:
    // Constructor que inicializa el tablero con los jugadores
    Tablero(std::vector<Jugador> jugadores);

    // Método para jugar una ronda
    void jugarRonda();

    // Método para verificar si el juego ha terminado
    bool juegoTerminado() const;

    // Método para mostrar el ganador
    void mostrarGanador() const;

    // Método para mostrar los puntajes actuales
    void mostrarPuntajes() const;
};

#endif