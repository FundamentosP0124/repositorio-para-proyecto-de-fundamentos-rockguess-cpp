#include "iostream"

using namespace std;

struct canciones {string titulo; string genero;};

// arreglo para guns n' roses
canciones roses[] = {{"cancion 1"},{"cancion 2"}};

// arreglo para megadeth
canciones megade[] = {{"cancion 1"},{"cancion 2"}};

// arreglo para poison
canciones poison[] = {{"cancion 1"},{"cancion 2"}};


// elegir una canción ramdom
canciones elegir_cancion_ale( const string& banda) {


  // seleccionar el arreglo de canciones
  canciones* cancion;
  int nummusica;

  if (banda == "guns n' roses") {
    cancion = roses;
    nummusica = sizeof(roses) / sizeof(canciones);
  } else if (banda == "megadeth") {
    cancion = megade;
    nummusica = sizeof(megade) / sizeof(canciones);
  } else if (banda == "poison") {
    cancion = poison;
    nummusica = sizeof(poison) / sizeof(canciones);
  } else {
    cout << "la opcion seleccionada no es valida: " << banda << endl;
    return canciones{"", ""};
  }

  // Genera el indice ramdom
  int indi_alea = rand() % nummusica;

  // se devuelve la cancion seleccionada
  return cancion[indi_alea];
}

int main (void) 
{
  string seleccionar_banda = "guns n' roses";

  canciones cancion_alea = elegir_cancion_ale(seleccionar_banda);

  cout << "cancion de " << seleccionar_banda << ":" << endl;
  cout << "titulo: " << cancion_alea.titulo << endl;
  cout << "genero: " << cancion_alea.genero << endl;

  return 0;
}
