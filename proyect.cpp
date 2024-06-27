#include <iostream>
#include <string>
using namespace std;

// Función para mostrar el menú y permitir que el jugador elija una banda
string Banda() {
    cout << "Elige una banda:" << endl;
    cout << "1. Guns N' Roses" << endl;
    cout << "2. Megadeth" << endl;
    cout << "3. Poison" << endl;
    cout << "4. Van Halen" << endl;
    cout << "5. Salir del menú" << endl;
    int option;
    cin >> option;
    switch (option) {
        case 1:
            return "Guns N' Roses";
        case 2:
            return "Megadeth";
        case 3:
            return "Poison";
        case 4:
            return "Van Halen";
        default:
            cout << "Opción inválida. Seleccionando Guns N' Roses por defecto." << endl;
            return "Guns N' Roses";
    }
}

// Función para imprimir el progreso actual del jugador de manera básica
void printProgress(const string& songName, const string& progress) {
    cout << "Progreso: ";
    for (int i = 0; i < songName.length(); ++i) {
        if (progress[i] != '_') {
            cout << progress[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

int main() {
    string songName = "Sweet Child O' Mine";
    string progress(songName.length(), '_');
    printProgress(songName, progress);
    string band = Banda(); // Llamar a la función Banda() para elegir la banda
    cout << "Has elegido la banda: " << band << endl;

    return 0;
}
