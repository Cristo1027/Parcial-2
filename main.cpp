#include <iostream>
#include <vector>
#include <limits>
#include "jugador.h"
#include "tablero.h"
#include "mazo.h"

const int MIN_JUGADORES = 2;
const int MAX_JUGADORES = 4;

int main() {
    std::vector<Jugador> jugadores;
    int cantidadJugadores;

    // Mensaje de bienvenida
    std::cout << "¡Bienvenido al juego de cartas! Por favor, ingresa el número de jugadores (2-4): ";

    // Validar el número de jugadores
    while (true) {
        std::cin >> cantidadJugadores;

        // Comprobar si la entrada es válida
        if (std::cin.fail() || cantidadJugadores < MIN_JUGADORES || cantidadJugadores > MAX_JUGADORES) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Número de jugadores no válido, mínimo " << MIN_JUGADORES << " y máximo " << MAX_JUGADORES << ". Inténtalo de nuevo: ";
        } else {
            break; 
        }
    }

    // Recoger los nombres de los jugadores
    for (int i = 0; i < cantidadJugadores; ++i) {
        std::string nombre;
        std::cout << "Ingrese el nombre del jugador " << i + 1 << ": ";
        std::cin >> nombre;
        jugadores.push_back(Jugador(nombre));
    }

    // Crear el mazo y barajarlo
    Mazo mazo;
    mazo.barajar();

    // Repartir todas las 36 cartas equitativamente entre los jugadores
    int cartasPorJugador = 36 / cantidadJugadores;
    for (auto& jugador : jugadores) {
        jugador.recibirCartas(mazo.repartirCartas(cartasPorJugador));
    }

    // Verificar que los jugadores recibieron cartas
    std::cout << "\nCartas repartidas a los jugadores:\n";
    for (const auto& jugador : jugadores) {
        jugador.mostrarMano();
    }

    Tablero tablero(jugadores);

    while (!tablero.juegoTerminado()) {
        tablero.jugarRonda();
    }

    tablero.mostrarGanador();

    return 0;
}