#include "iostream"
#include "string"
using namespace std;

// Función para mostrar el menú y permitir que el jugador elija una banda
int Banda() {
    cout << "Elige una banda:" << endl;
    cout << "1. Guns N' Roses" << endl;
    cout << "2. Megadeth" << endl;
    cout << "3. Poison" << endl;
    cout << "4. Van Halen" << endl;
    cout << "5. Salir del menu" << endl;
    int option;
    cin >> option;
    return option;
}

// Función para imprimir el progreso actual del jugador 
void printprogress(const string& songName, const string& progress) {
    cout << "Progreso: ";
    for (int i = 0; i < songName.length(); ++i) {
        if (progress[i] != '_') {
            cout << progress[i] << " "; // Imprimir el progreso
        } else {
            cout << "_ "; // Mostrar un guion bajo para las letras no reveladas
        }
    }
    cout << endl;
}

int main() {
    // Arreglos para las canciones de cada banda
    string gunsNRoses[] = {
        "Sweet Child O' Mine",
        "November Rain",
        "Welcome to the Jungle",
        "Paradise City",
        "Knockin' on Heaven's Door",
        "Don't Cry",
        "Patience",
        "Civil War",
        "You Could Be Mine",
        "Estranged"
    };

    string megadeth[] = {
        "Symphony of Destruction",
        "Hangar 18",
        "Holy Wars... The Punishment Due",
        "Peace Sells",
        "Tornado of Souls",
        "A Tout Le Monde",
        "Sweating Bullets",
        "Trust",
        "In My Darkest Hour",
        "Mechanix"
    };

    string poison[] = {
        "Every Rose Has Its Thorn",
        "Talk Dirty to Me",
        "Nothin' But a Good Time",
        "Fallen Angel",
        "Unskinny Bop",
        "Ride the Wind",
        "Something to Believe In",
        "I Won't Forget You",
        "Your Mama Don't Dance",
        "Life Goes On"
    };

    string vanHalen[] = {
        "Jump",
        "Panama",
        "Hot for Teacher",
        "Runnin' with the Devil",
        "Ain't Talkin' 'bout Love",
        "Why Can't This Be Love",
        "Right Now",
        "Dance the Night Away",
        "Eruption",
        "Dreams"
    };

    int option = Banda(); // El usuario podra elegir tan solo una banda

    switch (option) {
        case 1:
            cout << "¡Rockeando con Guns N' Roses!" << endl;
            // Imprimir las canciones de Guns N' Roses
            for (int i = 0; i < 10; ++i) {
                cout << gunsNRoses[i] << endl;
            }
            break;
        case 2:
            cout << "Megadeth en la casa!" << endl;
            // Listar las canciones de Megadeth
            for (int i = 0; i < 10; ++i) {
                cout << megadeth[i] << endl;
            }
            break;
        case 3:
            cout << "El espiritu de Poison esta presente." << endl;
            // Imprimir las canciones de Poison
            for (int i = 0; i < 10; ++i) {
                cout << poison[i] << endl;
            }
            break;
        case 4:
            cout << "¡Es hora de Van Halen!" << endl;
            // Listar las canciones de Van Halen
            for (int i = 0; i < 10; ++i) {
                cout << vanHalen[i] << endl;
            }
            break;
            case 5:
            cout << "Saliendo del menu..." << endl;
            break;
        default:
            cout << "Opcion no valida. Vamos con Guns N' Roses por defecto." << endl;
            option = 1; // Si la opcion inválida, seleccionara Guns N' Roses 
            // Imprimir las canciones de Guns N' Roses 
            for (int i = 0; i < 10; ++i) {
                cout << gunsNRoses[i] << endl;
            }
            break;
    }

    return 0;
}