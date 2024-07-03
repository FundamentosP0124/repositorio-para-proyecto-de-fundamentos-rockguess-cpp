#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Estructura para representar a un participante
struct Participante {
    string nombreCompleto;
    string carne;
    string banda;
    int puntaje;
    int intentosSobrantes;

    Participante() : puntaje(0), intentosSobrantes(3) {}
};

// Canciones por banda
const string cancionesGuns[] = {"Sweet Child O' Mine", "November Rain", "Welcome to the Jungle"};
const string cancionesMegadeth[] = {"Symphony of Destruction", "Hangar 18", "Holy Wars... The Punishment Due"};
const string cancionesPoison[] = {"Every Rose Has Its Thorn", "Talk Dirty to Me", "Nothin' but a Good Time"};
const string cancionesVanHalen[] = {"Jump", "Panama", "Hot for Teacher"};

// Función para elegir una canción aleatoria de una banda
string elegirCancion(const string& banda) {
    int indice = rand() % 3;
    if (banda == "Guns N' Roses") {
        return cancionesGuns[indice];
    } else if (banda == "Megadeth") {
        return cancionesMegadeth[indice];
    } else if (banda == "Poison") {
        return cancionesPoison[indice];
    } else if (banda == "Van Halen") {
        return cancionesVanHalen[indice];
    }
    return "";
}

// Función para que el jugador elija la banda que desee
string elegirBanda() {
    cout << "¡Bienvenido al juego de Bandas!" << endl;
    cout << "Elige tu banda favorita:" << endl;
    cout << "1. Guns N' Roses" << endl;
    cout << "2. Megadeth" << endl;
    cout << "3. Poison" << endl;
    cout << "4. Van Halen" << endl;

    int opcion;
    do {
        cout << "Ingresa el número de la banda: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                return "Guns N' Roses";
            case 2:
                return "Megadeth";
            case 3:
                return "Poison";
            case 4:
                return "Van Halen";
            default:
                cout << "Opción inválida. Por favor, elige una opción válida." << endl;
        }
    } while (true);
}

// Función para mostrar el progreso actual en la canción sin revelar el nombre completo de la canción
void mostrarProgreso(const string& progreso) {
    cout << "Progreso actual: ";
    for (size_t i = 0; i < progreso.length(); ++i) {
        if (progreso[i] != '_') {
            cout << progreso[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

// Función para registrar participantes en un archivo con carné
void registrarParticipante(const string& archivoRegistro, Participante& participante) {
    ofstream archivo;
    archivo.open(archivoRegistro, ios_base::app);

    if (archivo.is_open()) {
        archivo << participante.nombreCompleto << "," << participante.carne << "," << participante.banda << "," << participante.puntaje << "\n";
        archivo.close();
        cout << "¡Registro exitoso de participante!" << endl;
    } else {
        cout << "¡Error al intentar abrir el archivo de registro!" << endl;
    }
}

// Función para determinar al ganador entre los participantes
void determinarGanador(Participante participantes[], int numParticipantes) {
    int indiceGanador = 0;
    for (int i = 1; i < numParticipantes; ++i) {
        if (participantes[i].intentosSobrantes > participantes[indiceGanador].intentosSobrantes) {
            indiceGanador = i;
        }
    }

    cout << "\nEl ganador es: " << participantes[indiceGanador].nombreCompleto << " con " << participantes[indiceGanador].intentosSobrantes << " intentos sobrantes." << endl;

    ofstream archivo;
    archivo.open("registro_ganador.txt");
    if (archivo.is_open()) {
        archivo << "El ganador es: " << participantes[indiceGanador].nombreCompleto << " de la banda " << participantes[indiceGanador].banda << " con " << participantes[indiceGanador].intentosSobrantes << " intentos sobrantes." << endl;
        archivo.close();
    } else {
        cout << "Error al intentar abrir el archivo para registrar al ganador." << endl;
    }
}

// Función para jugar a adivinar la canción
void jugarAdivinarCancion(Participante& participante, const string& cancion) {
    string progreso(cancion.length(), '_');
    int intentos = 3;

    cout << "\n¡Adivina la canción de " << participante.banda << "!" << endl;

    while (intentos > 0) {
        cout << "Intentos restantes: " << intentos << endl;
        mostrarProgreso(progreso);

        cout << "Ingresa una letra o la canción completa: ";
        string respuesta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, respuesta);

        if (respuesta == cancion) {
            cout << "¡Felicidades! Has adivinado la canción correctamente." << endl;
            participante.puntaje += intentos;
            participante.intentosSobrantes = intentos;
            break;
        } else {
            cout << "Incorrecto. Intenta de nuevo." << endl;
            intentos--;
        }
    }

    if (intentos == 0) {
        cout << "Lo siento, has agotado tus intentos. La canción era: " << cancion << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    string bandaElegida = elegirBanda();
    string nombreCancion = elegirCancion(bandaElegida);

    cout << "Has seleccionado la banda: " << bandaElegida << endl;

    Participante participantes[3];

    // Registro de participantes
    for (int i = 0; i < 3; ++i) {
        cout << "\nRegistro del participante " << i + 1 << endl;
        cout << "----------------------------------" << endl;

        cout << "Ingresa tu nombre completo: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, participantes[i].nombreCompleto);

        cout << "Ingresa tu número de carné: ";
        cin >> participantes[i].carne;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        participantes[i].banda = bandaElegida;

        registrarParticipante("registro_participantes.txt", participantes[i]);
    }

    // Juego de adivinar la canción
    for (int i = 0; i < 3; ++i) {
        jugarAdivinarCancion(participantes[i], nombreCancion);
    }

    // Determinar y mostrar al ganador
    determinarGanador(participantes, 3);

    return 0;
}
