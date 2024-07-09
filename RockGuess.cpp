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

const string cancionesAliceCooper[] = {
    "Poison", "Feed My Frankenstein", "School's Out",
    "No More Mr. Nice Guy", "Billion Dollar Babies", "I'm Eighteen",
    "Under My Wheels", "Hey Stoopid", "Teenage Frankenstein", "Freedom"
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
    } else if (banda == "Alice Cooper") {
        return cancionesAliceCooper[indice];
    }
    return "";
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

// Función para registrar al ganador en un archivo
void registrarGanador(const string& archivoRegistro, Participante& ganador) {
    ofstream archivo;
    archivo.open(archivoRegistro);

    if (archivo.is_open()) {
        archivo << "El ganador es: " << ganador.nombreCompleto << " de la banda " << ganador.banda << " con " << ganador.intentosTotales << " intentos y " << ganador.puntajeTotal << " puntos." << endl;
        archivo.close();
        cout << "¡Registro exitoso del ganador!" << endl; // Mensaje de confirmación
    } else {
        cout << "¡Error al intentar abrir el archivo de registro del ganador!" << endl; // Mensaje de error
    }
}

// Función para determinar al ganador entre los participantes
int determinarGanador(Participante participantes[], int numParticipantes) {
    int indiceGanador = 0;
    int menorIntentos = participantes[0].intentosTotales;

    // Encontrar al participante con menos intentos totales
    for (int i = 1; i < numParticipantes; ++i) {
        if (participantes[i].intentosTotales < menorIntentos) {
            menorIntentos = participantes[i].intentosTotales;
            indiceGanador = i;
        }
    }

    // Verificar si hay empate
    bool hayEmpate = false;
    for (int i = 0; i < numParticipantes; ++i) {
        if (participantes[i].intentosTotales == menorIntentos && i != indiceGanador) {
            hayEmpate = true;
            break;
        }
    }

    if (hayEmpate) {
        cout << "\n¡Hay un empate entre varios participantes!" << endl;
        cout << "¿Desean seguir jugando para desempatar? (s/n): ";

        char opcion;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcion == 's' || opcion == 'S') {
            return -1; // Indicador de empate, se debe seguir jugando
        } else {
            cout << "\n¡No sean conformistas! Sigamos jugando para desempatar." << endl;
            return -2; // Indicador de empate, no se desea seguir jugando
        }
    } else {
        return indiceGanador; // Retorna el índice del ganador si no hay empate
    }
}

// Función para jugar a adivinar la banda de la canción
void jugarAdivinarBanda(Participante& participante, const string& cancion) {
    cout << "\n¡Adivina a qué banda pertenece la canción!" << endl;
    cout << "Canción: " << cancion << endl;

    string respuesta;
    cout << "Ingresa el nombre de la banda: ";
    getline(cin, respuesta);

    if (respuesta == participante.banda) {
        cout << "¡Respuesta correcta! La canción '" << cancion << "' pertenece a la banda " << participante.banda << "." << endl;
        participante.puntajeTotal += 100; // Sumar 100 puntos por cada respuesta correcta
        participante.intentosTotales += 1; // Sumar intento actual al total de intentos
    } else {
        cout << "Respuesta incorrecta." << endl;
        participante.intentosTotales += 1; // Sumar intento actual al total de intentos
    }
}

// Función para manejar el menú de selección de banda
string seleccionarBanda() {
    cout << "Elige una banda:" << endl;
    cout << "1. Guns N' Roses" << endl;
    cout << "2. Megadeth" << endl;
    cout << "3. Poison" << endl;
    cout << "4. Van Halen" << endl;
    cout << "5. Alice Cooper" << endl;

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
            return "Alice Cooper";
        default:
            cout << "Opción no válida. Seleccionando Guns N' Roses por defecto." << endl;
            return "Guns N' Roses";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Inicializa la semilla para números aleatorios

    cout << "¡Bienvenido al juego de adivinar la banda de la canción!" << endl;

    // Número de participantes
    int numParticipantes;
    cout << "Ingrese el número de participantes: ";
    cin >> numParticipantes;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Arreglo de participantes
    Participante participantes[numParticipantes];

    // Registro de participantes
    for (int i = 0; i < numParticipantes; ++i) {
        cout << "\nParticipante " << i + 1 << endl;
        cout << "Nombre completo: ";
        getline(cin, participantes[i].nombreCompleto);
        cout << "Carné: ";
        getline(cin, participantes[i].carne);

        participantes[i].banda = seleccionarBanda(); // Elige una banda para el participante

        registrarParticipante("registro_participantes.txt", participantes[i]); // Registra al participante
    }

    // Juego de adivinar la banda de la canción (Ronda única)
    cout << "\n--- Ronda única ---" << endl;

    for (int i = 0; i < numParticipantes; ++i) {
        string cancion = elegirCancion(participantes[i].banda); // Se elige una canción aleatoria de la banda seleccionada por el participante

        cout << "\nTurno de " << participantes[i].nombreCompleto << endl;
        jugarAdivinarBanda(participantes[i], cancion); // Cada participante intenta adivinar la banda de la canción
    }

    // Determinar y mostrar al ganador
    cout << "\n--- ¡Juego Terminado! ---" << endl;
    int indiceGanador = determinarGanador(participantes, numParticipantes); // Determina al ganador

    if (indiceGanador >= 0) {
        cout << "\nEl ganador es: " << participantes[indiceGanador].nombreCompleto << " de la banda " << participantes[indiceGanador].banda << " con " << participantes[indiceGanador].intentosTotales << " intentos y " << participantes[indiceGanador].puntajeTotal << " puntos." << endl;
        registrarGanador("registro_ganador.txt", participantes[indiceGanador]); // Registrar al ganador en un archivo
    } else if (indiceGanador == -1) {
        cout << "\n¡Empate! Continuemos jugando para desempatar." << endl;
    } else if (indiceGanador == -2) {
        cout << "\n¡No sean conformistas! Sigamos jugando para desempatar." << endl;
    }

    return 0;
}
