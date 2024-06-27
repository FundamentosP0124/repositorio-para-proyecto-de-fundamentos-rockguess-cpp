#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>  // Para numeric_limits

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

// Función para elegir una canción aleatoria de una banda
string elegirCancion(const string banda) {
    int indice = rand() % 3;
    if (banda == "Guns N' Roses") {
        return cancionesGuns[indice];
    } else if (banda == "Megadeth") {
        return cancionesMegadeth[indice];
    } else if (banda == "Poison") {
        return cancionesPoison[indice];
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
    cout << "4. Salir del menú" << endl;

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
                exit(0);
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

// Función para mostrar el nombre completo de la canción
void mostrarNombreCancion(const string& nombreCancion) {
    cout << "La canción era: " << nombreCancion << endl;
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
        char letra;
        cin >> letra;

        letra = tolower(letra);

        bool acierto = false;
        for (size_t i = 0; i < cancion.length(); ++i) {
            if (tolower(cancion[i]) == letra) {
                progreso[i] = cancion[i];
                acierto = true;
            }
        }

        if (acierto) {
            cout << "¡Correcto! Has encontrado la letra \"" << letra << "\" en la canción." << endl;
        } else {
            cout << "Incorrecto. Intenta de nuevo." << endl;
            intentos--;
        }

        if (progreso == cancion) {
            cout << "¡Felicidades! Has adivinado la canción correctamente." << endl;
            participante.puntaje += intentos;
            participante.intentosSobrantes = intentos;
            break;
        }
    }

    if (intentos == 0) {
        cout << "Lo siento, has agotado tus intentos. La canción era: " << cancion << endl;
    }
}

// Función para jugar a adivinar la canción recursivamente entre los participantes
void jugarCancion(string cancion, Participante participantes[], int& turno, int numParticipantes) {
    string respuesta;
    cout << "Participante " << turno << ", adivina la canción: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, respuesta);

    if (respuesta == cancion) {
        cout << "¡FELICIDADES, " << participantes[turno - 1].nombreCompleto << ", LOGRASTE ADIVINAR LA CANCIÓN!" << endl;
    } else {
        turno = (turno % numParticipantes) + 1; // Cambia de turno
        jugarCancion(cancion, participantes, turno, numParticipantes); // Llama a la función recursivamente
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    string nombreCancion;
    string bandaElegida = elegirBanda();

    if (bandaElegida == "Guns N' Roses") {
        nombreCancion = elegirCancion("Guns N' Roses");
    } else if (bandaElegida == "Megadeth") {
        nombreCancion = elegirCancion("Megadeth");
    } else if (bandaElegida == "Poison") {
        nombreCancion = elegirCancion("Poison");
    }

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
    int turno = 1;
    jugarCancion(nombreCancion, participantes, turno, 3);

    determinarGanador(participantes, 3);

    // Mostrar el nombre de la canción al final
    mostrarNombreCancion(nombreCancion);

    return 0;
}
