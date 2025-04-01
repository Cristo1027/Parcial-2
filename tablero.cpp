#include "tablero.h"
#include <iostream>

// Constructor que inicializa el tablero con los jugadores
Tablero::Tablero(std::vector<Jugador> jugadores) : jugadores(jugadores), juegoFinalizado(false) {}

// Método para jugar una ronda
void Tablero::jugarRonda() {
    static int ronda = 1;
    std::cout << "\n--- Ronda " << ronda++ << " ---\n";

    // Verificar si todos los jugadores tienen cartas
    for (const auto& jugador : jugadores) {
        if (jugador.manoVacia()) {
            std::cout << jugador.getNombre() << " no tiene más cartas. Fin del juego.\n";
            juegoFinalizado = true;
            return;  // Sale de la función si un jugador no tiene cartas
        }
    }

    std::vector<Carta> cartasJugadas;
    std::string color_base;
    int mayor_valor = -1;
    int ganador_idx = -1;

    for (size_t i = 0; i < jugadores.size(); ++i) {
        int indice;
        std::cout << jugadores[i].getNombre() << ", tu mano es:\n";
        jugadores[i].mostrarMano();
        std::cout << "Elige una carta para jugar (1-" << jugadores[i].getNumeroCartas() << "): ";
        std::cin >> indice;
        while (std::cin.fail() || indice < 1 || indice > jugadores[i].getNumeroCartas()) {
            std::cin.clear(); // Limpiar error
            std::cin.ignore(1000, '\n'); // Ignorar entrada incorrecta
            std::cout << "Selección inválida. Inténtalo de nuevo: ";
            std::cin >> indice;
        }
        indice--; // Ajustar índice a base 0
        Carta carta_jugada = jugadores[i].jugarCarta(indice);
        cartasJugadas.push_back(carta_jugada);

        if (i == 0) {
            color_base = carta_jugada.getColor();
            mayor_valor = carta_jugada.getNumero();
            ganador_idx = 0;
        } else if (carta_jugada.getColor() == color_base && carta_jugada.getNumero() > mayor_valor) {
            mayor_valor = carta_jugada.getNumero();
            ganador_idx = i;
        }
    }

    jugadores[ganador_idx].ganarPunto();
    std::cout << "\nEl ganador de la ronda es: " << jugadores[ganador_idx].getNombre() << "\n";
    mostrarPuntajes();

    // Verificar si el juego ha terminado después de la ronda
    for (const auto& jugador : jugadores) {
        if (!jugador.manoVacia()) {
            return;  // Si al menos un jugador tiene cartas, el juego sigue
        }
    }

    std::cout << "Todos los jugadores se han quedado sin cartas. Fin del juego.\n";
    juegoFinalizado = true;
}

// Método para verificar si el juego ha terminado
bool Tablero::juegoTerminado() const {
    return juegoFinalizado;
}

// Método para mostrar los puntajes actuales
void Tablero::mostrarPuntajes() const {
    std::cout << "\n--- Puntajes Actuales ---\n";
    for (const auto& jugador : jugadores) {
        std::cout << jugador.getNombre() << ": " << jugador.getPuntos() << " puntos\n";
    }
    std::cout << "-------------------------\n";
}

// Método para mostrar el ganador
void Tablero::mostrarGanador() const {
    std::cout << "\n--- Fin del Juego ---\n";
    int maxPuntos = 0;
    std::string ganador;

    for (const auto& jugador : jugadores) {
        if (jugador.getPuntos() > maxPuntos) {
            maxPuntos = jugador.getPuntos();
            ganador = jugador.getNombre();
        }
    }

    std::cout << "El ganador es: " << ganador << " con " << maxPuntos << " puntos.\n";
}