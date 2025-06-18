#include "./../tda/tda_Auto.cpp"

void Auto::arrancar()            { motEnc = true; velAct = 0; }
void Auto::acelerar()            { velAct++; }
void Auto::frenar()              { velAct--; }
bool Auto::tieneGas()            { return cantGas > 1.0; }
void Auto::cargarGas(float cant) { cantGas += cant; }
void Auto::consumirGas()         { cantGas -= (cantGas*0.1); }
void Auto::subirCambio()         { cambAct++; }
void Auto::bajarCambio()         { cambAct--; }
void Auto::neutro()              { cambAct=0; }
int Auto::getVelAct()            { return velAct; }
int Auto::getId()            	 { return id; }
float Auto::getCantGas()         { return cantGas; }
bool Auto::pruebaFuncionamiento(){ 
	int num = rand() % 200;
	return (num%2 == 0); 
}