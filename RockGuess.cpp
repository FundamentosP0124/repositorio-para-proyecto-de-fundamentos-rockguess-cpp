#include <iostream>
#include <string>

using namespace std;

// Función para mostrar el menú y que permitira que el jugador elija una banda
string banda() {
    cout << "Elige una banda:" << endl;
    cout << "1. Guns N' Roses" << endl;
    cout << "2. Megadeth" << endl;
    cout << "3. Poison" << endl;
    cout << "4, Salir del menu" << endl;
    int option;
    cin >> option;

    switch (option) {
        case 1:
            return "Guns N' Roses";
        case 2:
            return "Megadeth";
        case 3:
            return "Poison";
        default:
            cout << "Opción inválida. Seleccionando Guns N' Roses por defecto." << endl;
            return "Guns N' Roses";
    }
}

int main() {
    string band = banda();

    // Aquí continuaremos con el código.

    return 0;
}