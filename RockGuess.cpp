#include <iostream>
#include <fstream> // Para trabajar con archivos
#include <string>
#include <sstream> 

using namespace std;

// Función para mostrar el menú y que permitira que el jugador elija una banda
string banda() {
    cout << "Elige una banda:" << endl;
// Función para que el jugador elija la banda que desee
string Banda() {
    cout << "¡Bienvenido al juego de Bandas!" << endl;
    cout << "Elige tu banda favorita:" << endl;
    cout << "1. Guns N' Roses" << endl;
    cout << "2. Megadeth" << endl;
    cout << "3. Poison" << endl;
    cout << "4, Salir del menu" << endl;
    int option;
    cin >> option;
    cout << "4. Salir del menú" << endl;
    int opcion;
    cin >> opcion;

    switch (option) {
    // Devolver la banda elegida según la opción del jugador
    switch (opcion) {
        case 1:
            return "Guns N' Roses";
        case 2:
@@ -25,11 +29,63 @@ string banda() {
            return "Guns N' Roses";
    }
}

// Función para imprimir el progreso actual del jugador en la canción
void imprimirProgreso(const string& nombreCancion, const string& progreso) {
    cout << "Progreso en la canción \"" << nombreCancion << "\": ";
    // Mostrar el progreso con espacios entre cada letra o guión bajo
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
void registrarParticipante(const string& archivoRegistro, const string& nombreCompleto, const string& carne, const string& banda) {
    ofstream archivo;
    archivo.open(archivoRegistro, ios_base::app); // Abrir el archivo en modo append (agregar al final)

    // Verificar si el archivo se abrió correctamente
    if (archivo.is_open()) {
        archivo << nombreCompleto << "," << carne << "," << banda << "\n"; // Escribir en el archivo en el formato: nombreCompleto,carné,banda
        archivo.close(); // Cerrar el archivo después de escribir
        cout << "¡Registro exitoso de participante!" << endl; // Confirmar que el registro fue exitoso
    } else {
        cout << "¡Error al intentar abrir el archivo de registro!" << endl; // Mostrar mensaje de error si no se pudo abrir el archivo
    }
}

int main() {
    string band = banda();
    int main() {
    string nombreCancion = "Sweet Child O' Mine";
    string progreso(nombreCancion.length(), '_');

    // Aquí continuaremos con el código.
    // Mostrar el progreso inicial en la canción
    imprimirProgreso(nombreCancion, progreso);

    string bandaElegida = Banda();
    cout << "Has seleccionado la banda: " << bandaElegida << endl;

    // Registro de tres participantes
    for (int i = 0; i < 3; ++i) {
        string nombreCompleto;
        string carne;

        // Solicitar nombre completo y carné del participante
        cout << "Ingresa el nombre completo del participante " << i + 1 << ": ";
        cin.ignore(); // Limpiar el buffer de entrada antes de getline
        getline(cin, nombreCompleto);

        cout << "Ingresa el número de carné del participante " << i + 1 << ": ";
        cin >> carne;

        // Llamar a la función para registrar participante en el archivo
        registrarParticipante("registro_participantes.txt", nombreCompleto, carne, bandaElegida);

    }

    return 0;
}
}