#include <iostream>
#include <fstream>

using namespace std;

int main() {
	/* apertura de archivo de lectura */
	/* stream de archivo */
	fstream ar; 
	string linea;
	
	/* asociar stream con archivo de a01_holamundo.cpp */
	ar.open(".\\a01_holamundo.cpp", ios::in);
	
	if( ar.is_open() ){
		cout << "Archivo abierto\n";
		// mientras lea una línea desde el archivo
		while (getline(ar, linea)) 
			cout << "linea: " << linea << "\n";
	} else {
		cout << "Error al abrir el archivo\n";
		exit(1);			
	}
	ar.close();
	
    return 0;
}

