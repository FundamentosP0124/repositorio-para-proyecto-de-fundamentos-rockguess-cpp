#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Estructura para representar a un participante
struct Participante {
    string nombreCompleto;
    string carne;
    string banda;
    int puntajeTotal;   // Puntaje acumulado a lo largo de todas las rondas
    int intentosTotales; // Intentos totales utilizados a lo largo de todas las rondas

    Participante() : puntajeTotal(0), intentosTotales(0) {}  // Constructor inicializa el puntaje y los intentos
};

// Listas de canciones por banda
const string cancionesGuns[] = {
    "Sweet Child O' Mine", "November Rain", "Welcome to the Jungle",
    "Paradise City", "Knockin' on Heaven's Door", "Don't Cry",
    "Patience", "Civil War", "You Could Be Mine", "Estranged"
};

const string cancionesMegadeth[] = {
    "Symphony of Destruction", "Hangar 18", "Holy Wars... The Punishment Due",
    "Peace Sells", "Tornado of Souls", "A Tout Le Monde",
    "Sweating Bullets", "Trust", "In My Darkest Hour", "Mechanix"
};

const string cancionesPoison[] = {
    "Every Rose Has Its Thorn", "Talk Dirty to Me", "Nothin' But a Good Time",
    "Fallen Angel", "Unskinny Bop", "Ride the Wind",
    "Something to Believe In", "I Won't Forget You", "Your Mama Don't Dance", "Life Goes On"
};

const string cancionesVanHalen[] = {
    "Jump", "Panama", "Hot for Teacher",
    "Runnin' with the Devil", "Ain't Talkin' 'bout Love", "Why Can't This Be Love",
    "Right Now", "Dance the Night Away", "Eruption", "Dreams"
};

// Función para elegir una canción aleatoria de una banda
string elegirCancion(const string& banda) {
    int indice = rand() % 10;
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

// Función para imprimir el progreso actual del jugador
void mostrarProgreso(const string& progreso) {
    cout << "Progreso: ";
    for (size_t i = 0; i < progreso.length(); ++i) {
        if (progreso[i] != '_') {
            cout << progreso[i] << " "; // Muestra la letra descubierta
        } else {
            cout << "_ "; // Muestra un guión bajo para las letras no descubiertas
        }
    }
    cout << endl;
}

// Función para registrar participantes en un archivo con carné
void registrarParticipante(const string& archivoRegistro, Participante& participante) {
    ofstream archivo;
    archivo.open(archivoRegistro, ios_base::app); // Abre el archivo en modo de añadir al final

    if (archivo.is_open()) {
        archivo << participante.nombreCompleto << "," << participante.carne << "," << participante.banda << "," << participante.puntajeTotal << "," << participante.intentosTotales << "\n";
        archivo.close();
        cout << "¡Registro exitoso de participante!" << endl; // Mensaje de confirmación
    } else {
        cout << "¡Error al intentar abrir el archivo de registro!" << endl; // Mensaje de error
    }
}

// Función para determinar al ganador entre los participantes
void determinarGanador(Participante participantes[], int numParticipantes) {
    int indiceGanador = 0;
    for (int i = 1; i < numParticipantes; ++i) {
        if (participantes[i].puntajeTotal > participantes[indiceGanador].puntajeTotal) {
            indiceGanador = i;
        }
    }

    cout << "\nEl ganador es: " << participantes[indiceGanador].nombreCompleto << " con un puntaje total de " << participantes[indiceGanador].puntajeTotal << " puntos." << endl; // Muestra el ganador y su puntaje total

    ofstream archivo;
    archivo.open("registro_ganador.txt");
    if (archivo.is_open()) {
        archivo << "El ganador es: " << participantes[indiceGanador].nombreCompleto << " de la banda " << participantes[indiceGanador].banda << " con un puntaje total de " << participantes[indiceGanador].puntajeTotal << " puntos." << endl;
        archivo.close();
    } else {
        cout << "Error al intentar abrir el archivo para registrar al ganador." << endl; // Mensaje de error si no se pudo abrir el archivo
    }
}

// Función para jugar a adivinar la canción
void jugarAdivinarCancion(Participante& participante, const string& cancion) {
    string progreso(cancion.length(), '_'); // Inicializa el progreso como guiones bajos
    int intentos = 3; // Número de intentos permitidos

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
            participante.puntajeTotal += intentos; // Suma puntos equivalentes a los intentos restantes
            break;
        } else if (respuesta.length() == 1 && cancion.find(respuesta) != string::npos) {
            cout << "¡Correcto! La letra '" << respuesta << "' está en la canción." << endl;
            for (size_t i = 0; i < cancion.length(); ++i) {
                if (cancion[i] == respuesta[0]) {
                    progreso[i] = respuesta[0]; // Actualiza el progreso mostrando las letras correctas
                }
            }
        } else {
            cout << "Incorrecto. Intenta de nuevo." << endl;
            intentos--; // Reducción del número de intentos si la respuesta es incorrecta
        }
    }

    participante.intentosTotales += (3 - intentos); // Actualiza los intentos totales utilizados

    if (intentos == 0) {
        cout << "Lo siento, has agotado tus intentos. La canción era: " << cancion << endl; // Mensaje si se agotan los intentos
    }
}

// Función para manejar el menú de selección de banda
string seleccionarBanda() {
    cout << "Elige una banda:" << endl;
    cout << "1. Guns N' Roses" << endl;
    cout << "2. Megadeth" << endl;
    cout << "3. Poison" << endl;
    cout << "4. Van Halen" << endl;
    cout << "5. Salir del menu" << endl;

    int opcion;
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (opcion) {
        case 1:
            return "Guns N' Roses";
        case 2:
            return "Megadeth";
        case 3:
            return "Poison";
        case 4:
            return "Van Halen";
        case 5:
            return "Salir";
        default:
            cout << "Opción no válida. Seleccionando Guns N' Roses por defecto." << endl;
            return "Guns N' Roses";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Inicializa la semilla para números aleatorios

    cout << "¡Bienvenido al juego de adivinar la canción!" << endl;

    // Número de participantes
    int numParticipantes;
    cout << "Ingrese el número de participantes: ";
    cin >> numParticipantes;

    // Arreglo de participantes
    Participante participantes[numParticipantes];

    // Registro de participantes
    for (int i = 0; i < numParticipantes; ++i) {
        cout << "\nParticipante " << i + 1 << endl;
        cout << "Nombre completo: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, participantes[i].nombreCompleto);
        cout << "Carné: ";
        getline(cin, participantes[i].carne);

        participantes[i].banda = seleccionarBanda(); // Elige una banda para el participante

        registrarParticipante("registro_participantes.txt", participantes[i]); // Registra al participante
    }

    
    for (int ronda = 0; ronda < 3; ++ronda) {
        string cancion = elegirCancion(participantes[0].banda); 

        cout << "\n--- Ronda " << ronda + 1 << " ---" << endl;
        for (int i = 0; i < numParticipantes; ++i) {
            jugarAdivinarCancion(participantes[i], cancion); 
        }
    }

    // Determinar y mostrar al ganador
    cout << "\n--- ¡Juego Terminado! ---" << endl;
    determinarGanador(participantes, numParticipantes); // Determina al ganador

    // Mostrar puntajes individuales
    cout << "\n--- Puntajes individuales ---" << endl;
    for (int i = 0; i < numParticipantes; ++i) {
        cout << participantes[i].nombreCompleto << " de la banda " << participantes[i].banda << " tiene un puntaje total de " << participantes[i].puntajeTotal << " puntos." << endl; // Muestra el puntaje individual de cada participante
    }

    return 0;
}
